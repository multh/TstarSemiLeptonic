
void Lumi_Plot(){
TLatex latex;

 gROOT->SetStyle("Plain");

  gStyle->SetOptTitle(0);

  gStyle->SetOptStat(kFALSE);


  // plot the lumi yield histogram
   TFile *Data = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/uhh2.AnalysisModuleRunner.DATA.SingleMuData.root","READ");
   //TFile *Data = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Nominal/uhh2.AnalysisModuleRunner.DATA.SingleMuDATA.root","READ");

  TH1F *h  = (TH1F*)Data->Get("chi2_Lumi/luminosity");
  //TH1F *h  = (TH1F*)Data->Get("twodcut_Lumi/luminosity");
  
  h->GetYaxis()->SetRangeUser(0,400);
  h->GetXaxis()->SetTitle("integrierte Luminosit#ddot{a}t [pb^{-1}]");
  h->GetXaxis()->SetTitleSize(0.04);
  h->GetXaxis()->SetTitleOffset(1.3);
  h->GetYaxis()->SetTitle("Ereignisse pro 50 pb^{-1}");
  h->GetYaxis()->SetTitleOffset(1.5);
  h->GetYaxis()->SetTitleSize(0.04);
  h->SetMarkerStyle(20);

  h->Draw();

  // calculate the average
  //TH1* h = hdata->GetHist();
  double sum=0;
  int bins=0;
  for (int i=1; i<h->GetNbinsX()+1; ++i){
    if (h->GetBinContent(i)>0){
      sum += h->GetBinContent(i);
      bins++;
    }
  }
  double av = sum / bins;

  // calculate average with outlier-rejection (4sigma)
  sum=0;
  bins=0;
  for (int i=1; i<h->GetNbinsX()+1; ++i){
    if (h->GetBinContent(i)>0){
      double dev = TMath::Abs( (h->GetBinContent(i) - av)/h->GetBinError(i) );
      if (dev<4){
	sum += h->GetBinContent(i);
	bins++;
      } else {
	cout << "Lumi yield: outlier in bin " << i << " with content " << h->GetBinContent(i) << " average = " << av << endl;
      } 
    }
  }
  av = sum / bins;

  // calculate error on mean and chi2
  double dev = 0;
  double chi2 = 0;
  for (int i=1; i<h->GetNbinsX()+1; ++i){
    if (h->GetBinContent(i)>0){
      double pull = (h->GetBinContent(i) - av)/h->GetBinError(i);
      if (TMath::Abs(pull)<4){
	dev += TMath::Power(h->GetBinContent(i)-av, 2);
	chi2 += pull*pull;
      }
    }
  }
  double err = TMath::Sqrt(dev/bins);

  // highlight points with deviations of more than 3, 4 and 5 sigma 
  double xr = h->GetXaxis()->GetXmax() - h->GetXaxis()->GetXmin();
  double wi = gPad->GetAbsWNDC() * (1 - gPad->GetLeftMargin() - gPad->GetRightMargin());
  double he = gPad->GetAbsHNDC() * (1 - gPad->GetTopMargin() - gPad->GetBottomMargin());
  double ar = wi/he;
  double fudge = 1.;
  //if (bSingleEPS) fudge = 1.2;
  double r1 = 0.02*xr*fudge;
  double yr = h->GetMaximum()-h->GetMinimum();
  double r2 = 0.016*yr*ar*fudge;
  for (int i=1; i<h->GetNbinsX()+1; ++i){
    if (h->GetBinContent(i)>0){
      double pull = (h->GetBinContent(i) - av)/h->GetBinError(i);
      if (TMath::Abs(pull)>5){
	TEllipse* circ = new TEllipse(h->GetXaxis()->GetBinCenter(i), h->GetBinContent(i), r1, r2);
	circ->SetFillColor(kWhite);
	circ->SetLineColor(kRed);
	circ->Draw();
      } else if (TMath::Abs(pull)>4){
	TEllipse* circ = new TEllipse(h->GetXaxis()->GetBinCenter(i), h->GetBinContent(i), r1, r2);
	circ->SetFillColor(kWhite);
	circ->SetLineColor(kOrange);
	circ->Draw();
      } else if (TMath::Abs(pull)>3){
	TEllipse* circ = new TEllipse(h->GetXaxis()->GetBinCenter(i), h->GetBinContent(i), r1, r2);
	circ->SetFillColor(kWhite);
	circ->SetLineColor(kRed);
	circ->Draw();
      }
    }
  }

  // draw the average
  TF1* f = new TF1("average", "[0]", h->GetXaxis()->GetXmin(), h->GetXaxis()->GetXmax());
  f->SetLineColor(kAzure+1);
  f->SetLineWidth(1);
  f->SetParameter(0, av);
  f->Draw("same");


  TF1* fup = new TF1("up", "[0]", h->GetXaxis()->GetXmin(), h->GetXaxis()->GetXmax());
  TF1* fdown = new TF1("down", "[0]", h->GetXaxis()->GetXmin(), h->GetXaxis()->GetXmax());
  fup->SetParameter(0, av+err);
  fdown->SetParameter(0, av-err);
  fup->SetLineColor(kAzure+1);
  fdown->SetLineColor(kAzure+1);
  fup->SetLineWidth(1);
  fdown->SetLineWidth(1);
  fup->SetLineStyle(kDashed);
  fdown->SetLineStyle(kDashed);
  fup->Draw("same");
  fdown->Draw("same");

  TLatex* text = new TLatex();
  text->SetTextFont(42);
  text->SetNDC();
  text->SetTextColor(kBlack);
  text->SetTextSize(0.04);
  //if (bSingleEPS)  text->SetTextSize(0.04);
  text->SetTextAlign(11);
  TString info = TString::Format("#chi^{2} / ndf");
  text->DrawLatex(0.3, 0.3, info.Data());
  info = TString::Format("%3.1f / %d", chi2, bins-1);
  text->DrawLatex(0.50, 0.3, info.Data());
  info = TString::Format("Durchschnitt");
  text->DrawLatex(0.3, 0.25, info.Data());
  info = TString::Format("%4.1f #pm %4.1f", av, err);
  text->DrawLatex(0.50, 0.25, info.Data());

  h->Draw("same");

}
