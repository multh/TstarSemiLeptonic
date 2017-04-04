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

    Discriminator                       = book<TH1F>("Discriminator",name,50,min,500);
    Discriminator_2                     = book<TH1F>("Discriminator_2",name,30,0,10);
    Discriminator_3                     = book<TH1F>("Discriminator_3",name,50,0,30); 
    Discriminator_4                     = book<TH1F>("Discriminator_4",name,50,0,2); 
   
    M_TstarhadTstarlep_rec              = book<TH1F>( "M_TstarhadTstarlep_rec", "M_{T*_{had}T*_{lep}}^{rec} [GeV/c^{2}]", 50, 0, 5000 ) ;
    M_TstarAntiTstar_gen                = book<TH1F>( "M_TstarAntiTstar_gen", "M_{T*#bar{T*}}^{gen} [GeV/c^{2}]", 70, 0, 5000 ) ;

    DeltaPhi_TstarhadTstarlep           = book<TH1F>("DeltaPhi_TstarhadTstarlep","#Delta #phi T*_{had}T*_{lep}",40,0,7);
    DeltaPhi_TstarAntiTstar_gen         = book<TH1F>("DeltaPhi_TstarAntiTstar_gen","#Delta #phi T*#bar{T*}",40,0,7);

    DeltaPhi_TophadGluonhad             = book<TH1F>("DeltaPhi_TophadGluonhad", "#Delta #phi Top_{had} Gluon_{had}",20,0,3.5);
    DeltaPhi_ToplepGluonlep             = book<TH1F>("DeltaPhi_ToplepGluonlep", "#Delta #phi Top_{lep} Gluon_{lep}",20,0,3.5);
    DeltaPhi_TophadToplep               = book<TH1F>("DeltaPhi_TophadToplep", "#Delta #phi Top_{had} Top_{lep}",20,0,3.5);
    DeltaPhi_GluonGluon                 = book<TH1F>("DeltaPhi_GluonhadGluonlep","#Delta #phi Gluon_{had} Gluon_{lep}",20,0,3.5);
    
    DeltaPhi_TopGluon_gen               = book<TH1F>("DeltaPhi_TopGluon_gen", "#Delta #phi Top_{T*} Gluon_{T*}",20,0,3.5);
    DeltaPhi_AntiTopAntiGluon_gen       = book<TH1F>("DeltaPhi_AntiTopAntiGluon_gen", "#Delta #phi Top_{#bar{T*}} Gluon_{#bar{T*}}",20,0,3.5);
    DeltaPhi_TopAntiTop_gen             = book<TH1F>("DeltaPhi_TophadToplep_gen", "#Delta #phi Top_{T*} Top_{#bar{T*}}",20,0,3.5);
    DeltaPhi_GluonGluon_gen             = book<TH1F>("DeltaPhi_GluonhadGluonlep_gen","#Delta #phi Gluon_{T*} Gluon_{#bar{T*}}",20,0,3.5);

    DeltaEta_TstarhadTstarlep       = book<TH1F>("DeltaEta_TstarhadTstarlep","#Delta #eta T*_{had}T*_{lep}",20,0,3.5);
    DeltaEta_TstarAntiTstar_gen         = book<TH1F>("DeltaEta_TstarAntiTstar_gen","#Delta #eta T*#bar{T*}",20,0,3.5);

    DeltaEta_TophadGluonhad             = book<TH1F>("DeltaEta_TophadGluonhad", "#Delta #eta Top_{had} Gluon_{had}",20,0,3.5);
    DeltaEta_ToplepGluonlep             = book<TH1F>("DeltaEta_ToplepGluonlep", "#Delta #eta Top_{lep} Gluon_{lep}",20,0,3.5);
    DeltaEta_TophadToplep               = book<TH1F>("DeltaEta_TophadToplep", "#Delta #eta Top_{had} Top_{lep}",20,0,3.5);
    DeltaEta_GluonGluon                 = book<TH1F>("DeltaEta_GluonhadGluonlep","#Delta #eta Gluon_{had} Gluon_{lep}",20,0,3.5);
  
    DeltaEta_TopGluon_gen               = book<TH1F>("DeltaEta_TopGluon_gen", "#Delta #eta Top_{T*} Gluon_{T*}",20,0,3.5);
    DeltaEta_AntiTopAntiGluon_gen       = book<TH1F>("DeltaEta_AntiTopAntiGluon_gen", "#Delta #eta Top_{#bar{T*}} Gluon_{#bar{T*}}",20,0,3.5);
    DeltaEta_TopAntiTop_gen             = book<TH1F>("DeltaEta_TopAntiTop_gen", "#Delta #eta Top_{T*} Top_{#bar{T*}}",20,0,3.5);
    DeltaEta_GluonGluon_gen             = book<TH1F>("DeltaEta_GluonGluon_gen","#Delta #eta Gluon_{T*} Gluon_{#bar{T*}}",20,0,3.5);


    M_TstarAntiTstar_gen_vs_M_TstarhadTstarlep_rec = book<TH2F>("M_TstarAntiTstar_gen_vs_M_TstarhadTstarlep_rec", "M_{T#bar{T}, gen} vs M_{T_{had}T_{lep}, rec}",100,0,5000,100,0,5000);
    M_Tstar_gen_vs_M_Tstar_rec                     = book<TH2F>("M_Tstar_gen_vs_M_Tstar_rec","M_{T*, gen} vs M_{T*, rec}",100,0,2000,100,100,2000);
    M_Top_gen_vs_M_Top_rec                         = book<TH2F>("M_Top_gen_vs_M_Top_rec","M_{top, gen} vs M_{top, rec}",50,0,300,50,0,300);
 
    M_Tstarlep_rec                      = book<TH1F>( "M_Tstarlep_rec", "M_{T*}^{lep} [GeV/c^{2}]", 30, 0, 2000 ) ;
    M_Tstarhad_rec                      = book<TH1F>( "M_Tstarhad_rec", "M_{T*}^{had} [GeV/c^{2}]", 30, 0, 2000 ) ;
    
    M_Tstar_comb                        = book<TH1F>( "M_Tstar_comb", "M_{T*}^{comb} [GeV/c^{2}]", 30, 0, 2000);

    M_TstarhadTstarlep_Diff             = book<TH1F>("M_TstarhadTstarlep_Diff", "M_{T,had}^{rec} - M_{T,lep}^{rec}", 7, -200,200) ;
    M_TstarhadTstarlep_Diff_rel         = book<TH1F>("M_TstarhadTstarlep_Diff_rel", "(M_{T,had}^{rec} - M_{T,lep}^{rec})/M_{T, med}",28 , -0.4,0.6) ;


    Pt_Tstarlep_rec                     = book<TH1F>( "Pt_Tstarlep_rec", "P_{T, T*}^{lep} [GeV/c]", 40, 0, 1200 ) ;
    Pt_Tstarhad_rec                     = book<TH1F>( "Pt_Tstarhad_rec", "P_{T, T*}^{had} [GeV/c]", 40, 0, 1200 ) ;
    
    Pt_TstarhadTstarlep_rec             = book<TH1F>( "Pt_TstarhadTstarlep_rec", "P_{T,T*_{had}T*_{lep}}^{rec} [GeV/c]", 70, 0, 1200 ) ;
    Pt_TstarAntiTstar_gen               = book<TH1F>( "Pt_TstarAntiTstar_gen", "P_{T,T*#bar{T*}}^{gen} [GeV/c]", 70, 0, 1200 ) ;
      
    M_TstarAntiTstar_resolution         = book<TH1F>("M_TstarAntiTstar_resolution", "(M_{T*#bar{T*}}^{gen} - M_{T*#bar{T*}}^{rec})/M_{T*#bar{T*}}^{gen}", 100, -5,5) ;
    M_Tstar_resolution                  = book<TH1F>("M_Tstar_resolution", "(M_{T*}^{gen} - M_{T*}^{rec})/M_{T*}^{gen}",100,-5,5);

    M_toplep_rec                        = book<TH1F>("M_toplep", "M_{top}^{lep} [GeV/c^{2}]",20, 50,350);
    M_tophad_rec                        = book<TH1F>("M_tophad", "M_{top}^{had} [GeV/c^{2}]",20, 50,350);

    Pt_toplep_rec                       = book<TH1F>("Pt_toplep", "P_{T, top}^{lep} [GeV/c]",70, 0,1000);
    Pt_tophad_rec                       = book<TH1F>("Pt_tophad", "P_{T, top}^{had} [GeV/c]",70, 0,1000);
     
    CSV_Lep_Signal                      = book<TH1F>("CSVLep_Signal","CSV Lep Signal",10,0,1);
    CSV_Had_Signal                      = book<TH1F>("CSVHad_Signal","CSV Had Signal",10,0,1);

    CSV_Lep_Background                  = book<TH1F>("CSVLep_Background","CSV Lep Background",10,0,1);
    CSV_Had_Background                  = book<TH1F>("CSVHad_Background","CSV Had Background",10,0,1);


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

 
  //Discriminators#####################################################################################
  Discriminator->Fill(hyp->discriminator(m_discriminator_name) ,weight);
  Discriminator_2->Fill(hyp->discriminator(m_discriminator_name) ,weight);
  Discriminator_3->Fill(hyp->discriminator(m_discriminator_name) ,weight);
  Discriminator_4->Fill(hyp->discriminator(m_discriminator_name) ,weight);

  //##################################################################################################



  //Delta Phi and Delta Eta ###########################################################################

  double m_deltaPhi = 0;
  if ((hyp->Tstarhad_v4().phi()-hyp->Tstarlep_v4().phi())<0) m_deltaPhi = hyp->Tstarlep_v4().phi()-hyp->Tstarhad_v4().phi();
  else{ m_deltaPhi = hyp->Tstarhad_v4().phi()-hyp->Tstarlep_v4().phi();}


  DeltaPhi_TstarhadTstarlep ->Fill(m_deltaPhi,weight);
  DeltaPhi_TophadGluonhad   ->Fill(TMath::Abs(hyp->tophad_v4().phi())-TMath::Abs(hyp->gluonhad_v4().phi()),weight);
  DeltaPhi_ToplepGluonlep   ->Fill(TMath::Abs(hyp->toplep_v4().phi())-TMath::Abs(hyp->gluonlep_v4().phi()),weight);
  DeltaPhi_TophadToplep     ->Fill(TMath::Abs(hyp->tophad_v4().phi())-TMath::Abs(hyp->toplep_v4().phi()),weight);
  DeltaPhi_GluonGluon       ->Fill(TMath::Abs(hyp->gluonhad_v4().phi())-TMath::Abs(hyp->gluonlep_v4().phi()),weight);

  DeltaEta_TstarhadTstarlep ->Fill(hyp->Tstarhad_v4().eta()-hyp->Tstarlep_v4().eta(),weight);
  DeltaEta_TophadGluonhad   ->Fill(hyp->tophad_v4().eta()-hyp->gluonhad_v4().eta(),weight);
  DeltaEta_ToplepGluonlep   ->Fill(hyp->toplep_v4().eta()-hyp->gluonlep_v4().eta(),weight);
  DeltaEta_TophadToplep     ->Fill(hyp->tophad_v4().eta()-hyp->toplep_v4().eta(),weight);
  DeltaEta_GluonGluon       ->Fill(hyp->gluonhad_v4().eta()-hyp->gluonlep_v4().eta(),weight);

  //####################################################################################################


  // Reconstructed Mass and Pt ########################################################################
  double m_toplep=0;
  double m_tophad=0;
  double m_Tstarhad=0;
  double m_Tstarlep=0;
  double m_TstarDiff=0;
  double m_Tstarmed_rec = 0;
  double m_Tstar_diff_rel=0;
  double m_TstarAntiTstar_gen = 0;
  double m_TstarhadTstarlep_rec = 0;


                                                                   
  if(hyp->Tstarlep_v4().isTimelike()) m_Tstarlep = hyp->Tstarlep_v4().M();
  else {m_Tstarlep = sqrt( -(hyp->Tstarlep_v4()).mass2());}
  if(hyp->Tstarhad_v4().isTimelike()) m_Tstarhad = hyp->Tstarhad_v4().M();
  else {m_Tstarhad = sqrt( -(hyp->Tstarhad_v4()).mass2());}
  
  if(hyp->toplep_v4().isTimelike()) m_toplep = hyp->toplep_v4().M();
  if(hyp->tophad_v4().isTimelike()) m_tophad = hyp->tophad_v4().M();

  if( (hyp->Tstarhad_v4()+hyp->Tstarlep_v4()).isTimelike() )
    m_TstarhadTstarlep_rec = (hyp->Tstarhad_v4()+hyp->Tstarlep_v4()).M();
  else{
    m_TstarhadTstarlep_rec = sqrt( -(hyp->Tstarlep_v4()+hyp->Tstarhad_v4()).mass2());
  }


  M_TstarhadTstarlep_rec  ->Fill(m_TstarhadTstarlep_rec, weight);

  M_toplep_rec            ->Fill(m_toplep,weight);
  M_tophad_rec            ->Fill(m_tophad,weight);

 
  m_Tstarmed_rec    = (m_Tstarhad + m_Tstarlep)/2;
  m_TstarDiff       = (m_Tstarhad - m_Tstarlep);
  m_Tstar_diff_rel  = m_TstarDiff/m_Tstarmed_rec;

  M_Tstarlep_rec    ->Fill(m_Tstarlep,weight);
  M_Tstarhad_rec    ->Fill(m_Tstarhad,weight);

  M_Tstar_comb      ->Fill(m_Tstarmed_rec,weight);

  M_TstarhadTstarlep_Diff     ->Fill(m_TstarDiff, weight);
  M_TstarhadTstarlep_Diff_rel ->Fill(m_Tstar_diff_rel, weight);

 
  double pt_TstarAntiTstar_rec = (hyp->Tstarhad_v4()+hyp->Tstarlep_v4()).Pt();
  double pt_TstarAntiTstar_gen = 0;

  Pt_TstarhadTstarlep_rec ->Fill( pt_TstarAntiTstar_rec, weight);
  Pt_Tstarlep_rec         ->Fill( hyp->Tstarlep_v4().Pt(),weight);
  Pt_Tstarhad_rec         ->Fill( hyp->Tstarhad_v4().Pt(),weight);
  Pt_toplep_rec           ->Fill( hyp->toplep_v4().Pt(),weight);
  Pt_tophad_rec           ->Fill( hyp->tophad_v4().Pt(),weight);
  //######################################################################################################


  //With  Generator Level Particles ###################################################################### 
  if(e.is_valid(h_tstargen)){
    const auto & tstargen = e.get(h_tstargen);
    
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



    M_TstarAntiTstar_gen_vs_M_TstarhadTstarlep_rec ->Fill(m_TstarAntiTstar_gen,m_TstarhadTstarlep_rec,weight);
    M_Tstar_gen_vs_M_Tstar_rec                     ->Fill(m_Tstar_gen, m_Tstarlep, weight);
    M_Top_gen_vs_M_Top_rec                         ->Fill(m_Top_gen, m_toplep, weight);

    Pt_TstarAntiTstar_gen                          ->Fill(pt_TstarAntiTstar_gen, weight);
  
    //Delta Phi and Delta Eta ##################################################################################

    DeltaPhi_TstarAntiTstar_gen    ->Fill( deltaPhi(tstargen.TStar(),tstargen.AntiTStar()),weight);
    DeltaPhi_TopGluon_gen          ->Fill(deltaPhi(tstargen.tTStar(),tstargen.gTStar()),weight);
    DeltaPhi_AntiTopAntiGluon_gen  ->Fill(deltaPhi(tstargen.tAntiTStar(),tstargen.gAntiTStar()),weight);
    DeltaPhi_TopAntiTop_gen        ->Fill(deltaPhi(tstargen.tTStar(),tstargen.tAntiTStar()),weight);
    DeltaPhi_GluonGluon_gen        ->Fill(deltaPhi(tstargen.gTStar(),tstargen.gAntiTStar()),weight);

    DeltaEta_TstarAntiTstar_gen    ->Fill( tstargen.TStar().eta()-tstargen.AntiTStar().eta(),weight);
    DeltaEta_TopGluon_gen          ->Fill(tstargen.tTStar().eta()-tstargen.gTStar().eta(),weight);
    DeltaEta_AntiTopAntiGluon_gen  ->Fill(tstargen.tAntiTStar().eta()-tstargen.gAntiTStar().eta(),weight);
    DeltaEta_TopAntiTop_gen        ->Fill(tstargen.tTStar().eta()-tstargen.tAntiTStar().eta(),weight);
    DeltaEta_GluonGluon_gen        ->Fill(tstargen.gTStar().eta()-tstargen.gAntiTStar().eta(),weight);
    //#########################################################################################################


    //CSV-Variable for b-Tag Discriminator in Correct Match ###################################################
 
   /*  
   if(hyp->blep_jets().size()!=0 && hyp->bhad_jets().size()!=0){

  double btag_Lep_csv = hyp->blep_jets().at(0).btag_combinedSecondaryVertex();
   if(deltaR(hyp->blep_v4(),tstargen.BLep())<0.4){
     CSV_Lep_Signal->Fill(btag_Lep_csv, weight);
   }
   else{
     CSV_Lep_Background->Fill(btag_Lep_csv, weight);
   }
   
   double btag_Had_csv = hyp->bhad_jets().at(0).btag_combinedSecondaryVertex();
   if(deltaR(hyp->bhad_v4(),tstargen.BHad())<0.4){
     CSV_Had_Signal->Fill(btag_Had_csv, weight);
   }
   else{
     CSV_Had_Background->Fill(btag_Had_csv, weight);
   }
   }
   //###########################################################################################################
   */
  }
  
 
}
 
