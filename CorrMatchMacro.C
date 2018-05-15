//CorrMatchMacro.C


void CorrMatchMacro() {
  
  const int n_files   = 10;

  const TString directory = "/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/03Feb2017_Relaunch_17Jan2018/Matching/bhad_blep/";
 
  const TString file_name[n_files] =  {"Tstar_M-700","Tstar_M-800","Tstar_M-900","Tstar_M-1000","Tstar_M-1100","Tstar_M-1200", "Tstar_M-1300", "Tstar_M-1400", "Tstar_M-1500", "Tstar_M-1600"};

  TList *list_tophad = new TList; 
  TList *list_toplep = new TList; 
  TList *list_Tstar_M_diff = new TList;
  TList *list_DeltaPhi = new TList;
  TList *list_DeltaPhi_gluon = new TList;
  TList *list_Pt_TstarTstar  = new TList;

  TH1F *h_signal_tophad[n_files];
  TH1F *h_signal_toplep[n_files];
  TH1F *h_signal_Tstar_M_diff[n_files];
  TH1F *h_signal_DeltaPhi[n_files];
  TH1F *h_signal_DeltaPhi_gluon[n_files];
  TH1F *h_signal_PtTstarTstar[n_files];

  TH1F *h_tophadVsMass = new TH1F("tophadVsMass","tophadVsMass", 10, 650, 1650);
  
  float tophad_mean[n_files];
 
  for(int i = 0; i<n_files; i++){
    TFile *signal = new TFile(directory+"uhh2.AnalysisModuleRunner.MC."+file_name[i]+".root");

    /*   
    h_signal_tophad[i]  = (TH1F*)signal->Get("corrmatch__HypHists/M_tophad");
    h_signal_toplep[i]  = (TH1F*)signal->Get("corrmatch__HypHists/M_toplep");
    h_signal_Tstar_M_diff[i] = (TH1F*)signal->Get("corrmatch__HypHists/M_TstarhadTstarlep_Diff_rel");
    h_signal_DeltaPhi[i] = (TH1F*)signal->Get("corrmatch__HypHists/DeltaPhi_TstarhadTstarlep");
    h_signal_DeltaPhi_gluon[i] = (TH1F*)signal->Get("corrmatch__HypHists/DeltaPhi_GluonhadGluonlep");
    */
    //  h_signal_PtTstarTstar[i] = (TH1F*)signal->Get("corrmatch__HypHists/Pt_TstarTstar_Diff");
    
    
    h_signal_tophad[i]  = (TH1F*)signal->Get("corrmatch_ttag__HypHists/M_tophad");
    h_signal_toplep[i]  = (TH1F*)signal->Get("corrmatch_ttag__HypHists/M_toplep");
    h_signal_Tstar_M_diff[i] = (TH1F*)signal->Get("corrmatch_ttag__HypHists/M_TstarhadTstarlep_Diff_rel");
    h_signal_DeltaPhi[i] = (TH1F*)signal->Get("corrmatch_ttag__HypHists/DeltaPhi_TstarhadTstarlep");
    h_signal_DeltaPhi_gluon[i] = (TH1F*)signal->Get("corrmatch_ttag__HypHists/DeltaPhi_GluonhadGluonlep");
    //  h_signal_PtTstarTstar[i] = (TH1F*)signal->Get("corrmatch_ttag__HypHists/Pt_TstarTstar_Diff");
    

    /*
    h_signal_tophad[i]->Fit("gaus","","",150,210);
      TF1 *myfunc = h_signal_tophad[i]->GetFunction("gaus");
    h_tophadVsMass->SetBinContent(i+1, myfunc->GetParameter(1));
    h_tophadVsMass->SetBinError(i+1,  myfunc->GetParError(1));
    */   
 
    list_tophad->Add(h_signal_tophad[i]);
    list_toplep->Add(h_signal_toplep[i]);
    list_Tstar_M_diff->Add(h_signal_Tstar_M_diff[i]);
    list_DeltaPhi->Add(h_signal_DeltaPhi[i]);
    list_DeltaPhi_gluon->Add(h_signal_DeltaPhi_gluon[i]);
    //    list_Pt_TstarTstar->Add(h_signal_PtTstarTstar[i]);
  }

  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0111);
  int bin_up = 700;
  int bin_down = 500;
  
  TCanvas* c1= new TCanvas("c1","c1",bin_up,bin_down);
  c1->Divide(2,2);
  c1->cd(1);
  TH1F *h = (TH1F*)h_signal_tophad[0]->Clone("h_tophad");
  h->Reset(); 
  h->Merge(list_tophad); 
  h->SetTitle("");
  h->GetXaxis()->SetTitle("M_{top}^{had} [GeV/c^{2}]");
  h->GetXaxis()->SetTitleSize(0.045);
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetYaxis()->SetTitle("Events");
  h->GetYaxis()->SetTitleSize(0.04);
  h->GetYaxis()->SetTitleOffset(1.1);
  h->Fit("gaus","","",50,230);
  h->Draw();
    
  c1->cd(2);
  TH1F *t = (TH1F*)h_signal_toplep[0]->Clone("h_toplep"); 
  t->Reset(); 
  t->Merge(list_toplep); 
  t->SetTitle("");
  t->GetXaxis()->SetTitle("M_{top}^{lep} [GeV/c^{2}]");
  t->GetXaxis()->SetTitleSize(0.045);
  t->GetXaxis()->SetTitleOffset(1.1);
  t->GetYaxis()->SetTitle("Events");
  t->GetYaxis()->SetTitleSize(0.04);
  t->GetYaxis()->SetTitleOffset(1.1);
  t->Fit("gaus","","",50,230);
  t->Draw();
  
  c1->cd(3);

  TH1F *p = (TH1F*)h_signal_Tstar_M_diff[0]->Clone("h_Tstar_M_diff"); 
  p->Reset(); 
  p->Merge(list_Tstar_M_diff); 
  p->SetTitle("");
  p->GetXaxis()->SetTitle("#Delta M_{T*#bar{T*}}");
  p->GetXaxis()->SetTitleSize(0.045);
  p->GetXaxis()->SetTitleOffset(1.1);
  p->GetYaxis()->SetTitle("Events");
  p->GetYaxis()->SetTitleSize(0.04);
  p->GetYaxis()->SetTitleOffset(1.1);
  p->Fit("gaus","","",-0.2,0.2);
  p->Draw();

  c1->cd(4);
  
  TH1F *k = (TH1F*)h_signal_DeltaPhi[0]->Clone("h_DeltaPhi"); 
  k->Reset(); 
  k->Merge(list_DeltaPhi); 
  k->SetTitle("");
  k->GetXaxis()->SetTitle("#Delta #Phi");
  k->GetXaxis()->SetTitleSize(0.045);
  k->GetXaxis()->SetTitleOffset(1.1);
  k->GetYaxis()->SetTitle("Events");
  k->GetYaxis()->SetTitleSize(0.04);
  k->GetYaxis()->SetTitleOffset(1.1);
  k->Fit("gaus","","",2.8,3.5);
  k->Draw();
  
  /*
  TH1F *k = (TH1F*)h_signal_DeltaPhi_gluon[0]->Clone("h_DeltaPhi"); 
  k->Reset(); 
  k->Merge(list_DeltaPhi_gluon); 
  k->SetTitle("");
  k->GetXaxis()->SetTitle("#Delta #Phi");
  k->GetXaxis()->SetTitleSize(0.045);
  k->GetXaxis()->SetTitleOffset(1.1);
  k->GetYaxis()->SetTitle("Events");
  k->GetYaxis()->SetTitleSize(0.04);
  k->GetYaxis()->SetTitleOffset(1.1);
  k->Fit("gaus","","",2.8,3.5);
  k->Draw();
  */
  
  /*
  TCanvas* c2= new TCanvas("c2","c2",bin_up,bin_down);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0111);
  h_tophadVsMass->SetTitle("");
  h_tophadVsMass->GetXaxis()->SetTitle("T* Mass");
  h_tophadVsMass->GetYaxis()->SetTitle("top_{had} mean");
  h_tophadVsMass->Draw();
  */
  /*
  TCanvas* c3= new TCanvas("c3","c3",bin_up,bin_down);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0111);
    h_signal_tophad[9]->Draw();
  */
}
