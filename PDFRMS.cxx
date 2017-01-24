{
  TFile* file_sig_DY = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Nominal/uhh2.AnalysisModuleRunner.MC.ZJets.root","READ");
  TFile* file_sig_ST = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Nominal/uhh2.AnalysisModuleRunner.MC.SingleTop.root","READ");
  TFile* file_sig_TTbar = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Nominal/uhh2.AnalysisModuleRunner.MC.TTbar.root","READ");
  TFile* file_sig_WJets = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Nominal/uhh2.AnalysisModuleRunner.MC.WJets.root","READ");

  std::vector<TH1D*> hists_ht_DY, hists_ht_ST, hists_ht_TTbar, hists_ht_WJets;
  
  TH1D* ht_nominal_DY = (TH1D*)file_sig_DY->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
  TH1D* ht_nominal_ST = (TH1D*)file_sig_ST->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
  TH1D* ht_nominal_TTbar = (TH1D*)file_sig_TTbar->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
  TH1D* ht_nominal_WJets = (TH1D*)file_sig_WJets->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
  
  TCanvas* c0 = new TCanvas("c0","initial",1);


  //DY
  int n=0;
  file_sig_DY->cd("PDF_variations");
  TDirectory* dir = gDirectory;
  TIter iter(dir->GetListOfKeys());
  TKey *key;
  while ((key = (TKey*)iter())) {
    //if(n%4!=0) {n++;continue;}
    TClass *cl = gROOT->GetClass(key->GetClassName());
    if (!cl->InheritsFrom("TH1")) continue;
    TH1D *h = (TH1D*)key->ReadObj();
    hists_ht_DY.push_back(h);
    n++;
    //cout << "naechstes histogramm " <<  n <<  endl;
  }

  //SingleTop
  n=0;
  file_sig_ST->cd("PDF_variations");
  dir = gDirectory;
  iter = dir->GetListOfKeys();
  while ((key = (TKey*)iter())) {
    // if(n%4!=0) { n++;continue;}
    TClass *cl = gROOT->GetClass(key->GetClassName());
    if (!cl->InheritsFrom("TH1")) continue;
    TH1D *h = (TH1D*)key->ReadObj();
    hists_ht_ST.push_back(h);
    n++;
    //cout << "naechstes histogramm " <<  n <<  endl;
  }

  //TTbar
  n=0;
  file_sig_TTbar->cd("PDF_variations");
  dir = gDirectory;
  iter = dir->GetListOfKeys();
  while ((key = (TKey*)iter())) {
    // if(n%4!=0) {n++;continue;}
    TClass *cl = gROOT->GetClass(key->GetClassName());
    if (!cl->InheritsFrom("TH1")) continue;
    TH1D *h = (TH1D*)key->ReadObj();
    hists_ht_TTbar.push_back(h);
    if(n==0)h->Draw();
    else h->Draw("SAME");
    n++;
    //cout << "naechstes histogramm " <<  n <<  endl;
  }

  //WJets
  n=0;
  file_sig_WJets->cd("PDF_variations");
  dir = gDirectory;
  iter = dir->GetListOfKeys();
  while ((key = (TKey*)iter())) {
    // if(n%4!=0) {n++;continue;}
    TClass *cl = gROOT->GetClass(key->GetClassName());
    if (!cl->InheritsFrom("TH1")) continue;
    TH1D *h = (TH1D*)key->ReadObj();
    hists_ht_WJets.push_back(h);
    n++;
    //cout << "naechstes histogramm " <<  n <<  endl;
  }


  //set up up and down histograms
  cout<<"N Bins: "<<hists_ht_DY.at(0)->GetNbinsX()<<endl;
  
  if(hists_ht_DY.at(0)->GetNbinsX()+1 != 31) throw runtime_error("number of bin-low edges is not 31, please adjust.");
  double low_edges[31];
  for(int i=1; i<hists_ht_DY.at(0)->GetNbinsX()+2; i++){
    low_edges[i-1] = hists_ht_DY.at(0)->GetBinLowEdge(i);
  }
  if(hists_ht_DY.at(0)->GetNbinsX() != 30) throw runtime_error("number of bins is not 10, please adjust.");
  
  TH1D* h_DY_up = new TH1D     ("Mass_Tstar","M_{T^*} [GeV], DY, PDF up",30,low_edges);
  TH1D* h_DY_down = new TH1D   ("Mass_Tstar","M_{T^*} [GeV], DY, PDF down",30,low_edges);
  TH1D* h_ST_up = new TH1D     ("Mass_Tstar","M_{T^*} [GeV], ST, PDF up",30,low_edges);
  TH1D* h_ST_down = new TH1D   ("Mass_Tstar","M_{T^*} [GeV], ST, PDF down",30,low_edges);
  TH1D* h_TTbar_up = new TH1D  ("Mass_Tstar","M_{T^*} [GeV], TTbar, PDF up",30,low_edges);
  TH1D* h_TTbar_down = new TH1D("Mass_Tstar","M_{T^*} [GeV], TTbar, PDF down",30,low_edges);
  TH1D* h_WJets_up = new TH1D  ("Mass_Tstar","M_{T^*} [GeV], WJets, PDF up",30,low_edges);
  TH1D* h_WJets_down = new TH1D("Mass_Tstar","M_{T^*} [GeV], WJets, PDF down",30,low_edges);
  
 

  //only for the sideband fine-binned histogram
  /*
  TH1D* h_DY_up = new TH1D     ("H_T_from350_rebin","H_{T} [GeV], DY, PDF up",80,0,7000);
  TH1D* h_DY_down = new TH1D   ("H_T_from350_rebin","H_{T} [GeV], DY, PDF down",80,0,7000);
  TH1D* h_ST_up = new TH1D     ("H_T_from350_rebin","H_{T} [GeV], ST, PDF up",80,0,7000);
  TH1D* h_ST_down = new TH1D   ("H_T_from350_rebin","H_{T} [GeV], ST, PDF down",80,0,7000);
  TH1D* h_TTbar_up = new TH1D  ("H_T_from350_rebin","H_{T} [GeV], TTbar, PDF up",80,0,7000);
  TH1D* h_TTbar_down = new TH1D("H_T_from350_rebin","H_{T} [GeV], TTbar, PDF down",80,0,7000);
  TH1D* h_WJets_up = new TH1D  ("H_T_from350_rebin","H_{T} [GeV], WJets, PDF up",80,0,7000);
  TH1D* h_WJets_down = new TH1D("H_T_from350_rebin","H_{T} [GeV], WJets, PDF down",80,0,7000);
  */



  //calculate RMS and fill up and down histograms
  std::vector<double> v_rms_DY, v_rms_ST, v_rms_TTbar, v_rms_WJets;
  for(unsigned int j=1; j<hists_ht_DY.at(0)->GetNbinsX()+1; j++){
    double nominal_DY = ht_nominal_DY->GetBinContent(j);
    //double nominal_ST = ht_nominal_ST->GetBinContent(j); nicht alle ST samples haben PDF weights --> bincontent des haddeten viel groesser als 102 variationshistogramme
    double nominal_ST = 0;
    for(unsigned int i=0; i<hists_ht_DY.size(); i++){
      nominal_ST += hists_ht_ST.at(i)->GetBinContent(j);
    }
    nominal_ST /= hists_ht_DY.size();
    double nominal_all_ST = ht_nominal_ST->GetBinContent(j);
    double nominal_TTbar = ht_nominal_TTbar->GetBinContent(j);
    double nominal_WJets = ht_nominal_WJets->GetBinContent(j);
    double rms_DY=0, rms_ST=0, rms_TTbar=0, rms_WJets=0;
    for(unsigned int i=0; i<hists_ht_DY.size(); i++){
      rms_DY += pow((hists_ht_DY.at(i)->GetBinContent(j)-nominal_DY),2);
      rms_ST += pow((hists_ht_ST.at(i)->GetBinContent(j)-nominal_ST),2);
      rms_TTbar += pow((hists_ht_TTbar.at(i)->GetBinContent(j)-nominal_TTbar),2);
      rms_WJets += pow((hists_ht_WJets.at(i)->GetBinContent(j)-nominal_WJets),2);
    }
    rms_DY /= (hists_ht_DY.size()-1);
    rms_ST /= (hists_ht_ST.size()-1);
    rms_TTbar /= (hists_ht_TTbar.size()-1);
    rms_WJets /= (hists_ht_WJets.size()-1);

    v_rms_DY.push_back(sqrt(rms_DY));
    v_rms_ST.push_back(sqrt(rms_ST));
    v_rms_TTbar.push_back(sqrt(rms_TTbar));
    v_rms_WJets.push_back(sqrt(rms_WJets));

    h_DY_up->SetBinContent(j,nominal_DY + v_rms_DY.at(j-1));
    h_DY_up->SetBinError(j,ht_nominal_DY->GetBinError(j));
    h_DY_down->SetBinContent(j,nominal_DY - v_rms_DY.at(j-1));
    h_DY_down->SetBinError(j,ht_nominal_DY->GetBinError(j));

    h_ST_up->SetBinContent(j,nominal_all_ST + v_rms_ST.at(j-1));
    h_ST_up->SetBinError(j,ht_nominal_ST->GetBinError(j));
    h_ST_down->SetBinContent(j,nominal_all_ST - v_rms_ST.at(j-1));
    h_ST_down->SetBinError(j,ht_nominal_ST->GetBinError(j));

    h_TTbar_up->SetBinContent(j,nominal_TTbar + v_rms_TTbar.at(j-1));
    h_TTbar_up->SetBinError(j,ht_nominal_TTbar->GetBinError(j));
    h_TTbar_down->SetBinContent(j,nominal_TTbar - v_rms_TTbar.at(j-1));
    h_TTbar_down->SetBinError(j,ht_nominal_TTbar->GetBinError(j));

    h_WJets_up->SetBinContent(j,nominal_WJets + v_rms_WJets.at(j-1));
    h_WJets_up->SetBinError(j,ht_nominal_WJets->GetBinError(j));
    h_WJets_down->SetBinContent(j,nominal_WJets - v_rms_WJets.at(j-1));
    h_WJets_down->SetBinError(j,ht_nominal_WJets->GetBinError(j));

    cout << "Content DY in bin " << j << ": " <<  nominal_DY << " +- " << v_rms_DY.at(j-1) << endl;
    cout << "Content ST in bin " << j << ": " <<  nominal_ST << " +- " << v_rms_ST.at(j-1) << endl;
    cout << "Content TTbar in bin " << j << ": " <<  nominal_TTbar << " +- " << v_rms_TTbar.at(j-1) << endl;
    cout << "Content WJets in bin " << j << ": " <<  nominal_WJets << " +- " << v_rms_WJets.at(j-1) << endl << endl;
  }

  //TCanvas* ctest = new TCanvas("ctest", "comparison", 1);
  ht_nominal_TTbar->SetLineColor(kYellow);
 
  h_TTbar_up->SetLineColor(2);
  h_TTbar_down->SetLineColor(3);
  h_TTbar_up->Draw("SAME");
  h_TTbar_down->Draw("SAME");
 ht_nominal_TTbar->Draw("SAME");
  
  TFile* f_out_TTbar_up = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Sys_PDF_Up/uhh2.AnalysisModuleRunner.MC.TTbar.root","RECREATE");
  h_TTbar_up->Write();
  TFile* f_out_TTbar_dn = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Sys_PDF_Down/uhh2.AnalysisModuleRunner.MC.TTbar.root","RECREATE");
  h_TTbar_down->Write();
  TFile* f_out_DY_up = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Sys_PDF_Up/uhh2.AnalysisModuleRunner.MC.ZJets.root","RECREATE");
  h_DY_up->Write();
  TFile* f_out_DY_dn = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Sys_PDF_Down/uhh2.AnalysisModuleRunner.MC.ZJets.root","RECREATE");
  h_DY_down->Write();
  TFile* f_out_ST_up = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Sys_PDF_Up/uhh2.AnalysisModuleRunner.MC.SingleTop.root","RECREATE");
  h_ST_up->Write();
  TFile* f_out_ST_dn = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Sys_PDF_Down/uhh2.AnalysisModuleRunner.MC.SingleTop.root","RECREATE");
  h_ST_down->Write();
  TFile* f_out_WJets_up = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Sys_PDF_Up/uhh2.AnalysisModuleRunner.MC.WJets.root","RECREATE");
  h_WJets_up->Write();
  TFile* f_out_WJets_dn = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Sys_PDF_Down/uhh2.AnalysisModuleRunner.MC.WJets.root","RECREATE");
  h_WJets_down->Write();
  
  /*
  
  TFile* f_out_TTbar_up = new TFile("/nfs/dust/cms/user/reimersa/LQToTopMu/Run2_74X_Thesis/Optimization/2318fb_MuonAndBTagSF_Sys_PDF_Up/ForTTbarSideband.root","RECREATE");
  h_TTbar_up->Write();
  TFile* f_out_TTbar_dn = new TFile("/nfs/dust/cms/user/reimersa/LQToTopMu/Run2_74X_Thesis/Optimization/2318fb_MuonAndBTagSF_Sys_PDF_Down/ForTTbarSideband.root","RECREATE");
  h_TTbar_down->Write();
  */

  cout << "done." << endl;
}
