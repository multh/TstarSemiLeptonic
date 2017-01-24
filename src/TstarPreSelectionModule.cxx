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
/** \brief module to produce "PreSelection" ntuples for the T*T*->ttbar gg semileptonic analysis
 *  NOTE: output ntuple contains uncleaned jets (no jet-lepton cleaning, no JER smearing)
 */
class TstarPreSelectionModule: public AnalysisModule {

 public:
  explicit TstarPreSelectionModule(Context & ctx);
  virtual bool process(Event & event) override;

 private:
  unique_ptr<CommonModules>  common;

  unique_ptr<JetCleaner> jet_cleaner;
  unique_ptr<JetLeptonCleaner> jetlepton_cleaner;
  unique_ptr<MuonCleaner> muon_cleaner;
  unique_ptr<JetCleaner>                  topjet_IDcleaner;
  unique_ptr<TopJetCorrector>             topjet_corrector;
  unique_ptr<TopJetLeptonDeltaRCleaner>   topjetlepton_cleaner;
  unique_ptr<TopJetCleaner>               topjet_cleaner;

  unique_ptr<AnalysisModule> SF_muonID, SF_muonTrigger;

// declare the Selections to use
  unique_ptr<Selection> trigger_sel, nmuon_sel, jet_sel, ht_sel, lumi_sel;


  // store the Hists collection as member variables
  unique_ptr<Hists> h_input, h_input_event,  h_input_bJet, h_input_jet, h_input_ele, h_input_muon, h_input_topjet, h_input_lumi;
  unique_ptr<Hists> h_trigger, h_trigger_event,  h_trigger_bJet, h_trigger_jet, h_trigger_ele, h_trigger_muon, h_trigger_topjet, h_trigger_lumi;
  unique_ptr<Hists> h_cleaner, h_cleaner_event,  h_cleaner_bJet, h_cleaner_jet, h_cleaner_ele, h_cleaner_muon, h_cleaner_topjet, h_cleaner_lumi;
  unique_ptr<Hists> h_lumi, h_lumi_event,  h_lumi_bJet, h_lumi_jet, h_lumi_ele, h_lumi_muon, h_lumi_topjet, h_lumi_lumi;
  unique_ptr<Hists> h_nmuon, h_nmuon_event, h_nmuon_bJet, h_nmuon_jet, h_nmuon_ele, h_nmuon_muon, h_nmuon_topjet, h_nmuon_lumi; 
  unique_ptr<Hists> h_jet, h_jet_event, h_jet_bJet, h_jet_jet, h_jet_ele, h_jet_muon, h_jet_topjet, h_jet_lumi;
  unique_ptr<Hists> h_ht, h_ht_event, h_ht_bJet, h_ht_jet, h_ht_ele, h_ht_muon, h_ht_topjet, h_ht_lumi;

  MuonId     MuId;
  ElectronId EleId;
  bool is_mc;
};

TstarPreSelectionModule::TstarPreSelectionModule(Context & ctx){


  MuId  = AndId<Muon>(MuonIDTight(), PtEtaCut(45., 2.1));
  EleId = AndId<Electron>(ElectronID_PHYS14_25ns_tight_noIso, PtEtaSCCut(50., 2.5));
  const JetId jetID(JetPFID(JetPFID::WP_LOOSE));
  const TopJetId topjetID = AndId<TopJet>(Type2TopTag(110,240,Type2TopTag::MassType::groomed), Tau32());
  string sys_muonID   = ctx.get("sys_muonID");
  string sys_muonTrig = ctx.get("sys_muonTrig");




///COMMON Modules
   common.reset(new CommonModules());
   common->switch_jetlepcleaner(true);
   common->set_electron_id(EleId);
   common->set_muon_id(MuId);
   common->set_jet_id(jetID);
   common->init(ctx);
   ///
  SF_muonID.reset(new MCMuonScaleFactor(ctx, "~/CMSSW_7_6_3/src/UHH2/common/data/MuonID_Z_RunCD_Reco76X_Feb15.root", "MC_NUM_TightIDandIPCut_DEN_genTracks_PAR_pt_spliteta_bin1", 1, "tightID",sys_muonID)); 
  SF_muonTrigger.reset(new MCMuonScaleFactor(ctx, "~/CMSSW_7_6_3/src/UHH2/common/data/SingleMuonTrigger_Z_RunCD_Reco76X_Feb15.root", "runD_Mu45_eta2p1_PtEtaBins", 0.5, "trigger",sys_muonTrig));

   jet_cleaner.reset(new JetCleaner(ctx,30.0,2.5));
   is_mc = (ctx.get("dataset_type") == "MC");

   std::vector<std::string> JEC_AK8;
   if(is_mc){
    JEC_AK8 = JERFiles::Fall15_25ns_L123_AK8PFchs_MC;
   }
  else {
    JEC_AK8 = JERFiles::Fall15_25ns_L123_AK8PFchs_DATA;
   }

  topjet_IDcleaner    .reset(new JetCleaner(ctx, jetID));
  topjet_corrector    .reset(new TopJetCorrector(ctx, JEC_AK8));
  topjetlepton_cleaner.reset(new TopJetLeptonDeltaRCleaner(.8));
  topjet_cleaner      .reset(new TopJetCleaner(ctx, TopJetId(PtEtaCut(400., 2.4))));
 
///Selections
   //PreSelection

   trigger_sel.reset(new TriggerSelection("HLT_Mu45_eta2p1_v*"));
   nmuon_sel.reset(new NMuonSelection(1, 1));
   jet_sel.reset(new NJetSelection(4,-1, JetId(PtEtaCut(50., 2.4)))); 
   ht_sel.reset(new HtSelection(500,-1));
   lumi_sel.reset(new LumiSelection(ctx));

  
  ///HIST Classes
  h_input       .reset(new TstarPreSelectionHists(ctx, "input"));
  h_input_event .reset(new EventHists(ctx, "input_Event"));
  h_input_bJet  .reset(new TstarSelectionHists(ctx, "input_bJet"));
  h_input_jet   .reset(new JetHists(ctx, "input_Jets"));
  h_input_ele   .reset(new ElectronHists(ctx, "input_Electrons"));
  h_input_muon   .reset(new MuonHists(ctx, "input_Muons"));
  h_input_topjet.reset(new TopJetHists(ctx, "input_TopJets"));
  h_input_lumi  .reset(new LuminosityHists(ctx, "input_Lumi"));

  h_trigger       .reset(new TstarPreSelectionHists(ctx, "trigger"));
  h_trigger_event .reset(new EventHists(ctx, "trigger_Event"));
  h_trigger_bJet  .reset(new TstarSelectionHists(ctx, "trigger_bJet"));
  h_trigger_jet   .reset(new JetHists(ctx, "trigger_Jets"));
  h_trigger_ele   .reset(new ElectronHists(ctx, "trigger_Electrons"));
  h_trigger_muon   .reset(new MuonHists(ctx, "trigger_Muons"));
  h_trigger_topjet.reset(new TopJetHists(ctx, "trigger_TopJets"));
  h_trigger_lumi  .reset(new LuminosityHists(ctx, "trigger_Lumi"));

  h_cleaner       .reset(new TstarPreSelectionHists(ctx, "cleaner"));
  h_cleaner_event .reset(new EventHists(ctx, "cleaner_Event"));
  h_cleaner_bJet  .reset(new TstarSelectionHists(ctx, "cleaner_bJet"));
  h_cleaner_jet   .reset(new JetHists(ctx, "cleaner_Jets"));
  h_cleaner_ele   .reset(new ElectronHists(ctx, "cleaner_Electrons"));
  h_cleaner_muon   .reset(new MuonHists(ctx, "cleaner_Muons"));
  h_cleaner_topjet.reset(new TopJetHists(ctx, "cleaner_TopJets"));
  h_cleaner_lumi  .reset(new LuminosityHists(ctx, "cleaner_Lumi"));

  h_lumi       .reset(new TstarPreSelectionHists(ctx, "lumi"));
  h_lumi_event .reset(new EventHists(ctx, "lumi_Event"));
  h_lumi_bJet  .reset(new TstarSelectionHists(ctx, "lumi_bJet"));
  h_lumi_jet   .reset(new JetHists(ctx, "lumi_Jets"));
  h_lumi_ele   .reset(new ElectronHists(ctx, "lumi_Electrons"));
  h_lumi_muon   .reset(new MuonHists(ctx, "lumi_Muons"));
  h_lumi_topjet.reset(new TopJetHists(ctx, "lumi_TopJets"));
  h_lumi_lumi  .reset(new LuminosityHists(ctx, "lumi_Lumi"));

  h_nmuon       .reset(new TstarPreSelectionHists(ctx, "1Muon"));
  h_nmuon_event .reset(new EventHists(ctx, "1Muon_Event"));
  h_nmuon_bJet  .reset(new TstarSelectionHists(ctx, "1Muon_bJet"));
  h_nmuon_jet   .reset(new JetHists(ctx, "1Muon_Jets",6));
  h_nmuon_ele   .reset(new ElectronHists(ctx, "1Muon_Electrons"));
  h_nmuon_muon  .reset(new MuonHists(ctx, "1Muon_Muons"));
  h_nmuon_topjet.reset(new TopJetHists(ctx, "1Muon_TopJets")); 
  h_nmuon_lumi  .reset(new LuminosityHists(ctx, "1Muon_Lumi"));

  h_jet       .reset(new TstarPreSelectionHists(ctx, "4Jets"));
  h_jet_event .reset(new EventHists(ctx, "4Jets_Event"));
  h_jet_bJet  .reset(new TstarSelectionHists(ctx, "4Jets_bJet"));
  h_jet_jet   .reset(new JetHists(ctx, "4Jets_Jets",6));
  h_jet_ele   .reset(new ElectronHists(ctx, "4Jets_Electrons"));
  h_jet_muon   .reset(new MuonHists(ctx, "4Jets_Muons"));
  h_jet_topjet.reset(new TopJetHists(ctx, "4Jets_TopJets")); 
  h_jet_lumi  .reset(new LuminosityHists(ctx, "4Jets_Lumi"));

  h_ht       .reset(new TstarPreSelectionHists(ctx, "HT500"));
  h_ht_event .reset(new EventHists(ctx, "HT500_Event"));
  h_ht_bJet  .reset(new TstarSelectionHists(ctx, "HT500_bJet"));
  h_ht_jet   .reset(new JetHists(ctx, "HT500_Jets",6));
  h_ht_ele   .reset(new ElectronHists(ctx, "HT500_Electrons"));
  h_ht_muon   .reset(new MuonHists(ctx, "HT500_Muons"));
  h_ht_topjet.reset(new TopJetHists(ctx, "HT500_TopJets")); 
  h_ht_lumi  .reset(new LuminosityHists(ctx, "HT500_Lumi"));
}

bool TstarPreSelectionModule::process(Event & event) {

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
 
if(!trigger_sel->passes(event)) return false;
    SF_muonTrigger->process(event);
  h_trigger       ->fill(event);
  h_trigger_event ->fill(event);
  h_trigger_bJet  ->fill(event);
  h_trigger_jet   ->fill(event);
  h_trigger_ele   ->fill(event);
  h_trigger_muon  ->fill(event);
  h_trigger_topjet->fill(event);
  h_trigger_lumi  ->fill(event);


  // COMMON MODULES
  bool pass_common = common->process(event);
    if(!pass_common) return false;
    jet_cleaner->process(event);
    topjet_IDcleaner    ->process(event);
    topjet_corrector    ->process(event);
    topjetlepton_cleaner->process(event);
    topjet_cleaner->process(event);
  sort_by_pt<TopJet>(*event.topjets);

    SF_muonID  ->process(event);
  
  h_cleaner       ->fill(event);
  h_cleaner_event ->fill(event);
  h_cleaner_bJet  ->fill(event);
  h_cleaner_jet   ->fill(event);
  h_cleaner_ele   ->fill(event);
  h_cleaner_muon  ->fill(event);
  h_cleaner_topjet->fill(event);
  h_cleaner_lumi  ->fill(event);
 
  // LEPTON PRE-SELECTION
  if(!nmuon_sel->passes(event)) return false;
  h_nmuon        ->fill(event);
  h_nmuon_event  ->fill(event);
  h_nmuon_bJet   ->fill(event);
  h_nmuon_jet    ->fill(event);
  h_nmuon_ele    ->fill(event);
  h_nmuon_muon    ->fill(event);
  h_nmuon_topjet ->fill(event);
  h_nmuon_lumi   ->fill(event);
  
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
