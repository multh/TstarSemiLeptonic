#include "UHH2/TstarSemiLeptonic/include/TstarPreSelectionHists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/Utils.h"
#include <math.h>

#include "TH1F.h"
#include "TH1D.h"

#include <vector>

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

  book<TH1D>("N_jets", "N_{jets}", 22, 0, 22);  
  book<TH1D>("eta_jet1", "#eta^{jet 1}", 40, -2.7, 2.7);
  book<TH1D>("eta_jet2", "#eta^{jet 2}", 40, -2.7, 2.7);
  book<TH1D>("eta_jet3", "#eta^{jet 3}", 40, -2.7, 2.7);
  book<TH1D>("eta_jet4", "#eta^{jet 4}", 40, -2.7, 2.7);
  book<TH1D>("eta_jet5", "#eta^{jet 5}", 40, -2.7, 2.7);
  book<TH1D>("eta_jet6", "#eta^{jet 6}", 40, -2.7, 2.7);
  book<TH1D>("pt_jet1", "p_{T}^{jet 1} [GeV/c]", 100, 0, 3000);
  book<TH1D>("pt_jet2", "p_{T}^{jet 2} [GeV/c]", 100, 0, 3000);
  book<TH1D>("pt_jet3", "p_{T}^{jet 3} [GeV/c]",  83, 0, 2500);
  book<TH1D>("pt_jet4", "p_{T}^{jet 4} [GeV/c]",  50, 0, 1500);
  book<TH1D>("pt_jet5", "p_{T}^{jet 5} [GeV/c]",  50, 0, 1500);
  book<TH1D>("pt_jet6", "p_{T}^{jet 6} [GeV/c]",  50, 0, 1500);

  // leptons
  book<TH1D>("N_mu", "N^{#mu}", 8, -0.5, 7.5);
  book<TH1D>("pt_mu", "p_{T}^{leading #mu} [GeV/c]", 80, 0, 400);
  book<TH1D>("eta_mu", "#eta^{leading #mu}", 40, -2.7, 2.7);
  book<TH1D>("reliso_mu", "#mu rel. Iso", 50, 0, 1);
  book<TH1D>("pTrel", "p_{T}^{rel} between muon and jet", 40, 0, 200);

  book<TH1D>("N_el", "N^{el}", 5, 0, 5);
  book<TH1D>("pt_el", "p_{T}^{leading ele} [GeV/c]", 40, 0, 200);
  book<TH1D>("eta_el", "#eta^{leading ele}", 40, -2.1, 2.1);
  book<TH1D>("reliso_el", "ele rel. Iso", 50, 0, 1);

  // general
  book<TH1D>("N_pv", "N_{PV}", 50, 0, 50);
  book<TH1D>("H_T", "H_{T}  [GeV]", 100, 0, 5000);
  book<TH1D>("MET", "MET [GeV] ", 100, 0, 500);
  book<TH1D>("sum_event_weights", "BinContent = sum(eventweights)", 1, 0.5, 1.5);
  book<TH1D>("mindr_mujet", "min(#Delta R) between a muon and a jet", 50,0,5);

  book<TH1F>("N_bJets_loose", "#N_{Bjets}^{loose}", 10, -0.5, 9.5);
  book<TH1F>("N_bJets_med", "#N_{Bjets}^{medium}", 10, -0.5, 9.5);
  book<TH1F>("N_bJets_tight", "#N_{Bjets}^{tight}", 10, -0.5, 9.5);
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
  
  vector<float> ptrel_buf;
  std::vector<Muon>* muons = event.muons;
  if(Nmuons >= 1){
    hist("pt_mu")->Fill(muons->at(0).pt(), weight);
      hist("eta_mu")->Fill(muons->at(0).eta(), weight);
      hist("reliso_mu")->Fill(muons->at(0).relIso(), weight);
      if(event.jets){
	auto nj = nextJet(muons->at(0), *event.jets);
	ptrel_buf.push_back(pTrel(muons->at(0), nj));
      }
      hist("pTrel")->Fill(ptrel_buf[0], weight);
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

 std::vector<Jet> bjets_loose, bjets_med, bjets_tight;
  for (unsigned int i =0; i<jets->size(); ++i) {
    if(jets->at(i).btag_combinedSecondaryVertex()>0.5426) { //loose: >0.605, medium: >0.890, tight: >0.970
      bjets_loose.push_back(jets->at(i));
    }
    if(jets->at(i).btag_combinedSecondaryVertex()>0.8484) { //loose: >0.605, medium: >0.890, tight: >0.970
      bjets_med.push_back(jets->at(i));
    }
    if(jets->at(i).btag_combinedSecondaryVertex()>0.9535) { //loose: >0.605, medium: >0.890, tight: >0.970
      bjets_tight.push_back(jets->at(i));
    }
  }
  int NbJets_loose = bjets_loose.size();
  hist("N_bJets_loose")->Fill(NbJets_loose,weight);
  int NbJets_med = bjets_med.size();
  hist("N_bJets_med")->Fill(NbJets_med,weight);
  int NbJets_tight = bjets_tight.size();
  hist("N_bJets_tight")->Fill(NbJets_tight,weight);
}

TstarPreSelectionHists::~TstarPreSelectionHists(){}
