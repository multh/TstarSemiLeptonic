#include "UHH2/TstarSemiLeptonic/include/TstarReconstruction.h"
#include "UHH2/core/include/LorentzVector.h"
#include "UHH2/common/include/Utils.h"
#include "UHH2/core/include/Utils.h"
#include "UHH2/core/include/Event.h"

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
//********************************************************************************************************************************************************************************************
HighMassGluonReconstruction::HighMassGluonReconstruction(Context & ctx, const string & label){
  h_recohyps = ctx.declare_event_output<vector<TstarReconstructionHypothesis>>(label);
  hypothesis = ctx.declare_event_output<vector<TstarReconstructionHypothesis>>(label);
  h_topHyps  = ctx.get_handle<std::vector<TstarReconstructionHypothesis>>("TstarReconstruction");
  h_tstargen = ctx.get_handle<TStarGen>("tstargen");
}
bool HighMassGluonReconstruction::process(uhh2::Event & event) {
  std::vector<TstarReconstructionHypothesis> hyps = event.get(h_topHyps);
  const TstarReconstructionHypothesis* hyp_top = get_best_top_hypothesis( hyps, "Chi2");
  
  if(!hyp_top) return false;
  
  std::vector<TstarReconstructionHypothesis> recoHyps;

  const auto & tstargen = event.get(h_tstargen);
  auto dec = tstargen.DecayChannel();
  if(dec == TStarGen::e_muhad){
    const Particle & gluon_had = tstargen.GluonHad();
    const Particle & gluon_lep = tstargen.GluonLep();

    vector<Jet> gluon_jet = hyp_top->gluon_jets();   

    LorentzVector toplep_v4 = hyp_top->toplep_v4();
    LorentzVector tophad_v4 = hyp_top->tophad_v4();

    LorentzVector blep_v4 = hyp_top->blep_v4();
    LorentzVector bhad_v4 = hyp_top->bhad_v4();
    
    Particle lepton = hyp_top->lepton();
  
    LorentzVector gluonlep_v4;
    LorentzVector gluonhad_v4;
    
    float mindr_had = 100;
    int index_had = -1;
    int num_had = 0;
    
    float mindr_lep = 100;
    int index_lep = -1;
    int num_lep = 0;

    TstarReconstructionHypothesis hyp;

    for(unsigned int i_jets = 0; i_jets < hyp_top->toplep_jets().size(); i_jets++){
      hyp.add_toplep_jet(hyp_top->toplep_jets().at(i_jets));
    }	      
    
    for(unsigned int i_jets = 0; i_jets < hyp_top->tophad_jets().size(); i_jets++){
      hyp.add_tophad_jet(hyp_top->tophad_jets().at(i_jets));
    }


    for(unsigned int i=0; i<gluon_jet.size(); i++){
          
      float dR_had = deltaR(gluon_had, gluon_jet.at(i));
      if(dR_had <0.4) {
	num_had++;
      }
  
      if(dR_had<mindr_had) {//  dR <0.2
	mindr_had=dR_had;
	index_had=i;
      }
    
      float dR_lep = deltaR(gluon_lep, gluon_jet.at(i));
      if(dR_lep <0.4) {
	num_lep++;
      }
 
      if(dR_lep<mindr_lep) {//  dR <0.2
	mindr_lep=dR_lep;
	index_lep=i;
      }
      
    }
  
     if(index_lep != -1 && index_had != -1 && index_lep != index_had){
      gluonhad_v4 = gluon_jet.at(index_had).v4();
      hyp.set_gluonhad_v4(gluonhad_v4);
      gluonlep_v4 = gluon_jet.at(index_lep).v4();
      hyp.set_Gluon_Had_num(num_had);
      hyp.set_Gluon_Lep_num(num_lep);
      hyp.set_gluonlep_v4(gluonlep_v4);
      hyp.set_tophad_v4(tophad_v4);
      hyp.set_toplep_v4(toplep_v4);

      hyp.set_blep_v4(blep_v4);
      hyp.set_bhad_v4(bhad_v4);

      hyp.set_lepton(lepton);
      
      if(deltaR(gluonhad_v4, tophad_v4)>0.4 && deltaR(gluonlep_v4, toplep_v4)>0.4 && deltaR(gluonlep_v4, gluonhad_v4)>0.4 && deltaR(toplep_v4, tophad_v4)>0.4 && deltaR(toplep_v4, gluonhad_v4)>0.4 && deltaR(tophad_v4, gluonlep_v4)>0.4){
	recoHyps.emplace_back(move(hyp));
      }
    }
  }  
  
  event.set(h_recohyps, std::move(recoHyps));
  //cout<<"Save Hypothesis!"<<endl<<endl;
  return true;
  }
/*
  vector<Jet> gluon_jet = hyp_top->gluon_jets();

  LorentzVector toplep_v4 = hyp_top->toplep_v4();
  LorentzVector tophad_v4 = hyp_top->tophad_v4();



  LorentzVector blep_v4 = hyp_top->blep_v4();
  LorentzVector bhad_v4 = hyp_top->bhad_v4();
  
  Particle lepton = hyp_top->lepton();
  
  LorentzVector gluonlep_v4;
  LorentzVector gluonhad_v4;
  
  vector<Jet> gluon_hadjets;
  vector<Jet> gluon_lepjets;

  unsigned int n_gluon_jets = gluon_jet.size();
  const unsigned int max_j = pow(3, n_gluon_jets);  

  for(unsigned int j = 0; j<max_j; j++){
    
    int gluonlep_jets = 0;
    int gluonhad_jets = 0;

    TstarReconstructionHypothesis hyp;
    
    int num = j;
    
    for(unsigned int i_jets = 0; i_jets < hyp_top->toplep_jets().size(); i_jets++){
      hyp.add_toplep_jet(hyp_top->toplep_jets().at(i_jets));
    }	      
    
    for(unsigned int i_jets = 0; i_jets < hyp_top->tophad_jets().size(); i_jets++){
      hyp.add_tophad_jet(hyp_top->tophad_jets().at(i_jets));
    }

    for (unsigned int i=0; i<n_gluon_jets; i++){
      if(num%3==0){
	gluonlep_v4 = gluonlep_v4 + gluon_jet.at(i).v4();
	gluon_lepjets.push_back(gluon_jet.at(i));
	hyp.add_gluonlep_jet(gluon_jet.at(i));
	gluonlep_jets++;
      }
      
      if(num%3==1){
	gluonhad_v4 = gluonhad_v4 + gluon_jet.at(i).v4();
	gluon_hadjets.push_back(gluon_jet.at(i));
	hyp.add_gluonhad_jet(gluon_jet.at(i));
	gluonhad_jets++;
      }
      
      //if(num%==2) dont use this jet in current hyp
  
      num/=3;
    }

    if(gluonlep_jets==1 && gluonhad_jets==1){
      hyp.set_gluonhad_v4(gluonhad_v4);
      hyp.set_gluonlep_v4(gluonlep_v4);

      hyp.set_tophad_v4(tophad_v4);
      hyp.set_toplep_v4(toplep_v4);

      hyp.set_blep_v4(blep_v4);
      hyp.set_bhad_v4(bhad_v4);

      hyp.set_lepton(lepton);
      
      if(deltaR(gluonhad_v4, tophad_v4)>0.4 && deltaR(gluonlep_v4, toplep_v4)>0.4 && deltaR(gluonlep_v4, gluonhad_v4)>2 && deltaR(toplep_v4, tophad_v4)>0.4 && deltaR(toplep_v4, gluonhad_v4)>0.4 && deltaR(tophad_v4, gluonlep_v4)>0.4){
	recoHyps.emplace_back(move(hyp));
      }
    }
  }
  event.set(h_recohyps, std::move(recoHyps));
  //cout<<"Save Hypothesis!"<<endl<<endl;
  return true;
}

*/

  /////////Option for Gluon Gen studies
  /*  
  const auto & tstargen = event.get(h_tstargen);
  auto dec = tstargen.DecayChannel();
  if(dec == TStarGen::e_muhad){
    const Particle & gluon_had = tstargen.GluonHad();
    const Particle & gluon_lep = tstargen.GluonLep();
    
    LorentzVector toplep_v4 = hyp_top->toplep_v4();
    LorentzVector tophad_v4 = hyp_top->tophad_v4();

    LorentzVector blep_v4 = hyp_top->blep_v4();
    LorentzVector bhad_v4 = hyp_top->bhad_v4();
    
    Particle lepton = hyp_top->lepton();
  
    LorentzVector gluonlep_v4;
    LorentzVector gluonhad_v4;
    
    float mindr_had = 100;
    int index_had = -1;
    int num_had = 0;
    
    float mindr_lep = 100;
    int index_lep = -1;
    int num_lep = 0;

    TstarReconstructionHypothesis hyp;

    for(unsigned int i=0; i<gluon_jet.size(); i++){
          
      float dR_had = deltaR(gluon_had, gluon_jet.at(i));
      if(dR_had <0.4) {
	num_had++;
      }
  
      if(dR_had<mindr_had) {//  dR <0.2
	mindr_had=dR_had;
	index_had=i;
      }
    
      float dR_lep = deltaR(gluon_lep, gluon_jet.at(i));
      if(dR_lep <0.4) {
	num_lep++;
      }
 
      if(dR_lep<mindr_lep) {//  dR <0.2
	mindr_lep=dR_lep;
	index_lep=i;
      }
      
    }
  
     if(index_lep != -1 && index_had != -1){
      gluonhad_v4 = gluon_jet.at(index_had).v4();
      hyp.set_gluonhad_v4(gluonhad_v4);
      gluonlep_v4 = gluon_jet.at(index_lep).v4();
      hyp.set_Gluon_Had_num(num_had);
      hyp.set_Gluon_Lep_num(num_lep);
      hyp.set_gluonlep_v4(gluonlep_v4);
      hyp.set_tophad_v4(tophad_v4);
      hyp.set_toplep_v4(toplep_v4);

      hyp.set_blep_v4(blep_v4);
      hyp.set_bhad_v4(bhad_v4);

      hyp.set_lepton(lepton);
      
      if(deltaR(gluonhad_v4, tophad_v4)>0.4 && deltaR(gluonlep_v4, toplep_v4)>0.4 && deltaR(gluonlep_v4, gluonhad_v4)>0.4 && deltaR(toplep_v4, tophad_v4)>0.4 && deltaR(toplep_v4, gluonhad_v4)>0.4 && deltaR(tophad_v4, gluonlep_v4)>0.4){
	recoHyps.emplace_back(move(hyp));
      }
    }
  }  
  
  event.set(h_recohyps, std::move(recoHyps));
  //cout<<"Save Hypothesis!"<<endl<<endl;
  return true;
  }*/


HighMassTopReconstruction::HighMassTopReconstruction(Context & ctx, const NeutrinoReconstructionMethod & neutrinofunction, const string & label): m_neutrinofunction(neutrinofunction) {
  h_recohyps = ctx.declare_event_output<vector<TstarReconstructionHypothesis>>(label);
  h_primlep = ctx.get_handle<FlavorParticle>("PrimaryLepton");
  hypothesis = ctx.declare_event_output<vector<TstarReconstructionHypothesis>>(label);
  h_tstargen = ctx.get_handle<TStarGen>("tstargen");  //
  FitNeutrino = NeutrinoFit();
}

HighMassTopReconstruction::~HighMassTopReconstruction() {}


bool HighMassTopReconstruction::process(uhh2::Event & event) {
    assert(event.jets);
    assert(event.met);

    //find primary charged lepton
    const Particle & lepton = event.get(h_primlep);
    std::vector<TstarReconstructionHypothesis> recoHyps;

    //reconstruct neutrino
    std::vector<LorentzVector> neutrinos = FitNeutrino.NeutrinoFitPolar(lepton.v4(), event.met->v4());
     sort_by_pt<Jet>(*event.jets);

    //  vector<Jet> gluon_jets;
    vector<Jet> top_jets;
    
    /*
    for(int i=0; i<2; i++){
      gluon_jets.push_back(event.jets->at(i));
    }
    */
    //****************************************************
    const auto & tstargen = event.get(h_tstargen);
    auto dec = tstargen.DecayChannel();
    if(dec == TStarGen::e_muhad){
      const Particle & gluon_had = tstargen.GluonHad();
      const Particle & gluon_lep = tstargen.GluonLep();
       //****************************************************      

      int n_top_jets = event.jets->size();
      if(n_top_jets>7) n_top_jets = 7;                    //Limit Number of Jets for Computation Time 

      for(int i=0; i<n_top_jets; i++){ //2
	top_jets.push_back(event.jets->at(i));
    }
      
    
    const unsigned int max_j = pow(3, top_jets.size());  
    //  cout<<"Maximum of top hyp iterations: "<< max_j << endl;
 
    // idea: loop over 3^Njet possibilities and write the current loop
    // index j in the 3-base system. The Njets digits represent whether
    // to assign each jet to the hadronic top (0), leptonic top (1),

      //   for(unsigned int k=0; k < gluon_jets.size(); k++){
      /*
	vector<Jet> gluonhad_jets;
	vector<Jet> gluonlep_jets;

	LorentzVector gluonhad_v4;
	LorentzVector gluonlep_v4;

	if(k==0){
	  gluonhad_v4 = gluon_jets.at(0).v4();
	  gluonhad_jets.push_back(gluon_jets.at(0));
	  gluonlep_v4 = gluon_jets.at(1).v4();
	  gluonlep_jets.push_back(gluon_jets.at(1));
	}
	if(k==1){
	  gluonhad_v4 = gluon_jets.at(1).v4();
	  gluonhad_jets.push_back(gluon_jets.at(1));
	  gluonlep_v4 = gluon_jets.at(0).v4();
	  gluonlep_jets.push_back(gluon_jets.at(0));
	}
      */
   for(const auto & neutrino_p4 : neutrinos) {
      const LorentzVector wlep_v4 = lepton.v4() + neutrino_p4;
      
	for (unsigned int j=0; j < max_j; j++) {
	  TstarReconstructionHypothesis hyp;
	  
	  /*
	  hyp.set_gluonhad_v4(gluonhad_v4);
	  hyp.set_gluonlep_v4(gluonlep_v4);
	  
	  hyp.add_gluonhad_jet(gluonhad_jets.at(0));
	  hyp.add_gluonlep_jet(gluonlep_jets.at(0));
	  */	  
	  //***************************************
	  float mindr_had = 100;
	  int index_had = -1;
	  int num_had = 0;
	  
	  float mindr_lep = 100;
	  int index_lep = -1;
	  int num_lep = 0;

	  LorentzVector gluonlep_v4;
	  LorentzVector gluonhad_v4;

	  vector<Jet> gluon_jet; //
	  //***************************************

	  LorentzVector toplep_v4 = wlep_v4;
	  LorentzVector tophad_v4;
	  
	  vector<Jet> toplep_jet;
	  vector<Jet> tophad_jet;

	  
	  int lepjets=0;
	  int hadjets=0;
	  
	  int num = j;
	  
	  for (unsigned int i=0; i<top_jets.size(); i++){
	    if(num%3==0){
	      toplep_v4 = toplep_v4 + top_jets.at(i).v4();
	      toplep_jet.push_back(top_jets.at(i));
	      hyp.add_toplep_jet(top_jets.at(i));
	      lepjets++;
	    }
	    
	    if(num%3==1){
	      tophad_v4 = tophad_v4 + top_jets.at(i).v4();
	      tophad_jet.push_back(top_jets.at(i));
	      hyp.add_tophad_jet(top_jets.at(i));
	      hadjets++;
	    }
	    
	    //if(num%==2) dont use this jet in current hyp
	    //***********************************************************************************
	    if(num%3==2){
	      gluon_jet.push_back(top_jets.at(i));
	    }
	    //***********************************************************************************

	    num/=3;
	  }
	     
	  //***************************************************************************************************
  
    //loop over neutrino solutions and jet assignments to fill hyotheses
 
      for(unsigned int i=0; i<gluon_jet.size(); i++){
	
	float dR_had = deltaR(gluon_had, gluon_jet.at(i));
	if(dR_had <0.4) {
	  num_had++;
	}
	
	if(dR_had<mindr_had) {//  dR <0.2
	  mindr_had=dR_had;
	  index_had=i;
	}
	
	float dR_lep = deltaR(gluon_lep, gluon_jet.at(i));
	if(dR_lep <0.4) {
	  num_lep++;
	}
	
	if(dR_lep<mindr_lep) {//  dR <0.2
	  mindr_lep=dR_lep;
	  index_lep=i;
	}
      }

	  if(index_lep != -1 && index_had != -1){
	    gluonhad_v4 = gluon_jet.at(index_had).v4();
	    hyp.set_gluonhad_v4(gluonhad_v4);
	    gluonlep_v4 = gluon_jet.at(index_lep).v4();
	    hyp.set_Gluon_Had_num(num_had);
	    hyp.set_Gluon_Lep_num(num_lep);
	    hyp.set_gluonlep_v4(gluonlep_v4);
	  }
	  // ***************************************************************************************************

	  //jet with highest pT used for b-quark hyp 
	  int blep_idx(-1);
	  float maxptlep(-1.);
          
	  for(unsigned int i=0; i<toplep_jet.size(); ++i){
	    if(maxptlep< toplep_jet.at(i).pt()){
	      maxptlep = toplep_jet.at(i).pt();
	      blep_idx = i;
	    }
	  }
	  
	  if(blep_idx != -1){
	    hyp.set_blep_v4(hyp.toplep_jets().at(blep_idx).v4());  //Handle Jet with highest pt as hadronic b-Jets
	    hyp.add_blep_jet(hyp.toplep_jets().at(blep_idx));
	  }
	  
	  int bhad_idx(-1);
	  float maxpthad(-1);
	  
	  for(unsigned int i=0; i<tophad_jet.size(); ++i){
	    if(maxpthad< tophad_jet.at(i).pt()){
	      maxpthad = tophad_jet.at(i).pt();
	      bhad_idx = i;
	    }
	  }
	  
	  if(bhad_idx != -1){
	    hyp.set_bhad_v4(hyp.tophad_jets().at(bhad_idx).v4());  //Handle Jet with highest pt as hadronic b-Jets
	    hyp.add_bhad_jet(hyp.tophad_jets().at(bhad_idx));
	  }
	  
	  if(deltaR(tophad_v4,   toplep_v4)<0.4) continue;
	  //  if(toplep_v4.pt()/tophad_v4.pt()>1.5) continue;

	  if( hadjets>0 && lepjets>0) { 
	    hyp.set_tophad_v4(tophad_v4);
	    hyp.set_toplep_v4(toplep_v4);
	    recoHyps.emplace_back(move(hyp));
	  }
	} // 3^n_jets jet combinations
      } //GluonHyp
    } // neutrinos 
    event.set(h_recohyps, std::move(recoHyps));
    //cout<<"Save Hypothesis!"<<endl<<endl;
    return true;
}

//********************************************************************************************************************************************************************************************

HighMassTopReconstructionTTag::HighMassTopReconstructionTTag(Context & ctx, const NeutrinoReconstructionMethod & neutrinofunction, const string & label, TopJetId tjetid, float minDR_tj_j):
  m_neutrinofunction(neutrinofunction), topjetID_(tjetid), minDR_topjet_jet_(minDR_tj_j) {
  h_recohyps = ctx.declare_event_output<vector<TstarReconstructionHypothesis>>(label);
  h_primlep = ctx.get_handle<FlavorParticle>("PrimaryLepton");
  FitNeutrino = NeutrinoFit();
}

bool HighMassTopReconstructionTTag::process(uhh2::Event & event) {
   assert(event.jets && event.topjets);
  assert(event.met);

  std::vector<TstarReconstructionHypothesis> recoHyps;

  const Particle& lepton = event.get(h_primlep);
  //reconstruct neutrino
  std::vector<LorentzVector> neutrinos = FitNeutrino.NeutrinoFitPolar(lepton.v4(), event.met->v4());
  //  std::vector<LorentzVector> neutrinos = m_neutrinofunction(lepton.v4(), event.met->v4());

  for(const auto& tj : *event.topjets){

    if(!topjetID_(tj, event)) continue;

    // jet candidates for leptonic-top (not overlapping with top-tagged jet)
    std::vector<const Jet*> tlep_jets;
    tlep_jets.reserve(event.jets->size());
    for(const auto & jet : *event.jets)
      if(deltaR(tj, jet) > minDR_topjet_jet_) tlep_jets.push_back(&jet);

    const unsigned int jet_combs = pow(2, tlep_jets.size());

    for(const auto& neutrino_p4 : neutrinos){

      for(unsigned int i=1; i<jet_combs; ++i){

        TstarReconstructionHypothesis hyp;
        hyp.set_lepton(lepton);
        hyp.set_neutrino_v4(neutrino_p4);

        LorentzVector tophad_v4(tj.v4());
        hyp.add_tophad_jet(tj);
        hyp.set_tophad_topjet_ptr(&tj);

	/*
	for(int k=0; k<2; k++){
	  hyp.add_gluon_jet(*tlep_jets.at(k));
	}
	*/

        LorentzVector toplep_v4(lepton.v4() + neutrino_p4);

        for(unsigned int j=0; j<tlep_jets.size(); ++j){
          // index for jet assignment to top leg (0=none, 1=leptonic-top)
          int jet_topidx = int(i/(pow(3,j))) % 3;

	  if(jet_topidx == 0){
	    hyp.add_gluon_jet(*tlep_jets.at(j));
	  }

          if(jet_topidx == 1){
            toplep_v4 += tlep_jets.at(j)->v4();
            hyp.add_toplep_jet(*tlep_jets.at(j));
          }
	}

        // b-jet of leptonic top (pt-leading)
        int blep_idx(-1);
        float maxpt(-1.);
        for(unsigned int i=0; i<hyp.toplep_jets().size(); ++i){
          if(maxpt< hyp.toplep_jets().at(i).pt()){
            maxpt = hyp.toplep_jets().at(i).pt();
            blep_idx = i;
          }
        }
        if(blep_idx != -1) hyp.set_blep_v4(hyp.toplep_jets().at(blep_idx).v4());

        if(hyp.tophad_jets().size() && hyp.toplep_jets().size()){
          hyp.set_tophad_v4(tophad_v4);
          hyp.set_toplep_v4(toplep_v4);
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
    if(n_jets>7) n_jets = 7;                    //Limit Number of Jets for Computation Time 
  

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
	      if(unused_jets.size()>0 && gluonlep_jets >0 && toplep_jet.size()>0){  //((gluonlep_v4.pt()-toplep_jet.at(blep_idx).pt())/(toplep_jet.at(blep_idx).pt()+gluonlep_v4.pt()))>0 && 	
		leptonic_kin = true;
	      }
	    }
	    if(!leptonic_kin) continue;
	    

	    if(toplep_v4.M()>350) continue;
	    if(deltaR(toplep_v4, gluonlep_v4)<0.4) continue;

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
		hyp.add_blep_jet(toplep_jet.at(blep_idx));
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

	      if(bhad_idx != -1 && gluonhad_jets>0){
		hyp.set_bhad_v4(hyp.tophad_jets().at(bhad_idx).v4());  //Handle Jet with highest pt as hadronic b-Jets
		hyp.add_bhad_jet(hyp.tophad_jets().at(bhad_idx));
	      }
	      else{ 
		continue;
	      }
	    
    
	
	      //  if(tophad_v4.M()>350) continue;

	      if(deltaR(gluonhad_v4, tophad_v4)<0.4) continue;
	      if(deltaR(gluonhad_v4, toplep_v4)<0.4) continue;
	      if(deltaR(gluonlep_v4, tophad_v4)<0.4) continue; //0.4
	      if(deltaR(gluonhad_v4, gluonlep_v4)<0.4) continue;
	      if(deltaR(tophad_v4,   toplep_v4)<0.4) continue;
	      if(deltaR(gluonhad_v4, hyp.bhad_v4())<0.4) continue;
	      if(deltaR(gluonlep_v4, hyp.bhad_v4())<0.4) continue;
	      
	      /*
	      if(hyp.blep_jets().at(0).btag_combinedSecondaryVertex()<0.4) continue;
	      if(hyp.bhad_jets().at(0).btag_combinedSecondaryVertex()<0.4) continue;
	      if(hyp.gluonlep_jets().at(0).btag_combinedSecondaryVertex()>0.8) continue;
	      if(hyp.gluonhad_jets().at(0).btag_combinedSecondaryVertex()>0.8) continue;
	      
	      if(gluonhad_jets>1){
		if(hyp.gluonhad_jets().at(1).btag_combinedSecondaryVertex()>0.8) continue;
	      }    
	      if(gluonlep_jets>1){
	      	if(hyp.gluonlep_jets().at(1).btag_combinedSecondaryVertex()>0.8) continue;
	      }
	      */
	   	   
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
    if(n_jets>8) n_jets=8;
    
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
	  if(hyp.toplep_jets().at(blep_idx).pt()<gluonlep_v4.pt() && gluonhadjets>0 && gluonlepjets>0){
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

	
	if(deltaR(gluonhad_v4, tophad_v4)<0.4) continue;
	if(deltaR(gluonhad_v4, toplep_v4)<0.4) continue;
	if(deltaR(gluonlep_v4, tophad_v4)<0.4) continue;
	if(deltaR(gluonhad_v4, gluonlep_v4)<0.4) continue;

	/*
	if(hyp.blep_jets().at(0).btag_combinedSecondaryVertex()<0.4) continue;
	if(hyp.gluonlep_jets().at(0).btag_combinedSecondaryVertex()>0.8) continue;
	if(hyp.gluonhad_jets().at(0).btag_combinedSecondaryVertex()>0.8) continue;
	
	if(gluonhadjets>1){
	  if(hyp.gluonhad_jets().at(1).btag_combinedSecondaryVertex()>0.8) continue;
	}    
	if(gluonlepjets>1){
	  if(hyp.gluonlep_jets().at(1).btag_combinedSecondaryVertex()>0.8) continue;
	}
	*/

	//	if(deltaR(gluonhad_v4, gluonlep_v4)<2.5 || deltaR(gluonhad_v4, gluonlep_v4)>3.5) continue;

	////Fill Hypothese
	if(lepjets>0 && gluonhadjets >0 && gluonlepjets >0) {
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


//**********************************************************************************

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

