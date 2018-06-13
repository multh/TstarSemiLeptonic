//Matching_Comp.C

//***********************************************************************
//
//Macro for Background Composition after every Selectionstep
//
//***********************************************************************

using namespace std;

void Matching_Comp() {

  const int n_Signal = 1;
  const int n_Hist = 33;
  const int n_Category=5;

  const TString File_Name[n_Signal] = {"Tstar_M-1300"};

  int Color[n_Category] = { 628, 412,415,858, 868};//858,
  //EColor Color[n_Hist] = { kRed, kGreen, kBlue, 434,kCyan};

  const TString Hist_Name[n_Hist] = {"Discriminator_sum","Number of subjets gluon had","Number of subjets gluon lep","DeltaR_GluonGluon","DeltaR_TopTop","DeltaR_TopHad_BLep","Pt_Ratio_gluonhad_subjets","DeltaR_gluonhad_subjets","DeltaR_gluonlep_subjets","CSV_gluonLep","CSV_bLep","DeltaR_GluonTop_lep","DeltaR_GluonTop_had","DeltaR_GluonHad_TopLep","DeltaR_GluonLep_TopHad","M_TstarhadTstarlep_Diff_rel","Pt_Ratio_blep_toplep","Pt_Diff_gluonlep_toplep","Pt_Diff_gluonlep_gluonhad","Pt_Diff_gluon_top_lep","Pt_Diff_gluon_top_had","M_Tstarlep_rec","M_Tstarhad_rec","M_toplep","M_tophad","M_Tstar_comb","M_Tstar_ratio","Pt_Tstar_ratio","M_gluon_ratio","M_gluonhad","M_gluonlep","Pt_gluonhad","Pt_gluonlep"};

  const TString Hist_Label[n_Hist] = {"#Chi^{2}","Number of subjets gluon had","Number of subjets gluon lep","#Delta R Gluon Gluon","#Delta R Top Top","#Delta R Top_{Had} B_{Lep}","Pt Ratio gluonhad subjets","#Delta R gluon had subjets","#Delta R gluon had subjets","CSV_gluonLep","CSV bLep","#Delta R gluon top lep","#Delta R gluon top had","#Delta R gluon_{had} top_{lep}","#Delta R gluon_{lep} top_{had}","M_TstarhadTstarlep_Diff_rel","Pt Ratio b_{lep} top_{lep}","Pt Diff gluonlep toplep","Pt Diff gluonlep gluonhad","Pt Diff gluon top lep","Pt Diff gluon top had","T*  Mass, lep","T*  Mass, had","M top lep","M top had","M T* comb","M_Tstar_ratio","Pt_Tstar_ratio","M_gluon_ratio","M_gluonhad","M_gluonlep","Pt gluonhad","Pt gluonlep"};

  const TString Category_Name[n_Category] = {"chi2_gluon_nomatch__HypHists","chi2_gluon_switch__HypHists","chi2_gluonlep_semimatch__HypHists", "chi2_gluonhad_semimatch__HypHists","chi2_gluon_match__HypHists"};//"chi2_gluonhad_semimatch__HypHists",
  const TString Legend_Name[n_Category] = {"No Match","Switched","Semimatch, wrong gluon","Semimatch, gluon", "Match"}; //"Semimatch, gluon",

  TLegend* leg1 = new TLegend(0.67,0.65,0.87,0.87);
  leg1->SetBorderSize(0);

  for(int i = 0; i<n_Signal; i++){
    TFile *signal = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/03Feb2017_Relaunch_17Jan2018/Muons/Kinematic_Study/uhh2.AnalysisModuleRunner.MC."+File_Name[i]+".root");

    TH1F *h_signal[n_Hist][n_Category];

    for(int j= 0; j<n_Hist; j++){
      THStack *hs = new THStack("hs","");
      
      for(int k = 0; k<n_Category; k++){
	h_signal[j][k] = (TH1F*)signal->Get(Category_Name[k]+"/"+Hist_Name[j]);
	h_signal[j][k] ->SetFillColor(Color[k]);
	h_signal[j][k] -> SetLineColor(Color[k]);
	h_signal[j][k] ->SetLineWidth(2);
	if(j==0)leg1->AddEntry(h_signal[j][k],Legend_Name[k],"f");

      hs->Add(h_signal[j][k]);

    }    

    TCanvas *b1 = new TCanvas("b1","b1",800,600);
    gStyle->SetOptStat(0);
    hs->Draw("hist");
    hs->GetXaxis()->SetTitle(Hist_Label[j]);
    hs->GetXaxis()->SetTitleSize(0.05);
    leg1->Draw();
    b1->Modified();

    b1->SaveAs("/nfs/dust/cms/user/multh/CMSSW_8_0_26_patch2/src/UHH2/TstarSemiLeptonic/Plots/"+Hist_Name[j]+"_match.pdf");
    }
    
  }
}
