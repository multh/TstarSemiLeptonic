#include <iostream>
#include <memory>

#include "UHH2/common/include/MCWeight.h"
#include <UHH2/common/include/CommonModules.h>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/EventHists.h"
#include "UHH2/common/include/CleaningModules.h"
#include "UHH2/common/include/NSelections.h"
#include "UHH2/common/include/MuonHists.h"
#include "UHH2/common/include/MuonIds.h"
#include "UHH2/common/include/ElectronHists.h"
#include "UHH2/common/include/ElectronIds.h"
#include "UHH2/common/include/TauHists.h"
#include "UHH2/common/include/TauIds.h"
#include "UHH2/common/include/JetHists.h"
#include "UHH2/common/include/JetIds.h"
#include <UHH2/common/include/TopJetIds.h>
#include "UHH2/common/include/LuminosityHists.h"
#include "UHH2/common/include/LumiSelection.h"
#include "UHH2/common/include/TriggerSelection.h"
#include "UHH2/TstarSemiLeptonic/include/TstarSemiLeptonicSelections.h"
#include "UHH2/TstarSemiLeptonic/include/TstarSemiLeptonicUtils.h"
#include "UHH2/TstarSemiLeptonic/include/TstarPreSelectionHists.h"
#include <UHH2/TstarSemiLeptonic/include/TstarSelectionHists.h>
#include "UHH2/common/include/JetCorrections.h"
#include "UHH2/common/include/ObjectIdUtils.h"
#include "UHH2/common/include/Utils.h"
#include "UHH2/core/include/Selection.h"
#include "UHH2/common/include/TopPtReweight.h"

using namespace uhh2;
using namespace std;
namespace uhh2examples {
//*****************************************************************************************************
//
// \brief module to produce "PreSelection" ntuples for the T*T*->ttbar gg semileptonic analysis
//  NOTE: output ntuple contains uncleaned jets/TopJets (no jet-lepton cleaning, no JER smearing)
//
//*****************************************************************************************************

class TstarPreSelectionModule: public AnalysisModule {

 public:
  explicit TstarPreSelectionModule(Context & ctx);
  virtual bool process(Event & event) override;

 private:
  enum lepton { muon, elec };
  lepton channel_;


  //Common Modules 
  unique_ptr<CommonModules>               common;      //comes with Muon/Electron cleaner, JetCorrector/Smearer /MClumiweight and mcPileupReweight
  
  //Cleaner
  unique_ptr<JetCleaner>                  topjet_IDcleaner;
  unique_ptr<TopJetCorrector>             topjet_corrector_MC;
  unique_ptr<TopJetCorrector>             topjet_corrector_BCD;
  unique_ptr<TopJetCorrector>             topjet_corrector_EFearly;
  unique_ptr<TopJetCorrector>             topjet_corrector_FlateG;
  unique_ptr<TopJetCorrector>             topjet_corrector_H;
  unique_ptr<TopJetLeptonDeltaRCleaner>   topjetlepton_cleaner;
  unique_ptr<TopJetCleaner>               topjet_cleaner;
  unique_ptr<JetCleaner>                  jet_cleaner; //Additional Jet Cleaner 

  
  //Scale Factors
  unique_ptr<AnalysisModule>              SF_muonID, SF_muonTrigger;

  // *********** Pre-Selections for Analysis *********************************************************************************************************** 
  // declare Selections
  unique_ptr<Selection>                   lumi_sel;
  unique_ptr<Selection>                   trigger_Mu50;
  unique_ptr<Selection>                   trigger_TkMu50;
  unique_ptr<AndSelection>                lep_sel;
  unique_ptr<Selection>                   jet_sel;
  unique_ptr<Selection>                   ht_sel;
  //*****************************************************************************************************************************************************

  //****************************** Histogramms **********************************************************************************************************
  // store the Hists collection as member variables
  unique_ptr<Hists> h_input,   h_input_event,   h_input_bJet,   h_input_jet,   h_input_ele,   h_input_muon,   h_input_topjet,   h_input_lumi;
  unique_ptr<Hists> h_trigger, h_trigger_event, h_trigger_bJet, h_trigger_jet, h_trigger_ele, h_trigger_muon, h_trigger_topjet, h_trigger_lumi;
  unique_ptr<Hists> h_cleaner, h_cleaner_event, h_cleaner_bJet, h_cleaner_jet, h_cleaner_ele, h_cleaner_muon, h_cleaner_topjet, h_cleaner_lumi;
  unique_ptr<Hists> h_lumi,    h_lumi_event,    h_lumi_bJet,    h_lumi_jet,    h_lumi_ele,    h_lumi_muon,    h_lumi_topjet,    h_lumi_lumi;
  unique_ptr<Hists> h_lep,     h_lep_event,     h_lep_bJet,     h_lep_jet,     h_lep_ele,     h_lep_muon,     h_lep_topjet,     h_lep_lumi; 
  unique_ptr<Hists> h_jet,     h_jet_event,     h_jet_bJet,     h_jet_jet,     h_jet_ele,     h_jet_muon,     h_jet_topjet,     h_jet_lumi;
  unique_ptr<Hists> h_ht,      h_ht_event,      h_ht_bJet,      h_ht_jet,      h_ht_ele,      h_ht_muon,      h_ht_topjet,      h_ht_lumi;
  //*****************************************************************************************************************************************************  

  //Set IDs
  MuonId     MuId;
  ElectronId EleId;

  bool is_mc;
  
};

TstarPreSelectionModule::TstarPreSelectionModule(Context & ctx){

 //********  New IDs for Summer 2016 Dataset ********************************************************
  //Leptons
  MuId  = AndId<Muon>(MuonIDMedium_ICHEP(), PtEtaCut(50., 2.1));
  EleId = AndId<Electron>( ElectronID_MVAGeneralPurpose_Spring16_loose, PtEtaCut(50., 2.5));     //check the ElectronID for Common Modules! 
  
  //Jets
  const JetId jetID(JetPFID(JetPFID::WP_LOOSE));
  const TopJetId topjetID = AndId<TopJet>(Type2TopTag(105,220,Type2TopTag::MassType::groomed), Tau32());
  //*************************************************************************************************

  // ********** Scale Factors for MuonID and Triggers ***********************************************
  //Still to add: Systematics for Scale Factors
  string sys_muonID   = ctx.get("sys_muonID");
  string sys_muonTrig = ctx.get("sys_muonTrig");

  SF_muonID.reset(new MCMuonScaleFactor(ctx,"/nfs/dust/cms/user/multh/CMSSW_8_0_24_patch1/src/UHH2/common/data/MuonID_EfficienciesAndSF_average_RunBtoH.root", "MC_NUM_MediumID2016_DEN_genTracks_PAR_pt_eta",1)); 
  SF_muonTrigger.reset(new MCMuonScaleFactor(ctx,"/nfs/dust/cms/user/multh/CMSSW_8_0_24_patch1/src/UHH2/common/data/MuonTrigger_EfficienciesAndSF_average_RunBtoH.root", "IsoMu50_OR_IsoTkMu50_PtEtaBins",1));
  //***************************************************************************************************
   
  //Boolean for MC/Data
  is_mc = (ctx.get("dataset_type") == "MC");

 
///COMMON Modules
   common.reset(new CommonModules());    //comes with Muon/Electron cleaner, JetCorrector/Smearer, MClumiweight and mcPileupReweight
   common->switch_jetlepcleaner(true);
   //common->set_electron_id(EleId);
   common->set_muon_id(MuId);
   common->set_jet_id(jetID);
   common->init(ctx);
  ///
  
  
//*********** Event Corrector and Cleaner **********************************************************************************************
   //TopJet Corector
  if(is_mc){
    topjet_corrector_MC.reset(new TopJetCorrector(ctx,JERFiles::Summer16_23Sep2016_V4_L123_AK8PFchs_MC));           //For MC
  }
  else {                                                                                                            //For Data ->
    topjet_corrector_BCD.reset(new TopJetCorrector(ctx,JERFiles::Summer16_23Sep2016_V4_BCD_L123_AK8PFchs_DATA));    //            Run Period BCD
    topjet_corrector_EFearly.reset(new TopJetCorrector(ctx,JERFiles::Summer16_23Sep2016_V4_EF_L123_AK8PFchs_DATA)); //            Run Period EF
    topjet_corrector_FlateG.reset(new TopJetCorrector(ctx,JERFiles::Summer16_23Sep2016_V4_G_L123_AK8PFchs_DATA));   //            Run Period G
    topjet_corrector_H.reset(new TopJetCorrector(ctx,JERFiles::Summer16_23Sep2016_V4_H_L123_AK8PFchs_DATA));        //            Run Period H
  }

  //TopJet Cleaner and TopJetLepton Cleaner
  topjet_IDcleaner    .reset(new JetCleaner(ctx, jetID));
  topjetlepton_cleaner.reset(new TopJetLeptonDeltaRCleaner(.8));
  topjet_cleaner      .reset(new TopJetCleaner(ctx, TopJetId(PtEtaCut(300., 2.4))));
  
  //Jet Cleaner
  jet_cleaner         .reset(new JetCleaner(ctx,30.0,2.5));
  //**************************************************************************************************************************************


  //*******************  Selections  *****************************************************************************************************

  //************* Lepton Selection **********************************************************
  //Get Channel: Muon or Electon
 const std::string& channel = ctx.get("channel", "");
  if     (channel == "muon") channel_ = muon;
  else if(channel == "elec") channel_ = elec;
  else throw std::runtime_error("TstarPreSelectionModule -- undefined argument for 'channel' key in xml file (must be 'muon' or 'elec'): "+channel);

  //Require exactly one Muon or one Electron
lep_sel.reset(new uhh2::AndSelection(ctx));
  if(channel_ == muon){
    lep_sel->add<NMuonSelection>    ("muoN == 1", 1, 1);
    lep_sel->add<NElectronSelection>("eleN == 0", 0, 0);
  }
  else if(channel_ == elec){
    lep_sel->add<NMuonSelection>    ("muoN == 0", 0, 0);
    lep_sel->add<NElectronSelection>("eleN == 1", 1, 1);
  }
  //*****************************************************************************************

  //Trigger Selection
  trigger_Mu50.reset(new TriggerSelection("HLT_Mu50_v*"));              //As recommended on MuonTwiki for Non-iso Muons
  trigger_TkMu50.reset(new TriggerSelection("HLT_TkMu50_v"));
 
 //Jet Selection
  jet_sel.reset(new NJetSelection(3,-1, JetId(PtEtaCut(55., 2.4)))); 

 //HT Selection
  ht_sel.reset(new HtSelection(200,-1));                                //Loose Ht-Cut for first Studies
 
 //Lumi Selection (For Data Only)
 lumi_sel.reset(new LumiSelection(ctx));
 //******************************************************************************************************************

 
 //*******************  Histogramms  ********************************************************************************
  ///HIST Classes
  h_input       .reset(new TstarPreSelectionHists(ctx, "input"));
  h_input_event .reset(new EventHists(ctx, "input_Event"));
  h_input_bJet  .reset(new TstarSelectionHists(ctx, "input_bJet"));
  h_input_jet   .reset(new JetHists(ctx, "input_Jets",6));
  h_input_ele   .reset(new ElectronHists(ctx, "input_Electrons"));
  h_input_muon   .reset(new MuonHists(ctx, "input_Muons"));
  h_input_topjet.reset(new TopJetHists(ctx, "input_TopJets"));
  h_input_lumi  .reset(new LuminosityHists(ctx, "input_Lumi"));

  h_trigger       .reset(new TstarPreSelectionHists(ctx, "trigger"));
  h_trigger_event .reset(new EventHists(ctx, "trigger_Event"));
  h_trigger_bJet  .reset(new TstarSelectionHists(ctx, "trigger_bJet"));
  h_trigger_jet   .reset(new JetHists(ctx, "trigger_Jets",6));
  h_trigger_ele   .reset(new ElectronHists(ctx, "trigger_Electrons"));
  h_trigger_muon   .reset(new MuonHists(ctx, "trigger_Muons"));
  h_trigger_topjet.reset(new TopJetHists(ctx, "trigger_TopJets"));
  h_trigger_lumi  .reset(new LuminosityHists(ctx, "trigger_Lumi"));

  h_cleaner       .reset(new TstarPreSelectionHists(ctx, "cleaner"));
  h_cleaner_event .reset(new EventHists(ctx, "cleaner_Event"));
  h_cleaner_bJet  .reset(new TstarSelectionHists(ctx, "cleaner_bJet"));
  h_cleaner_jet   .reset(new JetHists(ctx, "cleaner_Jets",6));
  h_cleaner_ele   .reset(new ElectronHists(ctx, "cleaner_Electrons"));
  h_cleaner_muon   .reset(new MuonHists(ctx, "cleaner_Muons"));
  h_cleaner_topjet.reset(new TopJetHists(ctx, "cleaner_TopJets"));
  h_cleaner_lumi  .reset(new LuminosityHists(ctx, "cleaner_Lumi"));

  h_lumi       .reset(new TstarPreSelectionHists(ctx, "lumi"));
  h_lumi_event .reset(new EventHists(ctx, "lumi_Event"));
  h_lumi_bJet  .reset(new TstarSelectionHists(ctx, "lumi_bJet"));
  h_lumi_jet   .reset(new JetHists(ctx, "lumi_Jets",6));
  h_lumi_ele   .reset(new ElectronHists(ctx, "lumi_Electrons"));
  h_lumi_muon   .reset(new MuonHists(ctx, "lumi_Muons"));
  h_lumi_topjet.reset(new TopJetHists(ctx, "lumi_TopJets"));
  h_lumi_lumi  .reset(new LuminosityHists(ctx, "lumi_Lumi"));

  h_lep       .reset(new TstarPreSelectionHists(ctx, "1Muon"));
  h_lep_event .reset(new EventHists(ctx, "1Muon_Event"));
  h_lep_bJet  .reset(new TstarSelectionHists(ctx, "1Muon_bJet"));
  h_lep_jet   .reset(new JetHists(ctx, "1Muon_Jets",6));
  h_lep_ele   .reset(new ElectronHists(ctx, "1Muon_Electrons"));
  h_lep_muon  .reset(new MuonHists(ctx, "1Muon_Muons"));
  h_lep_topjet.reset(new TopJetHists(ctx, "1Muon_TopJets")); 
  h_lep_lumi  .reset(new LuminosityHists(ctx, "1Muon_Lumi"));

  h_jet       .reset(new TstarPreSelectionHists(ctx, "4Jets"));
  h_jet_event .reset(new EventHists(ctx, "4Jets_Event"));
  h_jet_bJet  .reset(new TstarSelectionHists(ctx, "4Jets_bJet"));
  h_jet_jet   .reset(new JetHists(ctx, "4Jets_Jets",6));
  h_jet_ele   .reset(new ElectronHists(ctx, "4Jets_Electrons"));
  h_jet_muon   .reset(new MuonHists(ctx, "4Jets_Muons"));
  h_jet_topjet.reset(new TopJetHists(ctx, "4Jets_TopJets")); 
  h_jet_lumi  .reset(new LuminosityHists(ctx, "4Jets_Lumi"));

  h_ht       .reset(new TstarPreSelectionHists(ctx, "HT300"));
  h_ht_event .reset(new EventHists(ctx, "HT300_Event"));
  h_ht_bJet  .reset(new TstarSelectionHists(ctx, "HT300_bJet"));
  h_ht_jet   .reset(new JetHists(ctx, "HT300_Jets",6));
  h_ht_ele   .reset(new ElectronHists(ctx, "HT300_Electrons"));
  h_ht_muon   .reset(new MuonHists(ctx, "HT300_Muons"));
  h_ht_topjet.reset(new TopJetHists(ctx, "HT300_TopJets")); 
  h_ht_lumi  .reset(new LuminosityHists(ctx, "HT300_Lumi"));

  //*****************************************************************************************************************
}

bool TstarPreSelectionModule::process(Event & event) {

  //Only for Data: Lumi-Selections
if(!is_mc){
   if(!lumi_sel->passes(event)) return false;
    }
  

 // dump input content
  h_input       ->fill(event);
  h_input_event ->fill(event);
  h_input_bJet  ->fill(event);
  h_input_jet   ->fill(event);
  h_input_ele   ->fill(event);
  h_input_muon   ->fill(event);
  h_input_topjet->fill(event);
  h_input_lumi  ->fill(event);
 
  
// keep Jets *before cleaning* to store them in the ntuple if event is accepted
  std::unique_ptr< std::vector<Jet> >    uncleaned_jets   (new std::vector<Jet>   (*event.jets));
  std::unique_ptr< std::vector<TopJet> > uncleaned_topjets(new std::vector<TopJet>(*event.topjets));

  //Trigger Selection  
if(!trigger_Mu50->passes(event) && !trigger_TkMu50) return false;
 
 SF_muonTrigger->process(event);     //Scale Factors for Muon Trigger

  h_trigger       ->fill(event);
  h_trigger_event ->fill(event);
  h_trigger_bJet  ->fill(event);
  h_trigger_jet   ->fill(event);
  h_trigger_ele   ->fill(event);
  h_trigger_muon  ->fill(event);
  h_trigger_topjet->fill(event);
  h_trigger_lumi  ->fill(event);
  
 
  //**********  Event Correctors and Cleaning **********************************
  // COMMON MODULES
    bool pass_common = common->process(event);
    if(!pass_common) return false;
  
    
    //Additional Cleaner 
    jet_cleaner         ->process(event);
    topjet_IDcleaner    ->process(event);
    // topjet_corrector    ->process(event);
    topjetlepton_cleaner->process(event);
    topjet_cleaner      ->process(event);
 
    const int runnr_BCD = 276811;
    const int runnr_EFearly = 278802;
    const int runnr_FlateG = 280385;

    if(is_mc){
      topjet_corrector_MC->process(event);
    }
    else{
      if(event.run <= runnr_BCD)          topjet_corrector_BCD->process(event);
      else if(event.run < runnr_EFearly)  topjet_corrector_EFearly->process(event);
      else if(event.run <= runnr_FlateG)  topjet_corrector_FlateG->process(event);
      else if(event.run > runnr_FlateG)   topjet_corrector_H->process(event);
      else throw runtime_error("TstarPreSelectionModule: run number not covered");
    }
    //*****************************************************************************   


   sort_by_pt<TopJet>(*event.topjets);

  SF_muonID  ->process(event);   //Scale Factors for MuonID
  
  h_cleaner       ->fill(event);
  h_cleaner_event ->fill(event);
  h_cleaner_bJet  ->fill(event);
  h_cleaner_jet   ->fill(event);
  h_cleaner_ele   ->fill(event);
  h_cleaner_muon  ->fill(event);
  h_cleaner_topjet->fill(event);
  h_cleaner_lumi  ->fill(event);
  

  // LEPTON PRE-SELECTION
  if(!lep_sel->passes(event)) return false;
  h_lep        ->fill(event);
  h_lep_event  ->fill(event);
  h_lep_bJet   ->fill(event);
  h_lep_jet    ->fill(event);
  h_lep_ele    ->fill(event);
  h_lep_muon    ->fill(event);
  h_lep_topjet ->fill(event);
  h_lep_lumi   ->fill(event);
  

   // JET PRE-SELECTION
  if(!jet_sel->passes(event)) return false;
  h_jet        ->fill(event);
  h_jet_event  ->fill(event);
  h_jet_bJet   ->fill(event);
  h_jet_jet    ->fill(event);
  h_jet_ele    ->fill(event);
  h_jet_muon   ->fill(event);
  h_jet_topjet ->fill(event);
  h_jet_lumi   ->fill(event);
  ////



   // HT PRE-SELECTION
  if(!ht_sel->passes(event)) return false;
  h_ht        ->fill(event);
  h_ht_event  ->fill(event);
  h_ht_bJet   ->fill(event);
  h_ht_jet    ->fill(event);
  h_ht_ele    ->fill(event);
  h_ht_muon   ->fill(event);
  h_ht_topjet ->fill(event);
  h_ht_lumi   ->fill(event);
  ////


  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(TstarPreSelectionModule)
}

