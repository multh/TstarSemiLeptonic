#include "UHH2/TstarSemiLeptonic/include/TstarReconstruction.h"
#include "UHH2/core/include/LorentzVector.h"
#include "UHH2/common/include/Utils.h"
#include "UHH2/core/include/Utils.h"

#include <cassert>
#include <iterator>
#include <iostream>

using namespace uhh2;
using namespace std;

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
	if(n_jets>7) n_jets = 7;
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
	      hyp.set_blep_v4(hyp.toplep_jets().at(blep_idx).v4());
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
	      hyp.add_bhad_jet(hyp.tophad_jets().at(bhad_idx));
	    }
	    

            //fill only hypotheses with at least one jet assigned to each top quark
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
  std::vector<LorentzVector> neutrinos = m_neutrinofunction(lepton.v4(), event.met->v4());

  for(const auto& tj : *event.topjets){
    if(!topjetID_(tj, event)) continue;

    // jet candidates for leptonic-top (not overlapping with top-tagged jet)
    std::vector<const Jet*> tlep_jets;
    tlep_jets.reserve(event.jets->size());

    for(const auto & jet : *event.jets)
    if(deltaR(tj, jet) > minDR_topjet_jet_) tlep_jets.push_back(&jet);
    
    unsigned int n_jets = tlep_jets.size();

    if(n_jets<3) return false;
    if(n_jets>7) n_jets=7;

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

        LorentzVector toplep_v4(lepton.v4() + neutrino_p4);
	int num = i;

	////Fill TopLep and Gluon Hypothese
        for(unsigned int j=0; j<n_jets; ++j){
          // index for jet assignment to top leg (0=none, 1=leptonic-top, 2=leptonic gluon, 3=hadronic gluon)
          
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
	      hyp.set_blep_v4(hyp.toplep_jets().at(blep_idx).v4());
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
	      hyp.add_bhad_jet(hyp.tophad_jets().at(bhad_idx));
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

////Neutrino Reconstruction
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

