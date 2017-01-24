//MassMacro.C


void MassMacro() {
 // open a file and get a histogram
 TFile *s1 = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Nominal/uhh2.AnalysisModuleRunner.MC.Tstar_M700.root");
 TFile *s2 = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Nominal/uhh2.AnalysisModuleRunner.MC.Tstar_M800.root");
 TFile *s3 = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Nominal/uhh2.AnalysisModuleRunner.MC.Tstar_M900.root");
 TFile *s4 = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Nominal/uhh2.AnalysisModuleRunner.MC.Tstar_M1000.root");
 TFile *s5 = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Nominal/uhh2.AnalysisModuleRunner.MC.Tstar_M1100.root");
 TFile *s6 = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Nominal/uhh2.AnalysisModuleRunner.MC.Tstar_M1200.root");
 TFile *s7 = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Nominal/uhh2.AnalysisModuleRunner.MC.Tstar_M1300.root");
 TFile *s8 = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Nominal/uhh2.AnalysisModuleRunner.MC.Tstar_M1400.root");
 TFile *s9 = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Nominal/uhh2.AnalysisModuleRunner.MC.Tstar_M1500.root");
 TFile *s10 = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Nominal/uhh2.AnalysisModuleRunner.MC.Tstar_M1600.root");


 TH1F *h1    = (TH1F*)s1->Get("chi2min__HypHists/M_Tstar_comb");
 TH1F *h2    = (TH1F*)s2->Get("chi2min__HypHists/M_Tstar_comb");
 TH1F *h3    = (TH1F*)s3->Get("chi2min__HypHists/M_Tstar_comb");
 TH1F *h4    = (TH1F*)s4->Get("chi2min__HypHists/M_Tstar_comb");
 TH1F *h5    = (TH1F*)s5->Get("chi2min__HypHists/M_Tstar_comb");
 TH1F *h6    = (TH1F*)s6->Get("chi2min__HypHists/M_Tstar_comb");
 TH1F *h7    = (TH1F*)s7->Get("chi2min__HypHists/M_Tstar_comb");
 TH1F *h8    = (TH1F*)s8->Get("chi2min__HypHists/M_Tstar_comb");
 TH1F *h9    = (TH1F*)s9->Get("chi2min__HypHists/M_Tstar_comb");
 TH1F *h10   = (TH1F*)s10->Get("chi2min__HypHists/M_Tstar_comb");



 gStyle->SetOptStat(0);
 gROOT->ForceStyle();
 int bin_up = 730;
  int bin_down = 610;

TCanvas* c1= new TCanvas("c1","c1",bin_up,bin_down);
 h1->Scale(1./(h2->Integral()));
 h1->SetTitle("");
 h1->SetLineColor(kRed);
 h1->SetLineWidth(3);
 h1->GetXaxis()->SetTitle("M_{T*}^{rec} [GeV/c^{2}]");
 h1->GetXaxis()->SetTitleSize(0.045);
 h1->GetXaxis()->SetTitleOffset(1.1);
 h1->GetYaxis()->SetTitle("#DeltaN/N");
 h1->GetYaxis()->SetTitleSize(0.04);
 h1->GetYaxis()->SetTitleOffset(1.2);
h1->Draw("hist");

 h4->Scale(1./(h6->Integral()));
 h4->SetTitle("");
 h4->SetLineColor(kBlue);
 h4->SetLineWidth(3);
 h4->GetXaxis()->SetTitle("M_{T*}^{rec} [GeV/c^{2}]");
 h4->GetXaxis()->SetTitleSize(0.045);
 h4->GetXaxis()->SetTitleOffset(1.1);
 h4->GetYaxis()->SetTitle("#DeltaN/N");
 h4->GetYaxis()->SetTitleSize(0.04);
 h4->GetYaxis()->SetTitleOffset(1.2);
h4->Draw("hist same");

 h8->Scale(1./(h10->Integral()));
 h8->SetTitle("");
 h8->SetLineColor(kGreen);
 h8->SetLineWidth(3);
 h8->GetXaxis()->SetTitle("M_{T*}^{rec} [GeV/c^{2}]");
 h8->GetXaxis()->SetTitleSize(0.045);
 h8->GetXaxis()->SetTitleOffset(1.1);
 h8->GetYaxis()->SetTitle("#DeltaN/N");
 h8->GetYaxis()->SetTitleSize(0.04);
 h8->GetYaxis()->SetTitleOffset(1.2);
h8->Draw("hist same");



 leg = new TLegend(0.1,0.7,0.48,0.9);
 leg->AddEntry(h2,"T* (700 GeV/c^{2})","l");
 leg->AddEntry(h6,"T* (1000 GeV/c^{2})","l");
 leg->AddEntry(h10,"T* (1400 GeV/c^{2})","l");

 leg->Draw();
}
