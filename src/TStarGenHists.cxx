#include "UHH2/TstarSemiLeptonic/include/TStarGenHists.h"
#include "UHH2/common/include/Utils.h"
#include "TH1F.h"
#include "TH2F.h"
#include <iostream>

using namespace uhh2;
using namespace std;

TStarGenHists::TStarGenHists(uhh2::Context & ctx, const std::string & dirname): Hists(ctx, dirname){

  M_TstarTstar  = book<TH1F>( "M_TstarTstar", "M_{T^{*}#bar{T}^{*}} [GeV/c^{2}]", 200, 0, 6000 ) ;   
  Pt_TstarTstar = book< TH1F>( "Pt_TstarTstar", "P_{T,T^{*}#bar{T^{*}}} [GeV/c]", 10, -0.5, 0.5 ) ;

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
  diffabsphi = book<TH1F>( "diffabsphi", "|#phi_{T^{*}}|-|#phi_{#bar{T}^{*}}|",200,-3.14,3.14);
       
  deltaR_Tstar_decays     = book<TH1F>( "deltaR_tstar_decays", "#DeltaR(T^{*} decay prod.)",200,0,5);
  deltaR_antiTstar_decays = book<TH1F>( "deltaR_antitstar_decays", "#DeltaR(#bar{T}^{*} decay prod.)",200,0,5);  
  
  M_Tstar_reco     = book< TH1F>("M_Tstar_reco", "M_{top+g} [GeV/c^{2}]", 185, 150, 2000) ;
  M_antiTstar_reco = book< TH1F>("M_AntiTstar_reco", "M_{#bar{t}+ g} [GeV/c^{2}]", 185, 150, 2000) ;
  
  Pt_gluon  = book<TH1F>("Pt_gluon_Tstar","P_{T,gluon} [GeV/c]",100,0,1000);
  eta_gluon = book<TH1F>("eta_gluon_Tstar","#eta_{gluon}",100,-5,5);
  phi_gluon = book<TH1F>("phi_gluon_Tstar", "#phi_{gluon}", 100, -3.14, 3.14);

  Pt_antigluon  = book<TH1F>("Pt_gluon_AntiTstar","P_{T,g} [GeV/c]",200,0,2000);
  eta_antigluon = book<TH1F>("eta_gluon_AntiTstar","#eta_{g}",100,-5,5);
  phi_antigluon = book<TH1F>("phi_gluon_AntiTstar", "#phi_{gluon}", 100, -3.14, 3.14);

  M_top   = book<TH1F>("M_top", "M_{t} [GeV/c^{2}]",50,0, 250);
  Pt_top  = book<TH1F>("Pt_top","P_{T,t} [GeV/c]",100,0,1000);
  eta_top = book<TH1F>("eta_top","#eta_{t}",100,-5.19,5.19);
  phi_top = book<TH1F>("phi_top", "#phi_{t}", 100, -3.14, 3.14);

  M_antitop   = book<TH1F>("M_antitop", "M_{#bar{t}} [GeV/c^{2}]", 50, 0, 250);
  Pt_antitop  = book<TH1F>("Pt_antitop","P_{T,#bar{t}} [GeV/c]",100,0,1000);
  eta_antitop = book<TH1F>( "eta_antitop","#eta_{#bar{t}}",100,-5,5);
  phi_antitop = book<TH1F>("phi_antitop", "#phi_{#bar{t}}", 100, -3.14, 3.14);

  deltaR_top_decays     = book<TH1F>( "deltaR_top_decays", "#DeltaR(t decay prod.)",100,0,5);
  deltaR_antitop_decays = book<TH1F>( "deltaR_antitop_decays", "#DeltaR(#bar{t} decay prod.)",100,0,5);  

  M_tTstar_reco     = book< TH1F>("M_tTstar_reco", "M_{W b} [GeV/c^{2}]", 185, 150, 2000) ;
  M_tAntiTstar_reco = book< TH1F>("M_tAntiTstar", "M_{W #bar{b}} [GeV/c^{2}]", 185, 150, 2000) ;

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
  
  const auto & tstargen = e.get(h_tstargen);
  
  LorentzVector tstar = tstargen.TStar().v4();
  LorentzVector antitstar = tstargen.AntiTStar().v4();
  
  double mtstar_gen = (tstar+antitstar).M();
  double  pttstar_gen = ( tstar + antitstar ).Pt();
  double sh = (e.genparticles->at(0).v4()+ e.genparticles->at(1).v4()).M();

  M_TstarTstar  -> Fill(mtstar_gen, e.weight);
  Pt_TstarTstar -> Fill(pttstar_gen, e.weight);

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

  Pt_Tstar_over_M_TstarTstar     -> Fill(tstar.Pt()/mtstar_gen, e.weight);
  Pt_antiTstar_over_M_TstarTstar -> Fill(antitstar.Pt()/mtstar_gen, e.weight);
  Pt_Tstar_over_shat             -> Fill(tstar.Pt()/sh, e.weight);
  Pt_antiTstar_over_shat         -> Fill(antitstar.Pt()/sh, e.weight);

  double difabseta = fabs( tstargen.TStar().eta()) - fabs( tstargen.AntiTStar().eta());
  double difabsphi = fabs( tstargen.TStar().phi()) - fabs( tstargen.AntiTStar().phi());

  diffabseta -> Fill(difabseta, e.weight);
  diffabsphi -> Fill(difabsphi, e.weight);
       

  double deltaR_tstar     =  uhh2::deltaR(tstargen.gTStar(), tstargen.tTStar());
  double deltaR_antitstar =  uhh2::deltaR(tstargen.gAntiTStar(), tstargen.tAntiTStar()); 
			
  deltaR_Tstar_decays     -> Fill(deltaR_tstar,e.weight);
  deltaR_antiTstar_decays -> Fill(deltaR_antitstar,e.weight);
   
  M_TstarTstar_vs_deltaR_Tstar     -> Fill(tstar.Pt(), deltaR_tstar, e.weight);
  M_TstarTstar_vs_deltaR_antiTstar -> Fill(antitstar.Pt(), deltaR_antitstar, e.weight);
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


  LorentzVector top = tstargen.tTStar().v4();
  double deltaR_top = std::max(std::max( uhh2::deltaR(tstargen.wPlusDecay1(), tstargen.wPlusDecay2()),
					 uhh2::deltaR(tstargen.wPlusDecay1(), tstargen.bTStar())), 
			       uhh2::deltaR(tstargen.wPlusDecay2(), tstargen.bTStar() ));  

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

  Pt_antitop  -> Fill(tstargen.tAntiTStar().pt(), e.weight);  
  eta_antitop -> Fill(tstargen.tAntiTStar().eta(), e.weight); 
  phi_antitop -> Fill(tstargen.tAntiTStar().phi(), e.weight);
  deltaR_antitop_decays -> Fill(deltaR_antitop,e.weight);
  
  double mantitstar_reco = (antitop+antigluon).M();
  M_antiTstar_reco->Fill( mantitstar_reco,e.weight);
 
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
