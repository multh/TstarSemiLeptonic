//SignalMacro.C

//Small Script for combining different Signal Shapes 


void SignalMacro() {
 // open a file and get a histogram
 const TString input_dir = "/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/03Feb2017_Relaunch_17Jan2018/Muons/Changed_Reco/Comp/";
  //  const TString input_dir = "/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/03Feb2017_Relaunch_17Jan2018/Electron/";
  const TString Hist_dir  = "chi2min__HypHists/";

  const int n_sig = 10;  
  const TString signal_file[n_sig] = {"Tstar_M-700", "Tstar_M-800", "Tstar_M-900", "Tstar_M-1000", "Tstar_M-1100", "Tstar_M-1200", "Tstar_M-1300", "Tstar_M-1400", "Tstar_M-1500", "Tstar_M-1600"};

 TFile *signal[n_sig];
 TH1F *h_signal_lep[n_sig];
 TH1F *h_signal_had[n_sig];

 TH1F *h_signal_toplep[n_sig];
 TH1F *h_signal_tophad[n_sig];


 for(int i =0; i<n_sig; i++){
   signal[i]   = new TFile(input_dir+"uhh2.AnalysisModuleRunner.MC."+signal_file[i]+".root");
   h_signal_lep[i] = (TH1F*)signal[i]->Get(Hist_dir+"M_Tstarlep_rec");
   h_signal_had[i] = (TH1F*)signal[i]->Get(Hist_dir+"M_Tstarhad_rec");

   h_signal_toplep[i] = (TH1F*)signal[i]->Get(Hist_dir+"M_toplep");
   h_signal_tophad[i] = (TH1F*)signal[i]->Get(Hist_dir+"M_tophad");
 }

 TCanvas *c1 = new TCanvas("c1", "",700,600);
 c1->Divide(2,2);
 gStyle->SetOptStat(0);

 c1->cd(1);

 //h_signal_lep[0]->Scale(1/(h_signal_lep[0]->Integral()));
 h_signal_lep[0]->SetMaximum(70);
 h_signal_lep[0]->SetTitle("");
 h_signal_lep[0]->SetLineColor(kBlue);
 h_signal_lep[0]->SetLineStyle(1);
 h_signal_lep[0]->SetLineWidth(2);
 h_signal_lep[0]->GetYaxis()->SetTitle("#Delta N/N");
 h_signal_lep[0]->GetYaxis()->SetTitleOffset(1.3);
 h_signal_lep[0]->GetXaxis()->SetTitle("M_{T_{lep}^{*}} [GeV/c^{2}]");
 h_signal_lep[0]->GetXaxis()->SetTitleOffset(1.2);
 h_signal_lep[0]->Draw("hist");
 //	 h_signal[4]->Scale(1/(h_signal[4]->Integral()));
 //h_signal[4]->Draw("same");
 //h_signal_lep[4]->Scale(1/(h_signal_lep[4]->Integral()));
 h_signal_lep[4]->SetTitle("");
 h_signal_lep[4]->SetLineColor(kRed);
 h_signal_lep[4]->SetLineStyle(1);
 h_signal_lep[4]->SetLineWidth(2);
 
 h_signal_lep[4]->Draw("hist same");

 // h_signal_lep[8]->Scale(1/(h_signal_lep[8]->Integral()));
 h_signal_lep[8]->SetTitle("");
 h_signal_lep[8]->SetLineColor(kGreen);
 h_signal_lep[8]->SetLineStyle(1);
 h_signal_lep[8]->SetLineWidth(2);
 
 h_signal_lep[8]->Draw("hist same");
 
 leg = new TLegend(0.65,0.8,0.9,0.9);
 leg->AddEntry(h_signal_lep[0],"M_{T^{*}} = 700 GeV/c^{2}","l");
 leg->AddEntry(h_signal_lep[4],"M_{T^{*}} = 1100 GeV/c^{2}","l");
 leg->AddEntry(h_signal_lep[8],"M_{T^{*}} = 1500 GeV/c^{2}","l");
 
 leg->Draw();
 
 c1->cd(2);

 // h_signal_had[0]->Scale(1/(h_signal_had[0]->Integral()));
 h_signal_had[0]->SetTitle("");
 h_signal_had[0]->SetMaximum(70);
 h_signal_had[0]->SetLineColor(kBlue);
 h_signal_had[0]->SetLineStyle(1);
 h_signal_had[0]->SetLineWidth(2);
 h_signal_had[0]->GetYaxis()->SetTitle("#Delta N/N");
 h_signal_had[0]->GetYaxis()->SetTitleOffset(1.3);
 h_signal_had[0]->GetXaxis()->SetTitle("M_{T_{had}^{*}} [GeV/c^{2}]");
 h_signal_had[0]->GetXaxis()->SetTitleOffset(1.2);
 h_signal_had[0]->Draw("hist");
 //	 h_signal[4]->Scale(1/(h_signal[4]->Integral()));
 //h_signal[4]->Draw("same");
 // h_signal_had[4]->Scale(1/(h_signal_had[4]->Integral()));
 h_signal_had[4]->SetTitle("");
 h_signal_had[4]->SetLineColor(kRed);
 h_signal_had[4]->SetLineStyle(1);
 h_signal_had[4]->SetLineWidth(2);
 
 h_signal_had[4]->Draw("hist same");

 // h_signal_had[8]->Scale(1/(h_signal_had[8]->Integral()));
 h_signal_had[8]->SetTitle("");
 h_signal_had[8]->SetLineColor(kGreen);
 h_signal_had[8]->SetLineStyle(1);
 h_signal_had[8]->SetLineWidth(2);
 
 h_signal_had[8]->Draw("hist same");
 
 leg1 = new TLegend(0.65,0.8,0.9,0.9);
 leg1->AddEntry(h_signal_had[0],"M_{T^{*}} = 700 GeV/c^{2}","l");
 leg1->AddEntry(h_signal_had[4],"M_{T^{*}} = 1100 GeV/c^{2}","l");
 leg1->AddEntry(h_signal_had[8],"M_{T^{*}} = 1500 GeV/c^{2}","l");
 
 leg1->Draw();


 c1->cd(3);
 //h_signal_toplep[0]->Scale(1/(h_signal_toplep[0]->Integral()));
 h_signal_toplep[0]->SetMaximum(70);
 h_signal_toplep[0]->SetTitle("");
 h_signal_toplep[0]->SetLineColor(kBlue);
 h_signal_toplep[0]->SetLineStyle(1);
 h_signal_toplep[0]->SetLineWidth(2);
 h_signal_toplep[0]->GetYaxis()->SetTitle("#Delta N/N");
 h_signal_toplep[0]->GetYaxis()->SetTitleOffset(1.3);
 h_signal_toplep[0]->GetXaxis()->SetTitle("M_{top_{lep}} [GeV/c^{2}]");
 h_signal_toplep[0]->GetXaxis()->SetTitleOffset(1.2);
 h_signal_toplep[0]->Draw("hist");
 //	 h_signal[4]->Scale(1/(h_signal[4]->Integral()));
 //h_signal[4]->Draw("same");
 //h_signal_toplep[4]->Scale(1/(h_signal_toplep[4]->Integral()));
 h_signal_toplep[4]->SetTitle("");
 h_signal_toplep[4]->SetLineColor(kRed);
 h_signal_toplep[4]->SetLineStyle(1);
 h_signal_toplep[4]->SetLineWidth(2);
 
 h_signal_toplep[4]->Draw("hist same");

 // h_signal_toplep[8]->Scale(1/(h_signal_toplep[8]->Integral()));
 h_signal_toplep[8]->SetTitle("");
 h_signal_toplep[8]->SetLineColor(kGreen);
 h_signal_toplep[8]->SetLineStyle(1);
 h_signal_toplep[8]->SetLineWidth(2);
 
 h_signal_toplep[8]->Draw("hist same");
 
 leg->Draw();


 c1->cd(4);
 //h_signal_tophad[0]->Scale(1/(h_signal_tophad[0]->Integral()));
 h_signal_tophad[0]->SetMaximum(70);
 h_signal_tophad[0]->SetTitle("");
 h_signal_tophad[0]->SetLineColor(kBlue);
 h_signal_tophad[0]->SetLineStyle(1);
 h_signal_tophad[0]->SetLineWidth(2);
 h_signal_tophad[0]->GetYaxis()->SetTitle("#Delta N/N");
 h_signal_tophad[0]->GetYaxis()->SetTitleOffset(1.3);
 h_signal_tophad[0]->GetXaxis()->SetTitle("M_{top_{had}} [GeV/c^{2}]");
 h_signal_tophad[0]->GetXaxis()->SetTitleOffset(1.2);
 h_signal_tophad[0]->Draw("hist");
 //	 h_signal[4]->Scale(1/(h_signal[4]->Integral()));
 //h_signal[4]->Draw("same");
 //h_signal_tophad[4]->Scale(1/(h_signal_tophad[4]->Integral()));
 h_signal_tophad[4]->SetTitle("");
 h_signal_tophad[4]->SetLineColor(kRed);
 h_signal_tophad[4]->SetLineStyle(1);
 h_signal_tophad[4]->SetLineWidth(2);
 
 h_signal_tophad[4]->Draw("hist same");

 // h_signal_tophad[8]->Scale(1/(h_signal_tophad[8]->Integral()));
 h_signal_tophad[8]->SetTitle("");
 h_signal_tophad[8]->SetLineColor(kGreen);
 h_signal_tophad[8]->SetLineStyle(1);
 h_signal_tophad[8]->SetLineWidth(2);
 
 h_signal_tophad[8]->Draw("hist same");
 
 leg->Draw();


}

