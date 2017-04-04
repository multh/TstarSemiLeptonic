//BkgMacro.C

//***********************************************************************
//
//Macro for Background Composition after every Selectionstep
//
//***********************************************************************


void BkgMacro() {

TCanvas *c1 = new TCanvas("c1","c1",600,500);
   gStyle->SetOptStat(0);
   c1->Divide(2,1);

 // open a file and get a histogram
 TFile *s1 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/uhh2.AnalysisModuleRunner.MC.Tstar_M-700.root");
 TFile *b1 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/uhh2.AnalysisModuleRunner.MC.TTbar_Tune.root");
 TFile *b2 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/uhh2.AnalysisModuleRunner.MC.WJets_Pt.root");
 TFile *b3 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/uhh2.AnalysisModuleRunner.MC.QCD.root");
 TFile *b4 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/uhh2.AnalysisModuleRunner.MC.ZJets.root");


THStack *hs = new THStack("hs","Background Composition");



 TH1F *h_signal0    = (TH1F*)s1->Get("input_Event/HT");
 TH1F *h_signal1    = (TH1F*)s1->Get("1Muon_Event/HT");
 TH1F *h_signal2    = (TH1F*)s1->Get("twodcut_Event/HT");
 TH1F *h_signal3    = (TH1F*)s1->Get("bTag_Event/HT");
 TH1F *h_signal4    = (TH1F*)s1->Get("5Jets_Event/HT");
 TH1F *h_signal5    = (TH1F*)s1->Get("HT500_Event/HT");
 TH1F *h_signal6    = (TH1F*)s1->Get("output_Event/HT");


 TH1F *h_TTbar0    = (TH1F*)b1->Get("input_Event/HT");
 TH1F *h_TTbar1    = (TH1F*)b1->Get("1Muon_Event/HT");
 TH1F *h_TTbar2    = (TH1F*)b1->Get("twodcut_Event/HT");
 TH1F *h_TTbar3    = (TH1F*)b1->Get("bTag_Event/HT");
 TH1F *h_TTbar4    = (TH1F*)b1->Get("5Jets_Event/HT");
 TH1F *h_TTbar5    = (TH1F*)b1->Get("HT500_Event/HT");
 TH1F *h_TTbar6    = (TH1F*)b1->Get("output_Event/HT");

 TH1F *h_WJets0    = (TH1F*)b2->Get("input_Event/HT");
 TH1F *h_WJets1    = (TH1F*)b2->Get("1Muon_Event/HT");
 TH1F *h_WJets2    = (TH1F*)b2->Get("twodcut_Event/HT");
 TH1F *h_WJets3    = (TH1F*)b2->Get("bTag_Event/HT");
 TH1F *h_WJets4    = (TH1F*)b2->Get("5Jets_Event/HT");
 TH1F *h_WJets5    = (TH1F*)b2->Get("HT500_Event/HT");
 TH1F *h_WJets6    = (TH1F*)b2->Get("output_Event/HT");

 TH1F *h_QCD0    = (TH1F*)b3->Get("input_Event/HT");
 TH1F *h_QCD1    = (TH1F*)b3->Get("1Muon_Event/HT");
 TH1F *h_QCD2    = (TH1F*)b3->Get("twodcut_Event/HT");
 TH1F *h_QCD3    = (TH1F*)b3->Get("bTag_Event/HT");
 TH1F *h_QCD4    = (TH1F*)b3->Get("5Jets_Event/HT");
 TH1F *h_QCD5    = (TH1F*)b3->Get("HT500_Event/HT");
 TH1F *h_QCD6    = (TH1F*)b3->Get("output_Event/HT");

 TH1F *h_ZJets0    = (TH1F*)b4->Get("input_Event/HT");
 TH1F *h_ZJets1    = (TH1F*)b4->Get("1Muon_Event/HT");
 TH1F *h_ZJets2    = (TH1F*)b4->Get("twodcut_Event/HT");
 TH1F *h_ZJets3    = (TH1F*)b4->Get("bTag_Event/HT");
 TH1F *h_ZJets4    = (TH1F*)b4->Get("5Jets_Event/HT");
 TH1F *h_ZJets5    = (TH1F*)b4->Get("HT500_Event/HT");
 TH1F *h_ZJets6    = (TH1F*)b4->Get("output_Event/HT");


 Double_t input_signal     = h_signal0->GetEntries();
 Double_t Lep1_signal        = h_signal1->GetEntries();
 Double_t twodcut_signal     = h_signal2->GetEntries();
 Double_t bTag_signal        = h_signal3->GetEntries();
 Double_t jet_signal         = h_signal4->GetEntries();
 Double_t ht_signal          = h_signal5->GetEntries();
 Double_t output_signal      = h_signal6->GetEntries();

 Double_t input_TTbar     = h_TTbar0->GetEntries();
 Double_t Lep1_TTbar        = h_TTbar1->GetEntries();
 Double_t twodcut_TTbar     = h_TTbar2->GetEntries();
 Double_t bTag_TTbar        = h_TTbar3->GetEntries();
 Double_t jet_TTbar         = h_TTbar4->GetEntries();
 Double_t ht_TTbar          = h_TTbar5->GetEntries();
 Double_t output_TTbar      = h_TTbar6->GetEntries();

 Double_t input_WJets     = h_WJets0->GetEntries();
 Double_t Lep1_WJets        = h_WJets1->GetEntries();
 Double_t twodcut_WJets     = h_WJets2->GetEntries();
 Double_t bTag_WJets        = h_WJets3->GetEntries();
 Double_t jet_WJets         = h_WJets4->GetEntries();
 Double_t ht_WJets          = h_WJets5->GetEntries();
 Double_t output_WJets      = h_WJets6->GetEntries();

 Double_t input_QCD     = h_QCD0->GetEntries();
 Double_t Lep1_QCD        = h_QCD1->GetEntries();
 Double_t twodcut_QCD     = h_QCD2->GetEntries();
 Double_t bTag_QCD        = h_QCD3->GetEntries();
 Double_t jet_QCD         = h_QCD4->GetEntries();
 Double_t ht_QCD          = h_QCD5->GetEntries();
 Double_t output_QCD      = h_QCD6->GetEntries();

 Double_t input_ZJets     = h_ZJets0->GetEntries();
 Double_t Lep1_ZJets        = h_ZJets1->GetEntries();
 Double_t twodcut_ZJets     = h_ZJets2->GetEntries();
 Double_t bTag_ZJets        = h_ZJets3->GetEntries();
 Double_t jet_ZJets         = h_ZJets4->GetEntries();
 Double_t ht_ZJets          = h_ZJets5->GetEntries();
 Double_t output_ZJets      = h_ZJets6->GetEntries();


 //Signal/Sqrt(Background) Estimation
 Double_t input_Input =  input_TTbar+input_WJets+input_QCD+input_ZJets; 
 Double_t Lep1_Input =  Lep1_TTbar+Lep1_WJets+Lep1_QCD+Lep1_ZJets; 
 Double_t twodcut_Input =  twodcut_TTbar+twodcut_WJets+twodcut_QCD+twodcut_ZJets; 
 Double_t jet_Input =  jet_TTbar+jet_WJets+jet_QCD+jet_ZJets; 
 Double_t bTag_Input =  bTag_TTbar+bTag_WJets+bTag_QCD+bTag_ZJets; 
 Double_t ht_Input =  ht_TTbar+ht_WJets+ht_QCD+ht_ZJets; 
 Double_t output_Input =  output_TTbar+output_WJets+output_QCD+output_ZJets; 
 
 Double_t input_Ratio = input_signal/sqrt(input_Input);
 Double_t Lep1_Ratio    = Lep1_signal/sqrt(Lep1_Input);
 Double_t twodcut_Ratio = twodcut_signal/sqrt(twodcut_Input);
 Double_t jet_Ratio = jet_signal/sqrt(jet_Input);
 Double_t bTag_Ratio = bTag_signal/sqrt(bTag_Input);
 Double_t ht_Ratio = ht_signal/sqrt(ht_Input);
 Double_t output_Ratio = output_signal/sqrt(output_Input);


 //Efficency for Selections
 Double_t Eff1_TTbar = input_TTbar/input_Input;
 Double_t Eff2_TTbar = Lep1_TTbar/Lep1_Input;
 Double_t Eff3_TTbar = twodcut_TTbar/twodcut_Input;
 Double_t Eff4_TTbar = jet_TTbar/jet_Input;
 Double_t Eff5_TTbar = bTag_TTbar/bTag_Input;
 Double_t Eff6_TTbar = ht_TTbar/ht_Input;
 Double_t Eff7_TTbar = output_TTbar/output_Input;

 Double_t Eff1_WJets = input_WJets/input_Input;
 Double_t Eff2_WJets = Lep1_WJets/Lep1_Input;
 Double_t Eff3_WJets = twodcut_WJets/twodcut_Input;
 Double_t Eff4_WJets = jet_WJets/jet_Input;
 Double_t Eff5_WJets = bTag_WJets/bTag_Input;
 Double_t Eff6_WJets = ht_WJets/ht_Input;
 Double_t Eff7_WJets = output_WJets/output_Input;

 Double_t Eff1_QCD = input_QCD/input_Input;
 Double_t Eff2_QCD = Lep1_QCD/Lep1_Input;
 Double_t Eff3_QCD = twodcut_QCD/twodcut_Input;
 Double_t Eff4_QCD = jet_QCD/jet_Input;
 Double_t Eff5_QCD = bTag_QCD/bTag_Input;
 Double_t Eff6_QCD = ht_QCD/ht_Input;
 Double_t Eff7_QCD = output_QCD/output_Input;

 Double_t Eff1_ZJets = input_ZJets/input_Input;
 Double_t Eff2_ZJets = Lep1_ZJets/Lep1_Input;
 Double_t Eff3_ZJets = twodcut_ZJets/twodcut_Input;
 Double_t Eff4_ZJets = jet_ZJets/jet_Input;
 Double_t Eff5_ZJets = bTag_ZJets/bTag_Input;
 Double_t Eff6_ZJets = ht_ZJets/ht_Input;
 Double_t Eff7_ZJets = output_ZJets/output_Input;

TH1F *h_Ratio = new TH1F("h_Ratio","S/#sqrt{B}",7,0,7);
 h_Ratio->SetBinContent(1,input_Ratio);
 h_Ratio->SetBinContent(2,Lep1_Ratio);
 h_Ratio->SetBinContent(3,twodcut_Ratio);
  h_Ratio->SetBinContent(5,jet_Ratio);
 h_Ratio->SetBinContent(4,bTag_Ratio);
 h_Ratio->SetBinContent(6,ht_Ratio);
  h_Ratio->SetBinContent(7,output_Ratio);

 h_Ratio->GetXaxis()->SetBinLabel(1,"input");
 h_Ratio->GetXaxis()->SetBinLabel(2,"Lepton-Cut");
 h_Ratio->GetXaxis()->SetBinLabel(3,"2D-Cut");
 h_Ratio->GetXaxis()->SetBinLabel(4,"Jet-Cut");
 h_Ratio->GetXaxis()->SetBinLabel(5,"b-Tag");
 h_Ratio->GetXaxis()->SetBinLabel(6,"HT-Cut");
 h_Ratio->GetXaxis()->SetBinLabel(7,"Chi2-Cut");

 c1->cd(1);
 h_Ratio->Draw();

 //Plot Results
TH1F *h_Eff_TTbar = new TH1F("h_Eff_TTbar","h_Eff_TTbar",7,0,7);
 h_Eff_TTbar->SetBinContent(1,Eff1_TTbar);
 h_Eff_TTbar->SetBinContent(2,Eff2_TTbar);
 h_Eff_TTbar->SetBinContent(3,Eff3_TTbar);
  h_Eff_TTbar->SetBinContent(4,Eff4_TTbar);
 h_Eff_TTbar->SetBinContent(5,Eff5_TTbar);
 h_Eff_TTbar->SetBinContent(6,Eff6_TTbar);
  h_Eff_TTbar->SetBinContent(7,Eff7_TTbar);

 h_Eff_TTbar->SetFillColor(kRed);
 h_Eff_TTbar->GetXaxis()->SetBinLabel(1,"Input");
 h_Eff_TTbar->GetXaxis()->SetBinLabel(2,"Lepton-Cut");
 h_Eff_TTbar->GetXaxis()->SetBinLabel(3,"2D-Cut");
 h_Eff_TTbar->GetXaxis()->SetBinLabel(4,"Jet-Cut");
 h_Eff_TTbar->GetXaxis()->SetBinLabel(5,"b-Tag");
 h_Eff_TTbar->GetXaxis()->SetBinLabel(6,"HT-Cut");
  h_Eff_TTbar->GetXaxis()->SetBinLabel(7,"Chi2-Cut");

 hs->Add(h_Eff_TTbar);


TH1F *h_Eff_WJets = new TH1F("h_Eff_WJets","h_Eff_WJets",7,0,7);
 h_Eff_WJets->SetBinContent(1,Eff1_WJets);
 h_Eff_WJets->SetBinContent(2,Eff2_WJets);
 h_Eff_WJets->SetBinContent(3,Eff3_WJets);
 h_Eff_WJets->SetBinContent(4,Eff4_WJets);
 h_Eff_WJets->SetBinContent(5,Eff5_WJets);
 h_Eff_WJets->SetBinContent(6,Eff6_WJets);
 h_Eff_WJets->SetBinContent(7,Eff7_WJets);

 h_Eff_WJets->SetFillColor(kGreen);

 hs->Add(h_Eff_WJets);
 

TH1F *h_Eff_QCD = new TH1F("h_Eff_QCD","h_Eff_QCD",7,0,7);
 h_Eff_QCD->SetBinContent(1,Eff1_QCD);
 h_Eff_QCD->SetBinContent(2,Eff2_QCD);
 h_Eff_QCD->SetBinContent(3,Eff3_QCD);
 h_Eff_QCD->SetBinContent(4,Eff4_QCD);
 h_Eff_QCD->SetBinContent(5,Eff5_QCD);
 h_Eff_QCD->SetBinContent(6,Eff6_QCD);
 h_Eff_QCD->SetBinContent(7,Eff7_QCD);

 h_Eff_QCD->SetFillColor(kBlue);

 hs->Add(h_Eff_QCD);


TH1F *h_Eff_ZJets = new TH1F("h_Eff_ZJets","h_Eff_ZJets",7,0,7);
 h_Eff_ZJets->SetBinContent(1,Eff1_ZJets);
 h_Eff_ZJets->SetBinContent(2,Eff2_ZJets);
 h_Eff_ZJets->SetBinContent(3,Eff3_ZJets);

 h_Eff_ZJets->SetBinContent(4,Eff4_ZJets);
 h_Eff_ZJets->SetBinContent(5,Eff5_ZJets);
 h_Eff_ZJets->SetBinContent(6,Eff6_ZJets);
 h_Eff_ZJets->SetBinContent(7,Eff7_ZJets);

 h_Eff_ZJets->SetFillColor(kYellow);

 hs->Add(h_Eff_ZJets);

 c1->cd(2);
 hs->Draw();
 
 leg = new TLegend(0.1,0.7,0.48,0.9);
   leg->AddEntry(h_Eff_TTbar,"TTbar","f");
   leg->AddEntry(h_Eff_WJets,"W+Jets","f");
   leg->AddEntry(h_Eff_QCD,"QCD","f");
   leg->AddEntry(h_Eff_ZJets,"Z+Jets","f");
  
   leg->Draw();
 
}
