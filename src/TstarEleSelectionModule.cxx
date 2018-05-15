#include <iostream>
#include <memory>

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/common/include/EventHists.h>
#include <UHH2/core/include/Selection.h>

#include <UHH2/common/include/MCWeight.h>
#include <UHH2/common/include/CommonModules.h>
#include <UHH2/common/include/CleaningModules.h>
#include <UHH2/common/include/NSelections.h>
#include <UHH2/common/include/LumiSelection.h>
#include <UHH2/common/include/LuminosityHists.h>
#include <UHH2/common/include/TriggerSelection.h>
#include <UHH2/common/include/JetCorrections.h>
#include <UHH2/common/include/ObjectIdUtils.h>
#include <UHH2/common/include/MuonIds.h>
#include <UHH2/common/include/MuonHists.h>
#include <UHH2/common/include/ElectronIds.h>
#include <UHH2/common/include/ElectronHists.h>
#include <UHH2/common/include/JetIds.h>
#include <UHH2/common/include/JetHists.h>
#include <UHH2/common/include/TopJetIds.h>
#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/TTbarReconstruction.h>
#include <UHH2/common/include/ReconstructionHypothesis.h>
#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>
#include <UHH2/common/include/HypothesisHists.h>
#include <UHH2/common/include/Utils.h>
#include "UHH2/common/include/PrintingModules.h"
#include "UHH2/common/include/TopPtReweight.h"

#include <UHH2/TstarSemiLeptonic/include/HypothesisHistsOwn.h>
#include <UHH2/TstarSemiLeptonic/include/TStarGen.h>
#include <UHH2/TstarSemiLeptonic/include/TStarGenHists.h>
#include "UHH2/TstarSemiLeptonic/include/TstarPDFHists.h"
#include <UHH2/TstarSemiLeptonic/include/TstarSelectionHists.h>
#include <UHH2/TstarSemiLeptonic/include/TstarReconstruction.h>
#include <UHH2/TstarSemiLeptonic/include/TstarReconstructionHypothesis.h>
#include <UHH2/TstarSemiLeptonic/include/TstarReconstructionHypothesisDiscriminators.h>



#include <UHH2/TstarSemiLeptonic/include/TstarSemiLeptonicSelections.h>
#include <UHH2/TstarSemiLeptonic/include/TstarSemiLeptonicUtils.h>

using namespace std;
using namespace uhh2;
using namespace uhh2examples;
//*****************************************************************************************************
//
// Analysis Module for the T*T*->ttbar gg semileptonic analysis
//
//*****************************************************************************************************


class TstarEleSelectionModule : public uhh2::AnalysisModule {
  
public:
  explicit TstarEleSelectionModule(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;
  
private:
  enum lepton { muon, elec };
  lepton channel_;
  
  //Common Modules 
  unique_ptr<CommonModules>               common;      //comes with Muon/Electron cleaner, JetCorrector/Smearer /MClumiweight and mcPileupReweight
  
  //TTbar re-weighting
  unique_ptr<TopPtReweight>               ttbar_reweight;
  //TopTag Flag
  uhh2::Event::Handle<int>                h_flag_toptagevent;
    
  // ************ Cleaner *************************************************************************************************************************
  unique_ptr<TopJetCleaner>               topjet_cleaner;
  // **********************************************************************************************************************************************
  
  // *********** Selections for Analysis *********************************************************************************************************** 
  unique_ptr<Selection>                   b_tag_medium_sel;                     //Require one or more b-tagged jets (Medium WP)
  unique_ptr<Selection>                   b_tag_loose_sel;                      //Require two or more b-tagged jest (Loose WP) 
  unique_ptr<Selection>                   b_tag_tight_sel;                      //Require one or more b-tagged jest (Tight WP) 

  unique_ptr<Selection>                   toptagevt_sel;                        //Top Tag in event?
  unique_ptr<Selection>                   ht_sel;                               //HT Selection for high hadronic part
  //*****************************************************************************************************************************************************
  
  // ************** Reconstruction and matching *************************************************************************************************************
  //Primary lepton
  unique_ptr<AnalysisModule> reco_primlep;
  
  //T*T*  reconstruction
  unique_ptr<AnalysisModule> tstargenprod;    //Generator Level 
  unique_ptr<AnalysisModule> tstar_reco;      //Reco Level
  unique_ptr<AnalysisModule> tstar_ttag_reco; //Reco Level with Top Tag
  
  //T*T* Matching 
  unique_ptr<AnalysisModule> tstar_match;    //Match Gen and Reco 
  unique_ptr<AnalysisModule> tstar_ttag_match;  //Match Gen and Reco with Top-Tag

  //Chi2 Discriminator
  unique_ptr<AnalysisModule> tstar_chi2;
  unique_ptr<AnalysisModule> tstar_ttag_chi2;
    
 //********************************************************************************************************************************************************
    
 // ************Systematics and Scale Factors ****************************************************************************************************************************
  string                                  sys_bTag, sys_PU, sys_muonTrigger, sys_muonID, sys_elecID;
  unique_ptr<AnalysisModule>              sys_scale_variation;

  unique_ptr<AnalysisModule>              SF_muonID, SF_muonTrigger, SF_btag;
  unique_ptr<AnalysisModule>              SF_elecID;

  unique_ptr<BTagMCEfficiencyHists>       BTagEffHists;                      //Important for bTag
  
  // ********************************************************************************************************************************************************     
  
  //****************************** Histogramms **********************************************************************************************************
  // store the Hists collection as member variables
  unique_ptr<Hists> h_input,     h_input_event,     h_input_jet,     h_input_ele,     h_input_muon,     h_input_topjet,     h_input_lumi;
  unique_ptr<Hists> h_cleaner,   h_cleaner_event,   h_cleaner_jet,   h_cleaner_ele,   h_cleaner_muon,   h_cleaner_topjet,   h_cleaner_lumi;
  unique_ptr<Hists> h_btag,      h_btag_event,      h_btag_jet,      h_btag_ele,      h_btag_muon,      h_btag_topjet,      h_btag_lumi;
  unique_ptr<Hists> h_toptagevt, h_toptagevt_event, h_toptagevt_jet, h_toptagevt_ele, h_toptagevt_muon, h_toptagevt_topjet, h_toptagevt_lumi;
  unique_ptr<Hists> h_jet,       h_jet_event,       h_jet_jet,       h_jet_ele,       h_jet_muon,       h_jet_topjet,       h_jet_lumi;
  unique_ptr<Hists> h_ht,        h_ht_event,        h_ht_jet,        h_ht_ele,        h_ht_muon,        h_ht_topjet,        h_ht_lumi;
  unique_ptr<Hists> h_output,    h_output_event,    h_output_jet,    h_output_ele,    h_output_muon,    h_output_topjet,    h_output_lumi;

  unique_ptr<Hists> h_btag_loose, h_btag_medium, h_btag_tight;
  
  
  unique_ptr<Hists> h_tstargenhists;
  
  unique_ptr<Hists> h_matchable,     h_matchable_event,     h_matchable_jet,     h_matchable_ele,     h_matchable_muon,     h_matchable_topjet,     h_matchable_lumi;
  unique_ptr<Hists> h_not_matchable, h_not_matchable_event, h_not_matchable_jet, h_not_matchable_ele, h_not_matchable_muon, h_not_matchable_topjet, h_not_matchable_lumi;
  
  unique_ptr<Hists> h_match_discr,         h_match,         h_match_event,         h_match_jet,         h_match_ele,         h_match_muon,         h_match_topjet,         h_match_lumi;
  unique_ptr<Hists> h_corrmatch_discr,     h_corrmatch,     h_corrmatch_event,     h_corrmatch_jet,     h_corrmatch_ele,     h_corrmatch_muon,     h_corrmatch_topjet,     h_corrmatch_lumi;
  unique_ptr<Hists> h_corrmatch_ttag_discr, h_corrmatch_ttag, h_corrmatch_ttag_event, h_corrmatch_ttag_jet, h_corrmatch_ttag_ele, h_corrmatch_ttag_muon, h_corrmatch_ttag_topjet, h_corrmatch_ttag_lumi;
  unique_ptr<Hists> h_no_corrmatch_discr,  h_no_corrmatch,  h_no_corrmatch_event,  h_no_corrmatch_jet,  h_no_corrmatch_ele,  h_no_corrmatch_muon,  h_no_corrmatch_topjet,  h_no_corrmatch_lumi;
  
  //Chi2 Hists
  unique_ptr<Hists> h_chi2,          h_chi2_event,       h_chi2_jet,       h_chi2_ele,       h_chi2_muon,       h_chi2_topjet,       h_chi2_lumi;
  unique_ptr<Hists> h_no_chi2,       h_no_chi2_event,    h_no_chi2_jet,    h_no_chi2_ele,    h_no_chi2_muon,    h_no_chi2_topjet,    h_no_chi2_lumi;
  unique_ptr<Hists> h_chi2min;
  unique_ptr<Hists> h_no_chi2min;
  unique_ptr<Hists> h_chi2_before;
  unique_ptr<Hists> h_chi2min_ttag;
  unique_ptr<Hists> h_chi2min_ttag_comb;
  //*****************************************************************************************************************************************************  
  //Set IDs
  JetId      Btag_loose;
  JetId      Btag_medium;
  JetId      Btag_tight;
  
  Event::Handle<TStarGen> h_tstargen;
  Event::Handle<vector<TstarReconstructionHypothesis>> h_hyps;
  
  bool is_mc;
  bool debug;
  bool do_scale_variation, do_pdf_variations;
  bool matching, chi2_discr;
  
  std::unique_ptr<Hists>                 h_PDF_variations;

///###########################################################################################################################################################################
};

///********************************************************************************************************************

TstarEleSelectionModule::TstarEleSelectionModule(uhh2::Context& ctx){
  
  std::cout << "Hello World from TstarSelectionModule!" << std::endl;
  
  //********  New IDs for Summer 2016 Dataset ********************************************************
  const TopJetId topjetID = AndId<TopJet>(Type2TopTag(105,220,Type2TopTag::MassType::groomed), Tau32(0.67));
  const TopJetId topjetID_with_bTag = AndId<TopJet>(Type2TopTag(105,220,Type2TopTag::MassType::groomed, Btag_loose), Tau32(0.67));

// ********* Systematics, Scale Variations and MC-Scale Factors *********************************************************************** 
    sys_muonID         = ctx.get("sys_muonID");
    sys_muonTrigger    = ctx.get("sys_muonTrigger");
    sys_bTag           = ctx.get("sys_bTag");
    sys_PU             = ctx.get("sys_PU");
    sys_elecID         = ctx.get("sys_elecID");

    //Scale Variations
    sys_scale_variation.reset(new MCScaleVariation(ctx));
    
 //Muon ID and Triggers
    SF_muonID          .reset(new MCMuonScaleFactor(ctx,"/nfs/dust/cms/user/multh/CMSSW_8_0_26_patch2/src/UHH2/common/data/MuonID_EfficienciesAndSF_average_RunBtoH.root", "MC_NUM_HighPtID_DEN_genTracks_PAR_pt_eta",1, sys_muonID)); 
    SF_muonTrigger     .reset(new MCMuonScaleFactor(ctx,"/nfs/dust/cms/user/multh/CMSSW_8_0_26_patch2/src/UHH2/common/data/MuonTrigger_EfficienciesAndSF_average_RunBtoH.root", "IsoMu50_OR_IsoTkMu50_PtEtaBins",0.5, sys_muonTrigger));

    SF_elecID          .reset(new MCElecScaleFactor(ctx,"/nfs/dust/cms/user/multh/CMSSW_8_0_26_patch2/src/UHH2/common/data/egammaEffi.txt_EGM2D_CutBased_Tight_ID.root",1,"",sys_elecID));

    BTagEffHists       .reset(new BTagMCEfficiencyHists(ctx,"EffHists/BTag",CSVBTag::WP_MEDIUM));
    SF_btag            .reset(new MCBTagScaleFactor(ctx,CSVBTag::WP_MEDIUM,"jets",sys_bTag));  // "mujets","incl","MCBtagEfficienciesAK4","_AK4","BTagCalibration"

// *************************************************************************************************

  //########################## Boolean and Common Module ##########################################################################
    is_mc              = ctx.get("dataset_type") == "MC";
    debug              = false;

    //Get Channel: Muon or Electon
    const std::string& channel = ctx.get("channel", "");
    if     (channel == "muon") channel_ = muon;
    else if(channel == "elec") channel_ = elec;
    else throw std::runtime_error("TstarPreSelectionModule -- undefined argument for 'channel' key in xml file (must be 'muon' or 'elec'): "+channel);

    do_scale_variation = (ctx.get("ScaleVariationMuR") == "up" || ctx.get("ScaleVariationMuR") == "down") || (ctx.get("ScaleVariationMuF") == "up" || ctx.get("ScaleVariationMuF") == "down");
    do_pdf_variations  =  ctx.get("b_PDFUncertainties") == "true";

    //Boolean for Discriminator
    matching = (ctx.get("matching") == "true");
    chi2_discr = (ctx.get("chi2_discr") == "true");

    ///COMMON Modules
    common.reset(new CommonModules());    //comes with Muon/Electron cleaner, JetCorrector/Smearer, MClumiweight and mcPileupReweight
    common->disable_jec();
    common->disable_jersmear();
    common->disable_lumisel();
    common->disable_metfilters();
    common->disable_pvfilter();
    common->disable_jetpfidfilter(); 
    common->init(ctx, sys_PU);
    ////

  //##############################################################################################################

    
// ########################### Jet/TopJet Cleaners  ##############################################################
    
    topjet_cleaner             .reset(new TopJetCleaner(ctx, TopJetId(PtEtaCut(400., 2.4))));
    
    //TTbar re-weightig for missmodelled pT
    //    ttbar_reweight      .reset(new TopPtReweight(ctx, 0.0615, -0.0005, "", "weight_ttbar", true, 0.9910819));  //13 TeV
    ttbar_reweight      .reset(new TopPtReweight(ctx, 0.159,  -0.00141,"", "weight_ttbar", true, 0.9910819));  // 8 TeV values l+jets 
    //

///###############################################################################################################


////############################# EVENT SELECTIONS ###############################################################
   
   ///b-Tag
   //LOOSE WP
   Btag_loose = CSVBTag(CSVBTag::WP_LOOSE);                          //Workingpoint for b-Tag (Loose)  
   b_tag_loose_sel         .reset(new NJetSelection(2,-1, Btag_loose));  

   //MEDIUM WP
   Btag_medium = CSVBTag(CSVBTag::WP_MEDIUM);                          //Workingpoint for b-Tag (Medium)  
   b_tag_medium_sel         .reset(new NJetSelection(1,-1, Btag_medium));  

   //Tight WP
   Btag_tight = CSVBTag(CSVBTag::WP_TIGHT);                          //Workingpoint for b-Tag (Tight)  
   b_tag_tight_sel         .reset(new NJetSelection(1,-1, Btag_tight));  
   ///
   
   ///HT Selection
   ht_sel                    .reset(new HtSelection(500,-1));
   //

   // top-tagging
   toptagevt_sel            .reset(new NTopJetSelection(1, -1, topjetID));
   //   toptagevt_sel            .reset(new NTopJetSelection(1, -1, topjetID_with_bTag));
   h_flag_toptagevent = ctx.declare_event_output<int>("flag_toptagevent");
   ////   
   
 //###############################################################################################################


////############################ T*T* KINEMATICAL RECO ##################################################
  const std::string tstar_gen_label ("tstargen");
  
  //Gen Producer
  tstargenprod     .reset(new TStarGenProducer(ctx, tstar_gen_label, false));

  h_tstargen       = ctx.get_handle<TStarGen>("tstargen");

  // Lepton
  reco_primlep     .reset(new PrimaryLepton(ctx));

  // TStar Reco
  tstar_reco       .reset(new HighMassTstarKinReconstruction(ctx, TstarNeutrinoReconstruction, "TstarReconstruction"));
  tstar_ttag_reco  .reset(new TstarTopTagKinReconstruction(ctx, NeutrinoReconstruction, "TstarReconstruction", topjetID, 1.2));

  // Correct Match
  tstar_match      .reset(new TstarCorrectMatchDiscriminator      (ctx, "TstarReconstruction"));
  tstar_ttag_match .reset(new TstarCorrectMatchDiscriminatorTTAG  (ctx, "TstarReconstruction"));
  
// Chi2
  tstar_chi2       .reset(new TstarChi2Discriminator(ctx, "TstarReconstruction"));
  tstar_ttag_chi2  .reset(new TstarChi2DiscriminatorTTAG(ctx, "TstarReconstruction"));
  
  // Hypothesis Container
  h_hyps = ctx.get_handle<std::vector<TstarReconstructionHypothesis>>("TstarReconstruction");
////#########################################################################################################################################

//*******************  Histogramms  ********************************************************************************
  ///HIST Classes
    h_input           .reset(new TstarSelectionHists(ctx, "input"));
    h_input_event     .reset(new EventHists(ctx, "input_Event"));
    h_input_jet       .reset(new JetHists(ctx, "input_Jets",6));
    h_input_ele       .reset(new ElectronHists(ctx, "input_Electrons"));
    h_input_muon      .reset(new MuonHists(ctx, "input_Muons"));
    h_input_topjet    .reset(new TopJetHists(ctx, "input_TopJets"));
    h_input_lumi      .reset(new LuminosityHists(ctx, "input_Lumi"));

    h_cleaner         .reset(new TstarSelectionHists(ctx, "cleaner"));
    h_cleaner_event   .reset(new EventHists(ctx, "cleaner_Event"));
    h_cleaner_jet     .reset(new JetHists(ctx, "cleaner_Jets",6));
    h_cleaner_ele     .reset(new ElectronHists(ctx, "cleaner_Electrons"));
    h_cleaner_muon    .reset(new MuonHists(ctx, "cleaner_Muons"));
    h_cleaner_topjet  .reset(new TopJetHists(ctx, "cleaner_TopJets"));
    h_cleaner_lumi    .reset(new LuminosityHists(ctx, "cleaner_Lumi"));
    
    h_btag_loose      .reset(new TstarSelectionHists(ctx, "btag_loose"));
    h_btag_medium     .reset(new TstarSelectionHists(ctx, "btag_medium"));
    h_btag_tight      .reset(new TstarSelectionHists(ctx, "btag_tight"));

    h_btag       .reset(new TstarSelectionHists(ctx, "btag"));
    h_btag_event .reset(new EventHists(ctx, "btag_Event"));
    h_btag_jet   .reset(new JetHists(ctx, "btag_Jets",6));
    h_btag_ele   .reset(new ElectronHists(ctx, "btag_Electrons"));
    h_btag_muon  .reset(new MuonHists(ctx, "btag_Muons"));
    h_btag_topjet.reset(new TopJetHists(ctx, "btag_TopJets"));
    h_btag_lumi  .reset(new LuminosityHists(ctx, "btag_Lumi"));

    h_toptagevt       .reset(new TstarSelectionHists(ctx, "toptagevt"));
    h_toptagevt_event .reset(new EventHists(ctx, "toptagevt_Event"));
    h_toptagevt_jet   .reset(new JetHists(ctx, "toptagevt_Jets",6));
    h_toptagevt_ele   .reset(new ElectronHists(ctx, "toptagevt_Electrons"));
    h_toptagevt_muon  .reset(new MuonHists(ctx, "toptagevt_Muons"));
    h_toptagevt_topjet.reset(new TopJetHists(ctx, "toptagevt_TopJets"));
    h_toptagevt_lumi  .reset(new LuminosityHists(ctx, "toptagevt_Lumi"));

    h_ht       .reset(new TstarSelectionHists(ctx, "ht"));
    h_ht_event .reset(new EventHists(ctx, "ht_Event"));
    h_ht_jet   .reset(new JetHists(ctx, "ht_Jets",6));
    h_ht_ele   .reset(new ElectronHists(ctx, "ht_Electrons"));
    h_ht_muon  .reset(new MuonHists(ctx, "ht_Muons"));
    h_ht_topjet.reset(new TopJetHists(ctx, "ht_TopJets"));
    h_ht_lumi  .reset(new LuminosityHists(ctx, "ht_Lumi"));
    
    h_output       .reset(new TstarSelectionHists(ctx, "output"));
    h_output_event .reset(new EventHists(ctx, "output_Event"));
    h_output_jet   .reset(new JetHists(ctx, "output_Jets",6));
    h_output_ele   .reset(new ElectronHists(ctx, "output_Electrons"));
    h_output_muon  .reset(new MuonHists(ctx, "output_Muons"));
    h_output_topjet.reset(new TopJetHists(ctx, "output_TopJets")); 
    h_output_lumi  .reset(new LuminosityHists(ctx, "output_Lumi"));

  //*********** Matching Hists **********************************************************
    h_matchable       .reset(new TstarSelectionHists(ctx, "matchable"));
    h_matchable_event .reset(new EventHists(ctx, "matchable_Event"));
    h_matchable_jet   .reset(new JetHists(ctx, "matchable_Jets",6));
    h_matchable_ele   .reset(new ElectronHists(ctx, "matchable_Electrons"));
    h_matchable_muon  .reset(new MuonHists(ctx, "matchable_Muons"));
    h_matchable_topjet.reset(new TopJetHists(ctx, "matchable_TopJets")); 
    h_matchable_lumi  .reset(new LuminosityHists(ctx, "matchable_Lumi"));

    h_not_matchable       .reset(new TstarSelectionHists(ctx, "not_matchable"));
    h_not_matchable_event .reset(new EventHists(ctx, "not_matchable_Event"));
    h_not_matchable_jet   .reset(new JetHists(ctx, "not_matchable_Jets",6));
    h_not_matchable_ele   .reset(new ElectronHists(ctx, "not_matchable_Electrons"));
    h_not_matchable_muon  .reset(new MuonHists(ctx, "not_matchable_Muons"));
    h_not_matchable_topjet.reset(new TopJetHists(ctx, "not_matchable_TopJets")); 
    h_not_matchable_lumi  .reset(new LuminosityHists(ctx, "not_matchable_Lumi"));
    
    h_match              .reset(new TstarSelectionHists(ctx, "match"));
    h_match_event        .reset(new EventHists(ctx, "match_Event"));
    h_match_jet          .reset(new JetHists(ctx, "match_Jets",6));
    h_match_ele          .reset(new ElectronHists(ctx, "match_Electrons"));
    h_match_muon         .reset(new MuonHists(ctx, "match_Muons"));
    h_match_topjet       .reset(new TopJetHists(ctx, "match_TopJets")); 
    h_match_lumi         .reset(new LuminosityHists(ctx, "match_Lumi"));

    h_corrmatch       .reset(new TstarSelectionHists(ctx, "corrmatch"));
    h_corrmatch_event .reset(new EventHists(ctx, "corrmatch_Event"));
    h_corrmatch_jet   .reset(new JetHists(ctx, "corrmatch_Jets",6));
    h_corrmatch_ele   .reset(new ElectronHists(ctx, "corrmatch_Electrons"));
    h_corrmatch_muon  .reset(new MuonHists(ctx, "corrmatch_Muons"));
    h_corrmatch_topjet.reset(new TopJetHists(ctx, "corrmatch_TopJets")); 
    h_corrmatch_lumi  .reset(new LuminosityHists(ctx, "corrmatch_Lumi"));

    h_corrmatch_ttag       .reset(new TstarSelectionHists(ctx, "corrmatch_ttag"));
    h_corrmatch_ttag_event .reset(new EventHists(ctx, "corrmatch_ttag_Event"));
    h_corrmatch_ttag_jet   .reset(new JetHists(ctx, "corrmatch_ttag_Jets",6));
    h_corrmatch_ttag_ele   .reset(new ElectronHists(ctx, "corrmatch_ttag_Electrons"));
    h_corrmatch_ttag_muon  .reset(new MuonHists(ctx, "corrmatch_ttag_Muons"));
    h_corrmatch_ttag_topjet.reset(new TopJetHists(ctx, "corrmatch_ttag_TopJets")); 
    h_corrmatch_ttag_lumi  .reset(new LuminosityHists(ctx, "corrmatch_ttag_Lumi"));

    h_no_corrmatch       .reset(new TstarSelectionHists(ctx, "no_corrmatch"));
    h_no_corrmatch_event .reset(new EventHists(ctx, "no_corrmatch_Event"));
    h_no_corrmatch_jet   .reset(new JetHists(ctx, "no_corrmatch_Jets",6));
    h_no_corrmatch_ele   .reset(new ElectronHists(ctx, "no_corrmatch_Electrons"));
    h_no_corrmatch_muon  .reset(new MuonHists(ctx, "no_corrmatch_Muons"));
    h_no_corrmatch_topjet.reset(new TopJetHists(ctx, "no_corrmatch_TopJets")); 
    h_no_corrmatch_lumi  .reset(new LuminosityHists(ctx, "no_corrmatch_Lumi"));
 
    //GenHists
    h_tstargenhists         .reset(new TStarGenHists(ctx, "tstargenhists"));

    h_match_discr           .reset(new HypothesisHistsOwn(ctx, "match__HypHists", "TstarReconstruction", "CorrectMatch"));
    h_corrmatch_discr       .reset(new HypothesisHistsOwn(ctx, "corrmatch__HypHists", "TstarReconstruction", "CorrectMatch"));
    h_corrmatch_ttag_discr  .reset(new HypothesisHistsOwn(ctx, "corrmatch_ttag__HypHists", "TstarReconstruction", "CorrectMatch"));
    h_no_corrmatch_discr    .reset(new HypothesisHistsOwn(ctx, "no_corrmatch__HypHists", "TstarReconstruction", "CorrectMatch"));

 // ********************************************************************************************************************

  // ****************** Chi2 Hists *************************************************************************************
    h_chi2                 .reset(new TstarSelectionHists(ctx, "chi2"));
    h_chi2_event           .reset(new EventHists(ctx, "chi2_Event"));
    h_chi2_jet             .reset(new JetHists(ctx, "chi2_Jets",6));
    h_chi2_ele             .reset(new ElectronHists(ctx, "chi2_Electrons"));
    h_chi2_muon            .reset(new MuonHists(ctx, "chi2_Muons"));
    h_chi2_topjet          .reset(new TopJetHists(ctx, "chi2_TopJets"));
    h_chi2_lumi            .reset(new LuminosityHists(ctx, "chi2_Lumi"));

    h_no_chi2                 .reset(new TstarSelectionHists(ctx, "chi2_no"));
    h_no_chi2_event           .reset(new EventHists(ctx, "chi2_no_Event"));
    h_no_chi2_jet             .reset(new JetHists(ctx, "chi2_no_Jets",6));
    h_no_chi2_ele             .reset(new ElectronHists(ctx, "chi2_no_Electrons"));
    h_no_chi2_muon            .reset(new MuonHists(ctx, "chi2_no_Muons"));
    h_no_chi2_topjet          .reset(new TopJetHists(ctx, "chi2_no_TopJets"));
    h_no_chi2_lumi            .reset(new LuminosityHists(ctx, "chi2_no_Lumi"));

    //Hists for Reconstruction
    h_chi2_before       .reset(new HypothesisHistsOwn(ctx, "chi2before__HypHists", "TstarReconstruction", "Chi2")); 
    h_chi2min           .reset(new HypothesisHistsOwn(ctx, "chi2min__HypHists", "TstarReconstruction", "Chi2")); 
    h_chi2min_ttag      .reset(new HypothesisHistsOwn(ctx, "chi2min_ttag__HypHists", "TstarReconstruction", "Chi2")); 
    h_chi2min_ttag_comb .reset(new HypothesisHistsOwn(ctx, "chi2min_ttag_comb__HypHists","TstarReconstruction", "Chi2"));

    h_no_chi2min        .reset(new HypothesisHistsOwn(ctx, "chi2min_no__HypHists", "TstarReconstruction", "Chi2")); 
    //

//Hist for PDF Variations
  h_PDF_variations      .reset(new TstarPDFHists(ctx, "PDF_variations", do_pdf_variations));

// ********************************************************************************************************************

}


bool TstarEleSelectionModule::process(uhh2::Event& event){
  // *************************************************************************************************************
  // \brief module to produce "PreSelection" ntuples for the T*T*->ttbar gg semileptonic analysis
  //  NOTE: output ntuple contains uncleaned Jets/TopJets (no jetID cleaning, no JetLepton cleaning, no JEC/JER smearing applied!)
  // 
  //  Selections: Luminosity selections (Data only);
  //              Common Modules: (For more details see UHH2/common/include/CommonModules.h)
  //                        MCPileupReweight (MC only);
  //                        JetCorrector (Summer16_23Sep2016_AK4PFchs);
  //                        JER;
  //                        MET filters (https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2);
  //                        good PV;
  //                        JetLepton Cleaning;
  //                        ID cleaner for Muons(Tight ID, pT>53 GeV);
  //                        Electrons(Spring16 Tight ID, pT>50 GeV);
  //                        Jets(WP_LOOSE, pT>30 GeV));
  //
  //              TopJetCorrector (Summer16_23Sep2016_AK8PFchs);
  //              SubJetCorrector (Summer16_23Sep2016_AK4PFchs)  
  //              TopJetLeptonCleaner (0.8) ;
  //              TopJetCleaner (PtEtaCut(200., 2.4), Type2TopTag(105,220,Type2TopTag::MassType::groomed), Tau32(0.67));
  //
  //              Lepton selection:
  //                         Muon channel:     exactly one muon (High Pt ID, pT>53 GeV)
  //                         Electron channel: exactly one electron (Spring16 Tight ID, pT>50 GeV)
  //
  //              Jet selection:
  //                         at least 4 jets (WP_LOOSE, pT>50 GeV) 
  //
  // *************************************************************************************************************

  // dump input content
  h_input        ->fill(event);
  h_input_event  ->fill(event);
  h_input_jet    ->fill(event);
  h_input_ele    ->fill(event);
  h_input_muon   ->fill(event);
  h_input_topjet ->fill(event);
  h_input_lumi   ->fill(event);

  // Scale Factors
   // for MuonID/MuonTrigger
    SF_muonTrigger->process(event);
    SF_muonID->process(event);

    //
    SF_elecID->process(event);
  
  /// ###################### Re-Weight TTbar events during miss modelled pT #############
  ttbar_reweight->process(event);
  if(debug) cout<<"Finished ttbar reweight: "<<endl;
  //####################################################################################  
      
      
      //########## Do MC-Scale Variations for Systematics #####################################
  if(do_scale_variation){
    sys_scale_variation->process(event);
  }
  

// ############## Common Modules and Object Cleaning #################################### 
//Common Modules
  bool pass_common = common->process(event);
  if(!pass_common) return false;
  if(debug) cout<<"Passed Common Modules: "<<endl;
 
////Object Cleaning for Jets/TopJets   
  sort_by_pt<Jet>(*event.jets);
  sort_by_pt<TopJet>(*event.topjets);

  topjet_cleaner       ->process(event);
  
  sort_by_pt<Jet>(*event.jets);
  sort_by_pt<TopJet>(*event.topjets);

  h_cleaner       ->fill(event);
  h_cleaner_event ->fill(event);
  h_cleaner_jet   ->fill(event);
  h_cleaner_ele   ->fill(event);
  h_cleaner_muon  ->fill(event);
  h_cleaner_topjet->fill(event);
  h_cleaner_lumi  ->fill(event);
  if(debug) cout<<"After Cleaner: "<<endl;

//################################################################################### 

  
  //################## B-Tag with Efficiency and SF #########################
  const bool pass_bTag_loose  = b_tag_loose_sel->passes(event);
  const bool pass_bTag_medium = b_tag_medium_sel->passes(event);
  const bool pass_bTag_tight  = b_tag_tight_sel->passes(event);

  if(pass_bTag_loose){
    h_btag_loose        ->fill(event);
  }
  if(pass_bTag_medium){
    h_btag_medium        ->fill(event);
  }
  if(pass_bTag_tight){
    h_btag_tight        ->fill(event);
  }

  BTagEffHists->fill(event);            //Run First Time without b-Tag and ScaleFactors (SF_btag)
  
  /// b-Tag 
  const bool pass_bTag = b_tag_medium_sel->passes(event);
  if(!pass_bTag) return false;
  
  SF_btag       ->process(event);     //Scale Factor for b-Tagging                        
  
  h_btag        ->fill(event);
  h_btag_event  ->fill(event);
  h_btag_jet    ->fill(event);
  h_btag_ele    ->fill(event);
  h_btag_muon   ->fill(event);
  h_btag_topjet ->fill(event);
  h_btag_lumi   ->fill(event);
  
  if(debug) cout<<"After b-Tag: "<<endl;
  ////#######################################################################
  
  
  //// ##########  Top-Tagging with appropriate Jet-Selection #################### 
  //Top-Tag
  const bool pass_ttagevt = toptagevt_sel->passes(event);
  
  if(pass_ttagevt){  
    if(debug) cout<<"After top-Tag: "<<endl;
    h_toptagevt        ->fill(event);
    h_toptagevt_event  ->fill(event);
    h_toptagevt_jet    ->fill(event);
    h_toptagevt_ele    ->fill(event);
    h_toptagevt_muon    ->fill(event);
    h_toptagevt_topjet ->fill(event);
    h_toptagevt_lumi   ->fill(event);
  }
  
  // add flag_toptagevent to output ntuple 
  event.set(h_flag_toptagevent, int(pass_ttagevt));
  if(debug) cout<<"After top-Tag Hists: "<<endl;
  
  
  ///HT Cut
  const bool pass_HTcut = ht_sel->passes(event);
  if(!pass_HTcut) return false;
  
  h_ht        ->fill(event);
  h_ht_event  ->fill(event);
  h_ht_jet    ->fill(event);
  h_ht_ele    ->fill(event);
  h_ht_muon    ->fill(event);
  h_ht_topjet ->fill(event);
  h_ht_lumi   ->fill(event);
  
  if(debug) cout<<"After HT Sel: "<<endl;
  
  //##############################################################################
//// ###############  SYSTEM RECO  #############################################################################

//***********************************************************************************************************
//
//  Fisrt Reconstruct Primary Lepton
//  Reconstruct the FourVector of Neutrino
//  
//  Reconstruct full Event  
//
//  Correct Matching between Reco and Gen Particles
//
//
//***********************************************************************************************************

 
////PrimeLep Reco
    reco_primlep->process(event);
    if(debug) cout<<"Primary Lepton Reconstruction"<<endl;
    
 ////*******  Reconstruction ************************************************************** 
    bool pass_reco(false);
    
    if(!pass_ttagevt){                                                              //Without Top-Tag
      tstar_reco->process(event);
    }
    else { 
      pass_reco = tstar_ttag_reco->process(event);                                //With Top-Tag
      if(!pass_reco) {                                                            //If reco with top-tag fails,  
	tstar_reco->process(event);                                               //Use reco without top-tag
      }
    }
////****************************************************************************************** 

//*********  For MC Only! Needs Generator Information ******************************************
    if(!event.isRealData){
      tstargenprod->process(event);
     
      //    h_tstargenhists->fill(event);
      

  // ****************  Matching betweeen Gen and Reco Level  ************************************************************************

      if(matching){
	if(debug) cout<<"Do Matching!"<<endl;
	//Get Generator Particles
	const auto & tstargen = event.get(h_tstargen);
	
	//Check if event is "matchable": pt and eta of objects inside the selection criteria
	bool matchable_tstar(false);
	if(tstargen.IsSemiLeptonicDecay()){
	  const LorentzVector gen_jetq1_v4    = tstargen.Q1().v4();
	  const LorentzVector gen_jetq2_v4    = tstargen.Q2().v4();
	  const LorentzVector gen_bhad_v4     = tstargen.BHad().v4();
	  const LorentzVector gen_blep_v4     = tstargen.BLep().v4();
	  const LorentzVector gen_lepton_v4   = tstargen.ChargedLepton().v4();
	  const LorentzVector gen_gluonhad_v4 = tstargen.GluonHad().v4();
	  const LorentzVector gen_gluonlep_v4 = tstargen.GluonLep().v4();
	  
	  bool pt_jets(false), eta_jets(false);
	  if(gen_jetq1_v4.Pt()>50. && gen_jetq2_v4.Pt()>50. && gen_bhad_v4.Pt()>50. && gen_blep_v4.Pt()>50. && gen_gluonhad_v4.Pt()>50 && gen_gluonlep_v4.Pt()>50) pt_jets = true;
	  if(fabs(gen_jetq1_v4.Eta())<2.4 && fabs(gen_jetq2_v4.Eta())<2.4 && fabs(gen_bhad_v4.Eta())<2.4 && fabs(gen_blep_v4.Eta())<2.4 && fabs(gen_gluonhad_v4.Eta())<2.4 && fabs(gen_gluonlep_v4.Eta())<2.4 ) eta_jets = true;
	  
	  bool pt_lepton(false), eta_lepton(false);
	  if(gen_lepton_v4.Pt()>53.) pt_lepton = true;
	  if(fabs(gen_lepton_v4.Eta())<2.4) eta_lepton = true;
	  
	  if(pt_jets && eta_jets && pt_lepton && eta_lepton) matchable_tstar = true;
	}      
	if(debug) cout<<"Matchable Event?"<<endl;
	
	if(matchable_tstar){
	  if(debug) cout<<"Matchable Event? Yes!"<<endl;
	  h_tstargenhists->fill(event);

	  h_matchable->fill(event);
	  h_matchable_event  ->fill(event);
	  h_matchable_jet    ->fill(event);
	  h_matchable_ele    ->fill(event);
	  h_matchable_muon   ->fill(event);
	  h_matchable_topjet ->fill(event);
	  
	  //if event is matchable, do matching!
	  if(!pass_ttagevt){
	    tstar_match->process(event);             //Do Matching
	  }
	  else{
	    if(pass_reco){
	      tstar_ttag_match->process(event);
	    }
	    else{
	      tstar_match->process(event);
	    }
	  }

	  
	  std::vector<TstarReconstructionHypothesis>& hyps = event.get(h_hyps);
	  
	  const TstarReconstructionHypothesis* hyp_c = get_best_hypothesis(hyps, "CorrectMatch");
	  if(!hyp_c){
	    return false;
	  }
	  
	  h_match_discr  ->fill(event);
	  
	  h_match        ->fill(event);
	  h_match_event  ->fill(event);
	  h_match_jet    ->fill(event);
	  h_match_ele    ->fill(event);
	  h_match_muon   ->fill(event);
	  h_match_topjet ->fill(event);
	  
	  //Declare Correct match for Discriminator < 3
	  if(hyp_c->discriminator("CorrectMatch")<3){
	    if(pass_ttagevt && pass_reco){
	      h_corrmatch_ttag_discr  ->fill(event);
	      
	      h_corrmatch_ttag        ->fill(event);
	      h_corrmatch_ttag_event  ->fill(event);
	      h_corrmatch_ttag_jet    ->fill(event);
	      h_corrmatch_ttag_ele    ->fill(event);
	      h_corrmatch_ttag_muon   ->fill(event);
	      h_corrmatch_ttag_topjet ->fill(event);
	    }
	    else{
	      h_corrmatch_discr  ->fill(event);
	      
	      h_corrmatch        ->fill(event);
	      h_corrmatch_event  ->fill(event);
	      h_corrmatch_jet    ->fill(event);
	      h_corrmatch_ele    ->fill(event);
	      h_corrmatch_muon   ->fill(event);
	      h_corrmatch_topjet ->fill(event);
	    }
	  }
	  else{
	    h_no_corrmatch_discr  ->fill(event);
	    
	    h_no_corrmatch        ->fill(event);
	    h_no_corrmatch_event  ->fill(event);
	    h_no_corrmatch_jet    ->fill(event);
	    h_no_corrmatch_ele    ->fill(event);
	    h_no_corrmatch_muon   ->fill(event);
	    h_no_corrmatch_topjet ->fill(event);
	  }
	  
	  const TstarReconstructionHypothesis hyp_obj(*hyp_c);
	  hyps.clear();
	  hyps.push_back(hyp_obj);
	}
	else{
	  if(debug) cout<<"Matchable Event? NO!"<<endl;
	  h_not_matchable        ->fill(event);
	  h_not_matchable_event  ->fill(event);
	  h_not_matchable_jet    ->fill(event);
	  h_not_matchable_ele    ->fill(event);
	  h_not_matchable_muon   ->fill(event);
	  h_not_matchable_topjet ->fill(event);
	}
      }
      // End Matching *******************************************************************************************************
    }//End MC
    

 //*****************************  Chi2 Hypothesis ***************************************************************************
    if(chi2_discr){
      bool pass_reco = false;

      if(debug) cout<<"Enter Chi2 with Top Tag"<<endl;
      
      if(!pass_ttagevt){                                                              //Without Top-Tag
	tstar_chi2->process(event);
      }
      else { 
  	if(!pass_reco){
	  tstar_chi2->process(event);
	}
	else{
	  tstar_ttag_chi2->process(event);
	}
      }
 
      //Chi2 Method for Final Reconstruction (Additional: KinFitter??)
      std::vector<TstarReconstructionHypothesis>& hyps = event.get(h_hyps);
      
      
      const TstarReconstructionHypothesis* hyp = get_best_hypothesis(hyps, "Chi2");        //Get best Hypothesis
      
      if(!hyp){ 
	std::cout<<"Nullpointer!"<<std::endl;
	return false;
      } 
      
      
      //Fill Reconstruction Hists BEFORE Discriminator Cut
      h_chi2_before ->fill(event);
      
      //Cut on Discriminator
      if(hyp->discriminator("Chi2")<90){
	
	if(!pass_ttagevt){
	  h_chi2min->fill(event);
	}
	else{
	  h_chi2min_ttag->fill(event);
	}
	h_chi2min_ttag_comb->fill(event);
	
	
	//Dump Events in Event Hists
	h_chi2        ->fill(event);
	h_chi2_event  ->fill(event);
	h_chi2_jet    ->fill(event);
	h_chi2_ele    ->fill(event);
	h_chi2_muon   ->fill(event);
	h_chi2_topjet ->fill(event);
	h_chi2_lumi   ->fill(event);
      }
      else{
	h_no_chi2 ->fill(event);

	//Dump Events in Event Hists
	h_no_chi2        ->fill(event);
	h_no_chi2_event  ->fill(event);
	h_no_chi2_jet    ->fill(event);
	h_no_chi2_ele    ->fill(event);
	h_no_chi2_muon   ->fill(event);
	h_no_chi2_topjet ->fill(event);
	h_no_chi2_lumi   ->fill(event);
      }
// ##########################################################################################################################
 

      
      // Histogramms for PDF-Variations 
      // if(hyp->discriminator("Chi2")<50) h_PDF_variations->fill(event);
      
      //Clear Hypothesis Vector
      const TstarReconstructionHypothesis hyp_obj(*hyp);
      hyps.clear();
      hyps.push_back(hyp_obj);
    }
    
    //Dump output 
    h_output        ->fill(event);
    h_output_event  ->fill(event);
    h_output_jet    ->fill(event);
    h_output_ele    ->fill(event);
    h_output_muon   ->fill(event);
    h_output_topjet ->fill(event);
    h_output_lumi   ->fill(event);
    if(debug) cout<<"End: "<<endl;
 
    return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(TstarEleSelectionModule)
