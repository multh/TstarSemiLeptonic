//CompMacro.C

//***********************************************************************
//
//Macro for Background Composition after every Selectionstep
//
//***********************************************************************

using namespace std;

void BackgroundComposition() {

  const int n_Samples = 6; 
  const int n_Cut = 4;

  const int n_Signal = 2;

  const TString File_Signal[n_Signal] = {"Tstar_M-700", "Tstar_M-1000"};

  const TString File_Name[n_Samples] = {"TTbar_Tune", "WJets_Pt", "QCD_Mu", "SingleT", "ZJets_HT", "Diboson"};
  const EColor Color[n_Samples] = { kRed, kGreen, kBlue, kOrange,  kViolet, kCyan};

  const TString Cut_Name[n_Cut] = {"input", "1Muon", "2DCut", "4Jets"};

  TH1F *h_background[n_Samples][n_Cut];
  TH1F *h_signal[n_Signal][n_Cut];

  double N_evt_all[n_Cut];
  double N_evt_bkg[n_Samples][n_Cut];

  double N_evt_cut[n_Samples][n_Cut];
  double Cut_eff[n_Samples][n_Cut];
  double Cut_eff_total[n_Samples][n_Cut];

  double N_evt_cut_sig[n_Signal][n_Cut];
  double Cut_eff_sig[n_Signal][n_Cut];
  double Cut_eff_sig_total[n_Signal][n_Cut];

  for(int i = 0; i<n_Samples; i++){
    TFile *background = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/PreSelection/03Feb2017_Relaunch_17Jan2018/2D_Cut_0.4_30/uhh2.AnalysisModuleRunner.MC."+File_Name[i]+".root");
    
    for(int k = 0; k<n_Cut; k++){
      h_background[i][k] = (TH1F*)background->Get(Cut_Name[k]+"/MET");

      N_evt_all[k] += h_background[i][k]->GetSumOfWeights(); 

      N_evt_cut[i][k] = h_background[i][k]->GetSumOfWeights(); 
    }    
  }


  for(int i = 0; i<n_Signal; i++){
    TFile *signal = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/PreSelection/03Feb2017_Relaunch_17Jan2018/2D_Cut_0.4_30/uhh2.AnalysisModuleRunner.MC."+File_Signal[i]+".root");
    
    for(int k = 0; k<n_Cut; k++){
      h_signal[i][k] = (TH1F*)signal->Get(Cut_Name[k]+"/MET");

      N_evt_cut_sig[i][k] = h_signal[i][k]->GetSumOfWeights(); 
    }    
  }

  THStack *hs = new THStack("hs","Background Composition");

  TH1F *h_comp[n_Samples];
  TH1F *h_eff[n_Samples];
  TH1F *h_eff_total[n_Samples];

  TH1F *h_eff_sig[n_Signal];
  TH1F *h_eff_sig_total[n_Signal];

  const char *cut_flow[n_Cut] = {"input", "1 Muon","2D-Cut", "4 Jets"};

  TLegend* legend  = new TLegend(0.73,0.65,0.9,0.9);
  TLegend* leg_eff = new TLegend(0.73,0.65,0.9,0.9);
  

  TCanvas *e1 = new TCanvas("e1","e1",1200,600);
  gStyle->SetOptStat(0);
  e1->Divide(2,1);

  for(int i = 0; i<n_Signal; i++){
    h_eff_sig[i]  = new TH1F("eff","Cut Efficiency",6,0,6);
    h_eff_sig_total[i]= new TH1F("eff_total","Cut Efficiency",6,0,6);
    for(int k = 0; k<n_Cut; k++){

      if(k == 0){ Cut_eff_sig[i][k] = 1; Cut_eff_sig_total[i][k] = 1;}
      else{
	Cut_eff_sig[i][k]       = N_evt_cut_sig[i][k]/N_evt_cut_sig[i][k-1];
	Cut_eff_sig_total[i][k] = N_evt_cut_sig[i][k]/N_evt_cut_sig[i][0];
      }

      h_eff_sig[i]  -> GetXaxis()->SetBinLabel(k+1, cut_flow[k]);
      h_eff_sig[i]  -> SetBinContent(k+1, Cut_eff_sig[i][k]);

      h_eff_sig_total[i]  -> GetXaxis()->SetBinLabel(k+1, cut_flow[k]);
      h_eff_sig_total[i]  -> SetBinContent(k+1, Cut_eff_sig_total[i][k]);
    }
    
    h_eff_sig[i]  -> SetLineWidth(2);
    h_eff_sig[i]  -> SetLineStyle(i+1);
    h_eff_sig[i]  -> SetMaximum(1.1);

    h_eff_sig_total[i]  -> SetLineWidth(2);
    h_eff_sig_total[i]  -> SetLineStyle(i+1);
    h_eff_sig_total[i]  -> SetMaximum(1.1);

    leg_eff -> AddEntry(h_eff_sig[i], File_Signal[i], "l");
 
    e1->cd(1);
    h_eff_sig[i]->Draw("SAME");

    e1->cd(2);
    h_eff_sig_total[i]->Draw("SAME");
  }


  for(int i = 0; i<n_Samples; i++){
    h_comp[i] = new TH1F("comp","",7,0,7);
    h_eff[i]  = new TH1F("eff","Cut Efficiency",7,0,7);
    h_eff_total[i]  = new TH1F("eff_total","Cut Efficiency",6,0,6);

    for(int k = 0; k<n_Cut; k++){
      N_evt_bkg[i][k]   = h_background[i][k]->GetSumOfWeights()/N_evt_all[k];  
      
      h_comp[i] -> GetXaxis()->SetBinLabel(k+1, cut_flow[k]);
      h_comp[i] -> SetBinContent(k+1, N_evt_bkg[i][k]);
      h_comp[i] -> SetFillColor(Color[i]);

      if(k == 0){ Cut_eff[i][k] = 1; Cut_eff_total[i][k] = 1;}
      else{
	Cut_eff[i][k]       = N_evt_cut[i][k]/N_evt_cut[i][k-1];
	Cut_eff_total[i][k] = N_evt_cut[i][k]/N_evt_cut[i][0];
      }

      h_eff[i]  -> GetXaxis()->SetBinLabel(k+1, cut_flow[k]);
      h_eff[i]  -> SetBinContent(k+1, Cut_eff[i][k]);
      h_eff[i]  -> SetLineColor(Color[i]);
      h_eff[i]  -> SetLineWidth(2);
      h_eff[i]  -> SetMaximum(1.1);

      h_eff_total[i]  -> GetXaxis()->SetBinLabel(k+1, cut_flow[k]);
      h_eff_total[i]  -> SetBinContent(k+1, Cut_eff_total[i][k]);
      h_eff_total[i]  -> SetLineColor(Color[i]);
      h_eff_total[i]  -> SetLineWidth(2);
      h_eff_total[i]  -> SetMaximum(1.1);
    }
    
    leg_eff -> AddEntry(h_eff[i], File_Name[i], "l");

    e1->cd(1);
    h_eff[i]->Draw("SAME");
    leg_eff -> Draw();

    e1->cd(2);
    h_eff_total[i]->Draw("SAME");
    leg_eff -> Draw();

    legend -> AddEntry(h_comp[i], File_Name[i], "f");
    
    hs->Add(h_comp[i]);
  }


  TCanvas *b1 = new TCanvas("b1","b1",800,600);
  gStyle->SetOptStat(0);
  hs->Draw();

  legend ->Draw();

  cout<<""<<endl;
  cout<<"Number of Events:"<<endl;
  /*
  for(int i = 0; i<6; i++){
    TFile *background = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/03Feb2017_Relaunch_17Jan2018/Matching/uhh2.AnalysisModuleRunner.MC."+File_Name[i]+".root");

    TH1F *h_bkg = (TH1F*)background->Get("output/MET");
    
    cout<<File_Name[i]+":   "<<h_bkg->GetSumOfWeights()<<endl;
  }
  */
  const TString File_Sig[10] = {"Tstar_M-700","Tstar_M-800","Tstar_M-900", "Tstar_M-1000", "Tstar_M-1100","Tstar_M-1200","Tstar_M-1300","Tstar_M-1400","Tstar_M-1500","Tstar_M-1600"};

  for(int i = 0; i<10; i++){
    TFile *signal = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/03Feb2017_Relaunch_17Jan2018/Matching/Matching_7Jets/uhh2.AnalysisModuleRunner.MC."+File_Sig[i]+".root");

      TH1F *h_sig = (TH1F*)signal->Get("output/MET");
    
    cout<<File_Sig[i]+":   "<<h_sig->GetSumOfWeights()<<endl;
  }
  /*
  for(int i = 0; i<0; i++){
    TFile *data = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/03Feb2017_Relaunch_17Jan2018/uhh2.AnalysisModuleRunner.DATA.SingleMuData.root");

    TH1F *h_data = (TH1F*)data->Get("output/MET");
    
    cout<<File_Signal[i]+":   "<<h_data->GetSumOfWeights()<<endl;
  }
  */

}
