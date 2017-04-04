void plot_eff(){
 // All root files
  TFile *Tstar700_pre = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/PreSelection/Nominal/uhh2.AnalysisModuleRunner.MC.Tstar_M700.root","READ");
  TFile *Tstar700_post = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Nominal/uhh2.AnalysisModuleRunner.MC.Tstar_M700.root","READ");
  TDirectory *Tstar700_cleaner = Tstar700_pre  -> GetDirectory("cleaner");
  TDirectory *Tstar700_1Muon   = Tstar700_pre  -> GetDirectory("1Muon");
  TDirectory *Tstar700_4Jets   = Tstar700_pre  -> GetDirectory("4Jets");
  TDirectory *Tstar700_HT500   = Tstar700_pre  -> GetDirectory("HT500");
  TDirectory *Tstar700_2DCut   = Tstar700_post -> GetDirectory("twodcut");
  TDirectory *Tstar700_bTag    = Tstar700_post -> GetDirectory("bTag");
  TDirectory *Tstar700_5Jets   = Tstar700_post -> GetDirectory("5Jets");
  TDirectory *Tstar700_output  = Tstar700_post -> GetDirectory("output");


  TFile *Tstar1600_pre = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/PreSelection/Nominal/uhh2.AnalysisModuleRunner.MC.Tstar_M1600.root","READ");
  TFile *Tstar1600_post = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Nominal/uhh2.AnalysisModuleRunner.MC.Tstar_M1600.root","READ");
  TDirectory *Tstar1600_cleaner = Tstar1600_pre  -> GetDirectory("cleaner");
  TDirectory *Tstar1600_1Muon   = Tstar1600_pre  -> GetDirectory("1Muon");
  TDirectory *Tstar1600_4Jets   = Tstar1600_pre  -> GetDirectory("4Jets");
  TDirectory *Tstar1600_HT500   = Tstar1600_pre  -> GetDirectory("HT500");
  TDirectory *Tstar1600_2DCut   = Tstar1600_post -> GetDirectory("twodcut");
  TDirectory *Tstar1600_bTag    = Tstar1600_post -> GetDirectory("bTag");
  TDirectory *Tstar1600_5Jets   = Tstar1600_post -> GetDirectory("5Jets");
  TDirectory *Tstar1600_output  = Tstar1600_post -> GetDirectory("output");



  TFile *QCD_pre = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/PreSelection/Nominal/uhh2.AnalysisModuleRunner.MC.QCD.root","READ");
  TFile *QCD_post = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Nominal/uhh2.AnalysisModuleRunner.MC.QCD.root","READ");
  TDirectory *QCD_cleaner = QCD_pre  -> GetDirectory("cleaner");
  TDirectory *QCD_1Muon   = QCD_pre  -> GetDirectory("1Muon");
  TDirectory *QCD_4Jets   = QCD_pre  -> GetDirectory("4Jets");
  TDirectory *QCD_HT500   = QCD_pre  -> GetDirectory("HT500");
  TDirectory *QCD_2DCut   = QCD_post -> GetDirectory("twodcut");
  TDirectory *QCD_bTag    = QCD_post -> GetDirectory("bTag");
  TDirectory *QCD_5Jets   = QCD_post -> GetDirectory("5Jets");
  TDirectory *QCD_output  = QCD_post -> GetDirectory("output");
 

  TFile *ttbar_pre = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/PreSelection/Nominal/uhh2.AnalysisModuleRunner.MC.TTbar.root","READ");
  TFile *ttbar_post = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Nominal/uhh2.AnalysisModuleRunner.MC.TTbar.root","READ");
  TDirectory *ttbar_cleaner = ttbar_pre  -> GetDirectory("cleaner");
  TDirectory *ttbar_1Muon   = ttbar_pre  -> GetDirectory("1Muon");
  TDirectory *ttbar_4Jets   = ttbar_pre  -> GetDirectory("4Jets");
  TDirectory *ttbar_HT500   = ttbar_pre  -> GetDirectory("HT500");
  TDirectory *ttbar_2DCut   = ttbar_post -> GetDirectory("twodcut");
  TDirectory *ttbar_bTag    = ttbar_post -> GetDirectory("bTag");
  TDirectory *ttbar_5Jets   = ttbar_post -> GetDirectory("5Jets");
  TDirectory *ttbar_output  = ttbar_post -> GetDirectory("output");
 
 TFile *WJets_pre = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/PreSelection/Nominal/uhh2.AnalysisModuleRunner.MC.WJets_HT.root","READ");
  TFile *WJets_post = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Nominal/uhh2.AnalysisModuleRunner.MC.WJets.root","READ");
  TDirectory *WJets_cleaner = WJets_pre  -> GetDirectory("cleaner");
  TDirectory *WJets_1Muon   = WJets_pre  -> GetDirectory("1Muon");
  TDirectory *WJets_4Jets   = WJets_pre  -> GetDirectory("4Jets");
  TDirectory *WJets_HT500   = WJets_pre  -> GetDirectory("HT500");
  TDirectory *WJets_2DCut   = WJets_post -> GetDirectory("twodcut");
  TDirectory *WJets_bTag    = WJets_post -> GetDirectory("bTag");
  TDirectory *WJets_5Jets   = WJets_post -> GetDirectory("5Jets");
  TDirectory *WJets_output  = WJets_post -> GetDirectory("output");

  TFile *ZJets_pre = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/PreSelection/Nominal/uhh2.AnalysisModuleRunner.MC.ZJets_HT.root","READ");
  TFile *ZJets_post = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Nominal/uhh2.AnalysisModuleRunner.MC.ZJets.root","READ");
  TDirectory *ZJets_cleaner = ZJets_pre -> GetDirectory("cleaner");
  TDirectory *ZJets_1Muon   = ZJets_pre -> GetDirectory("1Muon");
  TDirectory *ZJets_4Jets   = ZJets_pre -> GetDirectory("4Jets");
  TDirectory *ZJets_HT500   = ZJets_pre -> GetDirectory("HT500");
  TDirectory *ZJets_2DCut   = ZJets_post -> GetDirectory("twodcut");
  TDirectory *ZJets_bTag    = ZJets_post -> GetDirectory("bTag");
  TDirectory *ZJets_5Jets   = ZJets_post -> GetDirectory("5Jets");
  TDirectory *ZJets_output  = ZJets_post -> GetDirectory("output");
 

  /*****************************          Eff Hists       (SELECTIONS)                        ******************************/


 /*****************************      Ht           ******************************/
 TH1D *Selection_eff = new TH1D("Selection_eff","Selection efficiencies",8,0,8);

 //Get all bin content
 TH1D *eff_cleaner = (TH1D*)Tstar700_cleaner ->Get("sum_event_weights");
 Float_t Input      = eff_cleaner->GetBinContent(1);
 TH1D *eff_1Muon   = (TH1D*)Tstar700_1Muon->Get("sum_event_weights");
 Float_t Lepton     = eff_1Muon->GetBinContent(1);
 TH1D *eff_4Jets   = (TH1D*)Tstar700_4Jets->Get("sum_event_weights");
 Float_t Jets       = eff_4Jets->GetBinContent(1);
 TH1D *eff_HT500   = (TH1D*)Tstar700_HT500->Get("sum_event_weights");
 Float_t HT         = eff_HT500 ->GetBinContent(1);

 TH1D *eff_2DCut  = (TH1D*)Tstar700_2DCut->Get("sum_event_weights");
 Float_t twodcut   = eff_2DCut->GetBinContent(1);
 TH1D *eff_bTag   = (TH1D*)Tstar700_bTag->Get("sum_event_weights");
 Float_t bTag      = eff_bTag->GetBinContent(1);
 TH1D *eff_5Jets  = (TH1D*)Tstar700_5Jets->Get("sum_event_weights");
 Float_t Jets5     = eff_5Jets->GetBinContent(1);
 TH1D *eff_output = (TH1D*)Tstar700_output->Get("sum_event_weights");
 Float_t output      = eff_bTag->GetBinContent(1);

 //Fill Histogram
 Selection_eff->Fill(" After Trigger",Input/Input);
 Selection_eff->Fill(" = 1 Muon",Lepton/Input);
 Selection_eff->Fill(" #geq 4 Jets",Jets/Input);
 Selection_eff->Fill(" HT #geq 500 ",HT/Input);

 Selection_eff->Fill(" 2D-Cut",twodcut/Input);
 Selection_eff->Fill(" b-Tag",bTag/Input);
 Selection_eff->Fill(" #geq 5 Jets",Jets5/Input);
 Selection_eff->Fill(" Output",output/Input);

 //Attributes
 Selection_eff->SetLineColor(600); 
 Selection_eff->GetXaxis()->SetTitle("");
 Selection_eff->GetYaxis()->SetTitle("");
 Selection_eff->GetXaxis()->SetLabelSize(0.05);
 /*****************************      Ht           ******************************/
 TH1D *Selection_eff1600 = new TH1D("Selection_eff1600","Selection efficiencies M=1600",8,0,8);

 //Get all bin content
 TH1D *eff1600_cleaner = (TH1D*)Tstar1600_cleaner ->Get("sum_event_weights");
 Float_t Input_1600      = eff1600_cleaner->GetBinContent(1);
 TH1D *eff1600_1Muon   = (TH1D*)Tstar1600_1Muon->Get("sum_event_weights");
 Float_t Lepton_1600     = eff1600_1Muon->GetBinContent(1);
 TH1D *eff1600_4Jets   = (TH1D*)Tstar1600_4Jets->Get("sum_event_weights");
 Float_t Jets_1600       = eff1600_4Jets->GetBinContent(1);
 TH1D *eff1600_HT500   = (TH1D*)Tstar1600_HT500->Get("sum_event_weights");
 Float_t HT_1600         = eff1600_HT500 ->GetBinContent(1);

 TH1D *eff1600_2DCut  = (TH1D*)Tstar1600_2DCut->Get("sum_event_weights");
 Float_t twodcut_1600   = eff1600_2DCut->GetBinContent(1);
 TH1D *eff1600_bTag   = (TH1D*)Tstar1600_bTag->Get("sum_event_weights");
 Float_t bTag_1600      = eff1600_bTag->GetBinContent(1);
 TH1D *eff1600_5Jets  = (TH1D*)Tstar1600_5Jets->Get("sum_event_weights");
 Float_t Jets5_1600     = eff1600_5Jets->GetBinContent(1);
 TH1D *eff1600_output = (TH1D*)Tstar1600_output->Get("sum_event_weights");
 Float_t output_1600    = eff1600_bTag->GetBinContent(1);

 //Fill Histogram
 Selection_eff1600->Fill(" After Trigger",Input_1600/Input_1600);
 Selection_eff1600->Fill(" = 1 Muon",Lepton_1600/Input_1600);
 Selection_eff1600->Fill(" #geq 4 Jets",Jets_1600/Input_1600);
 Selection_eff1600->Fill(" HT #geq 500 ",HT_1600/Input_1600);

 Selection_eff1600->Fill(" 2D-Cut",twodcut_1600/Input_1600);
 Selection_eff1600->Fill(" b-Tag",bTag_1600/Input_1600);
 Selection_eff1600->Fill(" #geq 5 Jets",Jets5_1600/Input_1600);
 Selection_eff1600->Fill(" Output",output_1600/Input_1600);

 //Attributes
 Selection_eff1600->SetLineColor(432); 
 Selection_eff1600->GetXaxis()->SetTitle("Selections");
 Selection_eff1600->GetYaxis()->SetTitle("");
 
 



/*****************************      Background           ******************************/
  //QCD
 TH1D *Selection_eff_QCD = new TH1D("Selection_eff_QCD","Selection eff. QCD",8,0,8);

 //Get all bin content
 TH1D *eff_cleaner_QCD  = (TH1D*)QCD_cleaner->Get("sum_event_weights");
 Float_t Input_QCD = eff_cleaner_QCD->GetBinContent(1);
 TH1D *eff_1Muon_QCD  = (TH1D*)QCD_1Muon->Get("sum_event_weights");
 Float_t Lepton_QCD = eff_1Muon_QCD->GetBinContent(1);
 TH1D *eff_4Jets_QCD  = (TH1D*)QCD_4Jets->Get("sum_event_weights");
 Float_t Jets_QCD = eff_4Jets_QCD->GetBinContent(1);
 TH1D *eff_HT500_QCD  = (TH1D*)QCD_HT500->Get("sum_event_weights");
 Float_t HT_QCD =eff_HT500_QCD ->GetBinContent(1);

 TH1D *eff_twodcut_QCD  = (TH1D*)QCD_2DCut->Get("sum_event_weights");
 Float_t twodcut_QCD = eff_twodcut_QCD->GetBinContent(1);
 TH1D *eff_bTag_QCD  = (TH1D*)QCD_bTag->Get("sum_event_weights");
 Float_t bTag_QCD = eff_bTag_QCD->GetBinContent(1);
 TH1D *eff_5Jets_QCD  = (TH1D*)QCD_5Jets->Get("sum_event_weights");
 Float_t Jets5_QCD = eff_5Jets_QCD->GetBinContent(1);
 TH1D *eff_output_QCD  = (TH1D*)QCD_output->Get("sum_event_weights");
 Float_t output_QCD = eff_output_QCD->GetBinContent(1);

 //Fill Histogram
 Selection_eff_QCD->Fill(" Input",Input_QCD/Input_QCD);
 Selection_eff_QCD->Fill(" = 1 Muon",Lepton_QCD/Input_QCD);
 Selection_eff_QCD->Fill(" #geq 4 Jets",Jets_QCD/Input_QCD);
 Selection_eff_QCD->Fill(" HT #geq 500",HT_QCD/Input_QCD);

 Selection_eff_QCD->Fill(" 2D-Cut",twodcut_QCD/Input_QCD);
 Selection_eff_QCD->Fill(" b-Tag",bTag_QCD/Input_QCD);
 Selection_eff_QCD->Fill(" #geq 5 Jets",Jets5_QCD/Input_QCD);
 Selection_eff_QCD->Fill(" #output",output_QCD/Input_QCD);

 //Attributes
 Selection_eff_QCD->SetLineColor(880); 
 Selection_eff_QCD->GetXaxis()->SetTitle("Selections");
 Selection_eff_QCD->GetYaxis()->SetTitle("");


/*****************************      Background           ******************************/
  //TTbar
TH1D *Selection_eff_tt = new TH1D("Selection_eff_tt","Selection eff. tt",8,0,8);

 //Get all bin content
 TH1D *eff_cleaner_tt  = (TH1D*)ttbar_cleaner->Get("sum_event_weights");
 Float_t Input_tt = eff_cleaner_tt->GetBinContent(1);
 TH1D *eff_1Muon_tt  = (TH1D*)ttbar_1Muon->Get("sum_event_weights");
 Float_t Lepton_tt = eff_1Muon_tt->GetBinContent(1);
 TH1D *eff_4Jets_tt  = (TH1D*)ttbar_4Jets->Get("sum_event_weights");
 Float_t Jets_tt = eff_4Jets_tt->GetBinContent(1);
 TH1D *eff_HT500_tt  = (TH1D*)ttbar_HT500->Get("sum_event_weights");
 Float_t HT_tt =eff_HT500_tt->GetBinContent(1);

 TH1D *eff_twodcut_tt  = (TH1D*)ttbar_2DCut->Get("sum_event_weights");
 Float_t twodcut_tt = eff_twodcut_tt->GetBinContent(1);
 TH1D *eff_bTag_tt  = (TH1D*)ttbar_bTag->Get("sum_event_weights");
 Float_t bTag_tt = eff_bTag_tt->GetBinContent(1);
 TH1D *eff_5Jets_tt  = (TH1D*)ttbar_5Jets->Get("sum_event_weights");
 Float_t Jets5_tt = eff_5Jets_tt->GetBinContent(1);
 TH1D *eff_output_tt  = (TH1D*)ttbar_output->Get("sum_event_weights");
 Float_t output_tt = eff_output_tt->GetBinContent(1);

 //Fill Histogram
 Selection_eff_tt->Fill(" Input",Input_tt/Input_tt);
 Selection_eff_tt->Fill(" = 1 Muon",Lepton_tt/Input_tt);
 Selection_eff_tt->Fill(" #geq 4 Jets",Jets_tt/Input_tt);
 Selection_eff_tt->Fill(" HT #geq 500",HT_tt/Input_tt);

 Selection_eff_tt->Fill(" 2D-Cut",twodcut_tt/Input_tt);
 Selection_eff_tt->Fill(" b-Tag",bTag_tt/Input_tt);
 Selection_eff_tt->Fill(" #geq 5 Jets",Jets5_tt/Input_tt);
 Selection_eff_tt->Fill(" #output",output_tt/Input_tt);

 //Attributes
 Selection_eff_tt->SetLineColor(625); 
 Selection_eff_tt->GetXaxis()->SetTitle("Selections");
 Selection_eff_tt->GetYaxis()->SetTitle("");

/*****************************      Background           ******************************/
  //WJets
TH1D *Selection_eff_WJets = new TH1D("Selection_eff_WJets","Selection eff. WJets",8,0,8);

 //Get all bin content
 TH1D *eff_cleaner_WJets  = (TH1D*)WJets_cleaner->Get("sum_event_weights");
 Float_t Input_WJets = eff_cleaner_WJets->GetBinContent(1);
 TH1D *eff_1Muon_WJets  = (TH1D*)WJets_1Muon->Get("sum_event_weights");
 Float_t Lepton_WJets = eff_1Muon_WJets->GetBinContent(1);
 TH1D *eff_4Jets_WJets  = (TH1D*)WJets_4Jets->Get("sum_event_weights");
 Float_t Jets_WJets = eff_4Jets_WJets->GetBinContent(1);
 TH1D *eff_HT500_WJets  = (TH1D*)WJets_HT500->Get("sum_event_weights");
 Float_t HT_WJets =eff_HT500_WJets ->GetBinContent(1);

 TH1D *eff_twodcut_WJets  = (TH1D*)WJets_2DCut->Get("sum_event_weights");
 Float_t twodcut_WJets = eff_twodcut_WJets->GetBinContent(1);
 TH1D *eff_bTag_WJets  = (TH1D*)WJets_bTag->Get("sum_event_weights");
 Float_t bTag_WJets = eff_bTag_WJets->GetBinContent(1);
 TH1D *eff_5Jets_WJets  = (TH1D*)WJets_5Jets->Get("sum_event_weights");
 Float_t Jets5_WJets = eff_5Jets_WJets->GetBinContent(1);
 TH1D *eff_output_WJets  = (TH1D*)WJets_output->Get("sum_event_weights");
 Float_t output_WJets = eff_output_WJets->GetBinContent(1);

 //Fill Histogram
 Selection_eff_WJets->Fill(" Input",Input_WJets/Input_WJets);
 Selection_eff_WJets->Fill(" = 1 Muon",Lepton_WJets/Input_WJets);
 Selection_eff_WJets->Fill(" #geq 4 Jets",Jets_WJets/Input_WJets);
 Selection_eff_WJets->Fill(" HT #geq 500",HT_WJets/Input_WJets);

 Selection_eff_WJets->Fill(" 2D-Cut",twodcut_WJets/Input_WJets);
 Selection_eff_WJets->Fill(" b-Tag",bTag_WJets/Input_WJets);
 Selection_eff_WJets->Fill(" #geq 5 Jets",Jets5_WJets/Input_WJets);
 Selection_eff_WJets->Fill(" #output",output_WJets/Input_WJets);

 //Attributes
 Selection_eff_WJets->SetLineColor(408); 
 Selection_eff_WJets->GetXaxis()->SetTitle("Selections");
 Selection_eff_WJets->GetYaxis()->SetTitle("");



  //ZJets
TH1D *Selection_eff_ZJets = new TH1D("Selection_eff_ZJets","Selection eff. ZJets",8,0,8);

 //Get all bin content
 TH1D *eff_cleaner_ZJets  = (TH1D*)ZJets_cleaner->Get("sum_event_weights");
 Float_t Input_ZJets = eff_cleaner_ZJets->GetBinContent(1);
 TH1D *eff_1Muon_ZJets  = (TH1D*)ZJets_1Muon->Get("sum_event_weights");
 Float_t Lepton_ZJets = eff_1Muon_ZJets->GetBinContent(1);
 TH1D *eff_4Jets_ZJets  = (TH1D*)ZJets_4Jets->Get("sum_event_weights");
 Float_t Jets_ZJets = eff_4Jets_ZJets->GetBinContent(1);
 TH1D *eff_HT500_ZJets  = (TH1D*)ZJets_HT500->Get("sum_event_weights");
 Float_t HT_ZJets =eff_HT500_ZJets ->GetBinContent(1);

 TH1D *eff_twodcut_ZJets  = (TH1D*)ZJets_2DCut->Get("sum_event_weights");
 Float_t twodcut_ZJets = eff_twodcut_ZJets->GetBinContent(1);
 TH1D *eff_bTag_ZJets  = (TH1D*)ZJets_bTag->Get("sum_event_weights");
 Float_t bTag_ZJets = eff_bTag_ZJets->GetBinContent(1);
 TH1D *eff_5Jets_ZJets  = (TH1D*)ZJets_5Jets->Get("sum_event_weights");
 Float_t Jets5_ZJets = eff_5Jets_ZJets->GetBinContent(1);
 TH1D *eff_output_ZJets  = (TH1D*)ZJets_output->Get("sum_event_weights");
 Float_t output_ZJets = eff_output_ZJets->GetBinContent(1);

 //Fill Histogram
 Selection_eff_ZJets->Fill(" Input",Input_ZJets/Input_ZJets);
 Selection_eff_ZJets->Fill(" = 1 Muon",Lepton_ZJets/Input_ZJets);
 Selection_eff_ZJets->Fill(" #geq 4 Jets",Jets_ZJets/Input_ZJets);
 Selection_eff_ZJets->Fill(" HT #geq 500",HT_ZJets/Input_ZJets);

 Selection_eff_ZJets->Fill(" 2D-Cut",twodcut_ZJets/Input_ZJets);
 Selection_eff_ZJets->Fill(" b-Tag",bTag_ZJets/Input_ZJets);
 Selection_eff_ZJets->Fill(" #geq 5 Jets",Jets5_ZJets/Input_ZJets);
 Selection_eff_ZJets->Fill(" #output",output_ZJets/Input_ZJets);

 //Attributes
 Selection_eff_ZJets->SetLineColor(408); 
 Selection_eff_ZJets->GetXaxis()->SetTitle("Selections");
 Selection_eff_ZJets->GetYaxis()->SetTitle("");
 

  
 /*****************************         Write to file                   ******************************/
 /*
 TFile *f= new TFile("Efficiency.root","RECREATE");


Selection_eff ->Write();
Selection_eff2000 ->Write();
Selection_eff_QCD ->Write();
Selection_eff_tt ->Write();
Selection_eff_ZJets ->Write();
 f->Close();
 */

 TCanvas* c1 = new TCanvas("c1", "Selection Efficency", 800,800);

 Selection_eff->SetStats(0);
 Selection_eff -> SetLineWidth(2);
Selection_eff1600 -> SetLineWidth(2);
 Selection_eff_QCD -> SetLineWidth(2);
 Selection_eff_QCD->SetLineStyle(7);
 Selection_eff_tt -> SetLineWidth(2);
Selection_eff_tt->SetLineStyle(7);
 Selection_eff_ZJets -> SetLineWidth(2);
Selection_eff_ZJets->SetLineStyle(7);

 Selection_eff->Draw("Hist");
 Selection_eff1600->Draw("Hist SAME");
 Selection_eff_tt->Draw("Hist SAME");
 Selection_eff_QCD->Draw("Hist SAME");
 Selection_eff_ZJets->Draw("Hist SAME");

 leg = new TLegend(0.6,0.7,0.89,0.89);
 leg -> AddEntry("Selection_eff","T^* M=700 GeV");
 leg -> AddEntry("Selection_eff1600","T^* M=1600 GeV");
 leg -> AddEntry("Selection_eff_QCD","QCD");
 leg -> AddEntry("Selection_eff_tt","TTbar");
 leg -> AddEntry("Selection_eff_WJets","W+Jets");
 leg -> AddEntry("Selection_eff_ZJets","Z+Jets");
 leg->Draw("Same");
 //c1->SetLogy();
 c1->Print("signal_eff.eps");




 TCanvas* c2 = new TCanvas("c2", "Selection Efficency Background Samples", 600,600);

 Selection_eff_tt->SetStats(0);
 Selection_eff_QCD -> SetLineWidth(2);
 Selection_eff_tt -> SetLineWidth(2);
 Selection_eff_WJets -> SetLineWidth(2);
 Selection_eff_ZJets -> SetLineWidth(2);

 Selection_eff_tt->Draw("Hist ");
 Selection_eff_QCD->Draw("Hist SAME");
 Selection_eff_WJets->Draw("Hist SAME");
 Selection_eff_ZJets->Draw("Hist SAME");
 
 legbg = new TLegend(0.6,0.7,0.89,0.89);
 legbg -> AddEntry("Selection_eff_QCD","QCD");
 legbg -> AddEntry("Selection_eff_tt","ttbar");
 legbg -> AddEntry("Selection_eff_WJets","W+Jets");
 legbg -> AddEntry("Selection_eff_ZJets","Z+Jets");
 legbg->Draw("Same");
 c2->SetLogy();
 c2->Print("background_eff.eps");
}//end effplots
