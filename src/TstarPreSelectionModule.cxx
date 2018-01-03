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
   
  // *********** Pre-Selections for Analysis *********************************************************************************************************** 
  // declare Selections
    unique_ptr<Selection>                   lumi_sel;
    unique_ptr<AndSelection>                lep_sel;
    unique_ptr<Selection>                   jet_sel;
  //*****************************************************************************************************************************************************
    
  //****************************** Histogramms **********************************************************************************************************
  // store the Hists collection as member variables
    unique_ptr<Hists> h_input,   h_input_event,   h_input_bJet,   h_input_jet,   h_input_ele,   h_input_muon,   h_input_topjet,   h_input_lumi;
    unique_ptr<Hists> h_trigger, h_trigger_event, h_trigger_bJet, h_trigger_jet, h_trigger_ele, h_trigger_muon, h_trigger_topjet, h_trigger_lumi;
    unique_ptr<Hists> h_cleaner, h_cleaner_event, h_cleaner_bJet, h_cleaner_jet, h_cleaner_ele, h_cleaner_muon, h_cleaner_topjet, h_cleaner_lumi;
    unique_ptr<Hists> h_lep,     h_lep_event,     h_lep_bJet,     h_lep_jet,     h_lep_ele,     h_lep_muon,     h_lep_topjet,     h_lep_lumi; 
    unique_ptr<Hists> h_jet,     h_jet_event,     h_jet_bJet,     h_jet_jet,     h_jet_ele,     h_jet_muon,     h_jet_topjet,     h_jet_lumi;
    unique_ptr<Hists> h_output,  h_output_event,  h_output_bJet,  h_output_jet,  h_output_ele,  h_output_muon,  h_output_topjet,  h_output_lumi;
  //*****************************************************************************************************************************************************  

  //Set IDs
    MuonId     MuId;
    ElectronId EleId;
    JetId      jetID;
    
    bool is_mc;
  };


  TstarPreSelectionModule::TstarPreSelectionModule(Context & ctx){
    
 //********  New IDs for Summer 2016 Dataset ********************************************************
 //Leptons
    MuId  = AndId<Muon>(MuonIDTight(), PtEtaCut(53., 2.4));                     //Muon ID:    Muon POG suggest HighPtID for HLT_Mu50_v* triggers, BUT analysis makes usage of PF objects.
    EleId = AndId<Electron>(ElectronID_Spring16_tight,PtEtaCut(50.0, 2.4));     //ElectronID: Egamma POG provided efficiency curves for WP, WP tight has no real plateau after pT>45 GeV. 
    
 //Jets
    jetID = AndId<Jet>(JetPFID(JetPFID::WP_LOOSE),PtEtaCut(30.0, 2.4));
    const TopJetId topjetID = AndId<TopJet>(Type2TopTag(105,220,Type2TopTag::MassType::groomed), Tau32());
 //*************************************************************************************************
    
  //Boolean for MC/Data
    is_mc = (ctx.get("dataset_type") == "MC");

 
///COMMON Modules
    common.reset(new CommonModules());    //comes with Muon/Electron cleaner, JetCorrector/Smearer, MClumiweight and mcPileupReweight
    common->switch_jetlepcleaner(true);
    common->set_electron_id(EleId);
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
    topjet_cleaner      .reset(new TopJetCleaner(ctx, TopJetId(PtEtaCut(200., 2.4))));
    topjetlepton_cleaner .reset(new TopJetLeptonDeltaRCleaner(.8));
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
    
 //Jet Selection
    jet_sel.reset(new NJetSelection(4,-1, JetId(PtEtaCut(50., 2.4)))); 
    
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
    h_input_muon  .reset(new MuonHists(ctx, "input_Muons"));
    h_input_topjet.reset(new TopJetHists(ctx, "input_TopJets"));
    h_input_lumi  .reset(new LuminosityHists(ctx, "input_Lumi"));
    
    h_cleaner       .reset(new TstarPreSelectionHists(ctx, "cleaner"));
    h_cleaner_event .reset(new EventHists(ctx, "cleaner_Event"));
    h_cleaner_bJet  .reset(new TstarSelectionHists(ctx, "cleaner_bJet"));
    h_cleaner_jet   .reset(new JetHists(ctx, "cleaner_Jets",6));
    h_cleaner_ele   .reset(new ElectronHists(ctx, "cleaner_Electrons"));
    h_cleaner_muon  .reset(new MuonHists(ctx, "cleaner_Muons"));
    h_cleaner_topjet.reset(new TopJetHists(ctx, "cleaner_TopJets"));
    h_cleaner_lumi  .reset(new LuminosityHists(ctx, "cleaner_Lumi"));
    
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
    h_jet_muon  .reset(new MuonHists(ctx, "4Jets_Muons"));
    h_jet_topjet.reset(new TopJetHists(ctx, "4Jets_TopJets")); 
    h_jet_lumi  .reset(new LuminosityHists(ctx, "4Jets_Lumi"));
    
    h_output       .reset(new TstarPreSelectionHists(ctx, "4Jets"));
    h_output_event .reset(new EventHists(ctx, "4Jets_Event"));
    h_output_bJet  .reset(new TstarSelectionHists(ctx, "4Jets_bJet"));
    h_output_jet   .reset(new JetHists(ctx, "4Jets_Jets",6));
    h_output_ele   .reset(new ElectronHists(ctx, "4Jets_Electrons"));
    h_output_muon  .reset(new MuonHists(ctx, "4Jets_Muons"));
    h_output_topjet.reset(new TopJetHists(ctx, "4Jets_TopJets")); 
    h_output_lumi  .reset(new LuminosityHists(ctx, "4Jets_Lumi"));
    

//*****************************************************************************************************************
}


bool TstarPreSelectionModule::process(Event & event) {
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
  //              TopJetLeptonCleaner (0.8) ;
  //              TopJetCleaner (PtEtaCut(200., 2.4), Type2TopTag(105,220,Type2TopTag::MassType::groomed), Tau32());
  //
  //              Lepton selection:
  //                         Muon channel:     exactly one muon (Tight ID, pT>53 GeV)
  //                         Electron channel: exactly one electron (Spring16 Tight ID, pT>50 GeV)
  //
  //              Jet selection:
  //                         at least 4 jets (WP_LOOSE, pT>50 GeV) 
  //
  // *************************************************************************************************************

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
  

  //**********  Event Correctors and Cleaning **********************************
  // COMMON MODULES
    bool pass_common = common->process(event);
    if(!pass_common) return false;
  
  //Additional Cleaner 
  
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
      else throw runtime_error("TstarPreSelectionModule: TopJetCorrector: run number not covered");
    }

    topjetlepton_cleaner ->process(event);
    topjet_cleaner      ->process(event);

    //sort objects by pT
    sort_by_pt<Jet>(*event.jets);
    sort_by_pt<TopJet>(*event.topjets);

    
    h_cleaner       ->fill(event);
    h_cleaner_event ->fill(event);
    h_cleaner_bJet  ->fill(event);
    h_cleaner_jet   ->fill(event);
    h_cleaner_ele   ->fill(event);
    h_cleaner_muon  ->fill(event);
    h_cleaner_topjet->fill(event);
    h_cleaner_lumi  ->fill(event);
 //*****************************************************************************   

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

 //Recover uncleaned Jets 
    event.jets->clear();
    event.jets->reserve(uncleaned_jets->size());
    for(const auto & j : *uncleaned_jets) event.jets->push_back(j); 
    sort_by_pt<Jet>(*event.jets);
    
 //Recover uncleaned TopJets 
    event.topjets->clear();
    event.topjets->reserve(uncleaned_topjets->size());
    for(const auto & j : *uncleaned_topjets) event.topjets->push_back(j); 
    sort_by_pt<TopJet>(*event.topjets);
    
 //Dump output 
    h_output        ->fill(event);
    h_output_event  ->fill(event);
    h_output_bJet   ->fill(event);
    h_output_jet    ->fill(event);
    h_output_ele    ->fill(event);
    h_output_muon   ->fill(event);
    h_output_topjet ->fill(event);
    h_output_lumi   ->fill(event);
    
    return true;
}
  
  UHH2_REGISTER_ANALYSIS_MODULE(TstarPreSelectionModule)
}

