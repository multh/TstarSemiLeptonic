//Efficiency.C


void Efficiency() {

TCanvas *c1 = new TCanvas("c1","c1",600,500);
   gStyle->SetOptStat(0);


 // open a file and get a histogram
 TFile *s1 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/uhh2.AnalysisModuleRunner.MC.Tstar_M-1000.root");
 
 TFile *b1 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/uhh2.AnalysisModuleRunner.MC.TTbar_Tune.root");
 TFile *b2 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/uhh2.AnalysisModuleRunner.MC.WJets_Pt.root");
 TFile *b3 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/uhh2.AnalysisModuleRunner.MC.QCD.root");
 TFile *b4 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/uhh2.AnalysisModuleRunner.MC.ZJets_HT.root");
 TFile *b5 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/uhh2.AnalysisModuleRunner.MC.SingleT.root");
 TFile *b6 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/uhh2.AnalysisModuleRunner.MC.Diboson.root");


THStack *hs = new THStack("hs","Efficiency Histogram");

 TH1F *h_signal0    = (TH1F*)s1->Get("input_Event/MET");
 TH1F *h_signal1    = (TH1F*)s1->Get("trigger_Event/MET");
 TH1F *h_signal2    = (TH1F*)s1->Get("1Muon_Event/MET");
 TH1F *h_signal3    = (TH1F*)s1->Get("twodcut_Event/MET");
 TH1F *h_signal4    = (TH1F*)s1->Get("met_Event/MET");
 TH1F *h_signal5    = (TH1F*)s1->Get("bTag_Event/MET");
 TH1F *h_signal6    = (TH1F*)s1->Get("HT500_Event/MET");
 

 Double_t Input_signal   = h_signal0->GetEntries();
 Double_t Trigger_signal = h_signal1->GetEntries();
 Double_t Lep1_signal    = h_signal2->GetEntries();
 Double_t twodcut_signal = h_signal3->GetEntries();
 Double_t met_signal    = h_signal4->GetEntries();
 Double_t bTag_signal    = h_signal5->GetEntries();
 Double_t ht_signal      = h_signal5->GetEntries();

 Double_t Eff1_signal = Trigger_signal/Input_signal;
 Double_t Eff2_signal = Lep1_signal/Input_signal;
 Double_t Eff3_signal = twodcut_signal/Input_signal;
 Double_t Eff4_signal = met_signal/Input_signal;
 Double_t Eff5_signal = bTag_signal/Input_signal;
 Double_t Eff6_signal = ht_signal/Input_signal;

 TH1F *h_Eff_signal = new TH1F("h_Eff_signal","h_Eff_signal",6,0,6);
 h_Eff_signal->SetBinContent(1,Eff1_signal);
 h_Eff_signal->SetBinContent(2,Eff2_signal);
 h_Eff_signal->SetBinContent(3,Eff3_signal);
  h_Eff_signal->SetBinContent(4,Eff4_signal);
 h_Eff_signal->SetBinContent(5,Eff5_signal);
 h_Eff_signal->SetBinContent(6,Eff6_signal);
 

 TH1F *h_TTbar0    = (TH1F*)b1->Get("input_Event/MET");
 TH1F *h_TTbar1    = (TH1F*)b1->Get("trigger_Event/MET");
 TH1F *h_TTbar2    = (TH1F*)b1->Get("1Muon_Event/MET");
 TH1F *h_TTbar3    = (TH1F*)b1->Get("twodcut_Event/MET");
 TH1F *h_TTbar4    = (TH1F*)b1->Get("met_Event/MET");
 TH1F *h_TTbar5    = (TH1F*)b1->Get("bTag_Event/MET");
 TH1F *h_TTbar6    = (TH1F*)b1->Get("HT500_Event/MET");
 

 Double_t Input_TTbar = h_TTbar0->GetEntries();

 Double_t Trigger_TTbar = h_TTbar1->GetEntries();
 Double_t Lep1_TTbar    = h_TTbar2->GetEntries();
 Double_t twodcut_TTbar = h_TTbar3->GetEntries();
 Double_t met_TTbar    = h_TTbar4->GetEntries();
 Double_t bTag_TTbar    = h_TTbar5->GetEntries();
 Double_t ht_TTbar      = h_TTbar6->GetEntries();

 Double_t Eff1_TTbar = Trigger_TTbar/Input_TTbar;
 Double_t Eff2_TTbar = Lep1_TTbar/Input_TTbar;
 Double_t Eff3_TTbar = twodcut_TTbar/Input_TTbar;
 Double_t Eff4_TTbar = met_TTbar/Input_TTbar;
 Double_t Eff5_TTbar = bTag_TTbar/Input_TTbar;
 Double_t Eff6_TTbar = ht_TTbar/Input_TTbar;

TH1F *h_Eff_TTbar = new TH1F("h_Eff_TTbar","h_Eff_TTbar",7,0,7);
 h_Eff_TTbar->SetBinContent(1,Eff1_TTbar);
 h_Eff_TTbar->SetBinContent(2,Eff2_TTbar);
 h_Eff_TTbar->SetBinContent(3,Eff3_TTbar);
 h_Eff_TTbar->SetBinContent(4,Eff4_TTbar);
 h_Eff_TTbar->SetBinContent(5,Eff5_TTbar);
 h_Eff_TTbar->SetBinContent(6,Eff6_TTbar);

 h_Eff_TTbar->GetXaxis()->SetBinLabel(1,"Trigger");
 h_Eff_TTbar->GetXaxis()->SetBinLabel(2,"Lepton-Cut");
 h_Eff_TTbar->GetXaxis()->SetBinLabel(3,"2D-Cut");
 
 h_Eff_TTbar->GetXaxis()->SetBinLabel(4,"MET-Cut");
 h_Eff_TTbar->GetXaxis()->SetBinLabel(5,"b-Tag");
 h_Eff_TTbar->GetXaxis()->SetBinLabel(6,"HT-Cut");
 
 TH1F *h_WJets0    = (TH1F*)b2->Get("input_Event/MET");
 TH1F *h_WJets1    = (TH1F*)b2->Get("trigger_Event/MET");
 TH1F *h_WJets2    = (TH1F*)b2->Get("1Muon_Event/MET");
 TH1F *h_WJets3    = (TH1F*)b2->Get("twodcut_Event/MET");
 TH1F *h_WJets4    = (TH1F*)b2->Get("met_Event/MET");
 TH1F *h_WJets5    = (TH1F*)b2->Get("bTag_Event/MET");
 TH1F *h_WJets6    = (TH1F*)b2->Get("HT500_Event/MET");

 Double_t Input_WJets = h_WJets0->GetEntries();
 Double_t Trigger_WJets = h_WJets1->GetEntries();
 Double_t Lep1_WJets    = h_WJets2->GetEntries();
 Double_t twodcut_WJets = h_WJets3->GetEntries();
 Double_t met_WJets    = h_WJets4->GetEntries();
 Double_t bTag_WJets    = h_WJets5->GetEntries();
 Double_t ht_WJets      = h_WJets6->GetEntries();

 Double_t Eff1_WJets = Trigger_WJets/Input_WJets;
 Double_t Eff2_WJets = Lep1_WJets/Input_WJets;
 Double_t Eff3_WJets = twodcut_WJets/Input_WJets;
 Double_t Eff4_WJets = met_WJets/Input_WJets;
 Double_t Eff5_WJets = bTag_WJets/Input_WJets;
 Double_t Eff6_WJets = ht_WJets/Input_WJets;

TH1F *h_Eff_WJets = new TH1F("h_Eff_WJets","h_Eff_WJets",6,0,6);
 h_Eff_WJets->SetBinContent(1,Eff1_WJets);
 h_Eff_WJets->SetBinContent(2,Eff2_WJets);
 h_Eff_WJets->SetBinContent(3,Eff3_WJets);
  h_Eff_WJets->SetBinContent(4,Eff4_WJets);
 h_Eff_WJets->SetBinContent(5,Eff5_WJets);
 h_Eff_WJets->SetBinContent(6,Eff6_WJets);
 
 /*
 TH1F *h_QCD1    = (TH1F*)b3->Get("trigger_Event/HT");
 TH1F *h_QCD2    = (TH1F*)b3->Get("1Muon_Event/HT");
 TH1F *h_QCD3    = (TH1F*)b3->Get("twodcut_Event/HT");
 TH1F *h_QCD4    = (TH1F*)b3->Get("met_Event/HT");
 TH1F *h_QCD5    = (TH1F*)b3->Get("bTag_Event/HT");
 TH1F *h_QCD6    = (TH1F*)b3->Get("HT500_Event/HT");

 Double_t Trigger_QCD = h_QCD1->GetEntries();
 Double_t Lep1_QCD    = h_QCD2->GetEntries();
 Double_t twodcut_QCD = h_QCD3->GetEntries();
 Double_t met_QCD    = h_QCD4->GetEntries();
 Double_t bTag_QCD    = h_QCD5->GetEntries();
 Double_t ht_QCD      = h_QCD6->GetEntries();

 Double_t Eff1_QCD = Trigger_QCD/Input;
 Double_t Eff2_QCD = Lep1_QCD/Input;
 Double_t Eff3_QCD = twodcut_QCD/Input;
 Double_t Eff4_QCD = met_QCD/Input;
 Double_t Eff5_QCD = bTag_QCD/Input;
 Double_t Eff6_QCD = ht_QCD/Input;

TH1F *h_Eff_QCD = new TH1F("h_Eff_QCD","h_Eff_QCD",6,0,6);
 h_Eff_QCD->SetBinContent(1,Eff1_QCD);
 h_Eff_QCD->SetBinContent(2,Eff2_QCD);
 h_Eff_QCD->SetBinContent(3,Eff3_QCD);
 
 h_Eff_QCD->SetBinContent(4,Eff4_QCD);
 h_Eff_QCD->SetBinContent(5,Eff5_QCD);
 h_Eff_QCD->SetBinContent(6,Eff6_QCD);
 

 h_Eff_QCD->SetFillColor(kBlue);

 hs->Add(h_Eff_QCD);


 TH1F *h_ZJets1    = (TH1F*)b4->Get("trigger_Event/HT");
 TH1F *h_ZJets2    = (TH1F*)b4->Get("1Muon_Event/HT");
 TH1F *h_ZJets3    = (TH1F*)b4->Get("twodcut_Event/HT");
 TH1F *h_ZJets4    = (TH1F*)b4->Get("met_Event/HT");
 TH1F *h_ZJets5    = (TH1F*)b4->Get("bTag_Event/HT");
 TH1F *h_ZJets6    = (TH1F*)b4->Get("HT500_Event/HT");

 Double_t Trigger_ZJets = h_ZJets1->GetEntries();
 Double_t Lep1_ZJets    = h_ZJets2->GetEntries();
 Double_t twodcut_ZJets = h_ZJets3->GetEntries();
 Double_t met_ZJets    = h_ZJets4->GetEntries();
 Double_t bTag_ZJets    = h_ZJets5->GetEntries();
 Double_t ht_ZJets      = h_ZJets6->GetEntries();

 Double_t Eff1_ZJets = Trigger_ZJets/Input;
 Double_t Eff2_ZJets = Lep1_ZJets/Input;
 Double_t Eff3_ZJets = twodcut_ZJets/Input;
 Double_t Eff4_ZJets = met_ZJets/Input;
 Double_t Eff5_ZJets = bTag_ZJets/Input;
 Double_t Eff6_ZJets = ht_ZJets/Input;

TH1F *h_Eff_ZJets = new TH1F("h_Eff_ZJets","h_Eff_ZJets",6,0,6);
 h_Eff_ZJets->SetBinContent(1,Eff1_ZJets);
 h_Eff_ZJets->SetBinContent(2,Eff2_ZJets);
 h_Eff_ZJets->SetBinContent(3,Eff3_ZJets);

 h_Eff_ZJets->SetBinContent(4,Eff4_ZJets);
 h_Eff_ZJets->SetBinContent(5,Eff5_ZJets);
 h_Eff_ZJets->SetBinContent(6,Eff6_ZJets);

 h_Eff_ZJets->SetFillColor(kYellow);

 hs->Add(h_Eff_ZJets);


 TH1F *h_SingleTop1    = (TH1F*)b5->Get("trigger_Event/HT");
 TH1F *h_SingleTop2    = (TH1F*)b5->Get("1Muon_Event/HT");
 TH1F *h_SingleTop3    = (TH1F*)b5->Get("twodcut_Event/HT");
 TH1F *h_SingleTop4    = (TH1F*)b5->Get("met_Event/HT");
 TH1F *h_SingleTop5    = (TH1F*)b5->Get("bTag_Event/HT");
 TH1F *h_SingleTop6    = (TH1F*)b5->Get("HT500_Event/HT");

 Double_t Trigger_SingleTop = h_SingleTop1->GetEntries();
 Double_t Lep1_SingleTop    = h_SingleTop2->GetEntries();
 Double_t twodcut_SingleTop = h_SingleTop3->GetEntries();
 Double_t met_SingleTop    = h_SingleTop4->GetEntries();
 Double_t bTag_SingleTop    = h_SingleTop5->GetEntries();
 Double_t ht_SingleTop      = h_SingleTop5->GetEntries();

 Double_t Eff1_SingleTop = Trigger_SingleTop/Input;
 Double_t Eff2_SingleTop = Lep1_SingleTop/Input;
 Double_t Eff3_SingleTop = twodcut_SingleTop/Input;
 Double_t Eff4_SingleTop = met_SingleTop/Input;
 Double_t Eff5_SingleTop = bTag_SingleTop/Input;
 Double_t Eff6_SingleTop = ht_SingleTop/Input;

TH1F *h_Eff_SingleTop = new TH1F("h_Eff_SingleTop","h_Eff_SingleTop",6,0,6);
 h_Eff_SingleTop->SetBinContent(1,Eff1_SingleTop);
 h_Eff_SingleTop->SetBinContent(2,Eff2_SingleTop);
 h_Eff_SingleTop->SetBinContent(3,Eff3_SingleTop);

 h_Eff_SingleTop->SetBinContent(4,Eff4_SingleTop);
 h_Eff_SingleTop->SetBinContent(5,Eff5_SingleTop);
 h_Eff_SingleTop->SetBinContent(6,Eff6_SingleTop);

 h_Eff_SingleTop->SetFillColor(kOrange);

 hs->Add(h_Eff_SingleTop);
 */

  

 h_Eff_TTbar->Draw();
 h_Eff_WJets->Draw("same");
 h_Eff_signal->Draw("same");

 leg = new TLegend(0.1,0.7,0.48,0.9);
   leg->AddEntry(h_Eff_TTbar,"TTbar","l");
   leg->AddEntry(h_Eff_WJets,"W+Jets","l");
   /*leg->AddEntry(h_Eff_QCD,"QCD","f");
   leg->AddEntry(h_Eff_ZJets,"Z+Jets","f");
   leg->AddEntry(h_Eff_SingleTop,"Single Top","f");
   */   
leg->AddEntry(h_Eff_signal,"Signal (M=700 GeV)");

   leg->Draw();

}
