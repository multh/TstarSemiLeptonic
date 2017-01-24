//CorrMatchMacro.C


void CorrMatchMacro() {
 // open a file and get a histogram
 TFile *s1 = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/uhh2.AnalysisModuleRunner.MC.Tstar_M700.root");
 TFile *s2 = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/uhh2.AnalysisModuleRunner.MC.Tstar_M800.root");
 TFile *s3 = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/uhh2.AnalysisModuleRunner.MC.Tstar_M900.root");
 TFile *s4 = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/uhh2.AnalysisModuleRunner.MC.Tstar_M1000.root");
 TFile *s5 = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/uhh2.AnalysisModuleRunner.MC.Tstar_M1100.root");
 TFile *s6 = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/uhh2.AnalysisModuleRunner.MC.Tstar_M1200.root");
 TFile *s7 = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/uhh2.AnalysisModuleRunner.MC.Tstar_M1300.root");
 TFile *s8 = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/uhh2.AnalysisModuleRunner.MC.Tstar_M1400.root");
 TFile *s9 = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/uhh2.AnalysisModuleRunner.MC.Tstar_M1500.root");
 TFile *s10 = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/uhh2.AnalysisModuleRunner.MC.Tstar_M1600.root");


 TH1F *h1    = (TH1F*)s1->Get("corrmatch__HypHists/M_TstarhadTstarlep_Diff_rel");
 TH1F *h2    = (TH1F*)s2->Get("corrmatch__HypHists/M_TstarhadTstarlep_Diff_rel");
 TH1F *h3    = (TH1F*)s3->Get("corrmatch__HypHists/M_TstarhadTstarlep_Diff_rel");
 TH1F *h4    = (TH1F*)s4->Get("corrmatch__HypHists/M_TstarhadTstarlep_Diff_rel");
 TH1F *h5    = (TH1F*)s5->Get("corrmatch__HypHists/M_TstarhadTstarlep_Diff_rel");
 TH1F *h6    = (TH1F*)s6->Get("corrmatch__HypHists/M_TstarhadTstarlep_Diff_rel");
 TH1F *h7    = (TH1F*)s7->Get("corrmatch__HypHists/M_TstarhadTstarlep_Diff_rel");
 TH1F *h8    = (TH1F*)s8->Get("corrmatch__HypHists/M_TstarhadTstarlep_Diff_rel");
 TH1F *h9    = (TH1F*)s9->Get("corrmatch__HypHists/M_TstarhadTstarlep_Diff_rel");
 TH1F *h10    = (TH1F*)s10->Get("corrmatch__HypHists/M_TstarhadTstarlep_Diff_rel");

 TH1F* histos[10]={h1,h2,h3,h4,h5,h6,h7,h8,h9,h10};
for (int i=0;i<10;++i){
         histos[i]->Sumw2(); // *Very* Important
        }

TList *list = new TList; 
list->Add(h1); 
list->Add(h2);
 list->Add(h3);
list->Add(h4);
list->Add(h5);
list->Add(h6);
list->Add(h7);
list->Add(h8);
list->Add(h9);
list->Add(h10);

TH1F *h = (TH1F*)h1->Clone("h"); 
h->Reset(); 
h->Merge(list); 
 h->Draw();


}
