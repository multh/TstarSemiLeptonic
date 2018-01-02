void plot()
{
  gStyle->SetOptStat(0);

  TFile* bkg = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Test/uhh2.AnalysisModuleRunner.MC.QCD.root", "READ");
  // TFile* sig = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/uhh2.AnalysisModuleRunner.MC.Tstar_M-1500.root", "READ");
  TFile* sig = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Test/uhh2.AnalysisModuleRunner.MC.Tstar_M-700.root", "READ");

  TH2D* hbkg = (TH2D*) bkg->Get("1Muon_Muons/deltaRmin_ptrel");

  TH2D* hsig = (TH2D*) sig->Get("1Muon_Muons/deltaRmin_ptrel");

  TLine *line1 = new TLine(0,25,0.3,25);
  TLine *line2 = new TLine(0.3,0,0.3,25);
 
  line1->SetLineWidth(4);
  line1->SetLineColor(kRed);
  
  line2->SetLineWidth(4);
  line2->SetLineColor(kRed);

  TLegend *leg1;
  leg1 = new TLegend(0.1,0.7,0.48,0.9);//x+0.1
  leg1->SetBorderSize(2);
  leg1->SetTextSize(0.035);
  leg1->SetFillColor(10);
  leg1->SetLineColor(1);
  leg1->SetTextFont(42);


  cout << "hbkg = " << hbkg << " sig =" << hsig << endl;

  hbkg->Scale(1./(hbkg->Integral()));
  hsig->Scale(1./(hsig->Integral()));

  hbkg->SetMarkerStyle(20);
  hbkg->SetMarkerSize(1);
  hbkg->SetMarkerColor(kBlack);

  hsig->SetMarkerStyle(20);
  hsig->SetMarkerSize(1);
  hsig->SetMarkerColor(kAzure+1);

  hsig->GetXaxis()->SetTitle("#Delta R_{min} (#mu,Jet)");
  hsig->GetXaxis()->SetTitleSize(0.045);
  hsig->GetYaxis()->SetTitle("p_{T}^{rel}");
  hsig->GetYaxis()->SetTitleSize(0.045);
  hsig->GetYaxis()->SetTitleOffset(1.1);

  hsig->SetTitle("");

  hsig->Draw("scat");
  hbkg->Draw("scat same");
 line1 ->Draw("L same");
 line2->Draw("L same");

  leg1->AddEntry(hsig, "T* (1500 GeV/c^{2})","P");
  leg1->AddEntry(hbkg, "QCD","P");

  leg1->Draw();

}
