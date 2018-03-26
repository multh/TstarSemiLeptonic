#include "UHH2/TstarSemiLeptonic/include/TstarSelectionHists.h"
#include "UHH2/core/include/Utils.h"
#include "UHH2/common/include/Utils.h"

using namespace uhh2;

TstarSelectionHists::TstarSelectionHists(uhh2::Context& ctx, const std::string& dirname): Hists(ctx, dirname){

  book<TH1F>("N_bJets_loose", "#N_{Bjets}^{loose}", 10, 0, 10);
  book<TH1F>("N_bJets_med", "#N_{Bjets}^{medium}", 10, 0, 10);
  book<TH1F>("N_bJets_tight", "#N_{Bjets}^{tight}", 10, 0, 10);

  book<TH1D>("N_jets", "N_{jets}", 20, 0, 20);  
  book<TH1D>("eta_jet1", "#eta^{jet 1}", 40, -2.5, 2.5);
  book<TH1D>("eta_jet2", "#eta^{jet 2}", 40, -2.5, 2.5);
  book<TH1D>("eta_jet3", "#eta^{jet 3}", 40, -2.5, 2.5);
  book<TH1D>("eta_jet4", "#eta^{jet 4}", 40, -2.5, 2.5);
  book<TH1D>("pt_jet1", "#p_{T}^{jet 1}", 100, 0, 3000);
  book<TH1D>("pt_jet2", "#p_{T}^{jet 2}", 100, 0, 3000);
  book<TH1D>("pt_jet3", "#p_{T}^{jet 3}", 100, 0, 3000);

  // leptons
  book<TH1D>("N_mu", "N^{#mu}", 5, -0.5, 4.5);
  book<TH1D>("pt_mu", "p_{T}^{#mu} [GeV/c]", 40, 0, 200);
  book<TH1D>("eta_mu", "#eta^{#mu}", 40, -2.5, 2.5);
  book<TH1D>("reliso_mu", "#mu rel. Iso", 40, 0, 0.5);

  // general
  book<TH1D>("N_pv", "N_{PV}", 50, 0, 50);
  book<TH1D>("H_T", "H_{T}", 100, 0, 5000);
  book<TH1D>("sum_event_weights", "BinContent = sum(eventweights)", 1, 0.5, 1.5);
  book<TH1D>("mindr_mujet", "min(#Delta R) between a muon and a jet", 50,0,5);



}

void TstarSelectionHists::fill(const uhh2::Event& event){

std::vector<Jet>* jets = event.jets;

  double weight = event.weight;

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


  int Njets = jets->size();
  hist("N_jets")->Fill(Njets, weight);
  
  if(Njets>=1){
    hist("eta_jet1")->Fill(jets->at(0).eta(), weight);
  }
  if(Njets>=2){
    hist("eta_jet2")->Fill(jets->at(1).eta(), weight);
  }
  if(Njets>=3){
    hist("eta_jet3")->Fill(jets->at(2).eta(), weight);
  }
  if(Njets>=4){
    hist("eta_jet4")->Fill(jets->at(3).eta(), weight);
  }
  if(Njets>=1){
    hist("pt_jet1")->Fill(jets->at(0).pt(), weight);
  }
  if(Njets>=2){
    hist("pt_jet2")->Fill(jets->at(1).pt(), weight);
  }
  if(Njets>=3){
    hist("pt_jet3")->Fill(jets->at(2).pt(), weight);
  }



  int Nmuons = event.muons->size();
  hist("N_mu")->Fill(Nmuons, weight);
  for (const Muon & thismu : *event.muons){
      hist("pt_mu")->Fill(thismu.pt(), weight);
      hist("eta_mu")->Fill(thismu.eta(), weight);
      hist("reliso_mu")->Fill(thismu.relIso(), weight);
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

  hist("sum_event_weights")->Fill(1., weight);

  double mindr_mujet = 999;
  for(const Muon & thismu : *event.muons){
    for(const Jet & thisjet : *event.jets){
      double dr = deltaR(thismu,thisjet);
      if (dr < mindr_mujet) mindr_mujet = dr;
    }
    hist("mindr_mujet")->Fill(mindr_mujet,weight);
  }


}

TstarSelectionHists::~TstarSelectionHists(){}
