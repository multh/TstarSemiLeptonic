//CompMacro.C

//***********************************************************************
//
//Macro for Correct match analysis plots
//
//***********************************************************************

using namespace std;

void CorrectMatchPlots() {

  const int n_Samples = 2; 

  const int n_Folders = 2;
  
  const int n_Hists = 16;

  const int n_Control = 11;


  const TString File_Name[n_Samples] = {"Tstar_M-900","Tstar_M-1600"};//, "Tstar_M-800","Tstar_M-900" ,"Tstar_M-1000","Tstar_M-1100","Tstar_M-1200","Tstar_M-1300","Tstar_M-1400","Tstar_M-1500","Tstar_M-1600"};

  const EColor Color[n_Folders] = { kBlue, kRed};


  const TString Hists_Name[n_Hists] = {"M_Tstar_comb", "M_Tstarlep_rec", "M_Tstarhad_rec", "M_toplep", "M_tophad", "M_Tstar_resolution", "DeltaPhi_TstarhadTstarlep", "Discriminator_4", "Pt_Diff_gluonhad_tophad", "Pt_Diff_gluonlep_toplep", "Pt_Diff_gluonhad_bhad", "Pt_Diff_gluonlep_blep", "Pt_Diff_gluonhad_blep", "Pt_Diff_gluonlep_bhad", "Pt_Diff_gluonlep_Wlep", "M_Wlep_rec"};

  const TString Control_Name[n_Control] = {"N_jets", "eta_jet1", "eta_jet2", "pt_jet1", "pt_jet2", "N_mu", "pt_mu", "eta_mu", "H_T", "mindr_mujet", "N_bJets_med"};


  TLegend* legend  = new TLegend(0.73,0.75,0.9,0.9);


  TH1F *h_corrmatch[n_Samples][n_Hists];
  TH1F *h_match[n_Samples][n_Hists];

  TH1F *h_corrmatch_control[n_Samples][n_Control];
  TH1F *h_match_control[n_Samples][n_Control];

  for(int i = 0; i<n_Samples; i++){
    TFile *sample = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/03Feb2017_Relaunch_17Jan2018/Matching/Changed_Reco/uhh2.AnalysisModuleRunner.MC."+File_Name[i]+".root");
 
      for(int j = 0; j<n_Hists; j++){
	THStack *hs = new THStack("hs","");
	h_corrmatch[i][j] = (TH1F*)sample->Get("corrmatch__HypHists/"+Hists_Name[j])->Clone();
	h_match[i][j] = (TH1F*)sample->Get("no_corrmatch__HypHists/"+Hists_Name[j])->Clone();


	h_match[i][j]     -> SetFillColor(kRed);
	hs->Add(h_match[i][j]);

	h_corrmatch[i][j] -> SetFillColor(kBlue);
	hs->Add(h_corrmatch[i][j]);

	if(j==0 && i==0){
	  legend -> AddEntry(h_corrmatch[i][j], "matched", "f");
	  legend -> AddEntry(h_match[i][j], "not matched", "f");
	}


	TCanvas *b1 = new TCanvas("b1","b1",800,600);
	gStyle->SetOptStat(0);

	hs->Draw("hist");
	hs->GetYaxis()->SetTitle("Events");
	hs->GetXaxis()->SetTitle(h_match[i][j]->GetTitle());
	b1->Modified();

	legend->Draw();

	b1->SaveAs("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/03Feb2017_Relaunch_17Jan2018/Matching/Changed_Reco/Plots/Matched_"+Hists_Name[j]+"_"+File_Name[i]+".pdf");

      }
      
      for(int j = 0; j<n_Control; j++){
	THStack *hb = new THStack("hb","");
	h_corrmatch_control[i][j] = (TH1F*)sample->Get("corrmatch/"+Control_Name[j])->Clone();
	h_match_control[i][j] = (TH1F*)sample->Get("no_corrmatch/"+Control_Name[j])->Clone();

	h_match_control[i][j]     -> SetFillColor(kRed);
	hb->Add(h_match_control[i][j]);

	h_corrmatch_control[i][j] -> SetFillColor(kBlue);
	hb->Add(h_corrmatch_control[i][j]);

      
	/*
	if(j==0){
	  legend -> AddEntry(h_corrmatch_control[i][j], "matched", "f");
	  legend -> AddEntry(h_match_control[i][j], "not matched", "f");
	}
	*/
      
	TCanvas *b2 = new TCanvas("b2","b2",800,600);
	gStyle->SetOptStat(0);

	hb->Draw("hist");
	hb->GetYaxis()->SetTitle("Events");
	hb->GetXaxis()->SetTitle(h_match_control[i][j]->GetTitle());
	b2->Modified();

	legend->Draw();

	b2->SaveAs("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/03Feb2017_Relaunch_17Jan2018/Matching/Changed_Reco/Plots/Matched_"+Control_Name[j]+"_"+File_Name[i]+".pdf");

      }

  }
  
  
}
