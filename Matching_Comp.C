//Matching_Comp.C

//***********************************************************************
//
//Macro for Background Composition after every Selectionstep
//
//***********************************************************************

using namespace std;

void Matching_Comp() {

  const int n_Signal = 1;
  const int n_Hist = 5;

  const TString File_Name[n_Signal] = {"Tstar_M-900"};

  const EColor Color[n_Hist] = { kRed, kGreen, kBlue, kOrange,  kViolet};

  const TString Hist_Name[n_Hist] = {"M_TstarLep_bMatch_gluonSwitch", "M_TstarLep_bhad_gluonlepSwitch", "M_TstarLep_bhad_gluonhadSwitch", "M_TstarLep_Match_All", "M_TstarLep_Match_Non"};

  TH1F *h_M_Tstarlep[n_Signal][n_Hist];

  for(int i = 0; i<n_Signal; i++){
    TFile *signal = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/03Feb2017_Relaunch_17Jan2018/Muons/Kinematic_Study/uhh2.AnalysisModuleRunner.MC."+File_Name[i]+".root");
    
    THStack *hs = new THStack("hs","Tstar Mass Lep");

    for(int k = 0; k<n_Hist; k++){
      h_M_Tstarlep[i][k] = (TH1F*)signal->Get("chi2min__HypHists/"+Hist_Name[k]);
      h_M_Tstarlep[i][k] -> SetLineColor(Color[k]);
      h_M_Tstarlep[i][k] ->SetLineWidth(2);
      

      hs->Add(h_M_Tstarlep[i][k]);

    }    

    TCanvas *b1 = new TCanvas("b1","b1",800,600);
    gStyle->SetOptStat(0);
    hs->Draw("hist");
  }
}
