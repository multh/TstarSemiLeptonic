//CompMacro.C

//***********************************************************************
//
//Macro for Background Composition after every Selectionstep
//
//***********************************************************************


void CompMacro() {

TCanvas *c1 = new TCanvas("c1","c1",600,500);
   gStyle->SetOptStat(0);
 

 // open a file and get a histogram
 TFile *mpf_old = new TFile("/nfs/dust/cms/user/multh/JEC/2016ReReco/Residuals/Summer16_03Feb2017_V3/AK4CHS/MC_Reweighted_chsMET/RunH/plots/");
 TFile *pt_old  = new TFile("/nfs/dust/cms/user/multh/JEC/2016ReReco/Residuals/Summer16_03Feb2017_V3/AK4CHS/MC_Reweighted_chsMET/RunH/plots/");
 TFile *mpf_new = new TFile("/nfs/dust/cms/user/multh/JEC/2016ReReco/Residuals/Summer16_03Feb2017_V3/AK4CHS/MC_Reweighted_chsMET_PhiCleaning/RunH/plots/");
 TFile *pt_new  = new TFile("/nfs/dust/cms/user/multh/JEC/2016ReReco/Residuals/Summer16_03Feb2017_V3/AK4CHS/MC_Reweighted_chsMET_PhiCleaning/RunH/plots/");
 
TH1F *h_pt_extrapolation_mpf_old    = (TH1F*)mpf_old->Get("pTextrapolation_MPF_pythia8_pT_00_0261");
TH1F *h_pt_extrapolation_mpf_new    = (TH1F*)mpf_new->Get("pTextrapolation_MPF_pythia8_pT_00_0261");

TH1F *h_pt_extrapolation_mpf_comp (TH1F*)h_pt_extrapolation_mpf_old->Clone("h");

 h_pt_extrapolation_mpf_comp->Draw();
 h_pt_extrapolation_mpf_new->Draw("same");

}
