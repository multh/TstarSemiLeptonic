#include "UHH2/TstarSemiLeptonic/include/TstarPreSelectionHists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/Utils.h"
#include <math.h>

#include "TH1F.h"
#include "TH1D.h"
#include <iostream>

using namespace std;
using namespace uhh2;
using namespace uhh2examples;

TstarPreSelectionHists::TstarPreSelectionHists(uhh2::Context& ctx, const std::string& dirname): Hists(ctx, dirname){

  // *************************************************************************
  //
  // User defined Hists for T*T* -> t+g t+g 
  //
  // Number of Jets, pT and eta distributions for leading 6 jets
  // Number of Leptons (Electrons/Muons) 
  // pT and eta for leading Lepton  
  //
  // *************************************************************************

  book<TH1D>("N_jets", "N_{jets}", 20, 0, 20);  
  book<TH1D>("eta_jet1", "#eta^{jet 1}", 40, -2.5, 2.5);
  book<TH1D>("eta_jet2", "#eta^{jet 2}", 40, -2.5, 2.5);
  book<TH1D>("eta_jet3", "#eta^{jet 3}", 40, -2.5, 2.5);
  book<TH1D>("eta_jet4", "#eta^{jet 4}", 40, -2.5, 2.5);
  book<TH1D>("eta_jet5", "#eta^{jet 5}", 40, -2.5, 2.5);
  book<TH1D>("eta_jet6", "#eta^{jet 6}", 40, -2.5, 2.5);
  book<TH1D>("pt_jet1", "#p_{T}^{jet 1}", 100, 0, 3000);
  book<TH1D>("pt_jet2", "#p_{T}^{jet 2}", 100, 0, 3000);
  book<TH1D>("pt_jet3", "#p_{T}^{jet 3}", 100, 0, 3000);
  book<TH1D>("pt_jet4", "#p_{T}^{jet 4}", 100, 0, 3000);
  book<TH1D>("pt_jet5", "#p_{T}^{jet 5}", 100, 0, 3000);
  book<TH1D>("pt_jet6", "#p_{T}^{jet 6}", 100, 0, 3000);

  // leptons
  book<TH1D>("N_mu", "N^{#mu}", 5, 0, 5);
  book<TH1D>("pt_mu", "p_{T}^{leading #mu} [GeV/c]", 40, 0, 200);
  book<TH1D>("eta_mu", "#eta^{leading #mu}", 40, -2.1, 2.1);
  book<TH1D>("reliso_mu", "#mu rel. Iso", 40, 0, 0.5);

  book<TH1D>("N_el", "N^{el}", 5, 0, 5);
  book<TH1D>("pt_el", "p_{T}^{leading ele} [GeV/c]", 40, 0, 200);
  book<TH1D>("eta_el", "#eta^{leading ele}", 40, -2.1, 2.1);


  // general
  book<TH1D>("N_pv", "N_{PV}", 50, 0, 50);
  book<TH1D>("H_T", "H_{T}", 100, 0, 5000);
  book<TH1D>("MET", "MET", 100, 0, 500);
  book<TH1D>("sum_event_weights", "BinContent = sum(eventweights)", 1, 0.5, 1.5);
  book<TH1D>("mindr_mujet", "min(#Delta R) between a muon and a jet", 50,0,5);

  book<TH1F>("NbJetsL", "Number of bjets loose", 7, -0.5,6.5);
  book<TH1F>("NbJetsM", "Number of bjets medium", 7, -0.5,6.5);
  book<TH1F>("NbJetsT", "Number of bjets tight", 7, -0.5,6.5);


}

void TstarPreSelectionHists::fill(const uhh2::Event& event){
 double weight = event.weight;

  std::vector<Jet>* jets = event.jets;
  int Njets = jets->size();
  hist("N_jets")->Fill(Njets, weight);
  
  if(Njets>=1){
    hist("eta_jet1")->Fill(jets->at(0).eta(), weight);
    hist("pt_jet1")->Fill(jets->at(0).pt(), weight);
  }
  if(Njets>=2){
    hist("eta_jet2")->Fill(jets->at(1).eta(), weight);
    hist("pt_jet2")->Fill(jets->at(1).pt(), weight);
  }
  if(Njets>=3){
    hist("eta_jet3")->Fill(jets->at(2).eta(), weight);
    hist("pt_jet3")->Fill(jets->at(2).pt(), weight);
  }
  if(Njets>=4){
    hist("eta_jet4")->Fill(jets->at(3).eta(), weight);
    hist("eta_jet4")->Fill(jets->at(3).pt(), weight);
  }
  if(Njets>=5){
    hist("eta_jet5")->Fill(jets->at(4).eta(), weight);
    hist("eta_jet5")->Fill(jets->at(4).pt(), weight);
  }
  if(Njets>=6){
    hist("eta_jet6")->Fill(jets->at(5).eta(), weight);
    hist("eta_jet6")->Fill(jets->at(5).pt(), weight);
  }



  int Nmuons = event.muons->size();
  hist("N_mu")->Fill(Nmuons, weight);

  std::vector<Muon>* muons = event.muons;
  if(Nmuons >= 1){
    hist("pt_mu")->Fill(muons->at(0).pt(), weight);
      hist("eta_mu")->Fill(muons->at(0).eta(), weight);
      hist("reliso_mu")->Fill(muons->at(0).relIso(), weight);
  }
  
  int Nelect = event.electrons->size();
  hist("N_el")->Fill(Nelect, weight);

  std::vector<Electron>* electrons = event.electrons;
  if(Nelect >= 1){
      hist("pt_el")->Fill(electrons->at(0).pt(), weight);
      hist("eta_el")->Fill(electrons->at(0).eta(), weight);
      hist("reliso_el")->Fill(electrons->at(0).relIso(), weight);
  }

  int Npvs = event.pvs->size();
  hist("N_pv")->Fill(Npvs, weight);

  //HT
  auto met = event.met->pt();
  double ht = 0.0;
  double ht_jets = 0.0;

  for(const auto & jet : *event.jets){
    ht_jets += jet.pt();
  }
 
  ht = ht_jets + met;
  hist("H_T")->Fill(ht, weight);
  hist("MET")->Fill(met, weight);

  hist("sum_event_weights")->Fill(1., weight);

  double mindr_mujet = 999;
  for(const Muon & thismu : *event.muons){
    for(const Jet & thisjet : *event.jets){
      double dr = deltaR(thismu,thisjet);
      if (dr < mindr_mujet) mindr_mujet = dr;
    }
    hist("mindr_mujet")->Fill(mindr_mujet,weight);
  }


  vector<Jet> bjetsL, bjetsM, bjetsT;
  for (unsigned int i =0; i<jets->size(); ++i) {
    if(jets->at(i).btag_combinedSecondaryVertex()>0.423) {
      bjetsL.push_back(jets->at(i));
    }
  }
  for (unsigned int i =0; i<jets->size(); ++i) {
    if(jets->at(i).btag_combinedSecondaryVertex()>0.814) {
      bjetsM.push_back(jets->at(i));
    }
  }
  for (unsigned int i =0; i<jets->size(); ++i) {
    if(jets->at(i).btag_combinedSecondaryVertex()>0.941) {
      bjetsT.push_back(jets->at(i));
    }
  }
  int NbJetsL = bjetsL.size();
  int NbJetsM = bjetsM.size();
  int NbJetsT = bjetsT.size();
  hist("NbJetsL")-> Fill(NbJetsL,weight);
  hist("NbJetsM")-> Fill(NbJetsM,weight);
  hist("NbJetsT")-> Fill(NbJetsT,weight);




}

TstarPreSelectionHists::~TstarPreSelectionHists(){}
