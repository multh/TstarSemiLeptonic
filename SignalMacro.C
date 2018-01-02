//SignalMacro.C

//Small Script for combining different Signal Shapes 


void SignalMacro() {
 // open a file and get a histogram
 TFile *s1 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/uhh2.AnalysisModuleRunner.MC.Tstar_M-700.root");
 TFile *s2 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/uhh2.AnalysisModuleRunner.MC.Tstar_M-800.root");
 TFile *s3 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/uhh2.AnalysisModuleRunner.MC.Tstar_M-900.root");
 TFile *s4 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/uhh2.AnalysisModuleRunner.MC.Tstar_M-1000.root");
 TFile *s5 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/uhh2.AnalysisModuleRunner.MC.Tstar_M-1100.root");
 TFile *s6 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/uhh2.AnalysisModuleRunner.MC.Tstar_M-1200.root");
 TFile *s7 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/uhh2.AnalysisModuleRunner.MC.Tstar_M-1300.root");
 TFile *s8 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/uhh2.AnalysisModuleRunner.MC.Tstar_M-1400.root");
 TFile *s9 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/uhh2.AnalysisModuleRunner.MC.Tstar_M-1500.root");
 TFile *s10 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/uhh2.AnalysisModuleRunner.MC.Tstar_M-1600.root");
 /*
 TH1F *h1    = (TH1F*)s1->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 //TH1F *h2    = (TH1F*)s2->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 //TH1F *h3    = (TH1F*)s3->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 //TH1F *h4    = (TH1F*)s4->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 TH1F *h5    = (TH1F*)s5->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 //TH1F *h6    = (TH1F*)s6->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 TH1F *h7    = (TH1F*)s7->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 //TH1F *h8    = (TH1F*)s8->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 //TH1F *h9    = (TH1F*)s9->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 TH1F *h10    = (TH1F*)s10->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 */
 TH1F *h1    = (TH1F*)s1->Get("chi2min_ttag__HypHists/M_Tstar_comb");
 //TH1F *h2    = (TH1F*)s2->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 //TH1F *h3    = (TH1F*)s3->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 //TH1F *h4    = (TH1F*)s4->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 TH1F *h5    = (TH1F*)s5->Get("chi2min_ttag__HypHists/M_Tstar_comb");
 //TH1F *h6    = (TH1F*)s6->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 TH1F *h7    = (TH1F*)s7->Get("chi2min_ttag__HypHists/M_Tstar_comb");
 //TH1F *h8    = (TH1F*)s8->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 //TH1F *h9    = (TH1F*)s9->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 TH1F *h10    = (TH1F*)s10->Get("chi2min_ttag__HypHists/M_Tstar_comb");



 TH1F* histos[4]={h1,h5,h7,h10};
for (int i=0;i<4;++i){
         histos[i]->Sumw2(); // *Very* Important
        }

 gStyle->SetOptStat(0);



	 histos[0]->Scale(1/(histos[0]->Integral()));
	 histos[0]->SetTitle("");
	 histos[0]->SetLineColor(kBlue);
	 histos[0]->SetLineStyle(1);
	 histos[0]->SetLineWidth(2);
	 histos[0]->GetYaxis()->SetTitle("#Delta N/N");
	 histos[0]->GetYaxis()->SetTitleOffset(1.3);
	 histos[0]->GetXaxis()->SetTitle("M_{T^{*}} [GeV/c^{2}]");
	 histos[0]->GetXaxis()->SetTitleOffset(1.2);
	 histos[0]->Draw("hist");
	 //	 histos[1]->Scale(1/(histos[1]->Integral()));
	 //histos[1]->Draw("same");
	 histos[1]->Scale(1/(histos[2]->Integral()));
	 histos[1]->SetTitle("");
	 histos[1]->SetLineColor(kRed);
	 histos[1]->SetLineStyle(1);
	 histos[1]->SetLineWidth(2);

	 histos[1]->Draw("hist same");
	 histos[3]->Scale(1/(histos[3]->Integral()));
	 histos[3]->SetTitle("");
	 histos[3]->SetLineColor(kGreen);
	 histos[3]->SetLineStyle(1);
	 histos[3]->SetLineWidth(2);

	 histos[3]->Draw("hist same");

leg = new TLegend(0.1,0.7,0.48,0.9);
   leg->AddEntry(histos[0],"M_{T^{*}} = 700 GeV/c^{2}","l");
   leg->AddEntry(histos[1],"M_{T^{*}} = 1100 GeV/c^{2}","l");
   leg->AddEntry(histos[3],"M_{T^{*}} = 1600 GeV/c^{2}","l");
  
   leg->Draw();

}

