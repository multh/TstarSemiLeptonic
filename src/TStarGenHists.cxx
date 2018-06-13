#include "UHH2/TstarSemiLeptonic/include/TStarGenHists.h"
#include "UHH2/common/include/Utils.h"
#include "TH1F.h"
#include "TH2F.h"
#include <iostream>

using namespace uhh2;
using namespace std;

namespace{
  float deltaPhi_calc(float p1, float p2){
    float deltaPhi = 100;
    
    if ((p1 - p2) < 0) deltaPhi = p2 - p1;
    else{ 
      deltaPhi = p1 - p2;
    }
    return deltaPhi;
  }
}


TStarGenHists::TStarGenHists(uhh2::Context & ctx, const std::string & dirname): Hists(ctx, dirname){

  DecayChannel  = book<TH1F>("Decay_Channel","Decay_Channel", 11, -0.5, 10.5);

  M_TstarTstar       = book<TH1F>( "M_TstarTstar", "M_{T^{*}#bar{T}^{*}} [GeV/c^{2}]", 200, 0, 6000 ) ;   
  Pt_TstarTstar      = book<TH1F>( "Pt_TstarTstar", "P_{T,T^{*}#bar{T^{*}}} [GeV/c]", 10, -0.5, 0.5 ) ;
  Pt_TstarTstar_Diff = book<TH1F>( "Pt_TstarTstar_Diff", "P_{T} T*T* diff [GeV/c]", 20, -1, 1 ) ;

  M_TstarTstar_vs_eta_Tstar     = book<TH2F>( "M_TstarTstar_vs_eta_Tstar", "M_{T*#bar{T*}} [GeV/c^{2}] vs #eta_{T*}",500,0,5000,500,-5,5); 
  M_TstarTstar_vs_eta_antiTstar = book<TH2F>( "M_TstarTstar_vs_eta_antiTstar", "M_{T*#bar{T*}} [GeV/c^{2}] vs #eta_{#bar{T*}}",500,0,5000,500,-5,5); 

  M_Tstar   = book< TH1F>("M_Tstar",   "M_{T^{*}} [GeV/c^{2}]", 185, 150, 2000) ;
  Pt_Tstar  = book< TH1F>("Pt_Tstar",  "P_{T,T^{*}} [GeV/c]", 250, 0, 2500 ) ;
  eta_Tstar = book< TH1F>("eta_Tstar", "#eta_{T^{*}}", 100, -5.19, 5.19 ) ;
  phi_Tstar = book< TH1F>("phi_Tstar", "#phi_{T^{*}}", 100, -3.14, 3.14 ) ;

  M_antiTstar   = book< TH1F>("M_AntiTStar", "M_{#bar{T}^{*}} [GeV/c^{2}]", 185, 150, 2000) ;  
  Pt_antiTstar  = book< TH1F>("Pt_AntiTstar", "P_{T,#bar{T}^{*}} [GeV/c]", 250, 0, 2500 ) ;
  eta_antiTstar = book< TH1F>("eta_AntiTstar", "#eta_{#bar{T}^{*}}", 100, -5.19, 5.19 ) ;
  phi_antiTstar = book< TH1F>("phi_AntiTstar", "#phi_{#bar{T}^{*}}", 100, -3.14, 3.14 ) ;

  M_TstarAntiTstar_ratio   = book< TH1F>("M_TstarAntiTstar_ratio",   "M_{T^{*}}/M_{#bar{T}^{*}} -1  [GeV/c^{2}]", 30, -1,1) ;
  Pt_TstarAntiTstar_ratio   = book< TH1F>("Pt_TstarAntiTstar_ratio",   "pT_{T^{*}}/pT_{#bar{T}^{*}} -1  [GeV/c^{2}]", 30, -1,1) ;

  Pt_Tstar_over_M_TstarTstar     = book< TH1F>("Pt_Tstar_over_M_TstarTstar", "P_{T,T*}/M_{T*#bar{T*}}", 100, 0, 1 );
  Pt_antiTstar_over_M_TstarTstar = book< TH1F>("Pt_antiTstar_over_M_TstarTstar", "P_{T,#bar{T*}}/M_{T*#bar{T*}}", 100, 0, 1 );
  Pt_Tstar_over_shat             = book< TH1F>("Pt_Tstar_over_shat", "P_{T,T*}/#hat{s}", 100, 0, 1 ) ;
  Pt_antiTstar_over_shat         = book< TH1F>("Pt_antiTstar_over_shat", "P_{T,T*}/#hat{s}", 100, 0, 1 ) ;

  M_TstarTstar_vs_deltaR_Tstar     = book<TH2F>( "M_TstarTstar_vs_deltaR_Tstar", "M_{T*#bar{T*}} [GeV/c^{2}] vs #DeltaR(T* decay prod.)",500,0,5000,500,0,5);
  M_TstarTstar_vs_deltaR_antiTstar = book<TH2F>( "M_TstarTstar_vs_deltaR_antiTstar", "M_{T*#bar{T*}} [GeV/c^{2}] vs #DeltaR(#bar{T*} decay prod.)",500,0,5000,500,0,5);
  shat_vs_deltaR_Tstar             = book<TH2F>( "shat_vs_deltaR_Tstar", "#hat{s} [GeV] vs #DeltaR(T* decay prod.)",500,0,5000,500,0,5);
  shat_vs_deltaR_antiTstar         = book<TH2F>( "shat_vs_deltaR_antiTstar", "#hat{s} [GeV] vs #DeltaR(#bar{T*} decay prod.)",500,0,5000,500,0,5);
  shat_vs_Pt_Tstar                 = book<TH2F>( "shat_vs_Pt_Tstar", "#hat{s} [GeV] vs P_{T,T*} [GeV/c]",500,0,5000,500,0,2000); 
  shat_vs_Pt_antiTstar             = book<TH2F>( "shat_vs_Pt_antiTstar", "#hat{s} [GeV] vs P_{T,#bar{T*}} [GeV/c]",500,0,5000,500,0,2000); 


  diffabseta = book<TH1F>( "diffabseta", "|#eta_{T^{*}}|-|#eta_{#bar{T}^{*}}|",200,-5,5);
  diffphi = book<TH1F>( "diffphi", "|#phi_{T^{*}}-#phi_{#bar{T}^{*}}|",20,0,6.5);
       
  deltaR_Tstar_decays     = book<TH1F>( "deltaR_tstar_decays", "#DeltaR(T^{*} decay prod.)",200,0,5);
  deltaR_antiTstar_decays = book<TH1F>( "deltaR_antitstar_decays", "#DeltaR(#bar{T}^{*} decay prod.)",200,0,5);  
  
  M_Tstar_reco     = book< TH1F>("M_Tstar_reco", "M_{top+g} [GeV/c^{2}]", 185, 150, 2000) ;
  M_antiTstar_reco = book< TH1F>("M_AntiTstar_reco", "M_{#bar{t}+ g} [GeV/c^{2}]", 185, 150, 2000) ;

  M_gluon   = book<TH1F>("M_gluon", "M_{t} [GeV/c^{2}]",30,0, 2000);
  Pt_gluon  = book<TH1F>("Pt_gluon_Tstar","P_{T,gluon} [GeV/c]",100,0,2000);
  eta_gluon = book<TH1F>("eta_gluon_Tstar","#eta_{gluon}",100,-5,5);
  phi_gluon = book<TH1F>("phi_gluon_Tstar", "#phi_{gluon}", 100, -3.14, 3.14);
  
  M_antigluon   = book<TH1F>("M_antigluon", "M_{t} [GeV/c^{2}]",30,0, 2000);
  Pt_antigluon  = book<TH1F>("Pt_gluon_AntiTstar","P_{T,g} [GeV/c]",200,0,2000);
  eta_antigluon = book<TH1F>("eta_gluon_AntiTstar","#eta_{g}",100,-5,5);
  phi_antigluon = book<TH1F>("phi_gluon_AntiTstar", "#phi_{gluon}", 100, -3.14, 3.14);

  Pt_gluonAntigluon_ratio   = book< TH1F>("Pt_gluonAntigluon_ratio",   "pT_{gluon}/pT_{#bar{gluon} -1  [GeV/c^{2}]", 30, -1,1) ;

  deltaPhi_gluon_antigluon   = book<TH1F>("deltaPhi_gluon_antigluon", "#Delta #phi gluon antigluon", 40,0,6);
  deltaPhi_top_antitop       = book<TH1F>("deltaPhi_top_antitop", "#Delta #phi top antitop", 40,0,6);
  deltaPhi_gluon_top         = book<TH1F>("deltaPhi_gluon_top", "#Delta #phi gluon top", 40,0,6);
  deltaPhi_antigluon_antitop = book<TH1F>("deltaPhi_antigluon_antitop", "#Delta #phi antigluon antitop", 40,0,6);
  deltaPhi_gluon_antitop     = book<TH1F>("deltaPhi_gluon_antitop", "#Delta #phi gluon antitop", 40, 0, 6);
  deltaPhi_antigluon_top     = book<TH1F>("deltaPhi_antigluon_top", "#Delta #phi antigluon top", 40, 0, 6);

  deltaR_gluon_antigluon   = book<TH1F>("deltaR_gluon_antigluon", "#Delta R gluon antigluon", 30,0,6);
  deltaR_top_antitop       = book<TH1F>("deltaR_top_antitop", "#Delta R top antitop", 30,0,6);
  deltaR_gluon_top         = book<TH1F>("deltaR_gluon_top", "#Delta R gluon top", 30,0,6);
  deltaR_antigluon_antitop = book<TH1F>("deltaR_antigluon_antitop", "#Delta R antigluon antitop", 30,0,6);
  deltaR_gluon_antitop     = book<TH1F>("deltaR_gluon_antitop", "#Delta R gluon antitop", 30, 0, 6);
  deltaR_antigluon_top     = book<TH1F>("deltaR_antigluon_top", "#Delta R antigluon top", 30, 0, 6);

  Diff_deltaR_leptonic     = book<TH1F>("Diff_deltaR_leptonic", "Diff #DeltaR lep - had", 60, -6, 6);
  Diff_deltaR_hadronic     = book<TH1F>("Diff_deltaR_hadronic", "Diff #DeltaR had - lep", 60, -6, 6);

  M_top   = book<TH1F>("M_top", "M_{t} [GeV/c^{2}]",50,140, 210);
  Pt_top  = book<TH1F>("Pt_top","P_{T,t} [GeV/c]",100,0,1000);
  eta_top = book<TH1F>("eta_top","#eta_{t}",100,-5.19,5.19);
  phi_top = book<TH1F>("phi_top", "#phi_{t}", 100, -3.14, 3.14);

  M_antitop   = book<TH1F>("M_antitop", "M_{#bar{t}} [GeV/c^{2}]", 50, 140, 210);
  Pt_antitop  = book<TH1F>("Pt_antitop","P_{T,#bar{t}} [GeV/c]",100,0,1000);
  eta_antitop = book<TH1F>( "eta_antitop","#eta_{#bar{t}}",100,-5,5);
  phi_antitop = book<TH1F>("phi_antitop", "#phi_{#bar{t}}", 100, -3.14, 3.14);

  deltaR_top_decays     = book<TH1F>( "deltaR_top_decays", "#DeltaR(t decay prod.)",100,0,5);
  deltaR_antitop_decays = book<TH1F>( "deltaR_antitop_decays", "#DeltaR(#bar{t} decay prod.)",100,0,5);  

  Pt_Top_vs_deltaR_top         = book<TH2F>( "Pt_top_vs_deltaR_top", "P_{T, t} [GeV/c] vs #DeltaR(top decay prod.)",200,0,3000,500,0,5);
  Pt_antiTop_vs_deltaR_antitop = book<TH2F>( "Pt_antitop_vs_deltaR_antitop", "P_{T, #bar{t}} [GeV/c] vs #DeltaR(top decay prod.)",200,0,3000,500,0,5);

  M_tTstar_reco     = book< TH1F>("M_tTstar_reco", "M_{W b} [GeV/c^{2}]", 50, 140, 210) ;
  M_tAntiTstar_reco = book< TH1F>("M_tAntiTstar", "M_{W #bar{b}} [GeV/c^{2}]", 50, 140, 210) ;

  Diff_Pt_gluon_top         = book<TH1F>("Diff_Pt_gluon_top", "(p_{T}^{gluon} - p_{T}^{top})/(p_{T}^{gluon} + p_{T}^{top})", 20, -1.5, 1.5);
  Diff_Pt_antigluon_antitop = book<TH1F>("Diff_Pt_antigluon_antitop", "(p_{T}^{#bar{gluon}} - p_{T}^{#bar{top}})/(p_{T}^{#bar{gluon}} + p_{T}^{#bar{top}})", 20,-1.5,1.5);

  Diff_Pt_gluon_btop         = book<TH1F>("Diff_Pt_gluon_btop", "(p_{T}^{gluon} - p_{T}^{b})/(p_{T}^{gluon} + p_{T}^{b})", 20, -1.5, 1.5);
  Diff_Pt_antigluon_bantitop = book<TH1F>("Diff_Pt_antigluon_bantitop", "p_{T}^{#bar{gluon}} - p_{T}^{#bar{b}}/(p_{T}^{#bar{gluon}} + p_{T}^{#bar{b}})", 20,-1.5,1.5);

  Diff_Pt_gluon_WplusDecay1 = book<TH1F>("Diff_Pt_gluon_WplusDecay1", "(p_{T}^{gluon} - p_{T}^{top, q1})/(p_{T}^{gluon} + p_{T}^{top, q1})", 20, -1.5, 1.5);
  Diff_Pt_gluon_WplusDecay2 = book<TH1F>("Diff_Pt_gluon_WplusDecay2", "(p_{T}^{gluon} - p_{T}^{top, q2})/(p_{T}^{gluon} + p_{T}^{top, q2})", 20, -1.5, 1.5);

  Diff_Pt_antigluon_WminusDecay1 = book<TH1F>("Diff_Pt_gluon_WminusDecay1", "(p_{T}^{#bar{gluon}} - p_{T}^{#bar{top}})/(p_{T}^{#bar{gluon}} + p_{T}^{#bar{top}, q1})", 20, -1.5, 1.5);
  Diff_Pt_antigluon_WminusDecay2 = book<TH1F>("Diff_Pt_gluon_WminusDecay2", "(p_{T}^{#bar{gluon}} - p_{T}^{#bar{top}})/(p_{T}^{#bar{gluon}} + p_{T}^{#bar{top}, q2})", 20, -1.5, 1.5);

  Diff_Pt_antigluon_gluon = book<TH1F>("Diff_Pt_antigluon_gluon", "(p_{T}^{#bar{gluon}} - p_{T}^{gluon})/(p_{T}^{#bar{gluon}} + p_{T}^{gluon})", 20,-1.5,1.5);
  Diff_Pt_bantitop_btop   = book<TH1F>("Diff_Pt_bantitop_btop", "(p_{T}^{#bar{b}} - p_{T}^{b})/(p_{T}^{#bar{b}} + p_{T}^{b})", 20,-1.5,1.5);

  Pt_bottom  = book<TH1F>("Pt_bottom_antitop", "p_{T, bottom} [GeV/c]", 50, 0, 500);
  eta_bottom = book<TH1F>("eta_bottom_antitop", "#eta_{bottom}", 100, -5, 5);
  phi_bottom = book<TH1F>("phi_bottom_antitop", "#phi_{bottom}", 100, -3.14, 3.14);

  Pt_antibottom  = book<TH1F>("Pt_antibottom_top", "p_{T, bottom} [GeV/c]", 50, 0, 500);
  eta_antibottom = book<TH1F>("eta_antibottom_top", "#eta_{bottom}", 100, -5, 5);
  phi_antibottom = book<TH1F>("phi_antibottom_top", "#phi_{bottom}", 100, -3.14, 3.14);


  h_tstargen = ctx.get_handle<TStarGen>("tstargen");
}


void TStarGenHists::fill(const uhh2::Event & e){
  //do not fill histograms if ttbargen information has not been filled
  if(!e.is_valid(h_tstargen)){
    return;
  }
  const char *channels[11] = {"ee","#mu#mu", "#tau#tau","e#mu", "e#tau", "#mu#tau","e+had", "#mu+had", "#tau+had", "all had", "not found"};
  for(int i=0; i<11; i++){
    DecayChannel->GetXaxis()->SetBinLabel(i+1, channels[i]);
  }

  const auto & tstargen = e.get(h_tstargen);
  
  DecayChannel -> Fill(tstargen.DecayChannel(), e.weight);

  LorentzVector tstar = tstargen.TStar().v4();
  LorentzVector antitstar = tstargen.AntiTStar().v4();
  
  double mtstar_gen = (tstar+antitstar).M();
  double  pttstar_gen = ( tstar + antitstar ).Pt();
  double sh = (e.genparticles->at(0).v4()+ e.genparticles->at(1).v4()).M();

  M_TstarTstar       -> Fill(mtstar_gen, e.weight);
  Pt_TstarTstar      -> Fill(pttstar_gen, e.weight);
  Pt_TstarTstar_Diff -> Fill((tstargen.TStar().v4().Pt() - tstargen.AntiTStar().v4().Pt())/(tstargen.TStar().v4().Pt() + tstargen.AntiTStar().v4().Pt()), e.weight);
  
  M_TstarTstar_vs_eta_Tstar     -> Fill(mtstar_gen, tstargen.TStar().eta(), e.weight);
  M_TstarTstar_vs_eta_antiTstar -> Fill(mtstar_gen, tstargen.AntiTStar().eta(), e.weight);
  
  M_Tstar  -> Fill(tstargen.TStar().v4().M(), e.weight);
  Pt_Tstar -> Fill(tstar.Pt(), e.weight);
  eta_Tstar-> Fill(tstargen.TStar().eta(), e.weight);
  phi_Tstar-> Fill(tstargen.TStar().phi(), e.weight);

  M_antiTstar  -> Fill(tstargen.AntiTStar().v4().M(), e.weight);
  Pt_antiTstar -> Fill(antitstar.Pt(), e.weight);
  eta_antiTstar-> Fill(tstargen.AntiTStar().eta(), e.weight);
  phi_antiTstar-> Fill(tstargen.AntiTStar().phi(), e.weight);

  M_TstarAntiTstar_ratio ->Fill((tstargen.AntiTStar().v4().M()/tstargen.TStar().v4().M())-1, e.weight);
  Pt_TstarAntiTstar_ratio ->Fill((tstargen.AntiTStar().v4().Pt()/tstargen.TStar().v4().Pt())-1, e.weight);
  Pt_gluonAntigluon_ratio  ->Fill((tstargen.gAntiTStar().v4().Pt()/tstargen.gTStar().v4().Pt())-1, e.weight);

  Pt_Tstar_over_M_TstarTstar     -> Fill(tstar.Pt()/mtstar_gen, e.weight);
  Pt_antiTstar_over_M_TstarTstar -> Fill(antitstar.Pt()/mtstar_gen, e.weight);
  Pt_Tstar_over_shat             -> Fill(tstar.Pt()/sh, e.weight);
  Pt_antiTstar_over_shat         -> Fill(antitstar.Pt()/sh, e.weight);

  double difabseta = fabs( tstargen.TStar().eta()) - fabs( tstargen.AntiTStar().eta());
  double difabsphi = fabs(tstargen.TStar().phi() - tstargen.AntiTStar().phi());

  diffabseta -> Fill(difabseta, e.weight);
  diffphi -> Fill(difabsphi, e.weight);
       

  double deltaR_tstar     =  uhh2::deltaR(tstargen.gTStar(), tstargen.tTStar());
  double deltaR_antitstar =  uhh2::deltaR(tstargen.gAntiTStar(), tstargen.tAntiTStar()); 
			
  deltaR_Tstar_decays     -> Fill(deltaR_tstar,e.weight);
  deltaR_antiTstar_decays -> Fill(deltaR_antitstar,e.weight);
   
  M_TstarTstar_vs_deltaR_Tstar     -> Fill(mtstar_gen, deltaR_tstar, e.weight);
  M_TstarTstar_vs_deltaR_antiTstar -> Fill(mtstar_gen, deltaR_antitstar, e.weight);
  shat_vs_deltaR_Tstar             -> Fill(sh, deltaR_tstar, e.weight);
  shat_vs_deltaR_antiTstar         -> Fill(sh, deltaR_antitstar, e.weight);
  shat_vs_Pt_Tstar                 -> Fill(sh, tstar.Pt(), e.weight);
  shat_vs_Pt_antiTstar             -> Fill(sh, antitstar.Pt(), e.weight);

  LorentzVector gluon = tstargen.gTStar().v4();
  Pt_gluon  -> Fill(gluon.Pt(), e.weight);
  eta_gluon -> Fill(tstargen.gTStar().eta(), e.weight);
  phi_gluon -> Fill(tstargen.gTStar().phi(), e.weight);
  
  LorentzVector antigluon = tstargen.gAntiTStar().v4();
  Pt_antigluon  -> Fill(antigluon.Pt(), e.weight);
  eta_antigluon -> Fill(tstargen.gAntiTStar().eta(), e.weight);
  phi_antigluon -> Fill(tstargen.gAntiTStar().phi(), e.weight);

  deltaPhi_gluon_antigluon   -> Fill(deltaPhi_calc(tstargen.gTStar().phi(), tstargen.gAntiTStar().phi()), e.weight);
  deltaPhi_top_antitop       -> Fill(deltaPhi_calc(tstargen.tTStar().phi(), tstargen.tAntiTStar().phi()), e.weight);
  deltaPhi_gluon_top         -> Fill(deltaPhi_calc(tstargen.gTStar().phi(), tstargen.tTStar().phi()), e.weight);
  deltaPhi_antigluon_antitop -> Fill(deltaPhi_calc(tstargen.gAntiTStar().phi(), tstargen.tAntiTStar().phi()), e.weight);
  deltaPhi_antigluon_top     -> Fill(deltaPhi_calc(tstargen.gAntiTStar().phi(), tstargen.tTStar().phi()), e.weight);
  deltaPhi_gluon_antitop     -> Fill(deltaPhi_calc(tstargen.gTStar().phi(), tstargen.tAntiTStar().phi()), e.weight);

  deltaR_gluon_antigluon   -> Fill(deltaR(tstargen.gTStar(), tstargen.gAntiTStar()), e.weight);
  deltaR_top_antitop       -> Fill(deltaR(tstargen.tTStar(), tstargen.tAntiTStar()), e.weight);
  deltaR_gluon_top         -> Fill(deltaR(tstargen.gTStar(), tstargen.tTStar()), e.weight);
  deltaR_antigluon_antitop -> Fill(deltaR(tstargen.gAntiTStar(), tstargen.tAntiTStar()), e.weight);
  deltaR_antigluon_top     -> Fill(deltaR(tstargen.gAntiTStar(), tstargen.tTStar()), e.weight);
  deltaR_gluon_antitop     -> Fill(deltaR(tstargen.gTStar(), tstargen.tAntiTStar()), e.weight);

  Diff_deltaR_leptonic     ->Fill(deltaR(tstargen.gAntiTStar(), tstargen.tTStar())-deltaR(tstargen.gAntiTStar(), tstargen.tAntiTStar()), e.weight);
  Diff_deltaR_hadronic     ->Fill(deltaR(tstargen.gTStar(), tstargen.tAntiTStar())-deltaR(tstargen.gTStar(), tstargen.tTStar()), e.weight);

  LorentzVector top = tstargen.tTStar().v4();
  double deltaR_top = std::max(std::max( uhh2::deltaR(tstargen.wPlusDecay1(), tstargen.wPlusDecay2()),
					 uhh2::deltaR(tstargen.wPlusDecay1(), tstargen.bTStar())), 
			       uhh2::deltaR(tstargen.wPlusDecay2(), tstargen.bTStar() ));  

  M_top   -> Fill(tstargen.tTStar().v4().M(), e.weight);
  Pt_top  -> Fill(tstargen.tTStar().pt(), e.weight);
  eta_top -> Fill(tstargen.tTStar().eta(), e.weight);
  phi_top -> Fill(tstargen.tTStar().phi(), e.weight);



  deltaR_top_decays     -> Fill(deltaR_top,e.weight);
 
  double mtstar_reco = (top+gluon).M();
  M_Tstar_reco->Fill( mtstar_reco,e.weight);
  

  LorentzVector antitop = tstargen.tAntiTStar().v4();
  double deltaR_antitop = std::max(std::max( uhh2::deltaR(tstargen.wMinusDecay1(), tstargen.wMinusDecay2()),
					     uhh2::deltaR(tstargen.wMinusDecay1(), tstargen.bAntiTStar())), 
				   uhh2::deltaR(tstargen.wMinusDecay2(), tstargen.bAntiTStar() ));  

  M_antitop   -> Fill(tstargen.tAntiTStar().v4().M(), e.weight);
  Pt_antitop  -> Fill(tstargen.tAntiTStar().pt(), e.weight);  
  eta_antitop -> Fill(tstargen.tAntiTStar().eta(), e.weight); 
  phi_antitop -> Fill(tstargen.tAntiTStar().phi(), e.weight);
  deltaR_antitop_decays -> Fill(deltaR_antitop,e.weight);
  
  M_gluon   -> Fill(tstargen.gTStar().v4().M(), e.weight);
  Pt_gluon  -> Fill(tstargen.gTStar().pt(), e.weight);
  eta_gluon -> Fill(tstargen.gTStar().eta(), e.weight);
  phi_gluon -> Fill(tstargen.gTStar().phi(), e.weight);

  M_antigluon   -> Fill(tstargen.gAntiTStar().v4().M(), e.weight);
  Pt_antigluon  -> Fill(tstargen.gAntiTStar().pt(), e.weight);  
  eta_antigluon -> Fill(tstargen.gAntiTStar().eta(), e.weight); 
  phi_antigluon -> Fill(tstargen.gAntiTStar().phi(), e.weight);

  double mantitstar_reco = (antitop+antigluon).M();
  M_antiTstar_reco->Fill( mantitstar_reco,e.weight);
 
  Pt_Top_vs_deltaR_top         -> Fill(tstargen.tTStar().pt(), deltaR_top, e.weight);
  Pt_antiTop_vs_deltaR_antitop -> Fill(tstargen.tAntiTStar().pt(), deltaR_antitop, e.weight);

  Diff_Pt_gluon_top            -> Fill((tstargen.gTStar().pt()-tstargen.tTStar().pt())/(tstargen.gTStar().pt()+tstargen.tTStar().pt()), e.weight);
  Diff_Pt_antigluon_antitop    -> Fill((tstargen.gAntiTStar().pt()-tstargen.tAntiTStar().pt())/(tstargen.gAntiTStar().pt()+tstargen.tAntiTStar().pt()), e.weight);

  Diff_Pt_gluon_btop           -> Fill((tstargen.gTStar().pt()-tstargen.bTStar().pt())/(tstargen.gTStar().pt()+tstargen.bTStar().pt()), e.weight);
  Diff_Pt_antigluon_bantitop   -> Fill((tstargen.gAntiTStar().pt()-tstargen.bAntiTStar().pt())/(tstargen.gAntiTStar().pt()+tstargen.bAntiTStar().pt()), e.weight);

  Diff_Pt_gluon_WplusDecay1    -> Fill((tstargen.gTStar().pt()-tstargen.wPlusDecay1().pt())/(tstargen.gTStar().pt()+tstargen.wPlusDecay1().pt()), e.weight);
  Diff_Pt_gluon_WplusDecay2    -> Fill((tstargen.gTStar().pt()-tstargen.wPlusDecay2().pt())/(tstargen.gTStar().pt()+tstargen.wPlusDecay2().pt()), e.weight);

  Diff_Pt_antigluon_WminusDecay1    -> Fill((tstargen.gTStar().pt()-tstargen.wMinusDecay1().pt())/(tstargen.gTStar().pt()+tstargen.wMinusDecay1().pt()), e.weight);
  Diff_Pt_antigluon_WminusDecay2    -> Fill((tstargen.gTStar().pt()-tstargen.wMinusDecay2().pt())/(tstargen.gTStar().pt()+tstargen.wMinusDecay2().pt()), e.weight);

  Diff_Pt_antigluon_gluon      -> Fill((tstargen.gAntiTStar().pt()-tstargen.gTStar().pt())/(tstargen.gAntiTStar().pt()+tstargen.gTStar().pt()), e.weight);
  Diff_Pt_bantitop_btop        -> Fill((tstargen.bAntiTStar().pt()-tstargen.bTStar().pt())/(tstargen.bAntiTStar().pt()+tstargen.bTStar().pt()), e.weight);

  Pt_bottom  -> Fill(tstargen.bTStar().pt(), e.weight);
  eta_bottom -> Fill(tstargen.bTStar().eta(), e.weight);
  phi_bottom -> Fill(tstargen.bTStar().phi(), e.weight);

  Pt_antibottom  -> Fill(tstargen.bAntiTStar().pt(), e.weight);
  eta_antibottom -> Fill(tstargen.bAntiTStar().eta(), e.weight);
  phi_antibottom -> Fill(tstargen.bAntiTStar().phi(), e.weight);

  LorentzVector wPlusDecay1 = tstargen.wPlusDecay1().v4();
  LorentzVector wPlusDecay2 = tstargen.wPlusDecay2().v4();
  LorentzVector bTStar = tstargen.bTStar().v4();
  
  double mttstar_reco = (wPlusDecay1+wPlusDecay2+bTStar).M();
  
  M_tTstar_reco->Fill( mttstar_reco,e.weight);
  
  LorentzVector wMinusDecay1 = tstargen.wMinusDecay1().v4();
  LorentzVector wMinusDecay2 = tstargen.wMinusDecay2().v4();
  LorentzVector bAntiTStar = tstargen.bAntiTStar().v4();
  
  double mtantitstar_reco = (wMinusDecay1+wMinusDecay2+bAntiTStar).M();
  
  M_tAntiTstar_reco->Fill( mtantitstar_reco,e.weight);

}
