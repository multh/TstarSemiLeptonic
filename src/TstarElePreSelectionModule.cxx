#include <iostream>
#include <memory>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/Selection.h"

#include "UHH2/common/include/MCWeight.h"
#include <UHH2/common/include/CommonModules.h>
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
#include "UHH2/common/include/JetCorrections.h"
#include "UHH2/common/include/ObjectIdUtils.h"
#include "UHH2/common/include/Utils.h"
#include "UHH2/common/include/TopPtReweight.h"

#include "UHH2/TstarSemiLeptonic/include/TstarSemiLeptonicSelections.h"
#include "UHH2/TstarSemiLeptonic/include/TstarSemiLeptonicUtils.h"
#include "UHH2/TstarSemiLeptonic/include/TstarPreSelectionHists.h"
#include <UHH2/TstarSemiLeptonic/include/TstarSelectionHists.h>


using namespace uhh2;
using namespace std;

namespace uhh2examples {

//*****************************************************************************************************
//
// \module for the T*T*->ttbar gg semileptonic analysis
//
//*****************************************************************************************************

  class TstarElePreSelectionModule: public AnalysisModule {
    
  public:
    explicit TstarElePreSelectionModule(Context & ctx);
    virtual bool process(Event & event) override;
    
  private:
    enum lepton { muon, elec };
    lepton channel_;
    
    //Common Modules 
    unique_ptr<CommonModules>               common;      //comes with Muon/Electron cleaner, JetCorrector/Smearer /MClumiweight and mcPileupReweight
    
  //Corrector and Cleaner
    unique_ptr<JetCleaner>                  topjet_IDcleaner;
    unique_ptr<TopJetCorrector>             topjet_corrector_MC;
    unique_ptr<TopJetCorrector>             topjet_corrector_BCD;
    unique_ptr<TopJetCorrector>             topjet_corrector_EFearly;
    unique_ptr<TopJetCorrector>             topjet_corrector_FlateG;
    unique_ptr<TopJetCorrector>             topjet_corrector_H;

    unique_ptr<SubJetCorrector>             subjet_corrector_MC;
    unique_ptr<SubJetCorrector>             subjet_corrector_BCD;
    unique_ptr<SubJetCorrector>             subjet_corrector_EFearly;
    unique_ptr<SubJetCorrector>             subjet_corrector_FlateG;
    unique_ptr<SubJetCorrector>             subjet_corrector_H;

    unique_ptr<JetCleaner>                  jet_cleaner_before2D;                 //Jet cleaner before 2D cut
    unique_ptr<JetCleaner>                  jet_cleaner_after2D;                  //Jet cleaner after 2D cut

    unique_ptr<TopJetLeptonDeltaRCleaner>   topjetlepton_cleaner;
    unique_ptr<GenericJetResolutionSmearer> topjetER_smearer;
   
  // *********** Pre-Selections for Analysis *********************************************************************************************************** 
  // declare Selections
    unique_ptr<Selection>                   trigger_Mu50;
    unique_ptr<Selection>                   trigger_TkMu50;

    unique_ptr<Selection>                   trigger_Ele27;
    unique_ptr<Selection>                   trigger_Ele115;

    unique_ptr<Selection>                   lumi_sel;
    unique_ptr<AndSelection>                lep_sel;
    unique_ptr<Selection>                   twodcut_sel;                          //QCD rejection
    unique_ptr<Selection>                   jet_sel;
     
    //*****************************************************************************************************************************************************


  //****************************** Histogramms **********************************************************************************************************
  // store the Hists collection as member variables
    unique_ptr<Hists> h_input,     h_input_event,     h_input_jet,     h_input_ele,     h_input_muon,     h_input_topjet,     h_input_lumi;
    unique_ptr<Hists> h_trigger,   h_trigger_event,   h_trigger_jet,   h_trigger_ele,   h_trigger_muon,   h_trigger_topjet,   h_trigger_lumi;
    unique_ptr<Hists> h_cleaner,   h_cleaner_event,   h_cleaner_jet,   h_cleaner_ele,   h_cleaner_muon,   h_cleaner_topjet,   h_cleaner_lumi;
    unique_ptr<Hists> h_lep,       h_lep_event,       h_lep_jet,       h_lep_ele,       h_lep_muon,       h_lep_topjet,       h_lep_lumi; 
    unique_ptr<Hists> h_twodcut,   h_twodcut_event,   h_twodcut_jet,   h_twodcut_ele,   h_twodcut_muon,   h_twodcut_topjet,   h_twodcut_lumi;
    unique_ptr<Hists> h_jet,       h_jet_event,       h_jet_jet,       h_jet_ele,       h_jet_muon,       h_jet_topjet,       h_jet_lumi;
    unique_ptr<Hists> h_output,    h_output_event,    h_output_jet,    h_output_ele,    h_output_muon,    h_output_topjet,    h_output_lumi;

  //*****************************************************************************************************************************************************  

  //Set IDs
    MuonId     MuId;
    ElectronId EleId;
    JetId      jetID;

    bool is_mc;
    bool debug;
  };


  TstarElePreSelectionModule::TstarElePreSelectionModule(Context & ctx){
    
 //********  New IDs for Summer 2016 Dataset ********************************************************
 //Leptons
    MuId  = AndId<Muon>(MuonIDHighPt(), PtEtaCut(53., 2.4));                     //Muon ID:   Muon POG: HighPtID for HLT_Mu50_v* triggers.
    EleId = AndId<Electron>(ElectronID_Spring16_tight, PtEtaCut(50.0, 2.4));     //ElectronID: Egamma POG provided efficiency curves for WP, WP tight has no real plateau after pT>45 GeV.  
     
 //Jets
    jetID = AndId<Jet>(JetPFID(JetPFID::WP_LOOSE), PtEtaCut(15.0, 2.4));
 //*************************************************************************************************
    
  //Boolean for MC/Data
    is_mc = (ctx.get("dataset_type") == "MC");
    debug = false;
    
///COMMON Modules
    common.reset(new CommonModules());    //comes with Muon/Electron cleaner, JetCorrector/Smearer, MClumiweight and mcPileupReweight
    common->switch_jetlepcleaner(true);
    common->set_electron_id(EleId);
    common->set_muon_id(MuId);
    common->set_jet_id(jetID);
    common->init(ctx);
  ////
  
  
//*********** Event Corrector and Cleaner **********************************************************************************************
    //TopJet Corector
    if(is_mc){
      topjet_corrector_MC      .reset(new TopJetCorrector(ctx,JERFiles::Summer16_23Sep2016_V4_L123_AK8PFchs_MC));           //For MC
      
      subjet_corrector_MC      .reset(new SubJetCorrector(ctx,JERFiles::Summer16_23Sep2016_V4_L123_AK4PFchs_MC));
    }
    else {                                                                                                            //For Data ->
      topjet_corrector_BCD     .reset(new TopJetCorrector(ctx,JERFiles::Summer16_23Sep2016_V4_BCD_L123_AK8PFchs_DATA));    //            Run Period BCD
      topjet_corrector_EFearly .reset(new TopJetCorrector(ctx,JERFiles::Summer16_23Sep2016_V4_EF_L123_AK8PFchs_DATA)); //            Run Period EF
      topjet_corrector_FlateG  .reset(new TopJetCorrector(ctx,JERFiles::Summer16_23Sep2016_V4_G_L123_AK8PFchs_DATA));   //            Run Period G
      topjet_corrector_H       .reset(new TopJetCorrector(ctx,JERFiles::Summer16_23Sep2016_V4_H_L123_AK8PFchs_DATA));        //            Run Period H
      
      subjet_corrector_BCD     .reset(new SubJetCorrector(ctx,JERFiles::Summer16_23Sep2016_V4_BCD_L123_AK4PFchs_DATA));    //            Run Period BCD
      subjet_corrector_EFearly .reset(new SubJetCorrector(ctx,JERFiles::Summer16_23Sep2016_V4_EF_L123_AK4PFchs_DATA)); //            Run Period EF
      subjet_corrector_FlateG  .reset(new SubJetCorrector(ctx,JERFiles::Summer16_23Sep2016_V4_G_L123_AK4PFchs_DATA));   //            Run Period G
      subjet_corrector_H       .reset(new SubJetCorrector(ctx,JERFiles::Summer16_23Sep2016_V4_H_L123_AK4PFchs_DATA));        //            Run Period H
    }
    
    jet_cleaner_before2D               .reset(new JetCleaner(ctx, 15., 2.4));
    jet_cleaner_after2D                .reset(new JetCleaner(ctx, 30., 2.4));
    
    //TopJet Cleaner and TopJetLepton Cleaner
    topjetlepton_cleaner       .reset(new TopJetLeptonDeltaRCleaner(.8));
   
  //**************************************************************************************************************************************


  //*******************  Selections  *****************************************************************************************************

  //************* Lepton Selection **********************************************************
  //Get Channel: Muon or Electon
    const std::string& channel = ctx.get("channel", "");
    if     (channel == "muon") channel_ = muon;
    else if(channel == "elec") channel_ = elec;
    else throw std::runtime_error("TstarPreSelectionModule -- undefined argument for 'channel' key in xml file (must be 'muon' or 'elec'): "+channel);
    
    //Trigger Selection

    trigger_Mu50.reset(new TriggerSelection("HLT_Mu50_v*"));              //As recommended on MuonTwiki for Non-iso Muons
    trigger_TkMu50.reset(new TriggerSelection("HLT_TkMu50_v*"));
 
    trigger_Ele27.reset(new TriggerSelection("HLT_Ele27_WPTight_Gsf_v*"));
    trigger_Ele115.reset(new TriggerSelection("HLT_Ele115_CaloIdVT_GsfTrkIdT_v*"));
    

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
    
    ///2D Cut Lepton-Jets
    twodcut_sel               .reset(new TwoDCut(.3, 25.));   //Still under investigation! QCD Problems  (.4, 30.)
    ///
    
    //Jet Selection
    jet_sel.reset(new NJetSelection(4,-1, JetId(PtEtaCut(50., 2.4)))); 

    //Lumi Selection (For Data Only)
    lumi_sel.reset(new LumiSelection(ctx));

//******************************************************************************************************************

//*******************  Histogramms  ********************************************************************************
  ///HIST Classes
    h_input           .reset(new TstarPreSelectionHists(ctx, "input"));
    h_input_event     .reset(new EventHists(ctx, "input_Event"));
    h_input_jet       .reset(new JetHists(ctx, "input_Jets",6));
    h_input_ele       .reset(new ElectronHists(ctx, "input_Electrons"));
    h_input_muon      .reset(new MuonHists(ctx, "input_Muons"));
    h_input_topjet    .reset(new TopJetHists(ctx, "input_TopJets"));
    h_input_lumi      .reset(new LuminosityHists(ctx, "input_Lumi"));
    
    h_trigger         .reset(new TstarPreSelectionHists(ctx, "trigger"));
    h_trigger_event   .reset(new EventHists(ctx, "trigger_Event"));
    h_trigger_jet     .reset(new JetHists(ctx, "trigger_Jets",6));
    h_trigger_ele     .reset(new ElectronHists(ctx, "trigger_Electrons"));
    h_trigger_muon    .reset(new MuonHists(ctx, "trigger_Muons"));
    h_trigger_topjet  .reset(new TopJetHists(ctx, "trigger_TopJets"));
    h_trigger_lumi    .reset(new LuminosityHists(ctx, "trigger_Lumi"));

    h_cleaner         .reset(new TstarPreSelectionHists(ctx, "cleaner"));
    h_cleaner_event   .reset(new EventHists(ctx, "cleaner_Event"));
    h_cleaner_jet     .reset(new JetHists(ctx, "cleaner_Jets",6));
    h_cleaner_ele     .reset(new ElectronHists(ctx, "cleaner_Electrons"));
    h_cleaner_muon    .reset(new MuonHists(ctx, "cleaner_Muons"));
    h_cleaner_topjet  .reset(new TopJetHists(ctx, "cleaner_TopJets"));
    h_cleaner_lumi    .reset(new LuminosityHists(ctx, "cleaner_Lumi"));
    
    h_lep       .reset(new TstarPreSelectionHists(ctx, "1Lepton"));
    h_lep_event .reset(new EventHists(ctx, "1Lepton_Event"));
    h_lep_jet   .reset(new JetHists(ctx, "1Lepton_Jets",6));
    h_lep_ele   .reset(new ElectronHists(ctx, "1Lepton_Electrons"));
    h_lep_muon  .reset(new MuonHists(ctx, "1Lepton_Muons"));
    h_lep_topjet.reset(new TopJetHists(ctx, "1Lepton_TopJets")); 
    h_lep_lumi  .reset(new LuminosityHists(ctx, "1Lepton_Lumi"));

    h_twodcut       .reset(new TstarPreSelectionHists(ctx, "2DCut"));
    h_twodcut_event .reset(new EventHists(ctx, "2DCut_Event"));
    h_twodcut_jet   .reset(new JetHists(ctx, "2DCut_Jets",6));
    h_twodcut_ele   .reset(new ElectronHists(ctx, "2DCut_Electrons"));
    h_twodcut_muon  .reset(new MuonHists(ctx, "2DCut_Muons"));
    h_twodcut_topjet.reset(new TopJetHists(ctx, "2DCut_TopJets")); 
    h_twodcut_lumi  .reset(new LuminosityHists(ctx, "2DCut_Lumi"));

    h_jet       .reset(new TstarPreSelectionHists(ctx, "4Jets"));
    h_jet_event .reset(new EventHists(ctx, "4Jets_Event"));
    h_jet_jet   .reset(new JetHists(ctx, "4Jets_Jets",6));
    h_jet_ele   .reset(new ElectronHists(ctx, "4Jets_Electrons"));
    h_jet_muon  .reset(new MuonHists(ctx, "4Jets_Muons"));
    h_jet_topjet.reset(new TopJetHists(ctx, "4Jets_TopJets")); 
    h_jet_lumi  .reset(new LuminosityHists(ctx, "4Jets_Lumi"));

    h_output       .reset(new TstarPreSelectionHists(ctx, "output"));
    h_output_event .reset(new EventHists(ctx, "output_Event"));
    h_output_jet   .reset(new JetHists(ctx, "output_Jets",6));
    h_output_ele   .reset(new ElectronHists(ctx, "output_Electrons"));
    h_output_muon  .reset(new MuonHists(ctx, "output_Muons"));
    h_output_topjet.reset(new TopJetHists(ctx, "output_TopJets")); 
    h_output_lumi  .reset(new LuminosityHists(ctx, "output_Lumi"));
  
//*****************************************************************************************************************
}


  bool TstarElePreSelectionModule::process(Event & event) {
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
  //                        Jets(WP_LOOSE, pT>15 GeV));
  //
  //              TopJetCorrector (Summer16_23Sep2016_AK8PFchs);
  //              SubJetCorrector (Summer16_23Sep2016_AK4PFchs)  
  //              TopJetLeptonCleaner (0.8) ;
  //
  //              Trigger: HLT_Mu50_v* || HLT_TkMu50_v*
  //
  //              Lepton selection:
  //                         Muon channel:     exactly one muon (High Pt ID, pT>53 GeV)
  //                         Electron channel: exactly one electron (Spring16 Tight ID, pT>50 GeV)
  //
  //              Jet selection:
  //                         at least 4 jets (WP_LOOSE, pT>50 GeV)               
  //
  // *************************************************************************************************************
    
    if(debug) cout<<"+++++++  New Event  ++++++++++++"<<endl;

  //Only for Data: Lumi-Selections
    if(!is_mc){
      if(debug) cout<<"Enter LumiSel: "<<endl;
      if(!lumi_sel->passes(event)) return false;
    }
    
    // dump input content
    h_input        ->fill(event);
    h_input_event  ->fill(event);
    h_input_jet    ->fill(event);
    h_input_ele    ->fill(event);
    h_input_muon   ->fill(event);
    h_input_topjet ->fill(event);
    h_input_lumi   ->fill(event);
    
    //// ############## Trigger Selection  ##################################################
    if(channel_ == muon){
      if (!is_mc){
	
	bool pass_Mu50 = trigger_Mu50->passes(event);
	if (event.run<274954) {
	  if (!pass_Mu50) return false;
	}
	else {
	  bool pass_TrkMu50 = trigger_TkMu50->passes(event);
	  if (!(pass_Mu50||pass_TrkMu50)) return false;
	}
      }
      
      else{
	bool pass_Mu50 = trigger_Mu50->passes(event);
	bool pass_TrkMu50 = trigger_TkMu50->passes(event);
	if (!(pass_Mu50||pass_TrkMu50)) return false;
      }

      if(debug) cout<<"Passed Muon triggers"<<endl;
    } 
    
    if(channel_ == elec){ 
      bool pass_Ele27 = trigger_Ele27->passes(event);
      bool pass_Ele115 = trigger_Ele115->passes(event);
      if(!(pass_Ele27||pass_Ele115)) return false;

      if(debug) cout<<"Passed Electron triggers"<<endl;
    }

    h_trigger       ->fill(event);
    h_trigger_event ->fill(event);
    h_trigger_jet   ->fill(event);
    h_trigger_ele   ->fill(event);
    h_trigger_muon  ->fill(event);
    h_trigger_topjet->fill(event);
    h_trigger_lumi  ->fill(event);

    //// ####################################################################################
    
    
    
    //**********  Event Correctors and Cleaning **********************************
    // COMMON MODULES
    bool pass_common = common->process(event);
    if(!pass_common) return false;
    if(debug) cout<<"Passed Common Modules: "<<endl;
    //Additional Cleaner 
    
    const int runnr_BCD = 276811;
    const int runnr_EFearly = 278802;
    const int runnr_FlateG = 280385;
    
    if(is_mc){
      topjet_corrector_MC->process(event);
      subjet_corrector_MC->process(event);
    }
    else{
      
      if(event.run <= runnr_BCD)          topjet_corrector_BCD->process(event);
      else if(event.run < runnr_EFearly)  topjet_corrector_EFearly->process(event);
      else if(event.run <= runnr_FlateG)  topjet_corrector_FlateG->process(event);
      else if(event.run > runnr_FlateG)   topjet_corrector_H->process(event);
      else throw runtime_error("TstarPreSelectionModule: TopJetCorrector: run number not covered");
      
      if(event.run <= runnr_BCD)          subjet_corrector_BCD->process(event);
      else if(event.run < runnr_EFearly)  subjet_corrector_EFearly->process(event);
      else if(event.run <= runnr_FlateG)  subjet_corrector_FlateG->process(event);
      else if(event.run > runnr_FlateG)   subjet_corrector_H->process(event);
      else throw runtime_error("TstarPreSelectionModule: SubJetCorrector run number not covered");
    }
    //sort objects by pT
    sort_by_pt<Jet>(*event.jets);
    sort_by_pt<TopJet>(*event.topjets);

    jet_cleaner_before2D ->process(event);
    topjetlepton_cleaner ->process(event);
    
    //sort objects by pT
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

    //*****************************************************************************   
    
    // LEPTON PRE-SELECTION
    if(!lep_sel->passes(event)) return false;
    
    h_lep        ->fill(event);
    h_lep_event  ->fill(event);
    h_lep_jet    ->fill(event);
    h_lep_ele    ->fill(event);
    h_lep_muon   ->fill(event);
    h_lep_topjet ->fill(event);
    h_lep_lumi   ->fill(event);

    if(debug){
      if(channel_ == muon) cout<<"Electron channel selection"<<endl;
      if(channel_ == elec) cout<<"Muon channel selection"<<endl;
      cout<<"After LeptonSel: "<<endl;
    }

    if(channel_ == muon){
    /// 2D-Cut for Muons
    const bool pass_twodcut = twodcut_sel->passes(event);
    if(!pass_twodcut) return false;
    
    h_twodcut        ->fill(event);
    h_twodcut_event  ->fill(event);
    h_twodcut_jet    ->fill(event);
    h_twodcut_ele    ->fill(event);
    h_twodcut_muon   ->fill(event);
    h_twodcut_topjet ->fill(event);
    h_twodcut_lumi   ->fill(event);
    if(debug) cout<<"After 2D-Cut: "<<endl;
    }
    
    //Second Jet-Cleaner
    jet_cleaner_after2D    ->process(event);
    
    
    // JET PRE-SELECTION
    if(!jet_sel->passes(event)) return false;
    
    h_jet        ->fill(event);
    h_jet_event  ->fill(event);
    h_jet_jet    ->fill(event);
    h_jet_ele    ->fill(event);
    h_jet_muon   ->fill(event);
    h_jet_topjet ->fill(event);
    h_jet_lumi   ->fill(event);
    if(debug) cout<<"After Jet Sel: "<<endl;
    ////
    
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
  
  UHH2_REGISTER_ANALYSIS_MODULE(TstarElePreSelectionModule)
}

