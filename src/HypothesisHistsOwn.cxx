#include "UHH2/TstarSemiLeptonic/include/HypothesisHistsOwn.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include <cmath>
#include "UHH2/common/include/Utils.h"
#include "UHH2/core/include/Event.h"
#include "Math/Vector4Dfwd.h"

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

HypothesisHistsOwn::HypothesisHistsOwn(uhh2::Context & ctx, const std::string & dirname, const std::string & hyps_name, const std::string & discriminator_name ): Hists(ctx, dirname){

  TString name = discriminator_name;
    double min=0;
    if(discriminator_name=="Chi2"){
      name = "#Chi^{2}";
    }
    else{
      name += " discriminator";
    }

    if( discriminator_name=="CorrectMatch"){
      min=0;

    }
    if( discriminator_name=="TopDRMC"){
      min=0;
     
    }

    Discriminator_sum                   = book<TH1F>("Discriminator_sum",name, 100,min,100);
    Discriminator_1                     = book<TH1F>("Discriminator_1", name + "_tlep", 100,min,100);
    Discriminator_2                     = book<TH1F>("Discriminator_2", name + "_thad", 100,min,100);
    Discriminator_3                     = book<TH1F>("Discriminator_3", name + "_MTstar_rel", 100,min,100);
    Discriminator_4                     = book<TH1F>("Discriminator_4", name + "_delta_Phi", 100,min,100); 
    Discriminator_5                     = book<TH1F>("Discriminator_5", name, 12,-0.5,11.5); 
   
    M_TstarhadTstarlep_rec              = book<TH1F>( "M_TstarhadTstarlep_rec", "M_{T*_{had}T*_{lep}}^{rec} [GeV/c^{2}]", 50, 0, 5000 ) ;
    M_TstarAntiTstar_gen                = book<TH1F>( "M_TstarAntiTstar_gen", "M_{T*#bar{T*}}^{gen} [GeV/c^{2}]", 70, 0, 5000 ) ;
    Pt_TstarTstar                       = book<TH1F>( "Pt_TstarTstar", "P_{T,T_{lep}^{*}T_{had}^{*}} [GeV/c]", 10, -0.5, 500.5 ) ;
    Pt_TstarTstar_diff                  = book<TH1F>( "Pt_TstarTstar_Diff", "p_{T} (T_{lep} - T_{had})/(T_{lep}+T_{had})", 20, -1, 1);

    Pt_Tstar_lep_over_M_TstarTstar      = book<TH1F>("Pt_Tstar_lep_over_M_TstarTstar", "P_{T,T_{lep}*}/M_{T*T*}", 100, 0, 1 ) ;
    Pt_Tstar_had_over_M_TstarTstar      = book<TH1F>("Pt_Tstar_had_over_M_TstarTstar", "P_{T,T_{had}*}/M_{T*T*}", 100, 0, 1 ) ;

    DeltaPhi_TstarhadTstarlep           = book<TH1F>("DeltaPhi_TstarhadTstarlep","#Delta #phi T*_{had}T*_{lep}",40,2,4);
    DeltaPhi_TstarAntiTstar_gen         = book<TH1F>("DeltaPhi_TstarAntiTstar_gen","#Delta #phi T*#bar{T*}",40,2,4);

    DeltaPhi_TophadGluonhad             = book<TH1F>("DeltaPhi_TophadGluonhad", "#Delta #phi Top_{had} Gluon_{had}",40,0,6);
    DeltaPhi_ToplepGluonlep             = book<TH1F>("DeltaPhi_ToplepGluonlep", "#Delta #phi Top_{lep} Gluon_{lep}",40,0,6);
    DeltaPhi_TophadToplep               = book<TH1F>("DeltaPhi_TophadToplep", "#Delta #phi Top_{had} Top_{lep}",40,0,6);
    DeltaPhi_GluonGluon                 = book<TH1F>("DeltaPhi_GluonhadGluonlep","#Delta #phi Gluon_{had} Gluon_{lep}",40,0,6);
    
    DeltaPhi_TopGluon_gen               = book<TH1F>("DeltaPhi_TopGluon_gen", "#Delta #phi Top_{T*} Gluon_{T*}",40,0,6);
    DeltaPhi_AntiTopAntiGluon_gen       = book<TH1F>("DeltaPhi_AntiTopAntiGluon_gen", "#Delta #phi Top_{#bar{T*}} Gluon_{#bar{T*}}",40,0,6);
    DeltaPhi_TopAntiTop_gen             = book<TH1F>("DeltaPhi_TophadToplep_gen", "#Delta #phi Top_{T*} Top_{#bar{T*}}",40,0,6);
    DeltaPhi_GluonGluon_gen             = book<TH1F>("DeltaPhi_GluonhadGluonlep_gen","#Delta #phi Gluon_{T*} Gluon_{#bar{T*}}",40,0,6);

    DeltaEta_TstarhadTstarlep           = book<TH1F>("DeltaEta_TstarhadTstarlep","#Delta #eta T*_{had}T*_{lep}",20,0,3.5);
    DeltaEta_TstarAntiTstar_gen         = book<TH1F>("DeltaEta_TstarAntiTstar_gen","#Delta #eta T*#bar{T*}",20,0,3.5);

    DeltaEta_TophadGluonhad             = book<TH1F>("DeltaEta_TophadGluonhad", "#Delta #eta Top_{had} Gluon_{had}",20,0,3.5);
    DeltaEta_ToplepGluonlep             = book<TH1F>("DeltaEta_ToplepGluonlep", "#Delta #eta Top_{lep} Gluon_{lep}",20,0,3.5);
    DeltaEta_TophadToplep               = book<TH1F>("DeltaEta_TophadToplep", "#Delta #eta Top_{had} Top_{lep}",20,0,3.5);
    DeltaEta_GluonGluon                 = book<TH1F>("DeltaEta_GluonhadGluonlep","#Delta #eta Gluon_{had} Gluon_{lep}",20,0,3.5);
  
    DeltaEta_TopGluon_gen               = book<TH1F>("DeltaEta_TopGluon_gen", "#Delta #eta Top_{T*} Gluon_{T*}",20,0,3.5);
    DeltaEta_AntiTopAntiGluon_gen       = book<TH1F>("DeltaEta_AntiTopAntiGluon_gen", "#Delta #eta Top_{#bar{T*}} Gluon_{#bar{T*}}",20,0,3.5);
    DeltaEta_TopAntiTop_gen             = book<TH1F>("DeltaEta_TopAntiTop_gen", "#Delta #eta Top_{T*} Top_{#bar{T*}}",20,0,3.5);
    DeltaEta_GluonGluon_gen             = book<TH1F>("DeltaEta_GluonGluon_gen","#Delta #eta Gluon_{T*} Gluon_{#bar{T*}}",20,0,3.5);

    DeltaR_GluonGluon                   = book<TH1F>("DeltaR_GluonGluon", "#Delta R gluon_{lep} gluon_{had}", 20, 0, 5);
    DeltaR_TopTop                       = book<TH1F>("DeltaR_TopTop",     "#Delta R top_{lep} top_{had}", 20, 0, 5);
    DeltaR_GluonTop_lep                 = book<TH1F>("DeltaR_GluonTop_lep", "#Delta R gluon_{lep} top_{lep}", 20, 0, 5);
    DeltaR_GluonTop_had                 = book<TH1F>("DeltaR_GluonTop_had", "#Delta R gluon_{had} top_{had}", 20, 0, 5);
    DeltaR_GluonHad_TopLep              = book<TH1F>("DeltaR_GluonHad_TopLep", "#Delta R gluon_{had} top_{lep}", 20, 0, 5);
    DeltaR_GluonLep_TopHad              = book<TH1F>("DeltaR_GluonLep_TopHad", "#Delta R gluon_{lep} top_{had}", 20, 0, 5);
    DeltaR_GluonHad_BHad                = book<TH1F>("DeltaR_GluonHad_BHad", "#Delta R gluon_{had} b_{had}", 20,0,5);
    DeltaR_GluonLep_BLep                = book<TH1F>("DeltaR_GluonLep_BLep", "#Delta R gluon_{lep} b_{lep}", 20,0,5);

    deltaR_tophad_decays                = book<TH1F>( "deltaR_tophad_decays", "#DeltaR(top had decay prod.)",20,0,5);
    deltaR_toplep_decays                = book<TH1F>( "deltaR_toplep_decays", "#DeltaR(top lep decay prod.)",20,0,5);  

 

    //    Pt_over_M_Tstarlep                  = book<TH1F>("Pt_over_M_Tstarlep", "p_{T}/M_{T*, lep}", 20,0,1);
    //    Pt_over_M_Tstarhad                  = book<TH1F>("Pt_over_M_Tstarhad", "p_{T}/M_{T*, had}", 20,0,1);
    
    M_TstarAntiTstar_gen_vs_M_TstarhadTstarlep_rec = book<TH2F>("M_TstarAntiTstar_gen_vs_M_TstarhadTstarlep_rec", "M_{T#bar{T}, gen} vs M_{T_{had}T_{lep}, rec}",100,0,5000,100,0,5000);
    M_Tstar_gen_vs_M_Tstar_rec                     = book<TH2F>("M_Tstar_gen_vs_M_Tstar_rec","M_{T*, gen} vs M_{T*, rec}",100,0,2000,100,100,2000);
    M_Top_gen_vs_M_Top_rec                         = book<TH2F>("M_Top_gen_vs_M_Top_rec","M_{top, gen} vs M_{top, rec}",50,0,300,50,0,300);
 
    M_Tstarlep_rec                      = book<TH1F>( "M_Tstarlep_rec", "M_{T*}^{lep} [GeV/c^{2}]", 35, 0, 2000 ) ;
    M_Tstarhad_rec                      = book<TH1F>( "M_Tstarhad_rec", "M_{T*}^{had} [GeV/c^{2}]", 35, 0, 2000 ) ;
    
    M_Tstar_comb                        = book<TH1F>( "M_Tstar_comb", "M_{T*}^{comb} [GeV/c^{2}]", 35, 0, 2000);

    M_TstarhadTstarlep_Diff             = book<TH1F>("M_TstarhadTstarlep_Diff", "M_{T,had}^{rec} - M_{T,lep}^{rec}", 7, -200,200) ;
    M_TstarhadTstarlep_Diff_rel         = book<TH1F>("M_TstarhadTstarlep_Diff_rel", "(M_{T,had}^{rec} - M_{T,lep}^{rec})/M_{T, med}",28 , -0.4,0.6) ;


    Pt_Tstarlep_rec                     = book<TH1F>( "Pt_Tstarlep_rec", "P_{T, T*}^{lep} [GeV/c]", 40, 0, 1200 ) ;
    Pt_Tstarhad_rec                     = book<TH1F>( "Pt_Tstarhad_rec", "P_{T, T*}^{had} [GeV/c]", 40, 0, 1200 ) ;
    
    Pt_TstarhadTstarlep_rec             = book<TH1F>( "Pt_TstarhadTstarlep_rec", "P_{T,T*_{had}T*_{lep}}^{rec} [GeV/c]", 70, 0, 1200 ) ;
    Pt_TstarAntiTstar_gen               = book<TH1F>( "Pt_TstarAntiTstar_gen", "P_{T,T*#bar{T*}}^{gen} [GeV/c]", 70, 0, 1200 ) ;
      
    M_TstarAntiTstar_resolution         = book<TH1F>("M_TstarAntiTstar_resolution", "(M_{T*#bar{T*}}^{gen} - M_{T*#bar{T*}}^{rec})/M_{T*#bar{T*}}^{gen}", 100, -5,5) ;
    M_Tstar_resolution                  = book<TH1F>("M_Tstar_resolution", "(M_{T*}^{gen} - M_{T*}^{rec})/M_{T*}^{gen}",100,-5,5);

    M_toplep_rec                        = book<TH1F>("M_toplep", "M_{top}^{lep} [GeV/c^{2}]",30, 50,350);
    M_tophad_rec                        = book<TH1F>("M_tophad", "M_{top}^{had} [GeV/c^{2}]",30, 50,350);

    Pt_toplep_rec                       = book<TH1F>("Pt_toplep", "P_{T, top}^{lep} [GeV/c]",70, 0,1000);
    Pt_tophad_rec                       = book<TH1F>("Pt_tophad", "P_{T, top}^{had} [GeV/c]",70, 0,1000);

    Pt_Diff_top                         = book<TH1F>("Pt_Diff_top", "(p_{T, top}^{lep}-p_{T, top}^{had})/p_{T, top}^{lep}", 20, -3, 6);
    Pt_Ratio_top                        = book<TH1F>("Pt_Ratio_top", "p_{T, top}^{lep}/p_{T, top}^{had}", 20, -5,5);

    Pt_Diff_gluon_top_had             = book<TH1F>("Pt_Diff_gluon_top_had", "(p_{T, gluon}^{had}-p_{T, top}^{had})/p_{T, gluon}^{had}", 20, -3, 6);
    Pt_Ratio_gluonhad_tophad            = book<TH1F>("Pt_Ratio_gluonhad_tophad", "p_{T, gluon}^{had}/p_{T, top}^{had}", 20, -5,5);

    Pt_Diff_gluon_top_lep             = book<TH1F>("Pt_Diff_gluon_top_lep", "(p_{T, gluon}^{lep}-p_{T, top}^{lep})/p_{T, gluon}^{lep}", 20, -3, 6);
    Pt_Ratio_gluonlep_toplep            = book<TH1F>("Pt_Ratio_gluonlep_toplep", "p_{T, gluon}^{lep}/p_{T, top}^{lep}", 20, -5,5);

    Number_tophad_jets                  = book<TH1F>("Number of subjets top had", "# subjets top had", 10, 0, 10);
    Number_toplep_jets                  = book<TH1F>("Number of subjets top lep", "# subjets top lep", 10, 0, 10);

    Number_gluonlep_jets                = book<TH1F>("Number of subjets gluon lep", "# subjets gluon lep", 10, 0, 10);
    Number_gluonhad_jets                = book<TH1F>("Number of subjets gluon had", "# subjets gluon had", 10, 0, 10);

    Pt_Diff_gluonhad_tophad             = book<TH1F>("Pt_Diff_gluonhad_tophad", "(p_{T}^{gluon, had}-p_{T}^{top, had})/(p_{T}^{gluon, had}+p_{T}^{top, had})", 20, -1.5, 1.5);
    Pt_Diff_gluonlep_toplep             = book<TH1F>("Pt_Diff_gluonlep_toplep", "(p_{T}^{gluon, lep}-p_{T}^{top, lep})/(p_{T}^{gluon, lep}+p_{T}^{top, lep})", 20, -1.5, 1.5);
     
    Pt_Diff_gluonhad_bhad               = book<TH1F>("Pt_Diff_gluonhad_bhad", "(p_{T}^{gluon, had}-p_{T}^{b, had})/(p_{T}^{gluon, had}+p_{T}^{b, had})", 20, -1.5, 1.5);
    Pt_Diff_gluonlep_blep               = book<TH1F>("Pt_Diff_gluonlep_blep", "(p_{T}^{gluon, lep}-p_{T}^{b, lep})/(p_{T}^{gluon, lep}+p_{T}^{b, lep})", 20, -1.5, 1.5);

    Pt_Diff_gluonhad_blep               = book<TH1F>("Pt_Diff_gluonhad_blep", "(p_{T}^{gluon, had}-p_{T}^{b, lep})/(p_{T}^{gluon, had}+p_{T}^{b, lep})", 20, -1.5, 1.5);
    Pt_Diff_gluonlep_bhad               = book<TH1F>("Pt_Diff_gluonlep_bhad", "(p_{T}^{gluon, lep}-p_{T}^{b, had})/(p_{T}^{gluon, lep}+p_{T}^{b, had})", 20, -1.5, 1.5);
 
    Pt_Diff_gluonlep_Wlep               = book<TH1F>("Pt_Diff_gluonlep_Wlep", "(p_{T}^{gluon, lep}-p_{T}^{W, lep})/(p_{T}^{gluon, lep}+p_{T}^{W, lep})", 20, -1.5, 1.5);
 
    Pt_Diff_gluonlep_gluonhad           = book<TH1F>("Pt_Diff_gluonlep_gluonhad", "(p_{T}^{gluon, lep}-p_{T}^{gluon, had})/(p_{T}^{gluon, lep}+p_{T}^{gluon, had})", 20, -1.5, 1.5);
    Pt_Diff_bhad_blep                   = book<TH1F>("Pt_Diff_bhad_blep", "(p_{T}^{b, had}-p_{T}^{b, lep})/(p_{T}^{b, had}+p_{T}^{b, lep})", 20, -1.5, 1.5);

    M_Whad_gen                          = book<TH1F>("M_Whad_gen", "M_{W}^{had} [GeV/c^{2}]",40, 50,150);
    M_Wlep_rec                          = book<TH1F>("M_Wlep_rec", "M_{W}^{lep} [GeV/c^{2}]",40, 50,150);
    M_toplep_Wlep                       = book<TH1F>("M_toplep_Wlep","M_{top}^{lep} [GeV/c^{2}]",20,50,350);
    M_Tstarlep_Wlep                     = book<TH1F>( "M_Tstarlep_Wlep", "M_{T*}^{lep} [GeV/c^{2}]", 30, 0, 2000 );
    M_Tstar_comb_Wlep                   = book<TH1F>( "M_Tstar_comb_Wlep", "M_{T*}^{comb} [GeV/c^{2}]", 30, 0, 2000);

    DeltaR_gluon_lep                    = book<TH1F>("DeltaR_gluon_lep", "#Delta R gluon_{lep}",20,0,3.5);
    DeltaR_gluon_had                    = book<TH1F>("DeltaR_gluon_had", "#Delta R gluon_{had}",20,0,3.5);

    DeltaR_blep                         = book<TH1F>("DeltaR_blep", "#Delta R b_{lep}",20,0,3.5);
    DeltaR_bhad                         = book<TH1F>("DeltaR_bhad", "#Delta R b_{had}",20,0,3.5);

    DeltaR_bhad_gluon                   = book<TH1F>("DeltaR_bhad_gluon", "#Delta R b_{had} gluon had",20,0,3.5);
    DeltaR_bhad_gluonlep                = book<TH1F>("DletaR_bhad_gluonlep", "Delta R b_{had} gluon lep", 20,0,3.5);

    DeltaR_Lepton                       = book<TH1F>("DeltaR_Lepton","#Delta R Lepton",20,0,3.5);
    DeltaR_Neutrino                     = book<TH1F>("DeltaR_Neutrino","#Delta R Neutrino",20,0,3.5);

    CSV_bLep                            = book<TH1F>("CSV_bLep","CSV b_{Lep}",20,0,1);
    CSV_bHad                            = book<TH1F>("CSV_bHad","CSV b_{Had}",20,0,1);

    CSV_gluonLep                        = book<TH1F>("CSV_gluonLep","CSV g_{Lep}",20,0,1);
    CSV_gluonHad                        = book<TH1F>("CSV_gluonHad","CSV g_{Had}",20,0,1);
    CSV_gluonLep_2                      = book<TH1F>("CSV_gluonLep_2","CSV g_{Lep, 2}",20,0,1);
    CSV_gluonHad_2                      = book<TH1F>("CSV_gluonHad_2","CSV g_{Had, 2}",20,0,1);

    CSV_vs_dR_blep                      = book<TH2F>("CSV_vs_dR_blep", "CSV_vs_dR_blep", 20,0,1 ,20, 0, 3.5);
    CSV_vs_dR_bhad                      = book<TH2F>("CSV_vs_dR_bhad", "CSV_vs_dR_bhad", 20,0,1,20, 0, 3.5);

    CSV_Lep_Background                  = book<TH1F>("CSVLep_Background","CSV Lep Background",20,0,1);
    CSV_Had_Background                  = book<TH1F>("CSVHad_Background","CSV Had Background",20,0,1);

    M_TstarLep_bMatch_gluonSwitch       = book<TH1F>("M_TstarLep_bMatch_gluonSwitch", "Tstar lep bMatch_gluonSwitch", 35, 0,2000);
    M_TstarHad_bMatch_gluonSwitch       = book<TH1F>("M_TstarHad_bMatch_gluonSwitch", "Tstar had bMatch_gluonSwitch", 35, 0,2000);

    M_TstarLep_bhad_gluonlepSwitch      = book<TH1F>("M_TstarLep_bhad_gluonlepSwitch", "M_TstarLep_bhad_gluonlepSwitch", 35, 0,2000);
    M_TstarHad_bhad_gluonlepSwitch      = book<TH1F>("M_TstarHad_bhad_gluonlepSwitch", "M_TstarHad_bhad_gluonlepSwitch", 35, 0,2000);

    M_TstarLep_bhad_gluonhadSwitch      = book<TH1F>("M_TstarLep_bhad_gluonhadSwitch", "M_TstarLep_bhad_gluonhadSwitch", 35, 0,2000);
    M_TstarHad_bhad_gluonhadSwitch      = book<TH1F>("M_TstarHad_bhad_gluonhadSwitch", "M_TstarHad_bhad_gluonhadSwitch", 35, 0,2000);

    M_TstarLep_Match_All                = book<TH1F>("M_TstarLep_Match_All", "M_TstarLep_Match_All", 35, 0,2000);
    M_TstarHad_Match_All                = book<TH1F>("M_TstarHad_Match_All", "M_TstarHad_Match_All", 35, 0,2000);

    M_TstarLep_Match_Non                = book<TH1F>("M_TstarLep_Match_Non", "M_TstarLep_Match_Non", 35, 0,2000);
    M_TstarHad_Match_Non                = book<TH1F>("M_TstarHad_Match_Non", "M_TstarHad_Match_Non", 35, 0,2000);

    h_hyps = ctx.get_handle<std::vector<TstarReconstructionHypothesis>>(hyps_name);
    h_tstargen = ctx.get_handle<TStarGen>("tstargen");
    m_discriminator_name = discriminator_name;

    auto dataset_type = ctx.get("dataset_type");
    is_data = dataset_type == "DATA";
}


void HypothesisHistsOwn::fill(const uhh2::Event & e){
  std::vector<TstarReconstructionHypothesis> hyps = e.get(h_hyps);
  const TstarReconstructionHypothesis* hyp = get_best_hypothesis( hyps, m_discriminator_name );



  double weight = e.weight;

  double m_toplep=0;
  double m_tophad=0;

  double m_Tstarhad=0;
  double m_Tstarlep=0;
    double m_TstarDiff=0;
    double m_Tstarmed_rec = 0;
    double m_Tstar_diff_rel=0;

  //Selection for Matching Analysis
    //With  Generator Level Particles ###################################################################### 

    /*
    bool fill_hist = false;

    if(e.is_valid(h_tstargen)){
     const auto & tstargen = e.get(h_tstargen);
     auto dec = tstargen.DecayChannel();
     if(dec == TStarGen::e_muhad){
       if(deltaR(tstargen.BHad(), hyp->bhad_v4())<0.4){
	 fill_hist = true;
       }
     }
    }
    
    if(fill_hist){ 
    */
    if(hyp->toplep_v4().isTimelike()) m_toplep = hyp->toplep_v4().M();
    else{m_toplep =sqrt( -(hyp->toplep_v4()).mass2());}
    if(hyp->tophad_v4().isTimelike()) m_tophad = hyp->tophad_v4().M();
    else{m_tophad =sqrt( -(hyp->tophad_v4()).mass2());}
    
    if(hyp->Tstarlep_v4().isTimelike()) m_Tstarlep = hyp->Tstarlep_v4().M();
    else {m_Tstarlep = sqrt( -(hyp->Tstarlep_v4()).mass2());}
    if(hyp->Tstarhad_v4().isTimelike()) m_Tstarhad = hyp->Tstarhad_v4().M();
    else {m_Tstarhad = sqrt( -(hyp->Tstarhad_v4()).mass2());}
    
    m_Tstarmed_rec    = (m_Tstarhad + m_Tstarlep);
    m_TstarDiff       = (m_Tstarhad - m_Tstarlep);
    m_Tstar_diff_rel  = m_TstarDiff/m_Tstarmed_rec;

    //  if(deltaR(hyp->gluonhad_v4(), hyp->gluonlep_v4())>1.75){
     
    //Discriminators#####################################################################################

    Discriminator_sum->Fill(hyp->discriminator(m_discriminator_name) ,weight);

   if(m_discriminator_name=="Chi2"){
    Discriminator_1->Fill(hyp->discriminator(m_discriminator_name + "_tlep") ,weight);
    Discriminator_2->Fill(hyp->discriminator(m_discriminator_name + "_thad") ,weight);
    Discriminator_3->Fill(hyp->discriminator(m_discriminator_name + "_MTstar_rel") ,weight);
    Discriminator_4->Fill(hyp->discriminator(m_discriminator_name + "_deltaPhi") ,weight);
   }

    const char *match_flow[12] = {"matched", "neutrino", "lep gluon jets","had gluon jets", "charged lepton","lep top jets", "had top jets", "had gluon size","lep gluon size", "had top size", "lep top size", "decay channel"};
    for(int i=0; i<12; i++){
      Discriminator_5->GetXaxis()->SetBinLabel(i+1, match_flow[i]);
    }
    Discriminator_5->Fill(hyp->Match_Flow() ,weight);
    
    //##################################################################################################
    double  pttstar = (hyp->Tstarlep_v4() + hyp->Tstarhad_v4()).Pt();

    Pt_TstarTstar                    ->Fill(pttstar, weight);
    Pt_TstarTstar_diff               ->Fill((hyp->Tstarlep_v4().Pt()-hyp->Tstarhad_v4().Pt())/(hyp->Tstarlep_v4().Pt()+hyp->Tstarhad_v4().Pt()), weight);
    Pt_Tstar_lep_over_M_TstarTstar   ->Fill(hyp->Tstarlep_v4().Pt()/(hyp->Tstarlep_v4() + hyp->Tstarhad_v4()).M(), weight);
    Pt_Tstar_had_over_M_TstarTstar   ->Fill(hyp->Tstarhad_v4().Pt()/(hyp->Tstarlep_v4() + hyp->Tstarhad_v4()).M(), weight);

    //Delta Phi and Delta Eta ###########################################################################
    
    double m_deltaPhi = 0;
    if ((hyp->Tstarhad_v4().phi()-hyp->Tstarlep_v4().phi())<0) m_deltaPhi = hyp->Tstarlep_v4().phi()-hyp->Tstarhad_v4().phi();
    else{ m_deltaPhi = hyp->Tstarhad_v4().phi()-hyp->Tstarlep_v4().phi();}

    double m_deltaPhi_gluon = 0;
    if ((hyp->gluonhad_v4().phi()-hyp->gluonlep_v4().phi())<0) m_deltaPhi_gluon = hyp->gluonlep_v4().phi()-hyp->gluonhad_v4().phi();
    else{ m_deltaPhi_gluon = hyp->gluonhad_v4().phi()-hyp->gluonlep_v4().phi();}
    
    DeltaPhi_TstarhadTstarlep ->Fill(m_deltaPhi,weight);
    DeltaPhi_TophadGluonhad   ->Fill(deltaPhi_calc(hyp->tophad_v4().phi(), hyp->gluonhad_v4().phi()),weight);
    DeltaPhi_ToplepGluonlep   ->Fill(deltaPhi_calc(hyp->toplep_v4().phi(), hyp->gluonlep_v4().phi()),weight);
    DeltaPhi_TophadToplep     ->Fill(deltaPhi_calc(hyp->tophad_v4().phi(), hyp->toplep_v4().phi()),weight);
    DeltaPhi_GluonGluon       ->Fill(m_deltaPhi_gluon, weight);
    
    DeltaEta_TstarhadTstarlep ->Fill(TMath::Abs(hyp->Tstarhad_v4().eta()-hyp->Tstarlep_v4().eta()),weight);
    DeltaEta_TophadGluonhad   ->Fill(TMath::Abs(hyp->tophad_v4().eta()-hyp->gluonhad_v4().eta()),weight);
    DeltaEta_ToplepGluonlep   ->Fill(TMath::Abs(hyp->toplep_v4().eta()-hyp->gluonlep_v4().eta()),weight);
    DeltaEta_TophadToplep     ->Fill(TMath::Abs(hyp->tophad_v4().eta()-hyp->toplep_v4().eta()),weight);
    DeltaEta_GluonGluon       ->Fill(TMath::Abs(hyp->gluonhad_v4().eta()-hyp->gluonlep_v4().eta()),weight);
    
    DeltaR_GluonGluon         ->Fill(deltaR(hyp->gluonhad_v4(), hyp->gluonlep_v4()), weight);
    DeltaR_TopTop             ->Fill(deltaR(hyp->tophad_v4(), hyp->toplep_v4()), weight);
    DeltaR_GluonTop_lep       ->Fill(deltaR(hyp->gluonlep_v4(), hyp->toplep_v4()), weight);
    DeltaR_GluonTop_had       ->Fill(deltaR(hyp->gluonhad_v4(), hyp->tophad_v4()), weight);
    DeltaR_GluonLep_TopHad    ->Fill(deltaR(hyp->gluonlep_v4(), hyp->tophad_v4()), weight);
    DeltaR_GluonHad_TopLep    ->Fill(deltaR(hyp->gluonhad_v4(), hyp->toplep_v4()), weight);
    DeltaR_GluonHad_BHad      ->Fill(deltaR(hyp->gluonhad_v4(), hyp->bhad_v4()), weight);
    DeltaR_GluonLep_BLep      ->Fill(deltaR(hyp->gluonlep_v4(), hyp->blep_v4()), weight);

    double deltaR_toplep = 0;

    if(hyp->toplep_jets().size() == 2){
      deltaR_toplep =  uhh2::deltaR(hyp->toplep_jets().at(0), hyp->toplep_jets().at(1));
    }
    else if(hyp->toplep_jets().size() == 3){
      deltaR_toplep = std::max(std::max(uhh2::deltaR(hyp->toplep_jets().at(0), hyp->toplep_jets().at(1)),
					     uhh2::deltaR(hyp->toplep_jets().at(0), hyp->toplep_jets().at(2))), 
				   uhh2::deltaR(hyp->toplep_jets().at(1), hyp->toplep_jets().at(2))); 
    }

    deltaR_toplep_decays -> Fill(deltaR_toplep,e.weight);

    double deltaR_tophad = 0;

    if(hyp->tophad_jets().size() == 2){
      deltaR_tophad =  uhh2::deltaR(hyp->tophad_jets().at(0), hyp->tophad_jets().at(1));
    }
    else if(hyp->tophad_jets().size() == 3){
      deltaR_tophad = std::max(std::max(uhh2::deltaR(hyp->tophad_jets().at(0), hyp->tophad_jets().at(1)),
					     uhh2::deltaR(hyp->tophad_jets().at(0), hyp->tophad_jets().at(2))), 
				   uhh2::deltaR(hyp->tophad_jets().at(1), hyp->tophad_jets().at(2))); 
    }

    deltaR_tophad_decays -> Fill(deltaR_tophad,e.weight);

  
    //####################################################################################################
    
    
    // Reconstructed Mass and Pt ########################################################################
    double m_TstarAntiTstar_gen = 0;
    double m_TstarhadTstarlep_rec = 0;
    double m_Wlep_rec=0;
    
    int n_tophad_jets = 0;
    int n_toplep_jets = 0;
    
    int n_gluonlep_jets = 0;
    int n_gluonhad_jets = 0;
    
    
    n_tophad_jets = hyp->tophad_jets().size();
    n_toplep_jets = hyp->toplep_jets().size();
    
    
    n_gluonhad_jets = hyp->gluonhad_jets().size();
    n_gluonlep_jets = hyp->gluonlep_jets().size();
    
    /*      
    n_gluonhad_jets = hyp->Gluon_Had_num();
    n_gluonlep_jets = hyp->Gluon_Lep_num();
    */

    Number_tophad_jets  ->Fill(n_tophad_jets, weight);
    Number_toplep_jets  ->Fill(n_toplep_jets, weight);
    
    Number_gluonhad_jets  ->Fill(n_gluonhad_jets, weight);
    Number_gluonlep_jets  ->Fill(n_gluonlep_jets, weight);
    
    
    if( (hyp->Tstarhad_v4()+hyp->Tstarlep_v4()).isTimelike() )
      m_TstarhadTstarlep_rec = (hyp->Tstarhad_v4()+hyp->Tstarlep_v4()).M();
    else{
      m_TstarhadTstarlep_rec = sqrt( -(hyp->Tstarlep_v4()+hyp->Tstarhad_v4()).mass2());
    }
    
    if( (hyp->neutrino_v4()+hyp->lepton().v4()).isTimelike() )
      m_Wlep_rec = (hyp->neutrino_v4()+hyp->lepton().v4()).M();
    else{
      m_Wlep_rec = sqrt( -(hyp->neutrino_v4()+hyp->lepton().v4()).mass2());
    }
    
    
    M_TstarhadTstarlep_rec  ->Fill(m_TstarhadTstarlep_rec, weight);
    
    M_toplep_rec            ->Fill(m_toplep,weight);
    M_tophad_rec            ->Fill(m_tophad,weight);
    

    M_Wlep_rec              ->Fill(m_Wlep_rec,weight);
    
    if(m_Wlep_rec < 90){
      M_toplep_Wlep         ->Fill(m_toplep, weight);
      M_Tstarlep_Wlep       ->Fill(m_Tstarlep, weight);
      M_Tstar_comb_Wlep     ->Fill(m_Tstarmed_rec,weight);
    }
    
   
    M_Tstarlep_rec    ->Fill(m_Tstarlep,weight);
    M_Tstarhad_rec    ->Fill(m_Tstarhad,weight);
    
    M_Tstar_comb      ->Fill(m_Tstarmed_rec/2,weight);
    
    M_TstarhadTstarlep_Diff     ->Fill(m_TstarDiff, weight);
    M_TstarhadTstarlep_Diff_rel ->Fill(m_Tstar_diff_rel, weight);
    
    
    double pt_TstarAntiTstar_rec = (hyp->Tstarhad_v4()+hyp->Tstarlep_v4()).Pt();
    double pt_TstarAntiTstar_gen = 0;
    
    Pt_TstarhadTstarlep_rec ->Fill( pt_TstarAntiTstar_rec, weight);
    Pt_Tstarlep_rec         ->Fill( hyp->Tstarlep_v4().Pt(),weight);
    Pt_Tstarhad_rec         ->Fill( hyp->Tstarhad_v4().Pt(),weight);
    Pt_toplep_rec           ->Fill( hyp->toplep_v4().Pt(),weight);
    Pt_tophad_rec           ->Fill( hyp->tophad_v4().Pt(),weight);
    
    Pt_Diff_top             ->Fill( (hyp->toplep_v4().Pt()-hyp->tophad_v4().Pt())/(hyp->toplep_v4().Pt()), weight);
    Pt_Ratio_top            ->Fill( hyp->toplep_v4().Pt()/hyp->tophad_v4().Pt(), weight);

    Pt_Diff_gluon_top_had ->Fill( (hyp->gluonhad_v4().Pt()-hyp->tophad_v4().Pt())/(hyp->gluonhad_v4().Pt()), weight);
    Pt_Ratio_gluonhad_tophad->Fill( hyp->gluonhad_v4().Pt()/hyp->tophad_v4().Pt(), weight);

    Pt_Diff_gluon_top_lep ->Fill( (hyp->gluonlep_v4().Pt()-hyp->toplep_v4().Pt())/(hyp->gluonlep_v4().Pt()), weight);
    Pt_Ratio_gluonlep_toplep->Fill( hyp->gluonlep_v4().Pt()/hyp->toplep_v4().Pt(), weight);

    Pt_Diff_gluonhad_tophad ->Fill( (hyp->gluonhad_v4().Pt()-hyp->tophad_v4().Pt())/(hyp->gluonhad_v4().Pt()+hyp->tophad_v4().Pt()), weight);
    Pt_Diff_gluonlep_toplep ->Fill( (hyp->gluonlep_v4().Pt()-hyp->toplep_v4().Pt())/(hyp->gluonlep_v4().Pt()+hyp->toplep_v4().Pt()), weight);
    
    Pt_Diff_gluonhad_bhad ->Fill( (hyp->gluonhad_v4().Pt()-hyp->bhad_v4().Pt())/(hyp->gluonhad_v4().Pt()+hyp->bhad_v4().Pt()), weight);
    Pt_Diff_gluonlep_blep ->Fill( (hyp->gluonlep_v4().Pt()-hyp->blep_v4().Pt())/(hyp->gluonlep_v4().Pt()+hyp->blep_v4().Pt()), weight);

    Pt_Diff_gluonhad_blep ->Fill( (hyp->gluonhad_v4().Pt()-hyp->blep_v4().Pt())/(hyp->gluonhad_v4().Pt()+hyp->blep_v4().Pt()), weight);
    Pt_Diff_gluonlep_bhad ->Fill( (hyp->gluonlep_v4().Pt()-hyp->bhad_v4().Pt())/(hyp->gluonlep_v4().Pt()+hyp->bhad_v4().Pt()), weight);
    
    Pt_Diff_gluonlep_Wlep ->Fill( (hyp->gluonlep_v4().Pt()-hyp->wlep_v4().Pt())/(hyp->gluonlep_v4().Pt()+hyp->wlep_v4().Pt()), weight);
  
    Pt_Diff_gluonlep_gluonhad ->Fill((hyp->gluonlep_v4().Pt()-hyp->gluonhad_v4().Pt())/(hyp->gluonlep_v4().Pt()+hyp->gluonhad_v4().Pt()), weight);
    Pt_Diff_bhad_blep         ->Fill((hyp->bhad_v4().Pt()-hyp->blep_v4().Pt())/(hyp->bhad_v4().Pt()+hyp->blep_v4().Pt()), weight);
    /*
    cout<<"bLep Jets Size: "<<hyp->blep_jets().size()<<endl;
    cout<<"bHad Jets Size: "<<hyp->bhad_jets().size()<<endl;
    cout<<"gluonLep Jets Size: "<<hyp->gluonlep_jets().size()<<endl;
    cout<<"gluonHad Jets Size: "<<hyp->gluonhad_jets().size()<<endl;
    */
    CSV_bLep               ->Fill(hyp->blep_jets().at(0).btag_combinedSecondaryVertex(), weight);
    CSV_bHad               ->Fill(hyp->bhad_jets().at(0).btag_combinedSecondaryVertex(), weight);

    CSV_gluonLep           ->Fill(hyp->gluonlep_jets().at(0).btag_combinedSecondaryVertex(), weight);
    CSV_gluonHad           ->Fill(hyp->gluonhad_jets().at(0).btag_combinedSecondaryVertex(), weight);

    if(hyp->gluonhad_jets().size()>1 ){
    CSV_gluonHad_2           ->Fill(hyp->gluonhad_jets().at(1).btag_combinedSecondaryVertex(), weight);
    }
    if(hyp->gluonlep_jets().size()>1 ){
    CSV_gluonLep_2           ->Fill(hyp->gluonlep_jets().at(1).btag_combinedSecondaryVertex(), weight);
    }

    //######################################################################################################
    
    
    //With  Generator Level Particles ###################################################################### 
    if(e.is_valid(h_tstargen)){
      const auto & tstargen = e.get(h_tstargen);
      auto dec = tstargen.DecayChannel();
      if(dec == TStarGen::e_muhad){
	
	
	double m_Top_gen       = tstargen.tTStar().v4().M();
	double m_Tstar_gen     = tstargen.TStar().v4().M();
	double m_Tstar_rec     = 0;
	
	if (deltaR(hyp->Tstarlep_v4(),tstargen.TStar())<0.4){
	  m_Tstar_rec =  hyp->Tstarlep_v4().M();      
	}
	else{
	  m_Tstar_rec =  hyp->Tstarhad_v4().M(); 
	}
	
	m_TstarAntiTstar_gen   = (tstargen.TStar().v4() + tstargen.AntiTStar().v4()).M();
	pt_TstarAntiTstar_gen  = (tstargen.TStar().v4() + tstargen.AntiTStar().v4()).Pt();
	
	M_TstarAntiTstar_gen                           ->Fill(m_TstarAntiTstar_gen, weight);
	M_TstarAntiTstar_resolution                    ->Fill((m_TstarAntiTstar_gen-m_TstarhadTstarlep_rec)/m_TstarAntiTstar_gen, weight);
	
	M_Tstar_resolution -> Fill((m_Tstar_gen-m_Tstar_rec)/m_Tstar_gen, weight);
	
	M_Whad_gen              ->Fill((tstargen.Q1().v4() + tstargen.Q2().v4()).M(), weight);
	
	M_TstarAntiTstar_gen_vs_M_TstarhadTstarlep_rec ->Fill(m_TstarAntiTstar_gen,m_TstarhadTstarlep_rec,weight);
	M_Tstar_gen_vs_M_Tstar_rec                     ->Fill(m_Tstar_gen, m_Tstarlep, weight);
	M_Top_gen_vs_M_Top_rec                         ->Fill(m_Top_gen, m_toplep, weight);
	
	Pt_TstarAntiTstar_gen                          ->Fill(pt_TstarAntiTstar_gen, weight);
	
	//Delta Phi and Delta Eta ##################################################################################
	
	DeltaPhi_TstarAntiTstar_gen    ->Fill( deltaPhi_calc(tstargen.TStar().phi(),tstargen.AntiTStar().phi()),weight);
	DeltaPhi_TopGluon_gen          ->Fill(deltaPhi_calc(tstargen.tTStar().phi(),tstargen.gTStar().phi()),weight);
	DeltaPhi_AntiTopAntiGluon_gen  ->Fill(deltaPhi_calc(tstargen.tAntiTStar().phi(),tstargen.gAntiTStar().phi()),weight);
	DeltaPhi_TopAntiTop_gen        ->Fill(deltaPhi_calc(tstargen.tTStar().phi(),tstargen.tAntiTStar().phi()),weight);
	DeltaPhi_GluonGluon_gen        ->Fill(deltaPhi_calc(tstargen.gTStar().phi(),tstargen.gAntiTStar().phi()),weight);
	
	DeltaEta_TstarAntiTstar_gen    ->Fill( tstargen.TStar().eta()-tstargen.AntiTStar().eta(),weight);
	DeltaEta_TopGluon_gen          ->Fill(tstargen.tTStar().eta()-tstargen.gTStar().eta(),weight);
	DeltaEta_AntiTopAntiGluon_gen  ->Fill(tstargen.tAntiTStar().eta()-tstargen.gAntiTStar().eta(),weight);
	DeltaEta_TopAntiTop_gen        ->Fill(tstargen.tTStar().eta()-tstargen.tAntiTStar().eta(),weight);
	DeltaEta_GluonGluon_gen        ->Fill(tstargen.gTStar().eta()-tstargen.gAntiTStar().eta(),weight);
	
	DeltaR_gluon_lep               ->Fill(deltaR(tstargen.GluonLep(), hyp->gluonlep_v4()), weight);
	DeltaR_gluon_had               ->Fill(deltaR(tstargen.GluonHad(), hyp->gluonhad_v4()), weight);
	
	DeltaR_blep                    ->Fill(deltaR(tstargen.BLep(), hyp->blep_v4()), weight);
	DeltaR_bhad                    ->Fill(deltaR(tstargen.BHad(), hyp->bhad_v4()), weight);

	DeltaR_bhad_gluon              ->Fill(deltaR(tstargen.BHad(), hyp->gluonhad_v4()), weight);
	DeltaR_bhad_gluonlep           ->Fill(deltaR(tstargen.BHad(), hyp->gluonlep_v4()), weight);

	DeltaR_Lepton                  ->Fill(deltaR(tstargen.ChargedLepton(), hyp->lepton().v4()),weight);
	DeltaR_Neutrino                ->Fill(deltaR(tstargen.Neutrino(), hyp->neutrino_v4()),weight);

	CSV_vs_dR_blep           ->Fill(hyp->blep_jets().at(0).btag_combinedSecondaryVertex(), deltaR(tstargen.BLep(), hyp->blep_v4()), weight);
        CSV_vs_dR_bhad           ->Fill(hyp->bhad_jets().at(0).btag_combinedSecondaryVertex(), deltaR(tstargen.BHad(), hyp->bhad_v4()), weight);
	//#########################################################################################################

	// Matching contributions to mass histograms

	if(deltaR(tstargen.GluonLep(), hyp->gluonhad_v4())<0.4){
	  M_TstarLep_bMatch_gluonSwitch -> Fill(m_Tstarlep,weight);
	  M_TstarHad_bMatch_gluonSwitch -> Fill(m_Tstarhad,weight);
	}
	
	else if(deltaR(tstargen.BLep(), hyp->gluonlep_v4())<0.4){
	  M_TstarLep_bhad_gluonlepSwitch -> Fill(m_Tstarlep,weight);
	  M_TstarHad_bhad_gluonlepSwitch -> Fill(m_Tstarhad,weight);
	}
	
	else if(deltaR(tstargen.BLep(), hyp->gluonhad_v4())<0.4){
	  M_TstarLep_bhad_gluonhadSwitch -> Fill(m_Tstarlep,weight);
	  M_TstarHad_bhad_gluonhadSwitch -> Fill(m_Tstarhad,weight);
	}

	else if(deltaR(tstargen.BLep(),hyp->blep_v4())<0.4 && deltaR(tstargen.GluonLep(), hyp->gluonlep_v4())<0.4 && deltaR(tstargen.GluonHad(), hyp->gluonhad_v4())<0.4){
	  M_TstarLep_Match_All -> Fill(m_Tstarlep,weight);
	  M_TstarHad_Match_All -> Fill(m_Tstarhad,weight);
	}	
	else if(deltaR(tstargen.BLep(),hyp->blep_v4())>0.4 && deltaR(tstargen.GluonLep(), hyp->gluonlep_v4())>0.4 && deltaR(tstargen.GluonHad(), hyp->gluonhad_v4())>0.4){
	  M_TstarLep_Match_Non -> Fill(m_Tstarlep,weight);
	  M_TstarHad_Match_Non -> Fill(m_Tstarhad,weight);
	}
      }
    }
    //   } //Cut of Matching
}

