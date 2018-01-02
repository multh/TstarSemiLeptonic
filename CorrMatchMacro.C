//CorrMatchMacro.C


void CorrMatchMacro() {
 // open a file and get a histogram
 TFile *s1 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/CorrectMatch/uhh2.AnalysisModuleRunner.MC.Tstar_M-700.root");
 TFile *s2 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/CorrectMatch/uhh2.AnalysisModuleRunner.MC.Tstar_M-800.root");
 TFile *s3 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/CorrectMatch/uhh2.AnalysisModuleRunner.MC.Tstar_M-900.root");
 TFile *s4 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/CorrectMatch/uhh2.AnalysisModuleRunner.MC.Tstar_M-1000.root");
 TFile *s5 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/CorrectMatch/uhh2.AnalysisModuleRunner.MC.Tstar_M-1100.root");
 TFile *s6 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/CorrectMatch/uhh2.AnalysisModuleRunner.MC.Tstar_M-1200.root");
 TFile *s7 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/CorrectMatch/uhh2.AnalysisModuleRunner.MC.Tstar_M-1300.root");
 TFile *s8 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/CorrectMatch/uhh2.AnalysisModuleRunner.MC.Tstar_M-1400.root");
 TFile *s9 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/CorrectMatch/uhh2.AnalysisModuleRunner.MC.Tstar_M-1500.root");
 TFile *s10 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/CorrectMatch/uhh2.AnalysisModuleRunner.MC.Tstar_M-1600.root");

 
 TH1F *h1    = (TH1F*)s1->Get("corrmatch__HypHists/M_tophad");
 TH1F *h2    = (TH1F*)s2->Get("corrmatch__HypHists/M_tophad");
 TH1F *h3    = (TH1F*)s3->Get("corrmatch__HypHists/M_tophad");
 TH1F *h4    = (TH1F*)s4->Get("corrmatch__HypHists/M_tophad");
 TH1F *h5    = (TH1F*)s5->Get("corrmatch__HypHists/M_tophad");
 TH1F *h6    = (TH1F*)s6->Get("corrmatch__HypHists/M_tophad");
 TH1F *h7    = (TH1F*)s7->Get("corrmatch__HypHists/M_tophad");
 TH1F *h8    = (TH1F*)s8->Get("corrmatch__HypHists/M_tophad");
 TH1F *h9    = (TH1F*)s9->Get("corrmatch__HypHists/M_tophad");
 TH1F *h10   = (TH1F*)s10->Get("corrmatch__HypHists/M_tophad");

 TH1F *t1    = (TH1F*)s1->Get("corrmatch__HypHists/M_toplep");
 TH1F *t2    = (TH1F*)s2->Get("corrmatch__HypHists/M_toplep");
 TH1F *t3    = (TH1F*)s3->Get("corrmatch__HypHists/M_toplep");
 TH1F *t4    = (TH1F*)s4->Get("corrmatch__HypHists/M_toplep");
 TH1F *t5    = (TH1F*)s5->Get("corrmatch__HypHists/M_toplep");
 TH1F *t6    = (TH1F*)s6->Get("corrmatch__HypHists/M_toplep");
 TH1F *t7    = (TH1F*)s7->Get("corrmatch__HypHists/M_toplep");
 TH1F *t8    = (TH1F*)s8->Get("corrmatch__HypHists/M_toplep");
 TH1F *t9    = (TH1F*)s9->Get("corrmatch__HypHists/M_toplep");
 TH1F *t10   = (TH1F*)s10->Get("corrmatch__HypHists/M_toplep");


 TH1F *p1    = (TH1F*)s1->Get("corrmatch__HypHists/DeltaPhi_TstarhadTstarlep");
 TH1F *p2    = (TH1F*)s2->Get("corrmatch__HypHists/DeltaPhi_TstarhadTstarlep");
 TH1F *p3    = (TH1F*)s3->Get("corrmatch__HypHists/DeltaPhi_TstarhadTstarlep");
 TH1F *p4    = (TH1F*)s4->Get("corrmatch__HypHists/DeltaPhi_TstarhadTstarlep");
 TH1F *p5    = (TH1F*)s5->Get("corrmatch__HypHists/DeltaPhi_TstarhadTstarlep");
 TH1F *p6    = (TH1F*)s6->Get("corrmatch__HypHists/DeltaPhi_TstarhadTstarlep");
 TH1F *p7    = (TH1F*)s7->Get("corrmatch__HypHists/DeltaPhi_TstarhadTstarlep");
 TH1F *p8    = (TH1F*)s8->Get("corrmatch__HypHists/DeltaPhi_TstarhadTstarlep");
 TH1F *p9    = (TH1F*)s9->Get("corrmatch__HypHists/DeltaPhi_TstarhadTstarlep");
 TH1F *p10   = (TH1F*)s10->Get("corrmatch__HypHists/DeltaPhi_TstarhadTstarlep");

 TH1F *d1    = (TH1F*)s1->Get("corrmatch__HypHists/M_TstarhadTstarlep_Diff_rel");
 TH1F *d2    = (TH1F*)s2->Get("corrmatch__HypHists/M_TstarhadTstarlep_Diff_rel");
 TH1F *d3    = (TH1F*)s3->Get("corrmatch__HypHists/M_TstarhadTstarlep_Diff_rel");
 TH1F *d4    = (TH1F*)s4->Get("corrmatch__HypHists/M_TstarhadTstarlep_Diff_rel");
 TH1F *d5    = (TH1F*)s5->Get("corrmatch__HypHists/M_TstarhadTstarlep_Diff_rel");
 TH1F *d6    = (TH1F*)s6->Get("corrmatch__HypHists/M_TstarhadTstarlep_Diff_rel");
 TH1F *d7    = (TH1F*)s7->Get("corrmatch__HypHists/M_TstarhadTstarlep_Diff_rel");
 TH1F *d8    = (TH1F*)s8->Get("corrmatch__HypHists/M_TstarhadTstarlep_Diff_rel");
 TH1F *d9    = (TH1F*)s9->Get("corrmatch__HypHists/M_TstarhadTstarlep_Diff_rel");
 TH1F *d10   = (TH1F*)s10->Get("corrmatch__HypHists/M_TstarhadTstarlep_Diff_rel");



TList *list1 = new TList; 
list1->Add(h1); 
list1->Add(h2);
list1->Add(h3);
list1->Add(h4);
list1->Add(h5);
list1->Add(h6);
list1->Add(h7);
list1->Add(h8);
list1->Add(h9);
list1->Add(h10);

TList *list2 = new TList; 
list2->Add(p1); 
list2->Add(p2);
list2->Add(p3);
list2->Add(p4);
list2->Add(p5);
list2->Add(p6);
list2->Add(p7);
list2->Add(p8);
list2->Add(p9);
list2->Add(p10);

TList *list3 = new TList; 
list3->Add(t1); 
list3->Add(t2);
list3->Add(t3);
list3->Add(t4);
list3->Add(t5);
list3->Add(t6);
list3->Add(t7);
list3->Add(t8);
list3->Add(t9);
list3->Add(t10);

TList *list4 = new TList; 
list4->Add(d1); 
list4->Add(d2);
list4->Add(d3);
list4->Add(d4);
list4->Add(d5);
list4->Add(d6);
list4->Add(d7);
list4->Add(d8);
list4->Add(d9);
list4->Add(d10);


 gStyle->SetOptStat(0);
 gStyle->SetOptFit(0111);
   int bin_up = 630;
  int bin_down = 510;

TCanvas* c1= new TCanvas("c1","c1",bin_up,bin_down);
 c1->Divide(2,2);
 c1->cd(1);
TH1F *h = (TH1F*)h1->Clone("h"); 
h->Reset(); 
h->Merge(list1); 
 h->SetTitle("");
 h->GetXaxis()->SetTitle("M_{top}^{had} [GeV/c^{2}]");
 h->GetXaxis()->SetTitleSize(0.045);
 h->GetXaxis()->SetTitleOffset(1.1);
 h->GetYaxis()->SetTitle("Anzahl MC-Ereignisse");
 h->GetYaxis()->SetTitleSize(0.04);
 h->GetYaxis()->SetTitleOffset(1.1);
 h->Fit("gaus");
h->Draw();

 c1->cd(2);
TH1F *t = (TH1F*)t1->Clone("t"); 
t->Reset(); 
t->Merge(list3); 
 t->SetTitle("");
 t->GetXaxis()->SetTitle("M_{top}^{lep} [GeV/c^{2}]");
 t->GetXaxis()->SetTitleSize(0.045);
 t->GetXaxis()->SetTitleOffset(1.1);
 t->GetYaxis()->SetTitle("Anzahl MC-Ereignisse");
 t->GetYaxis()->SetTitleSize(0.04);
 t->GetYaxis()->SetTitleOffset(1.1);
 t->Fit("gaus","","",50,230);
t->Draw();


 c1->cd(3);
TH1F *p = (TH1F*)p1->Clone("p"); 
p->Reset(); 
p->Merge(list2); 
 p->SetTitle("");
 p->GetXaxis()->SetTitle("#Delta #Phi");
 p->GetXaxis()->SetTitleSize(0.045);
 p->GetXaxis()->SetTitleOffset(1.1);
 p->GetYaxis()->SetTitle("Anzahl MC-Ereignisse");
 p->GetYaxis()->SetTitleSize(0.04);
 p->GetYaxis()->SetTitleOffset(1.1);
 p->Fit("gaus");
p->Draw();

 c1->cd(4);
TH1F *d = (TH1F*)d1->Clone("d"); 
d->Reset(); 
d->Merge(list4); 
 d->SetTitle("");
 d->GetXaxis()->SetTitle("#Delta M_{T*#bar{T*}}");
 d->GetXaxis()->SetTitleSize(0.045);
 d->GetXaxis()->SetTitleOffset(1.1);
 d->GetYaxis()->SetTitle("Anzahl MC-Ereignisse");
 d->GetYaxis()->SetTitleSize(0.04);
 d->GetYaxis()->SetTitleOffset(1.1);
 d->Fit("gaus","","",-0.19,0.21);
d->Draw();


}
