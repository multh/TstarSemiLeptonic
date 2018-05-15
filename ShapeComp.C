//ShapeComp.C

//Small Script for combining different Signal Shapes 


void ShapeComp() {
  const TString signal1_input = "/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/03Feb2017_Relaunch_17Jan2018/Muons/CSV_Study/No_Cuts/";
  const TString signal2_input = "/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/03Feb2017_Relaunch_17Jan2018/Muons/CSV_Study/Cuts/";

  const TString chi2_dir  = "chi2min__HypHists/";
  const TString ttag_dir  = "chi2min_ttag__HypHists/";

  const int n_sig = 2;  
  const TString signal_file[n_sig] = {"Tstar_M-900","Tstar_M-1500"};

  TFile *signal1[n_sig];
  TFile *signal2[n_sig];

  TH1F *h_Tstarlep_signal1[n_sig];
  TH1F *h_Tstarhad_signal1[n_sig];

  TH1F *h_Tstarlep_signal2[n_sig];
  TH1F *h_Tstarhad_signal2[n_sig];

  TH1F *h_Tstarlep_ttag_signal1[n_sig];
  TH1F *h_Tstarhad_ttag_signal1[n_sig];

  TH1F *h_Tstarlep_ttag_signal2[n_sig];
  TH1F *h_Tstarhad_ttag_signal2[n_sig];


  for(int i =0; i<n_sig; i++){
    signal1[i]   = new TFile(signal1_input+"uhh2.AnalysisModuleRunner.MC."+signal_file[i]+".root");
    signal2[i]   = new TFile(signal2_input+"uhh2.AnalysisModuleRunner.MC."+signal_file[i]+".root");

    h_Tstarlep_signal1[i] = (TH1F*)signal1[i]->Get(chi2_dir+"M_Tstarlep_rec");
    h_Tstarlep_signal1[i] ->Scale(1/(h_Tstarlep_signal1[i]->Integral()));

    h_Tstarlep_signal2[i] = (TH1F*)signal2[i]->Get(chi2_dir+"M_Tstarlep_rec");
    h_Tstarlep_signal2[i] ->Scale(1/(h_Tstarlep_signal2[i]->Integral()));

    h_Tstarhad_signal1[i] = (TH1F*)signal1[i]->Get(chi2_dir+"M_Tstarhad_rec");
    h_Tstarhad_signal1[i] ->Scale(1/(h_Tstarhad_signal1[i]->Integral()));

    h_Tstarhad_signal2[i] = (TH1F*)signal2[i]->Get(chi2_dir+"M_Tstarhad_rec");
    h_Tstarhad_signal2[i] ->Scale(1/(h_Tstarhad_signal2[i]->Integral()));

    h_Tstarlep_ttag_signal1[i] = (TH1F*)signal1[i]->Get(ttag_dir+"M_Tstarlep_rec");
    h_Tstarlep_ttag_signal1[i] ->Scale(1/(h_Tstarlep_ttag_signal1[i]->Integral()));

    h_Tstarlep_ttag_signal2[i] = (TH1F*)signal2[i]->Get(ttag_dir+"M_Tstarlep_rec");
    h_Tstarlep_ttag_signal2[i] ->Scale(1/(h_Tstarlep_ttag_signal2[i]->Integral()));

    h_Tstarhad_ttag_signal1[i] = (TH1F*)signal1[i]->Get(ttag_dir+"M_Tstarhad_rec");
    h_Tstarhad_ttag_signal1[i] ->Scale(1/(h_Tstarhad_ttag_signal1[i]->Integral()));

    h_Tstarhad_ttag_signal2[i] = (TH1F*)signal2[i]->Get(ttag_dir+"M_Tstarhad_rec");
    h_Tstarhad_ttag_signal2[i] ->Scale(1/(h_Tstarhad_ttag_signal2[i]->Integral()));

  }


  TCanvas *c1 = new TCanvas("c1", "",700,600);
  gStyle->SetOptStat(0);

  h_Tstarlep_signal1[0] -> SetLineColor(kBlue);
  h_Tstarlep_signal1[0] -> SetLineWidth(3);
  h_Tstarlep_signal1[0] -> SetMaximum(0.14);
  h_Tstarlep_signal1[0] -> GetYaxis() -> SetTitle("#Delta N/N");
  h_Tstarlep_signal1[0] -> GetXaxis() -> SetTitle("M_{T_{lep}^{*}} [GeV/c^{2}]");
  h_Tstarlep_signal1[0] -> Draw("hist");
  h_Tstarlep_signal2[0] -> SetLineWidth(3);
  h_Tstarlep_signal2[0] -> SetLineColor(kRed);
  h_Tstarlep_signal2[0] -> Draw("hist,SAME");

  c1->Print("/nfs/dust/cms/user/multh/CMSSW_8_0_26_patch2/src/UHH2/TstarSemiLeptonic/Signal_Shape_lep_"+signal_file[0]+".pdf");

  
  TCanvas *c2 = new TCanvas("c2", "",700,600);
  gStyle->SetOptStat(0);

  h_Tstarlep_signal1[1] -> SetLineColor(kBlue);
  h_Tstarlep_signal1[1] -> SetLineWidth(3);
  h_Tstarlep_signal1[1] -> SetMaximum(0.14);
  h_Tstarlep_signal1[1] -> GetYaxis() -> SetTitle("#Delta N/N");
  h_Tstarlep_signal1[1] -> GetXaxis() -> SetTitle("M_{T_{lep}^{*}} [GeV/c^{2}]");
  h_Tstarlep_signal1[1] -> Draw("hist");
  h_Tstarlep_signal2[1] -> SetLineWidth(3);
  h_Tstarlep_signal2[1] -> SetLineColor(kRed);
  h_Tstarlep_signal2[1] -> Draw("hist, SAME");

  c2->Print("/nfs/dust/cms/user/multh/CMSSW_8_0_26_patch2/src/UHH2/TstarSemiLeptonic/Signal_Shape_lep_"+signal_file[1]+".pdf");

  TCanvas *c3 = new TCanvas("c3", "",700,600);
  gStyle->SetOptStat(0);

  h_Tstarlep_ttag_signal1[0] -> SetLineColor(kBlue);
  h_Tstarlep_ttag_signal1[0] -> SetLineWidth(3);
  h_Tstarlep_ttag_signal1[0] -> SetMaximum(0.2);
  h_Tstarlep_ttag_signal1[0] -> GetYaxis() -> SetTitle("#Delta N/N");
  h_Tstarlep_ttag_signal1[0] -> GetXaxis() -> SetTitle("M_{T_{lep}^{*}} [GeV/c^{2}]");
  h_Tstarlep_ttag_signal1[0] -> Draw("hist");
  h_Tstarlep_ttag_signal2[0] -> SetLineWidth(3);
  h_Tstarlep_ttag_signal2[0] -> SetLineColor(kRed);
  h_Tstarlep_ttag_signal2[0] -> Draw("hist, SAME");

  c3->Print("/nfs/dust/cms/user/multh/CMSSW_8_0_26_patch2/src/UHH2/TstarSemiLeptonic/Signal_Shape_lep_ttag_"+signal_file[0]+".pdf");

  
  TCanvas *c4 = new TCanvas("c4", "",700,600);
  gStyle->SetOptStat(0);

  h_Tstarlep_ttag_signal1[1] -> SetLineColor(kBlue);
  h_Tstarlep_ttag_signal1[1] -> SetLineWidth(3);
  h_Tstarlep_ttag_signal1[1] -> SetMaximum(0.2);
  h_Tstarlep_ttag_signal1[1] -> GetYaxis() -> SetTitle("#Delta N/N");
  h_Tstarlep_ttag_signal1[1] -> GetXaxis() -> SetTitle("M_{T_{lep}^{*}} [GeV/c^{2}]");
  h_Tstarlep_ttag_signal1[1] -> Draw("hist");
  h_Tstarlep_ttag_signal2[1] -> SetLineWidth(3);
  h_Tstarlep_ttag_signal2[1] -> SetLineColor(kRed);
  h_Tstarlep_ttag_signal2[1] -> Draw("hist, SAME");

  c4->Print("/nfs/dust/cms/user/multh/CMSSW_8_0_26_patch2/src/UHH2/TstarSemiLeptonic/Signal_Shape_lep_ttag_"+signal_file[1]+".pdf");

  
}
