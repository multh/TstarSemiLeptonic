#include "UHH2/TstarSemiLeptonic/include/TstarReconstruction.h"
#include "UHH2/core/include/LorentzVector.h"
#include "UHH2/common/include/Utils.h"
#include "UHH2/core/include/Utils.h"

#include <UHH2/common/include/CleaningModules.h>
#include <UHH2/common/include/JetCorrections.h>
#include <UHH2/TstarSemiLeptonic/include/NeutrinoFit.h>

#include <cassert>
#include <iterator>
#include <iostream>

using namespace uhh2;
using namespace std;

//**********************************************************************************
// Module for Mass Reconstruction of T* in SemiLeptonic Channel
//
//**********************************************************************************




HighMassTstarReconstruction::HighMassTstarReconstruction(Context & ctx, const NeutrinoReconstructionMethod & neutrinofunction, const string & label): m_neutrinofunction(neutrinofunction) {
  h_recohyps = ctx.declare_event_output<vector<TstarReconstructionHypothesis>>(label);
  h_primlep = ctx.get_handle<FlavorParticle>("PrimaryLepton");
  hypothesis = ctx.declare_event_output<vector<TstarReconstructionHypothesis>>(label);
}

HighMassTstarReconstruction::~HighMassTstarReconstruction() {}


bool HighMassTstarReconstruction::process(uhh2::Event & event) {
    assert(event.jets);
    assert(event.met);

    //find primary charged lepton
    const Particle & lepton = event.get(h_primlep);
    std::vector<TstarReconstructionHypothesis> recoHyps;
    //reconstruct neutrino
    std::vector<LorentzVector> neutrinos = m_neutrinofunction( lepton.v4(), event.met->v4());

    unsigned int n_jets = event.jets->size();
    if(n_jets>7) n_jets = 7;                    //Limit Number of Jets for Computation Time 
    //if(n_jets>8) n_jets = 8; 
    const unsigned int max_j = pow(5, n_jets);  
 
    // idea: loop over 5^Njet possibilities and write the current loop
    // index j in the 5-base system. The Njets digits represent whether
    // to assign each jet to the hadronic top (0), leptonic top (1),
    // to leptonic gluon (2), hadronic gluon (3)
    // or none of them (4).

    //loop over neutrino solutions and jet assignments to fill hyotheses
    for(const auto & neutrino_p4 : neutrinos) {
        const LorentzVector wlep_v4 = lepton.v4() + neutrino_p4;

        for (unsigned int j=0; j < max_j; j++) {
            LorentzVector tophad_v4;
            LorentzVector toplep_v4 = wlep_v4;

            LorentzVector gluonhad_v4;
            LorentzVector gluonlep_v4;
	    int hadjets=0;
            int lepjets=0;
	    int gluonlepjets=0;
	    int gluonhadjets=0;
            int num = j;
            TstarReconstructionHypothesis hyp;
            hyp.set_lepton(lepton);
            hyp.set_neutrino_v4(neutrino_p4);


           for (unsigned int k=0; k<n_jets; k++) {

	      if(num%5==0) {
                    tophad_v4 = tophad_v4 + event.jets->at(k).v4();
                    hyp.add_tophad_jet(event.jets->at(k));
		    hadjets++;
                }

                if(num%5==1) {
                    toplep_v4 = toplep_v4 + event.jets->at(k).v4();
                    hyp.add_toplep_jet(event.jets->at(k));
		    lepjets++;
                }
	    
		if(num%5==2) {
		  gluonlep_v4 = gluonlep_v4 + event.jets->at(k).v4();
		  hyp.add_gluonlep_jet(event.jets->at(k));
		    gluonlepjets++;
                }
		
		if(num%5==3) {
		  gluonhad_v4 = gluonhad_v4 + event.jets->at(k).v4();
		  hyp.add_gluonhad_jet(event.jets->at(k));
		    gluonhadjets++;
                }

                //in case num%5==4 do not take this jet at all
                //shift the trigits of num to the right:

                num /= 5;
	       }

	    //search jet with highest pt assigned to leptonic top
            int blep_idx(-1);
            float maxptlep(-1.);
            for(unsigned int i=0; i<hyp.toplep_jets().size(); ++i){
              if(maxptlep< hyp.toplep_jets().at(i).pt()){
                maxptlep = hyp.toplep_jets().at(i).pt();
                blep_idx = i;
              }
	    }
            if(blep_idx != -1){ 
	      hyp.set_blep_v4(hyp.toplep_jets().at(blep_idx).v4());  //Handle Jet with highest pt as leptonic b-Jet
	      hyp.add_blep_jet(hyp.toplep_jets().at(blep_idx));
	    }

	    //search jet with highest pt assigned to hadronic top
            int bhad_idx(-1);
            float maxpthad(-1.);
            for(unsigned int i=0; i<hyp.tophad_jets().size(); ++i){
              if(maxpthad< hyp.tophad_jets().at(i).pt()){
                maxpthad = hyp.tophad_jets().at(i).pt();
                bhad_idx = i;
              }
	    }
            if(bhad_idx != -1){
	      hyp.set_bhad_v4(hyp.tophad_jets().at(bhad_idx).v4());  //Handle Jet with highest pt as hadronic b-Jets
	      hyp.add_bhad_jet(hyp.tophad_jets().at(bhad_idx));
	    }
	    
            //fill only hypotheses with at least one jet assigned to each top quark and gluon 
	    if( hadjets>0 && lepjets>0 && gluonhadjets>0 && gluonlepjets>0) { 
	        hyp.set_tophad_v4(tophad_v4);
                hyp.set_toplep_v4(toplep_v4);
                hyp.set_gluonhad_v4(gluonhad_v4);
		hyp.set_gluonlep_v4(gluonlep_v4);

		recoHyps.emplace_back(move(hyp));
            }
        } 
// 5^n_jets jet combinations
} // neutrinos 
  event.set(h_recohyps, std::move(recoHyps));
  return true;
}




//***************************** Mass Reconstruction with Top-Tag *******************************************
 
TstarTopTagReconstruction::TstarTopTagReconstruction(Context & ctx, const NeutrinoReconstructionMethod & neutrinofunction, const string & label, TopJetId tjetid, float minDR_tj_j):
  m_neutrinofunction(neutrinofunction), topjetID_(tjetid), minDR_topjet_jet_(minDR_tj_j) {
  h_recohyps = ctx.declare_event_output<vector<TstarReconstructionHypothesis>>(label);
  h_primlep = ctx.get_handle<FlavorParticle>("PrimaryLepton");
}

bool TstarTopTagReconstruction::process(uhh2::Event & event) {
 
  assert(event.jets && event.topjets);
  assert(event.met);

  std::vector<TstarReconstructionHypothesis> recoHyps;

  const Particle& lepton = event.get(h_primlep);
  std::vector<LorentzVector> neutrinos = m_neutrinofunction(lepton.v4(), event.met->v4());   //Neutrion Solutions

  for(const auto& tj : *event.topjets){
    if(!topjetID_(tj, event)) continue;

    // jet candidates for leptonic-top (not overlapping with top-tagged jet)
    std::vector<const Jet*> tlep_jets;
    tlep_jets.reserve(event.jets->size());
   
    //Make sure Jets not overlap with Top-Jets  
    for(const auto & jet : *event.jets)
    if(deltaR(tj, jet) > minDR_topjet_jet_) tlep_jets.push_back(&jet);
    
    unsigned int n_jets = tlep_jets.size();

    if(n_jets<3) return false;
    if(n_jets>7) n_jets=7;

  // idea: loop over ^Njet possibilities and write the current loop
 
    const unsigned int jet_combs = pow(4, n_jets);

    for(const auto& neutrino_p4 : neutrinos){
      for(unsigned int i=1; i<jet_combs; ++i){

        TstarReconstructionHypothesis hyp;
        hyp.set_lepton(lepton);
        hyp.set_neutrino_v4(neutrino_p4);

	LorentzVector gluonhad_v4;
        LorentzVector gluonlep_v4;
        int gluonlepjets=0;
	int gluonhadjets=0;
        int lepjets=0;

	////Fill TopHad Hypothese
        LorentzVector tophad_v4(tj.v4());
        hyp.add_tophad_jet(tj);
        hyp.set_tophad_topjet_ptr(&tj);

	//Combine Lepton and Neutrino LorentzVector
        LorentzVector toplep_v4(lepton.v4() + neutrino_p4);
	int num = i;
  
 // index j in the 4-base system. The Njets digits represent whether
    // to assign each jet to the leptonic top (0),
    // to leptonic gluon (1), hadronic gluon (2)
    // or none of them (3).

	////Fill TopLep and Gluon Hypothese
        for(unsigned int j=0; j<n_jets; ++j){

          if(num%4==0){
            toplep_v4 += tlep_jets.at(j)->v4();
            hyp.add_toplep_jet(*tlep_jets.at(j));
	    lepjets++;
	  }
	    
	  if(num%4==1){
            gluonlep_v4 += tlep_jets.at(j)->v4();
	    hyp.add_gluonlep_jet(*tlep_jets.at(j));
	    gluonlepjets++;
	  }

	  if(num%4==2){
            gluonhad_v4 += tlep_jets.at(j)->v4();
	    hyp.add_gluonhad_jet(*tlep_jets.at(j));
            gluonhadjets++;
	  }
          num/=4;
        }

	int blep_idx(-1);
            float maxptlep(-1.);
            for(unsigned int i=0; i<hyp.toplep_jets().size(); ++i){
              if(maxptlep< hyp.toplep_jets().at(i).pt()){
                maxptlep = hyp.toplep_jets().at(i).pt();
                blep_idx = i;
              }
            }
            if(blep_idx != -1){ 
	      hyp.set_blep_v4(hyp.toplep_jets().at(blep_idx).v4()); //Handle Jet with highest pt as leptonic b-Jets
	      hyp.add_blep_jet(hyp.toplep_jets().at(blep_idx));
	    }

	    //search jet with highest pt assigned to hadronic top
            int bhad_idx(-1);
            float maxpthad(-1.);
            for(unsigned int i=0; i<hyp.tophad_jets().size(); ++i){
              if(maxpthad< hyp.tophad_jets().at(i).pt()){
                maxpthad = hyp.tophad_jets().at(i).pt();
                bhad_idx = i;
              }
            }
            if(bhad_idx != -1){
	      hyp.set_bhad_v4(hyp.tophad_jets().at(bhad_idx).v4());
	      hyp.add_bhad_jet(hyp.tophad_jets().at(bhad_idx));     //Handle Jet with highest pt as hadronic b-Jets
	    }

       ////Fill Hypothese
        if(lepjets>0 && gluonhadjets>0 && gluonlepjets>0) {
	  hyp.set_tophad_v4(tophad_v4);
          hyp.set_toplep_v4(toplep_v4);
	  hyp.set_gluonhad_v4(gluonhad_v4);
	  hyp.set_gluonlep_v4(gluonlep_v4);
          recoHyps.emplace_back(std::move(hyp));
        }
      }
    }
  }

  event.set(h_recohyps, std::move(recoHyps));
  return true;
}




//********************************************************************************************************************************************************************************************

HighMassTstarKinReconstruction::HighMassTstarKinReconstruction(Context & ctx, const NeutrinoReconstructionMethod & neutrinofunction, const string & label): m_neutrinofunction(neutrinofunction) {
  h_recohyps = ctx.declare_event_output<vector<TstarReconstructionHypothesis>>(label);
  h_primlep = ctx.get_handle<FlavorParticle>("PrimaryLepton");
  hypothesis = ctx.declare_event_output<vector<TstarReconstructionHypothesis>>(label);
  FitNeutrino = NeutrinoFit();
}

HighMassTstarKinReconstruction::~HighMassTstarKinReconstruction() {}


bool HighMassTstarKinReconstruction::process(uhh2::Event & event) {
    assert(event.jets);
    assert(event.met);

    //find primary charged lepton
    const Particle & lepton = event.get(h_primlep);
    std::vector<TstarReconstructionHypothesis> recoHyps;

    //reconstruct neutrino
    std::vector<LorentzVector> neutrinos = FitNeutrino.NeutrinoFitPolar(lepton.v4(), event.met->v4());
    // std::vector<LorentzVector> neutrinos = m_neutrinofunction( lepton.v4(), event.met->v4());

    sort_by_pt<Jet>(*event.jets);
   
    unsigned int n_jets = event.jets->size();
    if(n_jets>8) n_jets = 8;                    //Limit Number of Jets for Computation Time 
  

    const unsigned int max_j = pow(3, n_jets);  
    //  cout<<"Maximum of top hyp iterations: "<< max_j << endl;
 
    // idea: loop over 5^Njet possibilities and write the current loop
    // index j in the 5-base system. The Njets digits represent whether
    // to assign each jet to the hadronic top (0), leptonic top (1),
    // to leptonic gluon (2), hadronic gluon (3)
    // or none of them (4).

    //loop over neutrino solutions and jet assignments to fill hyotheses
    for(const auto & neutrino_p4 : neutrinos) {
        const LorentzVector wlep_v4 = lepton.v4() + neutrino_p4;

	  
	  for (unsigned int j=0; j < max_j; j++) {
	    LorentzVector gluonlep_v4;
	    LorentzVector toplep_v4 = wlep_v4;
	    
	    vector<Jet> toplep_jet;
	    vector<Jet> gluonlep_jet;
	    vector<Jet> unused_jets;
	    
            int lepjets=0;
	    int gluonlep_jets=0;
	    int hadjets;
	    int gluonhad_jets;

	    int num = j;
	    
	    for (unsigned int i=0; i<n_jets; i++){

	      if(num%3==0){
		toplep_v4 = toplep_v4 + event.jets->at(i).v4();
		toplep_jet.push_back(event.jets->at(i));
		lepjets++;
	      }

	      if(num%3==1){
		gluonlep_v4 = gluonlep_v4 + event.jets->at(i).v4();
		gluonlep_jet.push_back(event.jets->at(i));
		gluonlep_jets++;
	      }
	      
	      if(num%3==2){
		unused_jets.push_back(event.jets->at(i));
	      }
	      
	      num/=3;
	    }
	   
	    int blep_idx(-1);
            float maxptlep(-1.);
            
	    for(unsigned int i=0; i<toplep_jet.size(); ++i){
              if(maxptlep< toplep_jet.at(i).pt()){
                maxptlep = toplep_jet.at(i).pt();
                blep_idx = i;
              }
	    }

	    bool leptonic_kin(false);
	    
	    if(blep_idx != -1){ 
	      if((((gluonlep_v4.pt()-toplep_jet.at(blep_idx).pt())/(toplep_jet.at(blep_idx).pt()+gluonlep_v4.pt()))>0) && unused_jets.size()>0 && gluonlep_jets>0 && toplep_jet.size()>0){		
		leptonic_kin = true;
	      }
	    }
	    
	    if(!leptonic_kin) continue;
	    if(toplep_v4.M()>350) continue;
	    if(deltaR(toplep_v4, gluonlep_v4)>2.8) continue;


	    unsigned int max_i = pow(3, unused_jets.size());

	    for(unsigned int i=0; i<max_i; i++){

	      int num_i = i;
	      
	      hadjets=0;
	      gluonhad_jets=0;

	      TstarReconstructionHypothesis hyp;
	      hyp.set_lepton(lepton);
	      hyp.set_neutrino_v4(neutrino_p4);
	      
	      hyp.set_toplep_v4(toplep_v4);
	      hyp.set_gluonlep_v4(gluonlep_v4);

	      for(unsigned int i_jets = 0; i_jets < toplep_jet.size(); i_jets++){
		hyp.add_toplep_jet(toplep_jet.at(i_jets));
	      }	      

	      for(unsigned int i_gluon = 0; i_gluon < gluonlep_jet.size(); i_gluon++){
		hyp.add_gluonlep_jet(gluonlep_jet.at(i_gluon));
	      }	 

	      if(blep_idx != -1){
		hyp.set_blep_v4(toplep_jet.at(blep_idx).v4());
	      }
	 	    
	      LorentzVector tophad_v4;
	      LorentzVector gluonhad_v4;

	      
	      for (unsigned int k=0; k<unused_jets.size(); k++) {
	
		if(num_i%3==0) {
		  tophad_v4 = tophad_v4 + unused_jets.at(k).v4();
		  hyp.add_tophad_jet(unused_jets.at(k));
		  hadjets++;
		}
		
		if(num_i%3==1) {
		  gluonhad_v4 = gluonhad_v4 + unused_jets.at(k).v4();
		  hyp.add_gluonhad_jet(unused_jets.at(k));
		  gluonhad_jets++;
		}
		
		//in case num%3==2 do not take this jet at all
		//shift the trigits of num to the right:
		num_i /= 3;
	      }
	      
	  

	      //search jet with highest pt assigned to hadronic top
	      int bhad_idx(-1);
	      float maxpthad(-1.);
	      for(unsigned int i=0; i<hyp.tophad_jets().size(); ++i){
		if(maxpthad< hyp.tophad_jets().at(i).pt()){
		  maxpthad = hyp.tophad_jets().at(i).pt();
		  bhad_idx = i;
		}
	      }

	      if(bhad_idx != -1){
		hyp.set_bhad_v4(hyp.tophad_jets().at(bhad_idx).v4());  //Handle Jet with highest pt as hadronic b-Jets
		hyp.add_bhad_jet(hyp.tophad_jets().at(bhad_idx));
	      }
	      if(tophad_v4.M()>350) continue;


	      bool hadronic_kin(false);
	      
	      if(bhad_idx != -1){ 
		if(((gluonhad_v4.pt()-hyp.tophad_jets().at(bhad_idx).pt())/(hyp.tophad_jets().at(bhad_idx).pt()+gluonhad_v4.pt()))>0){		
		  hadronic_kin = true;
		}
	      }
	      
	      if(!hadronic_kin) continue;
	      

	      if( hadjets>0 && gluonhad_jets>0) { 
		hyp.set_tophad_v4(tophad_v4);
		hyp.set_gluonhad_v4(gluonhad_v4);
		recoHyps.emplace_back(move(hyp));
	      }
	      
	    }	  
	  } // 3^n_jets jet combinations
    } // neutrinos 
    event.set(h_recohyps, std::move(recoHyps));
    //cout<<"Save Hypothesis!"<<endl<<endl;
    return true;
}

//********************************************************************************************************************************************************************************************


TstarTopTagKinReconstruction::TstarTopTagKinReconstruction(Context & ctx, const NeutrinoReconstructionMethod & neutrinofunction, const string & label, TopJetId tjetid, float minDR_tj_j):
  m_neutrinofunction(neutrinofunction), topjetID_(tjetid), minDR_topjet_jet_(minDR_tj_j) {
  h_recohyps = ctx.declare_event_output<vector<TstarReconstructionHypothesis>>(label);
  h_primlep = ctx.get_handle<FlavorParticle>("PrimaryLepton");
  FitNeutrino = NeutrinoFit();
}

bool TstarTopTagKinReconstruction::process(uhh2::Event & event) {
 
  assert(event.jets && event.topjets);
  assert(event.met);

  std::vector<TstarReconstructionHypothesis> recoHyps;

  const Particle& lepton = event.get(h_primlep);

  //reconstruct neutrino
  std::vector<LorentzVector> neutrinos = FitNeutrino.NeutrinoFitPolar(lepton.v4(), event.met->v4());
  // std::vector<LorentzVector> neutrinos = m_neutrinofunction(lepton.v4(), event.met->v4());  


  for(const auto& tj : *event.topjets){
    if(!topjetID_(tj, event)) continue;
    
    // jet candidates for leptonic-top (not overlapping with top-tagged jet)
    std::vector<const Jet*> tlep_jets;
    tlep_jets.reserve(event.jets->size());
    
    //Make sure Jets not overlap with Top-Jets  
    for(const auto & jet : *event.jets)
      if(deltaR(tj, jet) > minDR_topjet_jet_) tlep_jets.push_back(&jet);
    
    unsigned int n_jets = tlep_jets.size();
    
    if(n_jets<3) return false;
    if(n_jets>7) n_jets=7;
    
  // idea: loop over ^Njet possibilities and write the current loop
 
    const unsigned int jet_combs = pow(4, n_jets);

    for(const auto& neutrino_p4 : neutrinos){
      for(unsigned int i=1; i<jet_combs; ++i){
	
        TstarReconstructionHypothesis hyp;
        hyp.set_lepton(lepton);
        hyp.set_neutrino_v4(neutrino_p4);
	
	LorentzVector gluonhad_v4;
        LorentzVector gluonlep_v4;
        int gluonlepjets=0;
	int gluonhadjets=0;
        int lepjets=0;
	
	////Fill TopHad Hypothese
        LorentzVector tophad_v4(tj.v4());
        hyp.add_tophad_jet(tj);
        hyp.set_tophad_topjet_ptr(&tj);
	
	//Combine Lepton and Neutrino LorentzVector
        LorentzVector toplep_v4(lepton.v4() + neutrino_p4);
	int num = i;
	
	// index j in the 4-base system. The Njets digits represent whether
	// to assign each jet to the leptonic top (0),
	// to leptonic gluon (1), hadronic gluon (2)
	// or none of them (3).
	
	////Fill TopLep and Gluon Hypothese
        for(unsigned int j=0; j<n_jets; ++j){
	  
          if(num%4==0){
            toplep_v4 += tlep_jets.at(j)->v4();
            hyp.add_toplep_jet(*tlep_jets.at(j));
	    lepjets++;
	  }
	  
	  if(num%4==1){
            gluonlep_v4 += tlep_jets.at(j)->v4();
	    hyp.add_gluonlep_jet(*tlep_jets.at(j));
	    gluonlepjets++;
	  }
	  
	  if(num%4==2){
            gluonhad_v4 += tlep_jets.at(j)->v4();
	    hyp.add_gluonhad_jet(*tlep_jets.at(j));
            gluonhadjets++;
	  }
          num/=4;
        }
	

	int blep_idx(-1);
	float maxptlep(-1.);
	for(unsigned int i=0; i<hyp.toplep_jets().size(); ++i){
	  if(maxptlep< hyp.toplep_jets().at(i).pt()){
	    maxptlep = hyp.toplep_jets().at(i).pt();
	    blep_idx = i;
	  }
	}

	bool leptonic_kin(false);
	
	if(blep_idx != -1){ 
	  hyp.set_blep_v4(hyp.toplep_jets().at(blep_idx).v4()); //Handle Jet with highest pt as leptonic b-Jets
	  hyp.add_blep_jet(hyp.toplep_jets().at(blep_idx));
	  if(hyp.toplep_jets().at(blep_idx).pt()<gluonlep_v4.pt()){
	    leptonic_kin = true;
	  }
	}
	
	if(!leptonic_kin) continue;

	
	//search jet with highest pt assigned to hadronic top
	int bhad_idx(-1);
	float maxpthad(-1.);
	for(unsigned int i=0; i<hyp.tophad_jets().size(); ++i){
	  if(maxpthad< hyp.tophad_jets().at(i).pt()){
	    maxpthad = hyp.tophad_jets().at(i).pt();
	    bhad_idx = i;
	  }
	}

	if(bhad_idx != -1){
	  hyp.set_bhad_v4(hyp.tophad_jets().at(bhad_idx).v4());
	  hyp.add_bhad_jet(hyp.tophad_jets().at(bhad_idx));     //Handle Jet with highest pt as hadronic b-Jets
	}

	////Fill Hypothese
	if(lepjets>0 && gluonhadjets>0 && gluonlepjets>0) {
	  hyp.set_tophad_v4(tophad_v4);
	  hyp.set_toplep_v4(toplep_v4);
	  hyp.set_gluonhad_v4(gluonhad_v4);
	  hyp.set_gluonlep_v4(gluonlep_v4);
	  recoHyps.emplace_back(std::move(hyp));
	}
      }
    }
  }

  event.set(h_recohyps, std::move(recoHyps));
  return true;
}










//**************************** Neutrino Reconstruction ************************************************************


std::vector<LorentzVector> TstarNeutrinoReconstruction(const LorentzVector & lepton, const LorentzVector & met) {
    TVector3 lepton_pT = toVector(lepton);
    lepton_pT.SetZ(0);
    TVector3 neutrino_pT = toVector(met);
    neutrino_pT.SetZ(0);
    constexpr float mass_w = 80.399f;
    float mu = mass_w * mass_w / 2 + lepton_pT * neutrino_pT;
    float A = - (lepton_pT * lepton_pT);
    float B = mu * lepton.pz();
    float C = mu * mu - lepton.e() * lepton.e() * (neutrino_pT * neutrino_pT);
    float discriminant = B * B - A * C;
    std::vector<LorentzVector> solutions;
    if (0 >= discriminant) {
        // Take only real part of the solution for pz:
        LorentzVectorXYZE solution (met.Px(),met.Py(),-B / A,0);
        solution.SetE(solution.P());
        solutions.emplace_back(toPtEtaPhi(solution));
    }
    else {
        discriminant = sqrt(discriminant);
        LorentzVectorXYZE solution (met.Px(),met.Py(),(-B - discriminant) / A,0);
        solution.SetE(solution.P());
        solutions.emplace_back(toPtEtaPhi(solution));

        LorentzVectorXYZE solution2 (met.Px(),met.Py(),(-B + discriminant) / A,0);
        solution2.SetE(solution2.P());
        solutions.emplace_back(toPtEtaPhi(solution2));
    }
    return solutions;
}

