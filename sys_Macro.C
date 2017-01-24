#include "HttStylesNew.cc"


void sys_Macro(TString Variable = "M_Tstar_comb", // variable to plot
		 int nBins =   30, // number of bins in histogram
		 float xmin =  0, // lower edgde of histogram
		 float xmax = 2000, // upper edge of histogram
		   //TString Weight = "puweight*mcweight*isoweight_1*trigweight_1*idEffMedium_2*", // event weight
		   //TString Cuts = "iso_1<0.1&&idMvaTight_2>0.5", // imposed cuts
		 TString xtitle = "M_{T^{*}} [GeV/c^{2}]", // title of x-axis
		 TString ytitle = "Verhaltnis" // title of y-axis
		 )
{

  //SetStyle();
gStyle->SetOptStat(0);
gROOT->ForceStyle();
  bool logY = false;

  TString rootDir_nominal    = "/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Nominal/"; // directory with RooT files
  TString rootDir_B_Tag_udsg_Down = "/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/B_Tag_udsg_Down/"; // directory with RooT files
  TString rootDir_B_Tag_udsg_Up = "/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/B_Tag_udsg_Up/"; // directory with RooT files
  
  TString rootDir_B_Tag_bc_Down = "/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/B_Tag_Down_bc/"; // directory with RooT files
  TString rootDir_B_Tag_bc_Up = "/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/B_Tag_Up_bc/"; // directory with RooT files

  TString rootDir_JEC_Down = "/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/JEC_Down/"; // directory with RooT files
  TString rootDir_JEC_Up = "/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/JEC_Up/"; // directory with RooT files

  TString rootDir_JER_Down = "/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/JER_Down/"; // directory with RooT files
  TString rootDir_JER_Up = "/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/JER_Up/"; // directory with RooT files

 TString rootDir_MuonID_Down = "/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/MuonID_Down/"; // directory with RooT files
  TString rootDir_MuonID_Up = "/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/MuonID_Up/"; // directory with RooT files

 TString rootDir_MuonTrigger_Down = "/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/MuonTrigger_Down/"; // directory with RooT files
  TString rootDir_MuonTrigger_Up = "/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/MuonTrigger_Up/"; // directory with RooT files

 TString rootDir_PU_Down = "/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/PU_Down/"; // directory with RooT files
  TString rootDir_PU_Up = "/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/PU_Up/"; // directory with RooT files

  double lumi = 2690; // integrated luminosity 

  // List of samples used in the analysis
  TString sampleNames[16] = {
    "uhh2.AnalysisModuleRunner.MC.TTbar", // TTbar
    "uhh2.AnalysisModuleRunner.MC.WJets", // W+Jets
    "uhh2.AnalysisModuleRunner.MC.ZJets", // // Z+Jets 
    "uhh2.AnalysisModuleRunner.MC.SingleTop", // single-top (t-channel)
    "uhh2.AnalysisModuleRunner.MC.Diboson", // Diboson 
    "uhh2.AnalysisModuleRunner.MC.QCD", // QCD 
    "uhh2.AnalysisModuleRunner.MC.Tstar_M700",  //Signal_M700
    "uhh2.AnalysisModuleRunner.MC.Tstar_M800",   //Signal_M800
    "uhh2.AnalysisModuleRunner.MC.Tstar_M900", //Signal_M900
    "uhh2.AnalysisModuleRunner.MC.Tstar_M1000", //Signal_M1000
    "uhh2.AnalysisModuleRunner.MC.Tstar_M1100", //Signal_M1100
    "uhh2.AnalysisModuleRunner.MC.Tstar_M1200", //Signal_M1200
    "uhh2.AnalysisModuleRunner.MC.Tstar_M1300", //Signal_M1300
    "uhh2.AnalysisModuleRunner.MC.Tstar_M1400", //Signal_M1400
    "uhh2.AnalysisModuleRunner.MC.Tstar_M1500", //Signal_M1500
    "uhh2.AnalysisModuleRunner.MC.Tstar_M1600", //Signal_M1600
}; 

 TH1F * hist_nominal[16];
 TH1F * hist_b_Tag_Down[16];
 TH1F * hist_b_Tag_Up[16];
 TH1F * hist_b_Ratio_Down[16];
 TH1F * hist_b_Ratio_Up[16];

 TH1F * hist_b_Tag_bc_Down[16];
 TH1F * hist_b_Tag_bc_Up[16];
 TH1F * hist_b_Ratio_bc_Down[16];
 TH1F * hist_b_Ratio_bc_Up[16];

 TH1F * hist_JEC_Down[16];
 TH1F * hist_JEC_Up[16];
 TH1F * hist_JEC_Ratio_Down[16];
 TH1F * hist_JEC_Ratio_Up[16];

 TH1F * hist_JER_Down[16];
 TH1F * hist_JER_Up[16];
 TH1F * hist_JER_Ratio_Down[16];
 TH1F * hist_JER_Ratio_Up[16];

 TH1F * hist_MuonID_Down[16];
 TH1F * hist_MuonID_Up[16];
 TH1F * hist_MuonID_Ratio_Down[16];
 TH1F * hist_MuonID_Ratio_Up[16];

 TH1F * hist_MuonTrigger_Down[16];
 TH1F * hist_MuonTrigger_Up[16];
 TH1F * hist_MuonTrigger_Ratio_Down[16];
 TH1F * hist_MuonTrigger_Ratio_Up[16];

 TH1F * hist_PU_Down[16];
 TH1F * hist_PU_Up[16];
 TH1F * hist_PU_Ratio_Down[16];
 TH1F * hist_PU_Ratio_Up[16];


  // dummy canvas (will be deleted later)
  //TCanvas * dummyCanv = new TCanvas("dummyCanv","",500,500);

 TString rootFileName     = "systematics.root";
TFile* fileSystematics  = TFile::Open(rootFileName,"RECREATE");
 TDirectory *B_Tag_bc_sys = fileSystematics->mkdir("B_Tag_bc_sys");
 TDirectory *B_Tag_udsg_sys = fileSystematics->mkdir("B_Tag_udsg_sys");
 TDirectory *JEC_sys = fileSystematics->mkdir("JEC_sys");
TDirectory *JER_sys = fileSystematics->mkdir("JER_sys");
TDirectory *MuonID_sys = fileSystematics->mkdir("MuonID_sys");
TDirectory *MuonTrigger_sys = fileSystematics->mkdir("MuonTrigger_sys");
TDirectory *PU_sys = fileSystematics->mkdir("PU_sys");

 TLine *line1 = new TLine(0,1,2000,1);
  
  line1->SetLineWidth(2);
  line1->SetLineColor(kBlack);

  int bin_up = 630;
  int bin_down = 510;


  for (int i=0; i<16; ++i) {
 TCanvas* c_B_Tag = new TCanvas(sampleNames[i],sampleNames[i],bin_up,bin_down);
gStyle->SetOptStat(0);
c_B_Tag->SetGrid();





    TFile * file_nominal = new TFile(rootDir_nominal+sampleNames[i]+".root");
    hist_nominal[i] = (TH1F*)file_nominal->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 
    TFile * file_b_Tag_Down = new TFile(rootDir_B_Tag_udsg_Down+sampleNames[i]+".root");
    hist_b_Tag_Down[i] = (TH1F*)file_b_Tag_Down->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");

    TFile * file_b_Tag_Up = new TFile(rootDir_B_Tag_udsg_Up+sampleNames[i]+".root");
    hist_b_Tag_Up[i] = (TH1F*)file_b_Tag_Up->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");

   hist_b_Ratio_Down[i] = (TH1F*)hist_b_Tag_Down[i]->Clone("hist_b_Ratio_Down");
   hist_b_Ratio_Up[i] = (TH1F*)hist_b_Tag_Up[i]->Clone("hist_b_Ratio_Up");
 
   hist_b_Ratio_Down[i]->Divide(hist_nominal[i]);
   hist_b_Ratio_Up[i]->Divide(hist_nominal[i]);

   hist_b_Ratio_Down[i]->SetTitle("");
   hist_b_Ratio_Up[i]->SetTitle("");
   hist_b_Ratio_Down[i]->SetLineColor(kRed);
   hist_b_Ratio_Up[i]->SetLineColor(kBlue);
   hist_b_Ratio_Down[i]->SetLineStyle(2);
   hist_b_Ratio_Up[i]->SetLineStyle(2);
   hist_b_Ratio_Down[i]->SetLineWidth(3);
   hist_b_Ratio_Up[i]->SetLineWidth(3);
   //hist_b_Ratio_Down[i]->GetYaxis()->SetRangeUser(0.8,1.2);
    hist_b_Ratio_Up[i]->GetYaxis()->SetRangeUser(0.83,1.17);
   hist_b_Ratio_Up[i]->GetXaxis()->SetRangeUser(0,2000);
  hist_b_Ratio_Down[i]->GetXaxis()->SetRangeUser(0,2000);
    // hist_b_Ratio_Down[i]->GetYaxis()->SetTitle("Verh#ddot{a}ltnis");
    hist_b_Ratio_Up[i]->GetYaxis()->SetTitle("Verh#ddot{a}ltnis");
    hist_b_Ratio_Up[i]->GetYaxis()->SetTitleSize(0.04);
     hist_b_Ratio_Up[i]->GetXaxis()->SetTitle("M_{T^{*}} [GeV/c^{2}]");
     hist_b_Ratio_Up[i]->GetXaxis()->SetTitleSize(0.04);
   hist_b_Ratio_Up[i]->GetYaxis()->SetTitleOffset(1.4);
  hist_b_Ratio_Up[i]->GetXaxis()->SetTitleOffset(1.2);
 
   hist_b_Ratio_Up[i]->Draw("hist");
    hist_b_Ratio_Down[i]->Draw("hist SAME");
    line1->Draw("Same");



B_Tag_udsg_sys->cd();
    c_B_Tag->Write();
}

 for (int i=0; i<16; ++i) {
 TCanvas* c_B_bc_Tag = new TCanvas(sampleNames[i],sampleNames[i],bin_up,bin_down);
gStyle->SetOptStat    (0);
c_B_bc_Tag->SetGrid();
    TFile * file_nominal = new TFile(rootDir_nominal+sampleNames[i]+".root");
    hist_nominal[i] = (TH1F*)file_nominal->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 
    TFile * file_b_Tag_bc_Down = new TFile(rootDir_B_Tag_bc_Down+sampleNames[i]+".root");
    hist_b_Tag_bc_Down[i] = (TH1F*)file_b_Tag_bc_Down->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");

    TFile * file_b_Tag_bc_Up = new TFile(rootDir_B_Tag_bc_Up+sampleNames[i]+".root");
    hist_b_Tag_bc_Up[i] = (TH1F*)file_b_Tag_bc_Up->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");

   hist_b_Ratio_bc_Down[i] = (TH1F*)hist_b_Tag_bc_Down[i]->Clone("hist_b_Ratio_bc_Down");
   hist_b_Ratio_bc_Up[i] = (TH1F*)hist_b_Tag_bc_Up[i]->Clone("hist_b_Ratio_bc_Up");
 
   hist_b_Ratio_bc_Down[i]->Divide(hist_nominal[i]);
   hist_b_Ratio_bc_Up[i]->Divide(hist_nominal[i]);

   hist_b_Ratio_bc_Down[i]->SetTitle("");
   hist_b_Ratio_bc_Up[i]->SetTitle("");
   hist_b_Ratio_bc_Down[i]->SetLineColor(kRed);
   hist_b_Ratio_bc_Up[i]->SetLineColor(kBlue);
   hist_b_Ratio_bc_Down[i]->SetLineStyle(2);
   hist_b_Ratio_bc_Up[i]->SetLineStyle(2);
   hist_b_Ratio_bc_Down[i]->SetLineWidth(2);
   hist_b_Ratio_bc_Up[i]->SetLineWidth(2);
   //hist_b_Ratio_Down[i]->GetYaxis()->SetRangeUser(0.8,1.2);
    hist_b_Ratio_bc_Up[i]->GetYaxis()->SetRangeUser(0.83,1.17);
   hist_b_Ratio_bc_Up[i]->GetXaxis()->SetRangeUser(0,2000);
  hist_b_Ratio_bc_Down[i]->GetXaxis()->SetRangeUser(0,2000);
    // hist_b_Ratio_Down[i]->GetYaxis()->SetTitle("Verh#ddot{a}ltnis");
    hist_b_Ratio_bc_Up[i]->GetYaxis()->SetTitle("Verh#ddot{a}ltnis");
    hist_b_Ratio_bc_Up[i]->GetYaxis()->SetTitleSize(0.04);
    hist_b_Ratio_bc_Up[i]->GetXaxis()->SetTitle("M_{T^{*}} [GeV/c^{2}]");
    hist_b_Ratio_bc_Up[i]->GetXaxis()->SetTitleSize(0.04);
   hist_b_Ratio_bc_Up[i]->GetYaxis()->SetTitleOffset(1.4);
  hist_b_Ratio_bc_Up[i]->GetXaxis()->SetTitleOffset(1.2);
 
   hist_b_Ratio_bc_Up[i]->Draw("hist");
    hist_b_Ratio_bc_Down[i]->Draw("hist SAME");
    line1->Draw("Same");
B_Tag_bc_sys->cd();
    c_B_bc_Tag->Write();
}


  //*************************************************************JEC****************************************************
 for (int i=0; i<16; ++i) {
 TCanvas* c_JEC = new TCanvas(sampleNames[i],sampleNames[i],bin_up,bin_down);
gStyle->SetOptStat(0);
c_JEC->SetGrid();
    TFile * file_nominal = new TFile(rootDir_nominal+sampleNames[i]+".root");
    hist_nominal[i] = (TH1F*)file_nominal->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 
    TFile * file_JEC_Down = new TFile(rootDir_JEC_Down+sampleNames[i]+".root");
    hist_JEC_Down[i] = (TH1F*)file_JEC_Down->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");

    TFile * file_JEC_Up = new TFile(rootDir_JEC_Up+sampleNames[i]+".root");
    hist_JEC_Up[i] = (TH1F*)file_JEC_Up->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");

   hist_JEC_Ratio_Down[i] = (TH1F*)hist_JEC_Down[i]->Clone("hist_JEC_Ratio_Down");
   hist_JEC_Ratio_Up[i] = (TH1F*)hist_JEC_Up[i]->Clone("hist_JEC_Ratio_Up");
 
   hist_JEC_Ratio_Down[i]->Divide(hist_nominal[i]);
   hist_JEC_Ratio_Up[i]->Divide(hist_nominal[i]);

   hist_JEC_Ratio_Down[i]->SetTitle("");
   hist_JEC_Ratio_Up[i]->SetTitle("");
   hist_JEC_Ratio_Down[i]->SetLineColor(kRed);
   hist_JEC_Ratio_Up[i]->SetLineColor(kBlue);
   hist_JEC_Ratio_Down[i]->SetLineStyle(2);
   hist_JEC_Ratio_Up[i]->SetLineStyle(2);
   hist_JEC_Ratio_Down[i]->SetLineWidth(2);
   hist_JEC_Ratio_Up[i]->SetLineWidth(2);
   //hist_JEC_Ratio_Down[i]->GetYaxis()->SetRangeUser(0.8,1.2);
    hist_JEC_Ratio_Up[i]->GetYaxis()->SetRangeUser(0.83,1.17);
   hist_JEC_Ratio_Up[i]->GetXaxis()->SetRangeUser(0,2000);
  hist_JEC_Ratio_Down[i]->GetXaxis()->SetRangeUser(0,2000);
    // hist_JEC_Ratio_Down[i]->GetYaxis()->SetTitle("Verh#ddot{a}ltnis");
    hist_JEC_Ratio_Up[i]->GetYaxis()->SetTitle("Verh#ddot{a}ltnis");
    hist_JEC_Ratio_Up[i]->GetYaxis()->SetTitleSize(0.04);
    hist_JEC_Ratio_Up[i]->GetXaxis()->SetTitle("M_{T^{*}} [GeV/c^{2}]");
    hist_JEC_Ratio_Up[i]->GetXaxis()->SetTitleSize(0.04);
   hist_JEC_Ratio_Up[i]->GetYaxis()->SetTitleOffset(1.4);
  hist_JEC_Ratio_Up[i]->GetXaxis()->SetTitleOffset(1.2);
 
   hist_JEC_Ratio_Up[i]->Draw("hist");
    hist_JEC_Ratio_Down[i]->Draw("hist SAME");
    line1->Draw("Same");
JEC_sys->cd();
    c_JEC->Write();
}

 //**************************************************************JER*************************************************************************
 for (int i=0; i<16; ++i) {
 TCanvas* c_JER = new TCanvas(sampleNames[i],sampleNames[i],bin_up,bin_down);
gStyle->SetOptStat(0);
c_JER->SetGrid();
    TFile * file_nominal = new TFile(rootDir_nominal+sampleNames[i]+".root");
    hist_nominal[i] = (TH1F*)file_nominal->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 
    TFile * file_JER_Down = new TFile(rootDir_JER_Down+sampleNames[i]+".root");
    hist_JER_Down[i] = (TH1F*)file_JER_Down->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");

    TFile * file_JER_Up = new TFile(rootDir_JER_Up+sampleNames[i]+".root");
    hist_JER_Up[i] = (TH1F*)file_JER_Up->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");

   hist_JER_Ratio_Down[i] = (TH1F*)hist_JER_Down[i]->Clone("hist_JER_Ratio_Down");
   hist_JER_Ratio_Up[i] = (TH1F*)hist_JER_Up[i]->Clone("hist_JER_Ratio_Up");
 
   hist_JER_Ratio_Down[i]->Divide(hist_nominal[i]);
   hist_JER_Ratio_Up[i]->Divide(hist_nominal[i]);

   hist_JER_Ratio_Down[i]->SetTitle("");
   hist_JER_Ratio_Up[i]->SetTitle("");
   hist_JER_Ratio_Down[i]->SetLineColor(kRed);
   hist_JER_Ratio_Up[i]->SetLineColor(kBlue);
   hist_JER_Ratio_Down[i]->SetLineStyle(2);
   hist_JER_Ratio_Up[i]->SetLineStyle(2);
   hist_JER_Ratio_Down[i]->SetLineWidth(2);
   hist_JER_Ratio_Up[i]->SetLineWidth(2);
   //hist_JER_Ratio_Down[i]->GetYaxis()->SetRangeUser(0.8,1.2);
    hist_JER_Ratio_Up[i]->GetYaxis()->SetRangeUser(0.83,1.17);
   hist_JER_Ratio_Up[i]->GetXaxis()->SetRangeUser(0,2000);
  hist_JER_Ratio_Down[i]->GetXaxis()->SetRangeUser(0,2000);
    // hist_JER_Ratio_Down[i]->GetYaxis()->SetTitle("Verh#ddot{a}ltnis");
    hist_JER_Ratio_Up[i]->GetYaxis()->SetTitle("Verh#ddot{a}ltnis");
    hist_JER_Ratio_Up[i]->GetYaxis()->SetTitleSize(0.04);
    hist_JER_Ratio_Up[i]->GetXaxis()->SetTitle("M_{T^{*}} [GeV/c^{2}]");
    hist_JER_Ratio_Up[i]->GetXaxis()->SetTitleSize(0.04);
   hist_JER_Ratio_Up[i]->GetYaxis()->SetTitleOffset(1.4);
  hist_JER_Ratio_Up[i]->GetXaxis()->SetTitleOffset(1.2);
 
   hist_JER_Ratio_Up[i]->Draw("hist");
   hist_JER_Ratio_Down[i]->Draw("hist SAME");
   line1->Draw("Same");
JER_sys->cd();
    c_JER->Write();
}


  for (int i=0; i<16; ++i) {
 TCanvas* c_MuonID = new TCanvas(sampleNames[i],sampleNames[i],bin_up,bin_down);
gStyle->SetOptStat(0);
c_MuonID->SetGrid();
    TFile * file_nominal = new TFile(rootDir_nominal+sampleNames[i]+".root");
    hist_nominal[i] = (TH1F*)file_nominal->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 
    TFile * file_MuonID_Down = new TFile(rootDir_MuonID_Down+sampleNames[i]+".root");
    hist_MuonID_Down[i] = (TH1F*)file_MuonID_Down->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");

    TFile * file_MuonID_Up = new TFile(rootDir_MuonID_Up+sampleNames[i]+".root");
    hist_MuonID_Up[i] = (TH1F*)file_MuonID_Up->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");

   hist_MuonID_Ratio_Down[i] = (TH1F*)hist_MuonID_Down[i]->Clone("hist_b_Ratio_Down");
   hist_MuonID_Ratio_Up[i] = (TH1F*)hist_MuonID_Up[i]->Clone("hist_b_Ratio_Up");
 
   hist_MuonID_Ratio_Down[i]->Divide(hist_nominal[i]);
   hist_MuonID_Ratio_Up[i]->Divide(hist_nominal[i]);

   hist_MuonID_Ratio_Down[i]->SetTitle("");
   hist_MuonID_Ratio_Up[i]->SetTitle("");
   hist_MuonID_Ratio_Down[i]->SetLineColor(kRed);
   hist_MuonID_Ratio_Up[i]->SetLineColor(kBlue);
   hist_MuonID_Ratio_Down[i]->SetLineStyle(2);
   hist_MuonID_Ratio_Up[i]->SetLineStyle(2);
   hist_MuonID_Ratio_Down[i]->SetLineWidth(2);
   hist_MuonID_Ratio_Up[i]->SetLineWidth(2);
   //hist_b_Ratio_Down[i]->GetYaxis()->SetRangeUser(0.8,1.2);
    hist_MuonID_Ratio_Up[i]->GetYaxis()->SetRangeUser(0.83,1.17);
   hist_MuonID_Ratio_Up[i]->GetXaxis()->SetRangeUser(0,2000);
  hist_MuonID_Ratio_Down[i]->GetXaxis()->SetRangeUser(0,2000);
    // hist_b_Ratio_Down[i]->GetYaxis()->SetTitle("Verh#ddot{a}ltnis");
    hist_MuonID_Ratio_Up[i]->GetYaxis()->SetTitle("Verh#ddot{a}ltnis");
    hist_MuonID_Ratio_Up[i]->GetYaxis()->SetTitleSize(0.04);
    hist_MuonID_Ratio_Up[i]->GetXaxis()->SetTitle("M_{T^{*}} [GeV/c^{2}]");
    hist_MuonID_Ratio_Up[i]->GetXaxis()->SetTitleSize(0.04);
   hist_MuonID_Ratio_Up[i]->GetYaxis()->SetTitleOffset(1.4);
  hist_MuonID_Ratio_Up[i]->GetXaxis()->SetTitleOffset(1.2);
 
   hist_MuonID_Ratio_Up[i]->Draw("hist");
    hist_MuonID_Ratio_Down[i]->Draw("hist SAME");
    line1->Draw("Same");
MuonID_sys->cd();
    c_MuonID->Write();
}


  for (int i=0; i<16; ++i) {
 TCanvas* c_MuonTrigger = new TCanvas(sampleNames[i],sampleNames[i],bin_up,bin_down);
gStyle->SetOptStat(0);
c_MuonTrigger->SetGrid();
    TFile * file_nominal = new TFile(rootDir_nominal+sampleNames[i]+".root");
    hist_nominal[i] = (TH1F*)file_nominal->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 
    TFile * file_MuonTrigger_Down = new TFile(rootDir_MuonTrigger_Down+sampleNames[i]+".root");
    hist_MuonTrigger_Down[i] = (TH1F*)file_MuonTrigger_Down->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");

    TFile * file_MuonTrigger_Up = new TFile(rootDir_MuonTrigger_Up+sampleNames[i]+".root");
    hist_MuonTrigger_Up[i] = (TH1F*)file_MuonTrigger_Up->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");

   hist_MuonTrigger_Ratio_Down[i] = (TH1F*)hist_MuonTrigger_Down[i]->Clone("hist_b_Ratio_Down");
   hist_MuonTrigger_Ratio_Up[i] = (TH1F*)hist_MuonTrigger_Up[i]->Clone("hist_b_Ratio_Up");
 
   hist_MuonTrigger_Ratio_Down[i]->Divide(hist_nominal[i]);
   hist_MuonTrigger_Ratio_Up[i]->Divide(hist_nominal[i]);

   hist_MuonTrigger_Ratio_Down[i]->SetTitle("");
   hist_MuonTrigger_Ratio_Up[i]->SetTitle("");
   hist_MuonTrigger_Ratio_Down[i]->SetLineColor(kRed);
   hist_MuonTrigger_Ratio_Up[i]->SetLineColor(kBlue);
   hist_MuonTrigger_Ratio_Down[i]->SetLineStyle(2);
   hist_MuonTrigger_Ratio_Up[i]->SetLineStyle(2);
   hist_MuonTrigger_Ratio_Down[i]->SetLineWidth(2);
   hist_MuonTrigger_Ratio_Up[i]->SetLineWidth(2);
   //hist_b_Ratio_Down[i]->GetYaxis()->SetRangeUser(0.8,1.2);
    hist_MuonTrigger_Ratio_Up[i]->GetYaxis()->SetRangeUser(0.83,1.17);
   hist_MuonTrigger_Ratio_Up[i]->GetXaxis()->SetRangeUser(0,2000);
  hist_MuonTrigger_Ratio_Down[i]->GetXaxis()->SetRangeUser(0,2000);
    // hist_b_Ratio_Down[i]->GetYaxis()->SetTitle("Verh#ddot{a}ltnis");
    hist_MuonTrigger_Ratio_Up[i]->GetYaxis()->SetTitle("Verh#ddot{a}ltnis");
    hist_MuonTrigger_Ratio_Up[i]->GetYaxis()->SetTitleSize(0.04);
    hist_MuonTrigger_Ratio_Up[i]->GetXaxis()->SetTitle("M_{T^{*}} [GeV/c^{2}]");
    hist_MuonTrigger_Ratio_Up[i]->GetXaxis()->SetTitleSize(0.04);
   hist_MuonTrigger_Ratio_Up[i]->GetYaxis()->SetTitleOffset(1.4);
  hist_MuonTrigger_Ratio_Up[i]->GetXaxis()->SetTitleOffset(1.2);
 
   hist_MuonTrigger_Ratio_Up[i]->Draw("hist");
   hist_MuonTrigger_Ratio_Down[i]->Draw("hist SAME");
   line1->Draw("Same");
MuonTrigger_sys->cd();
    c_MuonTrigger->Write();
}


  for (int i=0; i<16; ++i) {
 TCanvas* c_PU = new TCanvas(sampleNames[i],sampleNames[i],bin_up,bin_down);
gStyle->SetOptStat(0);
c_PU->SetGrid();
    TFile * file_nominal = new TFile(rootDir_nominal+sampleNames[i]+".root");
    hist_nominal[i] = (TH1F*)file_nominal->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 
    TFile * file_PU_Down = new TFile(rootDir_PU_Down+sampleNames[i]+".root");
    hist_PU_Down[i] = (TH1F*)file_PU_Down->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");

    TFile * file_PU_Up = new TFile(rootDir_PU_Up+sampleNames[i]+".root");
    hist_PU_Up[i] = (TH1F*)file_PU_Up->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");

   hist_PU_Ratio_Down[i] = (TH1F*)hist_PU_Down[i]->Clone("hist_b_Ratio_Down");
   hist_PU_Ratio_Up[i] = (TH1F*)hist_PU_Up[i]->Clone("hist_b_Ratio_Up");
 
   hist_PU_Ratio_Down[i]->Divide(hist_nominal[i]);
   hist_PU_Ratio_Up[i]->Divide(hist_nominal[i]);

   hist_PU_Ratio_Down[i]->SetTitle("");
   hist_PU_Ratio_Up[i]->SetTitle("");
   hist_PU_Ratio_Down[i]->SetLineColor(kRed);
   hist_PU_Ratio_Up[i]->SetLineColor(kBlue);
   hist_PU_Ratio_Down[i]->SetLineStyle(2);
   hist_PU_Ratio_Up[i]->SetLineStyle(2);
   hist_PU_Ratio_Down[i]->SetLineWidth(2);
   hist_PU_Ratio_Up[i]->SetLineWidth(2);
   //hist_b_Ratio_Down[i]->GetYaxis()->SetRangeUser(0.8,1.2);
    hist_PU_Ratio_Up[i]->GetYaxis()->SetRangeUser(0.83,1.17);
   hist_PU_Ratio_Up[i]->GetXaxis()->SetRangeUser(0,2000);
  hist_PU_Ratio_Down[i]->GetXaxis()->SetRangeUser(0,2000);
    // hist_b_Ratio_Down[i]->GetYaxis()->SetTitle("Verh#ddot{a}ltnis");
    hist_PU_Ratio_Up[i]->GetYaxis()->SetTitle("Verh#ddot{a}ltnis");
    hist_PU_Ratio_Up[i]->GetYaxis()->SetTitleSize(0.04);
    hist_PU_Ratio_Up[i]->GetXaxis()->SetTitle("M_{T^{*}} [GeV/c^{2}]");
   hist_PU_Ratio_Up[i]->GetXaxis()->SetTitleSize(0.04);
   hist_PU_Ratio_Up[i]->GetYaxis()->SetTitleOffset(1.4);
  hist_PU_Ratio_Up[i]->GetXaxis()->SetTitleOffset(1.2);
 
   hist_PU_Ratio_Up[i]->Draw("hist");
   hist_PU_Ratio_Down[i]->Draw("hist SAME");
   line1->Draw("Same");
PU_sys->cd();
    c_PU->Write();
}



fileSystematics->Write();
fileSystematics->Close();



  // ******************************************
 
}












