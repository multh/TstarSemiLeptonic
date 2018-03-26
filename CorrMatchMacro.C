//CorrMatchMacro.C


void CorrMatchMacro() {
  
  const int n_files   = 10;

  const TString directory = "/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/03Feb2017_Relaunch_17Jan2018/Matching/Changed_Reco/";
 
  const TString file_name[n_files] =  {"Tstar_M-700","Tstar_M-800","Tstar_M-900","Tstar_M-1000","Tstar_M-1100","Tstar_M-1200", "Tstar_M-1300", "Tstar_M-1400", "Tstar_M-1500", "Tstar_M-1600"};

  TList *list_tophad = new TList; 
  TList *list_toplep = new TList; 
  TList *list_Tstar_M_diff = new TList;
  TList *list_DeltaPhi = new TList;
  TList *list_DeltaPt_lep = new TList;
  TList *list_DeltaPhi_Gluon = new TList;
  TList *list_DeltaEta_Gluon = new TList;
  TList *list_DeltaR_Gluon = new TList;

  TH1F *h_signal_tophad[n_files];
  TH1F *h_signal_toplep[n_files];
  TH1F *h_signal_Tstar_M_diff[n_files];
  TH1F *h_signal_DeltaPhi[n_files];
  TH1F *h_signal_DeltaPt_lep[n_files];
  TH1F *h_signal_DeltaR_Gluon[n_files];
  TH1F *h_signal_DeltaPhi_Gluon[n_files];
  TH1F *h_signal_DeltaEta_Gluon[n_files];
 
  for(int i = 0; i<n_files; i++){
    TFile *signal = new TFile(directory+"uhh2.AnalysisModuleRunner.MC."+file_name[i]+".root");

     
    h_signal_tophad[i]  = (TH1F*)signal->Get("corrmatch__HypHists/M_tophad");
    h_signal_toplep[i]  = (TH1F*)signal->Get("corrmatch__HypHists/M_toplep");
    h_signal_Tstar_M_diff[i] = (TH1F*)signal->Get("corrmatch__HypHists/M_TstarhadTstarlep_Diff_rel");
    h_signal_DeltaPhi[i] = (TH1F*)signal->Get("corrmatch__HypHists/DeltaPhi_TstarhadTstarlep");
    h_signal_DeltaPt_lep[i] = (TH1F*)signal->Get("corrmatch__HypHists/Pt_Diff_gluonlep_toplep");
    //   h_signal_DeltaPt_had[i] = (TH1F*)signal->Get("corrmatch__HypHists/Pt_Diff_gluonhad_tophad");
    h_signal_DeltaPhi_Gluon[i] = (TH1F*)signal->Get("corrmatch__HypHists/DeltaPhi_GluonhadGluonlep_gen");
    h_signal_DeltaEta_Gluon[i] = (TH1F*)signal->Get("corrmatch__HypHists/DeltaEta_GluonhadGluonlep");
    h_signal_DeltaR_Gluon[i] = (TH1F*)signal->Get("corrmatch__HypHists/DeltaR_GluonGluon");
    /*
    h_signal_tophad[i]  = (TH1F*)signal->Get("corrmatch_ttag__HypHists/M_tophad");
    h_signal_toplep[i]  = (TH1F*)signal->Get("corrmatch_ttag__HypHists/M_toplep");
    h_signal_Tstar_M_diff[i] = (TH1F*)signal->Get("corrmatch_ttag__HypHists/M_TstarhadTstarlep_Diff_rel");
    h_signal_DeltaPhi[i] = (TH1F*)signal->Get("corrmatch_ttag__HypHists/DeltaPhi_TstarhadTstarlep");
    h_signal_DeltaPt_lep[i] = (TH1F*)signal->Get("corrmatch_ttag__HypHists/Pt_Diff_gluonlep_toplep");
    h_signal_DeltaPhi_Gluon[i] = (TH1F*)signal->Get("corrmatch_ttag__HypHists/DeltaPhi_GluonhadGluonlep");
    h_signal_DeltaEta_Gluon[i] = (TH1F*)signal->Get("corrmatch_ttag__HypHists/DeltaEta_GluonhadGluonlep");
    h_signal_DeltaR_Gluon[i] = (TH1F*)signal->Get("corrmatch_ttag__HypHists/DeltaR_GluonGluon");
    */

    list_tophad->Add(h_signal_tophad[i]);
    list_toplep->Add(h_signal_toplep[i]);
    list_Tstar_M_diff->Add(h_signal_Tstar_M_diff[i]);
    list_DeltaPhi->Add(h_signal_DeltaPhi[i]);
    list_DeltaPt_lep->Add(h_signal_DeltaPt_lep[i]);
    list_DeltaPhi_Gluon->Add(h_signal_DeltaPhi_Gluon[i]);
    list_DeltaEta_Gluon->Add(h_signal_DeltaEta_Gluon[i]);
    list_DeltaR_Gluon->Add(h_signal_DeltaR_Gluon[i]);
    
  }

  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0111);
  int bin_up = 700;
  int bin_down = 500;
  
  TCanvas* c1= new TCanvas("c1","c1",bin_up,bin_down);
  c1->Divide(2,3);
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
  h->Fit("gaus");
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
  
  
  c1->cd(5);
  /*
  TH1F *d = (TH1F*)h_signal_DeltaEta_Gluon[0]->Clone("h_DeltaEta_Gluon"); 
  d->Reset(); 
  d->Merge(list_DeltaEta_Gluon); 
  d->SetTitle("");
  d->GetXaxis()->SetTitle("#Delta #Phi gluons");
  d->GetXaxis()->SetTitleSize(0.045);
  d->GetXaxis()->SetTitleOffset(1.1);
  d->GetYaxis()->SetTitle("Events");
  d->GetYaxis()->SetTitleSize(0.04);
  d->GetYaxis()->SetTitleOffset(1.1);
  // d->Fit("gaus","","",2.8,3.5);
  d->Draw();
*/

  
  TH1F *d = (TH1F*)h_signal_DeltaPhi_Gluon[0]->Clone("h_DeltaPhi_Gluon"); 
  d->Reset(); 
  d->Merge(list_DeltaPhi_Gluon); 
  d->SetTitle("");
  d->GetXaxis()->SetTitle("#Delta #Phi gluons");
  d->GetXaxis()->SetTitleSize(0.045);
  d->GetXaxis()->SetTitleOffset(1.1);
  d->GetYaxis()->SetTitle("Events");
  d->GetYaxis()->SetTitleSize(0.04);
  d->GetYaxis()->SetTitleOffset(1.1);
  // d->Fit("gaus","","",2.8,3.5);
  d->Draw();
  

  c1->cd(6);

  TH1F *e = (TH1F*)h_signal_DeltaR_Gluon[0]->Clone("h_DeltaR_Gluon"); 
  e->Reset(); 
  e->Merge(list_DeltaR_Gluon); 
  e->SetTitle("");
  e->GetXaxis()->SetTitle("#Delta R gluons");
  e->GetXaxis()->SetTitleSize(0.045);
  e->GetXaxis()->SetTitleOffset(1.1);
  e->GetYaxis()->SetTitle("Events");
  e->GetYaxis()->SetTitleSize(0.04);
  e->GetYaxis()->SetTitleOffset(1.1);
  // e->Fit("gaus","","",2.8,3.5);
  e->Draw();
  

}
