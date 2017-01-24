#include "HttStylesNew.cc"

void TstarAnalysis(TString Variable = "M_Tstar_comb", // variable to plot
		 int nBins =   30, // number of bins in histogram
		 float xmin =  0, // lower edgde of histogram
		 float xmax = 2000, // upper edge of histogram
		   //TString Weight = "puweight*mcweight*isoweight_1*trigweight_1*idEffMedium_2*", // event weight
		   //TString Cuts = "iso_1<0.1&&idMvaTight_2>0.5", // imposed cuts
		 TString xtitle = "M_{T^{*}} [GeV/c^{2}]", // title of x-axis
		 TString ytitle = "Ereignisse" // title of y-axis
		 )
{

  SetStyle();

  bool logY = false;
  TString DataFile = "uhh2.AnalysisModuleRunner.DATA.SingleMuDATA"; // w/o .root extension
  TString rootDir = "/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/"; // directory with RooT files

  double lumi = 2690; // integrated luminosity 

 TString Names[19]={
    "Nominal",
     "B_Tag_Down_bc",
     "B_Tag_Up_bc",
     "B_Tag_udsg_Down",
     "B_Tag_udsg_Up",
     "JEC_Down",
     "JEC_Up",
     "JER_Down",
     "JER_Up",
     "MuonID_Up",
     "MuonID_Down",
     "MuonTrigger_Up",
     "MuonTrigger_Down",
     "PU_Up",
     "PU_Down",
     "Sys_PDF_Down",
     "Sys_PDF_Up",
     "ScaleVariation_Up",
     "ScaleVariation_Down",
      };

   // List of samples used in the analysis
  TString sampleNames[17] = {
    DataFile, // data
    "uhh2.AnalysisModuleRunner.MC.TTbar", // TTbar
    "uhh2.AnalysisModuleRunner.MC.WJets", // W+Jets
    "uhh2.AnalysisModuleRunner.MC.ZJets", // // Z+Jets 
    "uhh2.AnalysisModuleRunner.MC.SingleTop", // single-top (t-channel)
    "uhh2.AnalysisModuleRunner.MC.Diboson", // Diboson 
    "uhh2.AnalysisModuleRunner.MC.QCD", // QCD 
    "uhh2.AnalysisModuleRunner.MC.Tstar_M700",  //Signal_M700
    "uhh2.AnalysisModuleRunner.MC.Tstar_M800",   //Signal_M800
    "uhh2.AnalysisModuleRunner.MC.Tstar_M900",   //Signal_M800
    "uhh2.AnalysisModuleRunner.MC.Tstar_M1000",
    "uhh2.AnalysisModuleRunner.MC.Tstar_M1100",   //Signal_M800
    "uhh2.AnalysisModuleRunner.MC.Tstar_M1200",   //Signal_M800
    "uhh2.AnalysisModuleRunner.MC.Tstar_M1300",   //Signal_M800
    "uhh2.AnalysisModuleRunner.MC.Tstar_M1400",   //Signal_M800
    "uhh2.AnalysisModuleRunner.MC.Tstar_M1500",   //Signal_M800
    "uhh2.AnalysisModuleRunner.MC.Tstar_M1600",   //Signal_M800
};  //Signal_M900
 
  TH1F * hist[17];
   for (int i=0; i<17; ++i) {
    TFile * file = new TFile(rootDir+Names[0]+"/"+sampleNames[i]+".root");
    hist[i] = (TH1F*)file->Get("output_Event/HT");
   
    hist[i]->Sumw2();
}
  
 // Cloning histograms 
  TH1D * histData = (TH1D*)hist[0]->Clone("data_obs");
  cout<<"Daten   : "<< histData ->GetSumOfWeights()<<endl;

  TH1D * h_TT = (TH1D*)hist[1]->Clone("TT");
  cout<<"Anzahl Eintrage TT   : "<< h_TT ->GetSumOfWeights()<<endl;

  TH1D * h_WJets = (TH1D*)hist[2]->Clone("WJets");
  cout<<"Anzahl Eintrage W+Jets   : "<< h_WJets ->GetSumOfWeights()<<endl;

  TH1D * h_ZJets = (TH1D*)hist[3]->Clone("ZJets");
  cout<<"Anzahl Eintrage Z+Jets   : "<< h_ZJets ->GetSumOfWeights()<<endl;

  TH1D * h_SingleTop  = (TH1D*)hist[4]->Clone("SingleTop");
  cout<<"Anzahl Eintrage SingleTop   : "<< h_SingleTop ->GetSumOfWeights()<<endl;

  TH1D * h_Diboson  = (TH1D*)hist[5]->Clone("Diboson");
  cout<<"Anzahl Eintrage Diboson   : "<< h_Diboson ->GetSumOfWeights()<<endl;

  TH1D * h_QCD = (TH1D*)hist[6]->Clone("QCD");
  cout<<"Anzahl Eintrage QCD  : "<< h_QCD ->GetSumOfWeights()<<endl;

  TH1D * h_Tstar_M700 = (TH1D*)hist[7]->Clone("Tstar_M700");
  cout<<"Anzahl Eintrage 700   : "<< h_Tstar_M700 ->GetSumOfWeights()<<endl;

  TH1D * h_Tstar_M800 = (TH1D*)hist[8]->Clone("Tstar_M800");
  cout<<"Anzahl Eintrage 800   : "<< h_Tstar_M800 ->GetSumOfWeights()<<endl;

  TH1D * h_Tstar_M900 = (TH1D*)hist[9]->Clone("Tstar_M900");
  cout<<"Anzahl Eintrage 900   : "<< h_Tstar_M900 ->GetSumOfWeights()<<endl;
  TH1D * h_Tstar_M1000 = (TH1D*)hist[10]->Clone("Tstar_M1000");
  cout<<"Anzahl Eintrage 1000   : "<< h_Tstar_M1000 ->GetSumOfWeights()<<endl;
  TH1D * h_Tstar_M1100 = (TH1D*)hist[11]->Clone("Tstar_M1100");
  cout<<"Anzahl Eintrage 1100   : "<< h_Tstar_M1100 ->GetSumOfWeights()<<endl;
  TH1D * h_Tstar_M1200 = (TH1D*)hist[12]->Clone("Tstar_M1200");
  cout<<"Anzahl Eintrage 1200   : "<< h_Tstar_M1200 ->GetSumOfWeights()<<endl;
  TH1D * h_Tstar_M1300 = (TH1D*)hist[13]->Clone("Tstar_M1300");
  cout<<"Anzahl Eintrage 1300   : "<< h_Tstar_M1300 ->GetSumOfWeights()<<endl;
  TH1D * h_Tstar_M1400 = (TH1D*)hist[14]->Clone("Tstar_M1400");
  cout<<"Anzahl Eintrage 1400   : "<< h_Tstar_M1400 ->GetSumOfWeights()<<endl;
  TH1D * h_Tstar_M1500 = (TH1D*)hist[15]->Clone("Tstar_M1500");
  cout<<"Anzahl Eintrage 1500   : "<< h_Tstar_M1500 ->GetSumOfWeights()<<endl;
  TH1D * h_Tstar_M1600 = (TH1D*)hist[16]->Clone("Tstar_M1600");
  cout<<"Anzahl Eintrage 1600   : "<< h_Tstar_M1600 ->GetSumOfWeights()<<endl;



  //*****************************************************************************************************
 TH1F * hist_bTag_bc_Down[17];
   for (int i=0; i<17; ++i) {
    TFile * file = new TFile(rootDir+Names[1]+"/"+sampleNames[i]+".root");
    hist_bTag_bc_Down[i] = (TH1F*)file->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
   
    hist_bTag_bc_Down[i]->Sumw2();
}
  
 // Cloning histograms 
  TH1D * histData_bTag_bc_Down = (TH1D*)hist_bTag_bc_Down[0]->Clone("data_obs");
  TH1D * h_TT_bTag_bc_Down = (TH1D*)hist_bTag_bc_Down[1]->Clone("TT");
  TH1D * h_WJets_bTag_bc_Down = (TH1D*)hist_bTag_bc_Down[2]->Clone("WJets");
  TH1D * h_ZJets_bTag_bc_Down = (TH1D*)hist_bTag_bc_Down[3]->Clone("ZJets");
  TH1D * h_SingleTop_bTag_bc_Down  = (TH1D*)hist_bTag_bc_Down[4]->Clone("SingleTop");
  TH1D * h_Diboson_bTag_bc_Down  = (TH1D*)hist_bTag_bc_Down[5]->Clone("Diboson");
  TH1D * h_QCD_bTag_bc_Down = (TH1D*)hist_bTag_bc_Down[6]->Clone("QCD");
  TH1D * h_Tstar_M700_bTag_bc_Down = (TH1D*)hist_bTag_bc_Down[7]->Clone("Tstar_M700");
  TH1D * h_Tstar_M800_bTag_bc_Down = (TH1D*)hist_bTag_bc_Down[8]->Clone("Tstar_M800");
  TH1D * h_Tstar_M900_bTag_bc_Down = (TH1D*)hist_bTag_bc_Down[9]->Clone("Tstar_M900");
  TH1D * h_Tstar_M1000_bTag_bc_Down = (TH1D*)hist_bTag_bc_Down[10]->Clone("Tstar_M1000");
  TH1D * h_Tstar_M1100_bTag_bc_Down = (TH1D*)hist_bTag_bc_Down[11]->Clone("Tstar_M1100");
  TH1D * h_Tstar_M1200_bTag_bc_Down = (TH1D*)hist_bTag_bc_Down[12]->Clone("Tstar_M1200");
  TH1D * h_Tstar_M1300_bTag_bc_Down = (TH1D*)hist_bTag_bc_Down[13]->Clone("Tstar_M1300");
  TH1D * h_Tstar_M1400_bTag_bc_Down = (TH1D*)hist_bTag_bc_Down[14]->Clone("Tstar_M1400");
  TH1D * h_Tstar_M1500_bTag_bc_Down = (TH1D*)hist_bTag_bc_Down[15]->Clone("Tstar_M1500");
  TH1D * h_Tstar_M1600_bTag_bc_Down = (TH1D*)hist_bTag_bc_Down[16]->Clone("Tstar_M1600");



  //***************************************************************************************************
TH1F * hist_bTag_bc_Up[17];
   for (int i=0; i<17; ++i) {
    TFile * file = new TFile(rootDir+Names[2]+"/"+sampleNames[i]+".root");
    hist_bTag_bc_Up[i] = (TH1F*)file->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
   
    hist_bTag_bc_Up[i]->Sumw2();
}
  
 // Cloning histograms 
  TH1D * histData_bTag_bc_Up = (TH1D*)hist_bTag_bc_Up[0]->Clone("data_obs");
  TH1D * h_TT_bTag_bc_Up = (TH1D*)hist_bTag_bc_Up[1]->Clone("TT");
  TH1D * h_WJets_bTag_bc_Up = (TH1D*)hist_bTag_bc_Up[2]->Clone("WJets");
  TH1D * h_ZJets_bTag_bc_Up = (TH1D*)hist_bTag_bc_Up[3]->Clone("ZJets");
  TH1D * h_SingleTop_bTag_bc_Up  = (TH1D*)hist_bTag_bc_Up[4]->Clone("SingleTop");
  TH1D * h_Diboson_bTag_bc_Up  = (TH1D*)hist_bTag_bc_Up[5]->Clone("Diboson");
  TH1D * h_QCD_bTag_bc_Up = (TH1D*)hist_bTag_bc_Up[6]->Clone("QCD");
  TH1D * h_Tstar_M700_bTag_bc_Up = (TH1D*)hist_bTag_bc_Up[7]->Clone("Tstar_M700");
  TH1D * h_Tstar_M800_bTag_bc_Up = (TH1D*)hist_bTag_bc_Up[8]->Clone("Tstar_M800");
  TH1D * h_Tstar_M900_bTag_bc_Up = (TH1D*)hist_bTag_bc_Up[9]->Clone("Tstar_M900");
  TH1D * h_Tstar_M1000_bTag_bc_Up = (TH1D*)hist_bTag_bc_Up[10]->Clone("Tstar_M1000");
  TH1D * h_Tstar_M1100_bTag_bc_Up = (TH1D*)hist_bTag_bc_Up[11]->Clone("Tstar_M1100");
  TH1D * h_Tstar_M1200_bTag_bc_Up = (TH1D*)hist_bTag_bc_Up[12]->Clone("Tstar_M1200");
  TH1D * h_Tstar_M1300_bTag_bc_Up = (TH1D*)hist_bTag_bc_Up[13]->Clone("Tstar_M1300");
  TH1D * h_Tstar_M1400_bTag_bc_Up = (TH1D*)hist_bTag_bc_Up[14]->Clone("Tstar_M1400");
  TH1D * h_Tstar_M1500_bTag_bc_Up = (TH1D*)hist_bTag_bc_Up[15]->Clone("Tstar_M1500");
  TH1D * h_Tstar_M1600_bTag_bc_Up = (TH1D*)hist_bTag_bc_Up[16]->Clone("Tstar_M1600");


  //***************************************************************************************************
TH1F * hist_bTag_udsg_Up[17];
   for (int i=0; i<17; ++i) {
    TFile * file = new TFile(rootDir+Names[3]+"/"+sampleNames[i]+".root");
    hist_bTag_udsg_Up[i] = (TH1F*)file->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
   
    hist_bTag_udsg_Up[i]->Sumw2();
}
  
 // Cloning histograms 
  TH1D * histData_bTag_udsg_Up = (TH1D*)hist_bTag_udsg_Up[0]->Clone("data_obs");
  TH1D * h_TT_bTag_udsg_Up = (TH1D*)hist_bTag_udsg_Up[1]->Clone("TT");
  TH1D * h_WJets_bTag_udsg_Up = (TH1D*)hist_bTag_udsg_Up[2]->Clone("WJets");
  TH1D * h_ZJets_bTag_udsg_Up = (TH1D*)hist_bTag_udsg_Up[3]->Clone("ZJets");
  TH1D * h_SingleTop_bTag_udsg_Up  = (TH1D*)hist_bTag_udsg_Up[4]->Clone("SingleTop");
  TH1D * h_Diboson_bTag_udsg_Up  = (TH1D*)hist_bTag_udsg_Up[5]->Clone("Diboson");
  TH1D * h_QCD_bTag_udsg_Up = (TH1D*)hist_bTag_udsg_Up[6]->Clone("QCD");
  TH1D * h_Tstar_M700_bTag_udsg_Up = (TH1D*)hist_bTag_udsg_Up[7]->Clone("Tstar_M700");
  TH1D * h_Tstar_M800_bTag_udsg_Up = (TH1D*)hist_bTag_udsg_Up[8]->Clone("Tstar_M800");
  TH1D * h_Tstar_M900_bTag_udsg_Up = (TH1D*)hist_bTag_udsg_Up[9]->Clone("Tstar_M900");
  TH1D * h_Tstar_M1000_bTag_udsg_Up = (TH1D*)hist_bTag_udsg_Up[10]->Clone("Tstar_M1000");
  TH1D * h_Tstar_M1100_bTag_udsg_Up = (TH1D*)hist_bTag_udsg_Up[11]->Clone("Tstar_M1100");
  TH1D * h_Tstar_M1200_bTag_udsg_Up = (TH1D*)hist_bTag_udsg_Up[12]->Clone("Tstar_M1200");
  TH1D * h_Tstar_M1300_bTag_udsg_Up = (TH1D*)hist_bTag_udsg_Up[13]->Clone("Tstar_M1300");
  TH1D * h_Tstar_M1400_bTag_udsg_Up = (TH1D*)hist_bTag_udsg_Up[14]->Clone("Tstar_M1400");
  TH1D * h_Tstar_M1500_bTag_udsg_Up = (TH1D*)hist_bTag_udsg_Up[15]->Clone("Tstar_M1500");
  TH1D * h_Tstar_M1600_bTag_udsg_Up = (TH1D*)hist_bTag_udsg_Up[16]->Clone("Tstar_M1600");

 //***************************************************************************************************
TH1F * hist_bTag_udsg_Down[17];
   for (int i=0; i<17; ++i) {
    TFile * file = new TFile(rootDir+Names[4]+"/"+sampleNames[i]+".root");
    hist_bTag_udsg_Down[i] = (TH1F*)file->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
   
    hist_bTag_udsg_Down[i]->Sumw2();
}
  
 // Cloning histograms 
  TH1D * histData_bTag_udsg_Down = (TH1D*)hist_bTag_udsg_Down[0]->Clone("data_obs");
  TH1D * h_TT_bTag_udsg_Down = (TH1D*)hist_bTag_udsg_Down[1]->Clone("TT");
  TH1D * h_WJets_bTag_udsg_Down = (TH1D*)hist_bTag_udsg_Down[2]->Clone("WJets");
  TH1D * h_ZJets_bTag_udsg_Down = (TH1D*)hist_bTag_udsg_Down[3]->Clone("ZJets");
  TH1D * h_SingleTop_bTag_udsg_Down  = (TH1D*)hist_bTag_udsg_Down[4]->Clone("SingleTop");
  TH1D * h_Diboson_bTag_udsg_Down  = (TH1D*)hist_bTag_udsg_Down[5]->Clone("Diboson");
  TH1D * h_QCD_bTag_udsg_Down = (TH1D*)hist_bTag_udsg_Down[6]->Clone("QCD");
  TH1D * h_Tstar_M700_bTag_udsg_Down = (TH1D*)hist_bTag_udsg_Down[7]->Clone("Tstar_M700");
  TH1D * h_Tstar_M800_bTag_udsg_Down = (TH1D*)hist_bTag_udsg_Down[8]->Clone("Tstar_M800");
  TH1D * h_Tstar_M900_bTag_udsg_Down = (TH1D*)hist_bTag_udsg_Down[9]->Clone("Tstar_M900");
  TH1D * h_Tstar_M1000_bTag_udsg_Down = (TH1D*)hist_bTag_udsg_Down[10]->Clone("Tstar_M1000");
  TH1D * h_Tstar_M1100_bTag_udsg_Down = (TH1D*)hist_bTag_udsg_Down[11]->Clone("Tstar_M1100");
  TH1D * h_Tstar_M1200_bTag_udsg_Down = (TH1D*)hist_bTag_udsg_Down[12]->Clone("Tstar_M1200");
  TH1D * h_Tstar_M1300_bTag_udsg_Down = (TH1D*)hist_bTag_udsg_Down[13]->Clone("Tstar_M1300");
  TH1D * h_Tstar_M1400_bTag_udsg_Down = (TH1D*)hist_bTag_udsg_Down[14]->Clone("Tstar_M1400");
  TH1D * h_Tstar_M1500_bTag_udsg_Down = (TH1D*)hist_bTag_udsg_Down[15]->Clone("Tstar_M1500");
  TH1D * h_Tstar_M1600_bTag_udsg_Down = (TH1D*)hist_bTag_udsg_Down[16]->Clone("Tstar_M1600");


//***************************************************************************************************
TH1F * hist_JEC_Down[17];
   for (int i=0; i<17; ++i) {
    TFile * file = new TFile(rootDir+Names[5]+"/"+sampleNames[i]+".root");
    hist_JEC_Down[i] = (TH1F*)file->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
   
    hist_JEC_Down[i]->Sumw2();
}
  
 // Cloning histograms 
  TH1D * histData_JEC_Down = (TH1D*)hist_JEC_Down[0]->Clone("data_obs");
  TH1D * h_TT_JEC_Down = (TH1D*)hist_JEC_Down[1]->Clone("TT");
  TH1D * h_WJets_JEC_Down = (TH1D*)hist_JEC_Down[2]->Clone("WJets");
  TH1D * h_ZJets_JEC_Down = (TH1D*)hist_JEC_Down[3]->Clone("ZJets");
  TH1D * h_SingleTop_JEC_Down  = (TH1D*)hist_JEC_Down[4]->Clone("SingleTop");
  TH1D * h_Diboson_JEC_Down  = (TH1D*)hist_JEC_Down[5]->Clone("Diboson");
  TH1D * h_QCD_JEC_Down = (TH1D*)hist_JEC_Down[6]->Clone("QCD");
  TH1D * h_Tstar_M700_JEC_Down = (TH1D*)hist_JEC_Down[7]->Clone("Tstar_M700");
  TH1D * h_Tstar_M800_JEC_Down = (TH1D*)hist_JEC_Down[8]->Clone("Tstar_M800");
  TH1D * h_Tstar_M900_JEC_Down = (TH1D*)hist_JEC_Down[9]->Clone("Tstar_M900");
  TH1D * h_Tstar_M1000_JEC_Down = (TH1D*)hist_JEC_Down[10]->Clone("Tstar_M1000");
  TH1D * h_Tstar_M1100_JEC_Down = (TH1D*)hist_JEC_Down[11]->Clone("Tstar_M1100");
  TH1D * h_Tstar_M1200_JEC_Down = (TH1D*)hist_JEC_Down[12]->Clone("Tstar_M1200");
  TH1D * h_Tstar_M1300_JEC_Down = (TH1D*)hist_JEC_Down[13]->Clone("Tstar_M1300");
  TH1D * h_Tstar_M1400_JEC_Down = (TH1D*)hist_JEC_Down[14]->Clone("Tstar_M1400");
  TH1D * h_Tstar_M1500_JEC_Down = (TH1D*)hist_JEC_Down[15]->Clone("Tstar_M1500");
  TH1D * h_Tstar_M1600_JEC_Down = (TH1D*)hist_JEC_Down[16]->Clone("Tstar_M1600");

//***************************************************************************************************
TH1F * hist_JEC_Up[17];
   for (int i=0; i<17; ++i) {
    TFile * file = new TFile(rootDir+Names[6]+"/"+sampleNames[i]+".root");
    hist_JEC_Up[i] = (TH1F*)file->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
   
    hist_JEC_Up[i]->Sumw2();
}
 
 // Cloning histograms 
  TH1D * histData_JEC_Up = (TH1D*)hist_JEC_Up[0]->Clone("data_obs");
  TH1D * h_TT_JEC_Up = (TH1D*)hist_JEC_Up[1]->Clone("TT");
  TH1D * h_WJets_JEC_Up = (TH1D*)hist_JEC_Up[2]->Clone("WJets");
  TH1D * h_ZJets_JEC_Up = (TH1D*)hist_JEC_Up[3]->Clone("ZJets");
  TH1D * h_SingleTop_JEC_Up  = (TH1D*)hist_JEC_Up[4]->Clone("SingleTop");
  TH1D * h_Diboson_JEC_Up  = (TH1D*)hist_JEC_Up[5]->Clone("Diboson");
  TH1D * h_QCD_JEC_Up = (TH1D*)hist_JEC_Up[6]->Clone("QCD");
  TH1D * h_Tstar_M700_JEC_Up = (TH1D*)hist_JEC_Up[7]->Clone("Tstar_M700");
  TH1D * h_Tstar_M800_JEC_Up = (TH1D*)hist_JEC_Up[8]->Clone("Tstar_M800");
  TH1D * h_Tstar_M900_JEC_Up = (TH1D*)hist_JEC_Up[9]->Clone("Tstar_M900");
  TH1D * h_Tstar_M1000_JEC_Up = (TH1D*)hist_JEC_Up[10]->Clone("Tstar_M1000");
  TH1D * h_Tstar_M1100_JEC_Up = (TH1D*)hist_JEC_Up[11]->Clone("Tstar_M1100");
  TH1D * h_Tstar_M1200_JEC_Up = (TH1D*)hist_JEC_Up[12]->Clone("Tstar_M1200");
  TH1D * h_Tstar_M1300_JEC_Up = (TH1D*)hist_JEC_Up[13]->Clone("Tstar_M1300");
  TH1D * h_Tstar_M1400_JEC_Up = (TH1D*)hist_JEC_Up[14]->Clone("Tstar_M1400");
  TH1D * h_Tstar_M1500_JEC_Up = (TH1D*)hist_JEC_Up[15]->Clone("Tstar_M1500");
  TH1D * h_Tstar_M1600_JEC_Up = (TH1D*)hist_JEC_Up[16]->Clone("Tstar_M1600");

//***************************************************************************************************
TH1F * hist_JER_Up[17];
   for (int i=0; i<17; ++i) {
    TFile * file = new TFile(rootDir+Names[7]+"/"+sampleNames[i]+".root");
    hist_JER_Up[i] = (TH1F*)file->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
   
    hist_JER_Up[i]->Sumw2();
}
  
 // Cloning histograms 
  TH1D * histData_JER_Up = (TH1D*)hist_JER_Up[0]->Clone("data_obs");
  TH1D * h_TT_JER_Up = (TH1D*)hist_JER_Up[1]->Clone("TT");
  TH1D * h_WJets_JER_Up = (TH1D*)hist_JER_Up[2]->Clone("WJets");
  TH1D * h_ZJets_JER_Up = (TH1D*)hist_JER_Up[3]->Clone("ZJets");
  TH1D * h_SingleTop_JER_Up  = (TH1D*)hist_JER_Up[4]->Clone("SingleTop");
  TH1D * h_Diboson_JER_Up  = (TH1D*)hist_JER_Up[5]->Clone("Diboson");
  TH1D * h_QCD_JER_Up = (TH1D*)hist_JER_Up[6]->Clone("QCD");
  TH1D * h_Tstar_M700_JER_Up = (TH1D*)hist_JER_Up[7]->Clone("Tstar_M700");
  TH1D * h_Tstar_M800_JER_Up = (TH1D*)hist_JER_Up[8]->Clone("Tstar_M800");
  TH1D * h_Tstar_M900_JER_Up = (TH1D*)hist_JER_Up[9]->Clone("Tstar_M900");
  TH1D * h_Tstar_M1000_JER_Up = (TH1D*)hist_JER_Up[10]->Clone("Tstar_M1000");
  TH1D * h_Tstar_M1100_JER_Up = (TH1D*)hist_JER_Up[11]->Clone("Tstar_M1100");
  TH1D * h_Tstar_M1200_JER_Up = (TH1D*)hist_JER_Up[12]->Clone("Tstar_M1200");
  TH1D * h_Tstar_M1300_JER_Up = (TH1D*)hist_JER_Up[13]->Clone("Tstar_M1300");
  TH1D * h_Tstar_M1400_JER_Up = (TH1D*)hist_JER_Up[14]->Clone("Tstar_M1400");
  TH1D * h_Tstar_M1500_JER_Up = (TH1D*)hist_JER_Up[15]->Clone("Tstar_M1500");
  TH1D * h_Tstar_M1600_JER_Up = (TH1D*)hist_JER_Up[16]->Clone("Tstar_M1600");

//***************************************************************************************************
TH1F * hist_JER_Down[17];
   for (int i=0; i<17; ++i) {
    TFile * file = new TFile(rootDir+Names[8]+"/"+sampleNames[i]+".root");
    hist_JER_Down[i] = (TH1F*)file->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
   
    hist_JER_Down[i]->Sumw2();
}
  
 // Cloning histograms 
  TH1D * histData_JER_Down = (TH1D*)hist_JER_Down[0]->Clone("data_obs");
  TH1D * h_TT_JER_Down = (TH1D*)hist_JER_Down[1]->Clone("TT");
  TH1D * h_WJets_JER_Down = (TH1D*)hist_JER_Down[2]->Clone("WJets");
  TH1D * h_ZJets_JER_Down = (TH1D*)hist_JER_Down[3]->Clone("ZJets");
  TH1D * h_SingleTop_JER_Down  = (TH1D*)hist_JER_Down[4]->Clone("SingleTop");
  TH1D * h_Diboson_JER_Down  = (TH1D*)hist_JER_Down[5]->Clone("Diboson");
  TH1D * h_QCD_JER_Down = (TH1D*)hist_JER_Down[6]->Clone("QCD");
  TH1D * h_Tstar_M700_JER_Down = (TH1D*)hist_JER_Down[7]->Clone("Tstar_M700");
  TH1D * h_Tstar_M800_JER_Down = (TH1D*)hist_JER_Down[8]->Clone("Tstar_M800");
  TH1D * h_Tstar_M900_JER_Down = (TH1D*)hist_JER_Down[9]->Clone("Tstar_M900");
  TH1D * h_Tstar_M1000_JER_Down = (TH1D*)hist_JER_Down[10]->Clone("Tstar_M1000");
  TH1D * h_Tstar_M1100_JER_Down = (TH1D*)hist_JER_Down[11]->Clone("Tstar_M1100");
  TH1D * h_Tstar_M1200_JER_Down = (TH1D*)hist_JER_Down[12]->Clone("Tstar_M1200");
  TH1D * h_Tstar_M1300_JER_Down = (TH1D*)hist_JER_Down[13]->Clone("Tstar_M1300");
  TH1D * h_Tstar_M1400_JER_Down = (TH1D*)hist_JER_Down[14]->Clone("Tstar_M1400");
  TH1D * h_Tstar_M1500_JER_Down = (TH1D*)hist_JER_Down[15]->Clone("Tstar_M1500");
  TH1D * h_Tstar_M1600_JER_Down = (TH1D*)hist_JER_Down[16]->Clone("Tstar_M1600");

  //*************************************************************************************************
TH1F * hist_MuonID_Down[17];
   for (int i=0; i<17; ++i) {
    TFile * file = new TFile(rootDir+Names[9]+"/"+sampleNames[i]+".root");
    hist_MuonID_Down[i] = (TH1F*)file->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
   
    hist_MuonID_Down[i]->Sumw2();
}
  
 // Cloning histograms 
  TH1D * histData_MuonID_Down = (TH1D*)hist_MuonID_Down[0]->Clone("data_obs");
  TH1D * h_TT_MuonID_Down = (TH1D*)hist_MuonID_Down[1]->Clone("TT");
  TH1D * h_WJets_MuonID_Down = (TH1D*)hist_MuonID_Down[2]->Clone("WJets");
  TH1D * h_ZJets_MuonID_Down = (TH1D*)hist_MuonID_Down[3]->Clone("ZJets");
  TH1D * h_SingleTop_MuonID_Down  = (TH1D*)hist_MuonID_Down[4]->Clone("SingleTop");
  TH1D * h_Diboson_MuonID_Down  = (TH1D*)hist_MuonID_Down[5]->Clone("Diboson");
  TH1D * h_QCD_MuonID_Down = (TH1D*)hist_MuonID_Down[6]->Clone("QCD");
  TH1D * h_Tstar_M700_MuonID_Down = (TH1D*)hist_MuonID_Down[7]->Clone("Tstar_M700");
  TH1D * h_Tstar_M800_MuonID_Down = (TH1D*)hist_MuonID_Down[8]->Clone("Tstar_M800");
  TH1D * h_Tstar_M900_MuonID_Down = (TH1D*)hist_MuonID_Down[9]->Clone("Tstar_M900");
  TH1D * h_Tstar_M1000_MuonID_Down = (TH1D*)hist_MuonID_Down[10]->Clone("Tstar_M1000");
  TH1D * h_Tstar_M1100_MuonID_Down = (TH1D*)hist_MuonID_Down[11]->Clone("Tstar_M1100");
  TH1D * h_Tstar_M1200_MuonID_Down = (TH1D*)hist_MuonID_Down[12]->Clone("Tstar_M1200");
  TH1D * h_Tstar_M1300_MuonID_Down = (TH1D*)hist_MuonID_Down[13]->Clone("Tstar_M1300");
  TH1D * h_Tstar_M1400_MuonID_Down = (TH1D*)hist_MuonID_Down[14]->Clone("Tstar_M1400");
  TH1D * h_Tstar_M1500_MuonID_Down = (TH1D*)hist_MuonID_Down[15]->Clone("Tstar_M1500");
  TH1D * h_Tstar_M1600_MuonID_Down = (TH1D*)hist_MuonID_Down[16]->Clone("Tstar_M1600");

 //*************************************************************************************************
TH1F * hist_MuonID_Up[17];
   for (int i=0; i<17; ++i) {
    TFile * file = new TFile(rootDir+Names[10]+"/"+sampleNames[i]+".root");
    hist_MuonID_Up[i] = (TH1F*)file->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
   
    hist_MuonID_Up[i]->Sumw2();
}
  
 // Cloning histograms 
  TH1D * histData_MuonID_Up = (TH1D*)hist_MuonID_Up[0]->Clone("data_obs");
  TH1D * h_TT_MuonID_Up = (TH1D*)hist_MuonID_Up[1]->Clone("TT");
  TH1D * h_WJets_MuonID_Up = (TH1D*)hist_MuonID_Up[2]->Clone("WJets");
  TH1D * h_ZJets_MuonID_Up = (TH1D*)hist_MuonID_Up[3]->Clone("ZJets");
  TH1D * h_SingleTop_MuonID_Up  = (TH1D*)hist_MuonID_Up[4]->Clone("SingleTop");
  TH1D * h_Diboson_MuonID_Up  = (TH1D*)hist_MuonID_Up[5]->Clone("Diboson");
  TH1D * h_QCD_MuonID_Up = (TH1D*)hist_MuonID_Up[6]->Clone("QCD");
  TH1D * h_Tstar_M700_MuonID_Up = (TH1D*)hist_MuonID_Up[7]->Clone("Tstar_M700");
  TH1D * h_Tstar_M800_MuonID_Up = (TH1D*)hist_MuonID_Up[8]->Clone("Tstar_M800");
  TH1D * h_Tstar_M900_MuonID_Up = (TH1D*)hist_MuonID_Up[9]->Clone("Tstar_M900");
  TH1D * h_Tstar_M1000_MuonID_Up = (TH1D*)hist_MuonID_Up[10]->Clone("Tstar_M1000");
  TH1D * h_Tstar_M1100_MuonID_Up = (TH1D*)hist_MuonID_Up[11]->Clone("Tstar_M1100");
  TH1D * h_Tstar_M1200_MuonID_Up = (TH1D*)hist_MuonID_Up[12]->Clone("Tstar_M1200");
  TH1D * h_Tstar_M1300_MuonID_Up = (TH1D*)hist_MuonID_Up[13]->Clone("Tstar_M1300");
  TH1D * h_Tstar_M1400_MuonID_Up = (TH1D*)hist_MuonID_Up[14]->Clone("Tstar_M1400");
  TH1D * h_Tstar_M1500_MuonID_Up = (TH1D*)hist_MuonID_Up[15]->Clone("Tstar_M1500");
  TH1D * h_Tstar_M1600_MuonID_Up = (TH1D*)hist_MuonID_Up[16]->Clone("Tstar_M1600");


 //*************************************************************************************************
TH1F * hist_MuonTrigger_Down[17];
   for (int i=0; i<17; ++i) {
    TFile * file = new TFile(rootDir+Names[11]+"/"+sampleNames[i]+".root");
    hist_MuonTrigger_Down[i] = (TH1F*)file->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
   
    hist_MuonTrigger_Down[i]->Sumw2();
}
  
 // Cloning histograms 
  TH1D * histData_MuonTrigger_Down = (TH1D*)hist_MuonTrigger_Down[0]->Clone("data_obs");
  TH1D * h_TT_MuonTrigger_Down = (TH1D*)hist_MuonTrigger_Down[1]->Clone("TT");
  TH1D * h_WJets_MuonTrigger_Down = (TH1D*)hist_MuonTrigger_Down[2]->Clone("WJets");
  TH1D * h_ZJets_MuonTrigger_Down = (TH1D*)hist_MuonTrigger_Down[3]->Clone("ZJets");
  TH1D * h_SingleTop_MuonTrigger_Down  = (TH1D*)hist_MuonTrigger_Down[4]->Clone("SingleTop");
  TH1D * h_Diboson_MuonTrigger_Down  = (TH1D*)hist_MuonTrigger_Down[5]->Clone("Diboson");
  TH1D * h_QCD_MuonTrigger_Down = (TH1D*)hist_MuonTrigger_Down[6]->Clone("QCD");
  TH1D * h_Tstar_M700_MuonTrigger_Down = (TH1D*)hist_MuonTrigger_Down[7]->Clone("Tstar_M700");
  TH1D * h_Tstar_M800_MuonTrigger_Down = (TH1D*)hist_MuonTrigger_Down[8]->Clone("Tstar_M800");
  TH1D * h_Tstar_M900_MuonTrigger_Down = (TH1D*)hist_MuonTrigger_Down[9]->Clone("Tstar_M900");
  TH1D * h_Tstar_M1000_MuonTrigger_Down = (TH1D*)hist_MuonTrigger_Down[10]->Clone("Tstar_M1000");
  TH1D * h_Tstar_M1100_MuonTrigger_Down = (TH1D*)hist_MuonTrigger_Down[11]->Clone("Tstar_M1100");
  TH1D * h_Tstar_M1200_MuonTrigger_Down = (TH1D*)hist_MuonTrigger_Down[12]->Clone("Tstar_M1200");
  TH1D * h_Tstar_M1300_MuonTrigger_Down = (TH1D*)hist_MuonTrigger_Down[13]->Clone("Tstar_M1300");
  TH1D * h_Tstar_M1400_MuonTrigger_Down = (TH1D*)hist_MuonTrigger_Down[14]->Clone("Tstar_M1400");
  TH1D * h_Tstar_M1500_MuonTrigger_Down = (TH1D*)hist_MuonTrigger_Down[15]->Clone("Tstar_M1500");
  TH1D * h_Tstar_M1600_MuonTrigger_Down = (TH1D*)hist_MuonTrigger_Down[16]->Clone("Tstar_M1600");

 //*************************************************************************************************
TH1F * hist_MuonTrigger_Up[17];
   for (int i=0; i<17; ++i) {
    TFile * file = new TFile(rootDir+Names[12]+"/"+sampleNames[i]+".root");
    hist_MuonTrigger_Up[i] = (TH1F*)file->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
   
    hist_MuonTrigger_Up[i]->Sumw2();
}
  
 // Cloning histograms 
  TH1D * histData_MuonTrigger_Up = (TH1D*)hist_MuonTrigger_Up[0]->Clone("data_obs");
  TH1D * h_TT_MuonTrigger_Up = (TH1D*)hist_MuonTrigger_Up[1]->Clone("TT");
  TH1D * h_WJets_MuonTrigger_Up = (TH1D*)hist_MuonTrigger_Up[2]->Clone("WJets");
  TH1D * h_ZJets_MuonTrigger_Up = (TH1D*)hist_MuonTrigger_Up[3]->Clone("ZJets");
  TH1D * h_SingleTop_MuonTrigger_Up  = (TH1D*)hist_MuonTrigger_Up[4]->Clone("SingleTop");
  TH1D * h_Diboson_MuonTrigger_Up  = (TH1D*)hist_MuonTrigger_Up[5]->Clone("Diboson");
  TH1D * h_QCD_MuonTrigger_Up = (TH1D*)hist_MuonTrigger_Up[6]->Clone("QCD");
  TH1D * h_Tstar_M700_MuonTrigger_Up = (TH1D*)hist_MuonTrigger_Up[7]->Clone("Tstar_M700");
  TH1D * h_Tstar_M800_MuonTrigger_Up = (TH1D*)hist_MuonTrigger_Up[8]->Clone("Tstar_M800");
  TH1D * h_Tstar_M900_MuonTrigger_Up = (TH1D*)hist_MuonTrigger_Up[9]->Clone("Tstar_M900");
  TH1D * h_Tstar_M1000_MuonTrigger_Up = (TH1D*)hist_MuonTrigger_Up[10]->Clone("Tstar_M1000");
  TH1D * h_Tstar_M1100_MuonTrigger_Up = (TH1D*)hist_MuonTrigger_Up[11]->Clone("Tstar_M1100");
  TH1D * h_Tstar_M1200_MuonTrigger_Up = (TH1D*)hist_MuonTrigger_Up[12]->Clone("Tstar_M1200");
  TH1D * h_Tstar_M1300_MuonTrigger_Up = (TH1D*)hist_MuonTrigger_Up[13]->Clone("Tstar_M1300");
  TH1D * h_Tstar_M1400_MuonTrigger_Up = (TH1D*)hist_MuonTrigger_Up[14]->Clone("Tstar_M1400");
  TH1D * h_Tstar_M1500_MuonTrigger_Up = (TH1D*)hist_MuonTrigger_Up[15]->Clone("Tstar_M1500");
  TH1D * h_Tstar_M1600_MuonTrigger_Up = (TH1D*)hist_MuonTrigger_Up[16]->Clone("Tstar_M1600");


 //*************************************************************************************************
TH1F * hist_PU_Down[17];
   for (int i=0; i<17; ++i) {
    TFile * file = new TFile(rootDir+Names[13]+"/"+sampleNames[i]+".root");
    hist_PU_Down[i] = (TH1F*)file->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
   
    hist_PU_Down[i]->Sumw2();
}
  
 // Cloning histograms 
  TH1D * histData_PU_Down = (TH1D*)hist_PU_Down[0]->Clone("data_obs");
  TH1D * h_TT_PU_Down = (TH1D*)hist_PU_Down[1]->Clone("TT");
  TH1D * h_WJets_PU_Down = (TH1D*)hist_PU_Down[2]->Clone("WJets");
  TH1D * h_ZJets_PU_Down = (TH1D*)hist_PU_Down[3]->Clone("ZJets");
  TH1D * h_SingleTop_PU_Down  = (TH1D*)hist_PU_Down[4]->Clone("SingleTop");
  TH1D * h_Diboson_PU_Down  = (TH1D*)hist_PU_Down[5]->Clone("Diboson");
  TH1D * h_QCD_PU_Down = (TH1D*)hist_PU_Down[6]->Clone("QCD");
  TH1D * h_Tstar_M700_PU_Down = (TH1D*)hist_PU_Down[7]->Clone("Tstar_M700");
  TH1D * h_Tstar_M800_PU_Down = (TH1D*)hist_PU_Down[8]->Clone("Tstar_M800");
  TH1D * h_Tstar_M900_PU_Down = (TH1D*)hist_PU_Down[9]->Clone("Tstar_M900");
  TH1D * h_Tstar_M1000_PU_Down = (TH1D*)hist_PU_Down[10]->Clone("Tstar_M1000");
  TH1D * h_Tstar_M1100_PU_Down = (TH1D*)hist_PU_Down[11]->Clone("Tstar_M1100");
  TH1D * h_Tstar_M1200_PU_Down = (TH1D*)hist_PU_Down[12]->Clone("Tstar_M1200");
  TH1D * h_Tstar_M1300_PU_Down = (TH1D*)hist_PU_Down[13]->Clone("Tstar_M1300");
  TH1D * h_Tstar_M1400_PU_Down = (TH1D*)hist_PU_Down[14]->Clone("Tstar_M1400");
  TH1D * h_Tstar_M1500_PU_Down = (TH1D*)hist_PU_Down[15]->Clone("Tstar_M1500");
  TH1D * h_Tstar_M1600_PU_Down = (TH1D*)hist_PU_Down[16]->Clone("Tstar_M1600");

 //*************************************************************************************************
TH1F * hist_PU_Up[17];
   for (int i=0; i<17; ++i) {
    TFile * file = new TFile(rootDir+Names[14]+"/"+sampleNames[i]+".root");
    hist_PU_Up[i] = (TH1F*)file->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
   
    hist_PU_Up[i]->Sumw2();
}
  
 // Cloning histograms 
  TH1D * histData_PU_Up = (TH1D*)hist_PU_Up[0]->Clone("data_obs");
  TH1D * h_TT_PU_Up = (TH1D*)hist_PU_Up[1]->Clone("TT");
  TH1D * h_WJets_PU_Up = (TH1D*)hist_PU_Up[2]->Clone("WJets");
  TH1D * h_ZJets_PU_Up = (TH1D*)hist_PU_Up[3]->Clone("ZJets");
  TH1D * h_SingleTop_PU_Up  = (TH1D*)hist_PU_Up[4]->Clone("SingleTop");
  TH1D * h_Diboson_PU_Up  = (TH1D*)hist_PU_Up[5]->Clone("Diboson");
  TH1D * h_QCD_PU_Up = (TH1D*)hist_PU_Up[6]->Clone("QCD");
  TH1D * h_Tstar_M700_PU_Up = (TH1D*)hist_PU_Up[7]->Clone("Tstar_M700");
  TH1D * h_Tstar_M800_PU_Up = (TH1D*)hist_PU_Up[8]->Clone("Tstar_M800");
  TH1D * h_Tstar_M900_PU_Up = (TH1D*)hist_PU_Up[9]->Clone("Tstar_M900");
  TH1D * h_Tstar_M1000_PU_Up = (TH1D*)hist_PU_Up[10]->Clone("Tstar_M1000");
  TH1D * h_Tstar_M1100_PU_Up = (TH1D*)hist_PU_Up[11]->Clone("Tstar_M1100");
  TH1D * h_Tstar_M1200_PU_Up = (TH1D*)hist_PU_Up[12]->Clone("Tstar_M1200");
  TH1D * h_Tstar_M1300_PU_Up = (TH1D*)hist_PU_Up[13]->Clone("Tstar_M1300");
  TH1D * h_Tstar_M1400_PU_Up = (TH1D*)hist_PU_Up[14]->Clone("Tstar_M1400");
  TH1D * h_Tstar_M1500_PU_Up = (TH1D*)hist_PU_Up[15]->Clone("Tstar_M1500");
  TH1D * h_Tstar_M1600_PU_Up = (TH1D*)hist_PU_Up[16]->Clone("Tstar_M1600");
  cout<<"Hello"<<endl;
TH1F * hist_PDF_Up[4];
   for (int i=1; i<5; ++i) {
    TFile * file = new TFile(rootDir+Names[15]+"/"+sampleNames[i]+".root");
    hist_PDF_Up[i-1] = (TH1F*)file->Get("Mass_Tstar");
   
    hist_PDF_Up[i-1]->Sumw2();
}

 // Cloning histograms 
 // TH1D * histData_PDF_Up = (TH1D*)hist_PDF_Up[0]->Clone("data_obs");
  TH1D * h_TT_PDF_Up = (TH1D*)hist_PDF_Up[0]->Clone("TT");
  TH1D * h_WJets_PDF_Up = (TH1D*)hist_PDF_Up[1]->Clone("WJets");
  TH1D * h_ZJets_PDF_Up = (TH1D*)hist_PDF_Up[2]->Clone("ZJets");
  TH1D * h_SingleTop_PDF_Up  = (TH1D*)hist_PDF_Up[3]->Clone("SingleTop");

  //*******************************************************************************************
TH1F * hist_PDF_Down[4];
   for (int i=1; i<5; ++i) {
    TFile * file = new TFile(rootDir+Names[16]+"/"+sampleNames[i]+".root");
    hist_PDF_Down[i-1] = (TH1F*)file->Get("Mass_Tstar");
   
    hist_PDF_Down[i-1]->Sumw2();
}

 // Cloning histograms 
 // TH1D * histData_PDF_Down = (TH1D*)hist_PDF_Down[0]->Clone("data_obs");
  TH1D * h_TT_PDF_Down = (TH1D*)hist_PDF_Down[0]->Clone("TT");
  TH1D * h_WJets_PDF_Down = (TH1D*)hist_PDF_Down[1]->Clone("WJets");
  TH1D * h_ZJets_PDF_Down = (TH1D*)hist_PDF_Down[2]->Clone("ZJets");
  TH1D * h_SingleTop_PDF_Down  = (TH1D*)hist_PDF_Down[3]->Clone("SingleTop");

  //*******************************************************************************************

TH1F * hist_Scale_Up[2];
   for (int i=1; i<3; ++i) {
    TFile * file = new TFile(rootDir+Names[17]+"/"+sampleNames[i]+".root");
    hist_Scale_Up[i-1] = (TH1F*)file->Get("Mass_Tstar_up");
   
    hist_Scale_Up[i-1]->Sumw2();
}  

 // Cloning histograms 
 // TH1D * histData_Scale_Up = (TH1D*)hist_Scale_Up[0]->Clone("data_obs");
  TH1D * h_TT_Scale_Up = (TH1D*)hist_Scale_Up[0]->Clone("TT");
  TH1D * h_WJets_Scale_Up = (TH1D*)hist_Scale_Up[1]->Clone("WJets");

  //*******************************************************************************************
    cout<<"Hello1"<<endl;
TH1F * hist_Scale_Down[2];
   for (int i=1; i<3; ++i) {
    TFile * file = new TFile(rootDir+Names[18]+"/"+sampleNames[i]+".root");
    hist_Scale_Down[i-1] = (TH1F*)file->Get("Mass_TStar_dn");
   
    hist_Scale_Down[i-1]->Sumw2();
}

 // Cloning histograms 
 // TH1D * histData_Scale_Down = (TH1D*)hist_Scale_Down[0]->Clone("data_obs");
  TH1D * h_TT_Scale_Down = (TH1D*)hist_Scale_Down[0]->Clone("TT");
  TH1D * h_WJets_Scale_Down = (TH1D*)hist_Scale_Down[1]->Clone("WJets");

  // ******************************************
    // for further statistical analysis with the Higgs combination software
 TString BaseName = "datacards.txt";
 /*
  TString rootFileName_bkg = "datacards_bkg.root";
  TFile * fileInputs_bkg = new TFile(rootFileName_bkg,"recreate"); 
  TDirectory *mTstar_bkg    = fileInputs_bkg->mkdir("mTstar");

  mTstar_bkg->cd();
  histData->Write("data_obs");
  histData_bTag_bc_Down->Write("data_obs_CMS_bTag_bc_Down");
  histData_bTag_bc_Up->Write("data_obs_CMS_bTag_bc_Up");
  histData_bTag_udsg_Up->Write("data_obs_CMS_bTag_udsg_bc_Up");
  histData_bTag_udsg_Down->Write("data_obs_CMS_bTag_udsg_bc_Down");
  histData_JEC_Down->Write("data_obs_CMS_JEC_Down");
  histData_JEC_Up->Write("data_obs_CMS_JEC_Up");
  histData_JER_Down->Write("data_obs_CMS_JER_Down");
  histData_JER_Up->Write("data_obs_CMS_JER_Up");
  histData_MuonID_Down->Write("data_obs_CMS_MuonID_Down");
  histData_MuonID_Up->Write("data_obs_CMS_MuonID_Up");
  histData_MuonTrigger_Down->Write("data_obs_CMS_MuonTrigger_Down");
  histData_MuonTrigger_Up->Write("data_obs_CMS_MuonTrigger_Up");
  histData_PU_Down->Write("data_obs_CMS_PU_Down");
  histData_PU_Up->Write("data_obs_CMS_PU_Up");

 //TTbar->cd(); 
 h_TT->Write("TT");
  h_TT_bTag_bc_Down->Write("TT_CMS_bTag_bc_Down");
  h_TT_bTag_bc_Up->Write("TT_CMS_bTag_bc_Up");
  h_TT_bTag_udsg_Up->Write("TT_CMS_bTag_udsg_bc_Up");
  h_TT_bTag_udsg_Down->Write("TT_CMS_bTag_udsg_bc_Down");
  h_TT_JEC_Down->Write("TT_CMS_JEC_Down");
  h_TT_JEC_Up->Write("TT_CMS_JEC_Up");
  h_TT_JER_Down->Write("TT_CMS_JER_Down");
  h_TT_JER_Up->Write("TT_CMS_JER_Up");
  h_TT_MuonID_Down->Write("TT_CMS_MuonID_Down");
  h_TT_MuonID_Up->Write("TT_CMS_MuonID_Up");
  h_TT_MuonTrigger_Down->Write("TT_CMS_MuonTrigger_Down");
  h_TT_MuonTrigger_Up->Write("TT_CMS_MuonTrigger_Up");
  h_TT_PU_Down->Write("TT_CMS_PU_Down");
  h_TT_PU_Up->Write("TT_CMS_PU_Up");
  h_TT_Scale_Up->Write("TT_CMS_Scale_Up");
  h_TT_Scale_Down->Write("TT_CMS_Scale_Down");
  h_TT_PDF_Up->Write("TT_CMS_PDF_Up");
  h_TT_PDF_Down->Write("TT_CMS_PDF_Down");

  //  QCD->cd();
 h_QCD->Write("QCD");
  h_QCD_bTag_bc_Down->Write("QCD_CMS_bTag_bc_Down");
  h_QCD_bTag_bc_Up->Write("QCD_CMS_bTag_bc_Up");
  h_QCD_bTag_udsg_Up->Write("QCD_CMS_bTag_udsg_bc_Up");
  h_QCD_bTag_udsg_Down->Write("QCD_CMS_bTag_udsg_bc_Down");
  h_QCD_JEC_Down->Write("QCD_CMS_JEC_Down");
  h_QCD_JEC_Up->Write("QCD_CMS_JEC_Up");
  h_QCD_JER_Down->Write("QCD_CMS_JER_Down");
  h_QCD_JER_Up->Write("QCD_CMS_JER_Up");
  h_QCD_MuonID_Down->Write("QCD_CMS_MuonID_Down");
  h_QCD_MuonID_Up->Write("QCD_CMS_MuonID_Up");
  h_QCD_MuonTrigger_Down->Write("QCD_CMS_MuonTrigger_Down");
  h_QCD_MuonTrigger_Up->Write("QCD_CMS_MuonTrigger_Up");
  h_QCD_PU_Down->Write("QCD_CMS_PU_Down");
  h_QCD_PU_Up->Write("QCD_CMS_PU_Up");

  // WJets->cd();
 h_WJets->Write("WJets");
  h_WJets_bTag_bc_Down->Write("WJets_CMS_bTag_bc_Down");
  h_WJets_bTag_bc_Up->Write("WJets_CMS_bTag_bc_Up");
  h_WJets_bTag_udsg_Up->Write("WJets_CMS_bTag_udsg_bc_Up");
  h_WJets_bTag_udsg_Down->Write("WJets_CMS_bTag_udsg_bc_Down");
  h_WJets_JEC_Down->Write("WJets_CMS_JEC_Down");
  h_WJets_JEC_Up->Write("WJets_CMS_JEC_Up");
  h_WJets_JER_Down->Write("WJets_CMS_JER_Down");
  h_WJets_JER_Up->Write("WJets_CMS_JER_Up");
  h_WJets_MuonID_Down->Write("WJets_CMS_MuonID_Down");
  h_WJets_MuonID_Up->Write("WJets_CMS_MuonID_Up");
  h_WJets_MuonTrigger_Down->Write("WJets_CMS_MuonTrigger_Down");
  h_WJets_MuonTrigger_Up->Write("WJets_CMS_MuonTrigger_Up");
  h_WJets_PU_Down->Write("WJets_CMS_PU_Down");
  h_WJets_PU_Up->Write("WJets_CMS_PU_Up");
  h_WJets_Scale_Up->Write("WJets_CMS_Scale_Up");
  h_WJets_Scale_Down->Write("WJets_CMS_Scale_Down");
  h_WJets_PDF_Up->Write("WJets_CMS_PDF_Up");
  h_WJets_PDF_Down->Write("WJets_CMS_PDF_Down");

  // ZJets->cd();
 h_ZJets->Write("ZJets");
  h_ZJets_bTag_bc_Down->Write("ZJets_CMS_bTag_bc_Down");
  h_ZJets_bTag_bc_Up->Write("ZJets_CMS_bTag_bc_Up");
  h_ZJets_bTag_udsg_Up->Write("ZJets_CMS_bTag_udsg_bc_Up");
  h_ZJets_bTag_udsg_Down->Write("ZJets_CMS_bTag_udsg_bc_Down");
  h_ZJets_JEC_Down->Write("ZJets_CMS_JEC_Down");
  h_ZJets_JEC_Up->Write("ZJets_CMS_JEC_Up");
  h_ZJets_JER_Down->Write("ZJets_CMS_JER_Down");
  h_ZJets_JER_Up->Write("ZJets_CMS_JER_Up");
  h_ZJets_MuonID_Down->Write("ZJets_CMS_MuonID_Down");
  h_ZJets_MuonID_Up->Write("ZJets_CMS_MuonID_Up");
  h_ZJets_MuonTrigger_Down->Write("ZJets_CMS_MuonTrigger_Down");
  h_ZJets_MuonTrigger_Up->Write("ZJets_CMS_MuonTrigger_Up");
  h_ZJets_PU_Down->Write("ZJets_CMS_PU_Down");
  h_ZJets_PU_Up->Write("ZJets_CMS_PU_Up");
  h_ZJets_PDF_Up->Write("ZJets_CMS_PDF_Up");
  h_ZJets_PDF_Down->Write("ZJets_CMS_PDF_Down");

  //SingleTop->cd();
h_SingleTop->Write("SingleTop");
  h_SingleTop_bTag_bc_Down->Write("SingleTop_CMS_bTag_bc_Down");
  h_SingleTop_bTag_bc_Up->Write("SingleTop_CMS_bTag_bc_Up");
  h_SingleTop_bTag_udsg_Up->Write("SingleTop_CMS_bTag_udsg_bc_Up");
  h_SingleTop_bTag_udsg_Down->Write("SingleTop_CMS_bTag_udsg_bc_Down");
  h_SingleTop_JEC_Down->Write("SingleTop_CMS_JEC_Down");
  h_SingleTop_JEC_Up->Write("SingleTop_CMS_JEC_Up");
  h_SingleTop_JER_Down->Write("SingleTop_CMS_JER_Down");
  h_SingleTop_JER_Up->Write("SingleTop_CMS_JER_Up");
  h_SingleTop_MuonID_Down->Write("SingleTop_CMS_MuonID_Down");
  h_SingleTop_MuonID_Up->Write("SingleTop_CMS_MuonID_Up");
  h_SingleTop_MuonTrigger_Down->Write("SingleTop_CMS_MuonTrigger_Down");
  h_SingleTop_MuonTrigger_Up->Write("SingleTop_CMS_MuonTrigger_Up");
  h_SingleTop_PU_Down->Write("SingleTop_CMS_PU_Down");
  h_SingleTop_PU_Up->Write("SingleTop_CMS_PU_Up");
  h_SingleTop_PDF_Up->Write("SingleTop_CMS_PDF_Up");
  h_SingleTop_PDF_Down->Write("SingleTop_CMS_PDF_Down");


  // Diboson->cd();
h_Diboson->Write("Diboson");
  h_Diboson_bTag_bc_Down->Write("Diboson_CMS_bTag_bc_Down");
  h_Diboson_bTag_bc_Up->Write("Diboson_CMS_bTag_bc_Up");
  h_Diboson_bTag_udsg_Up->Write("Diboson_CMS_bTag_udsg_bc_Up");
  h_Diboson_bTag_udsg_Down->Write("Diboson_CMS_bTag_udsg_bc_Down");
  h_Diboson_JEC_Down->Write("Diboson_CMS_JEC_Down");
  h_Diboson_JEC_Up->Write("Diboson_CMS_JEC_Up");
  h_Diboson_JER_Down->Write("Diboson_CMS_JER_Down");
  h_Diboson_JER_Up->Write("Diboson_CMS_JER_Up");
  h_Diboson_MuonID_Down->Write("Diboson_CMS_MuonID_Down");
  h_Diboson_MuonID_Up->Write("Diboson_CMS_MuonID_Up");
  h_Diboson_MuonTrigger_Down->Write("Diboson_CMS_MuonTrigger_Down");
  h_Diboson_MuonTrigger_Up->Write("Diboson_CMS_MuonTrigger_Up");
  h_Diboson_PU_Down->Write("Diboson_CMS_PU_Down");
  h_Diboson_PU_Up->Write("Diboson_CMS_PU_Up");

 fileInputs_bkg->Close();

   TString rootFileName_signal = "datacards_signal.root";
  TFile * fileInputs_signal = new TFile(rootFileName_signal,"recreate"); 
  TDirectory *mTstar_sig    = fileInputs_signal->mkdir("mTstar");
  mTstar_sig->cd();
  //Tstar_700->cd();
  h_Tstar_M700->Write("Tstar_M700");
  h_Tstar_M700_bTag_bc_Down->Write("Tstar_M700_CMS_bTag_bc_Down");
  h_Tstar_M700_bTag_bc_Up->Write("Tstar_M700_CMS_bTag_bc_Up");
  h_Tstar_M700_bTag_udsg_Up->Write("Tstar_M700_CMS_bTag_udsg_bc_Up");
  h_Tstar_M700_bTag_udsg_Down->Write("Tstar_M700_CMS_bTag_udsg_bc_Down");
  h_Tstar_M700_JEC_Down->Write("Tstar_M700_CMS_JEC_Down");
  h_Tstar_M700_JEC_Up->Write("Tstar_M700_CMS_JEC_Up");
  h_Tstar_M700_JER_Down->Write("Tstar_M700_CMS_JER_Down");
  h_Tstar_M700_JER_Up->Write("Tstar_M700_CMS_JER_Up");
  h_Tstar_M700_MuonID_Down->Write("Tstar_M700_CMS_MuonID_Down");
  h_Tstar_M700_MuonID_Up->Write("Tstar_M700_CMS_MuonID_Up");
  h_Tstar_M700_MuonTrigger_Down->Write("Tstar_M700_CMS_MuonTrigger_Down");
  h_Tstar_M700_MuonTrigger_Up->Write("Tstar_M700_CMS_MuonTrigger_Up");
  h_Tstar_M700_PU_Down->Write("Tstar_M700_CMS_PU_Down");
  h_Tstar_M700_PU_Up->Write("Tstar_M700_CMS_PU_Up");

  //Tstar_800->cd();
 h_Tstar_M800->Write("Tstar_M800");
  h_Tstar_M800_bTag_bc_Down->Write("Tstar_M800_CMS_bTag_bc_Down");
  h_Tstar_M800_bTag_bc_Up->Write("Tstar_M800_CMS_bTag_bc_Up");
  h_Tstar_M800_bTag_udsg_Up->Write("Tstar_M800_CMS_bTag_udsg_bc_Up");
  h_Tstar_M800_bTag_udsg_Down->Write("Tstar_M800_CMS_bTag_udsg_bc_Down");
  h_Tstar_M800_JEC_Down->Write("Tstar_M800_CMS_JEC_Down");
  h_Tstar_M800_JEC_Up->Write("Tstar_M800_CMS_JEC_Up");
  h_Tstar_M800_JER_Down->Write("Tstar_M800_CMS_JER_Down");
  h_Tstar_M800_JER_Up->Write("Tstar_M800_CMS_JER_Up");
  h_Tstar_M800_MuonID_Down->Write("Tstar_M800_CMS_MuonID_Down");
  h_Tstar_M800_MuonID_Up->Write("Tstar_M800_CMS_MuonID_Up");
  h_Tstar_M800_MuonTrigger_Down->Write("Tstar_M800_CMS_MuonTrigger_Down");
  h_Tstar_M800_MuonTrigger_Up->Write("Tstar_M800_CMS_MuonTrigger_Up");
  h_Tstar_M800_PU_Down->Write("Tstar_M800_CMS_PU_Down");
  h_Tstar_M800_PU_Up->Write("Tstar_M800_CMS_PU_Up");

  //Tstar_900->cd();
 h_Tstar_M900->Write("Tstar_M900");
  h_Tstar_M900_bTag_bc_Down->Write("Tstar_M900_CMS_bTag_bc_Down");
  h_Tstar_M900_bTag_bc_Up->Write("Tstar_M900_CMS_bTag_bc_Up");
  h_Tstar_M900_bTag_udsg_Up->Write("Tstar_M900_CMS_bTag_udsg_bc_Up");
  h_Tstar_M900_bTag_udsg_Down->Write("Tstar_M900_CMS_bTag_udsg_bc_Down");
  h_Tstar_M900_JEC_Down->Write("Tstar_M900_CMS_JEC_Down");
  h_Tstar_M900_JEC_Up->Write("Tstar_M900_CMS_JEC_Up");
  h_Tstar_M900_JER_Down->Write("Tstar_M900_CMS_JER_Down");
  h_Tstar_M900_JER_Up->Write("Tstar_M900_CMS_JER_Up");
  h_Tstar_M900_MuonID_Down->Write("Tstar_M900_CMS_MuonID_Down");
  h_Tstar_M900_MuonID_Up->Write("Tstar_M900_CMS_MuonID_Up");
  h_Tstar_M900_MuonTrigger_Down->Write("Tstar_M900_CMS_MuonTrigger_Down");
  h_Tstar_M900_MuonTrigger_Up->Write("Tstar_M900_CMS_MuonTrigger_Up");
  h_Tstar_M900_PU_Down->Write("Tstar_M900_CMS_PU_Down");
  h_Tstar_M900_PU_Up->Write("Tstar_M900_CMS_PU_Up");


  //Tstar_1000->cd();
 h_Tstar_M1000->Write("Tstar_M1000");
  h_Tstar_M1000_bTag_bc_Down->Write("Tstar_M1000_CMS_bTag_bc_Down");
  h_Tstar_M1000_bTag_bc_Up->Write("Tstar_M1000_CMS_bTag_bc_Up");
  h_Tstar_M1000_bTag_udsg_Up->Write("Tstar_M1000_CMS_bTag_udsg_bc_Up");
  h_Tstar_M1000_bTag_udsg_Down->Write("Tstar_M1000_CMS_bTag_udsg_bc_Down");
  h_Tstar_M1000_JEC_Down->Write("Tstar_M1000_CMS_JEC_Down");
  h_Tstar_M1000_JEC_Up->Write("Tstar_M1000_CMS_JEC_Up");
  h_Tstar_M1000_JER_Down->Write("Tstar_M1000_CMS_JER_Down");
  h_Tstar_M1000_JER_Up->Write("Tstar_M1000_CMS_JER_Up");
  h_Tstar_M1000_MuonID_Down->Write("Tstar_M1000_CMS_MuonID_Down");
  h_Tstar_M1000_MuonID_Up->Write("Tstar_M1000_CMS_MuonID_Up");
  h_Tstar_M1000_MuonTrigger_Down->Write("Tstar_M1000_CMS_MuonTrigger_Down");
  h_Tstar_M1000_MuonTrigger_Up->Write("Tstar_M1000_CMS_MuonTrigger_Up");
  h_Tstar_M1000_PU_Down->Write("Tstar_M1000_CMS_PU_Down");
  h_Tstar_M1000_PU_Up->Write("Tstar_M1000_CMS_PU_Up");

  //Tstar_1100->cd();
 h_Tstar_M1100->Write("Tstar_M1100");
  h_Tstar_M1100_bTag_bc_Down->Write("Tstar_M1100_CMS_bTag_bc_Down");
  h_Tstar_M1100_bTag_bc_Up->Write("Tstar_M1100_CMS_bTag_bc_Up");
  h_Tstar_M1100_bTag_udsg_Up->Write("Tstar_M1100_CMS_bTag_udsg_bc_Up");
  h_Tstar_M1100_bTag_udsg_Down->Write("Tstar_M1100_CMS_bTag_udsg_bc_Down");
  h_Tstar_M1100_JEC_Down->Write("Tstar_M1100_CMS_JEC_Down");
  h_Tstar_M1100_JEC_Up->Write("Tstar_M1100_CMS_JEC_Up");
  h_Tstar_M1100_JER_Down->Write("Tstar_M1100_CMS_JER_Down");
  h_Tstar_M1100_JER_Up->Write("Tstar_M1100_CMS_JER_Up");
  h_Tstar_M1100_MuonID_Down->Write("Tstar_M1100_CMS_MuonID_Down");
  h_Tstar_M1100_MuonID_Up->Write("Tstar_M1100_CMS_MuonID_Up");
  h_Tstar_M1100_MuonTrigger_Down->Write("Tstar_M1100_CMS_MuonTrigger_Down");
  h_Tstar_M1100_MuonTrigger_Up->Write("Tstar_M1100_CMS_MuonTrigger_Up");
  h_Tstar_M1100_PU_Down->Write("Tstar_M1100_CMS_PU_Down");
  h_Tstar_M1100_PU_Up->Write("Tstar_M1100_CMS_PU_Up");


  //Tstar_1200->cd();
h_Tstar_M1200->Write("Tstar_M1200");
  h_Tstar_M1200_bTag_bc_Down->Write("Tstar_M1200_CMS_bTag_bc_Down");
  h_Tstar_M1200_bTag_bc_Up->Write("Tstar_M1200_CMS_bTag_bc_Up");
  h_Tstar_M1200_bTag_udsg_Up->Write("Tstar_M1200_CMS_bTag_udsg_bc_Up");
  h_Tstar_M1200_bTag_udsg_Down->Write("Tstar_M1200_CMS_bTag_udsg_bc_Down");
  h_Tstar_M1200_JEC_Down->Write("Tstar_M1200_CMS_JEC_Down");
  h_Tstar_M1200_JEC_Up->Write("Tstar_M1200_CMS_JEC_Up");
  h_Tstar_M1200_JER_Down->Write("Tstar_M1200_CMS_JER_Down");
  h_Tstar_M1200_JER_Up->Write("Tstar_M1200_CMS_JER_Up");
  h_Tstar_M1200_MuonID_Down->Write("Tstar_M1200_CMS_MuonID_Down");
  h_Tstar_M1200_MuonID_Up->Write("Tstar_M1200_CMS_MuonID_Up");
  h_Tstar_M1200_MuonTrigger_Down->Write("Tstar_M1200_CMS_MuonTrigger_Down");
  h_Tstar_M1200_MuonTrigger_Up->Write("Tstar_M1200_CMS_MuonTrigger_Up");
  h_Tstar_M1200_PU_Down->Write("Tstar_M1200_CMS_PU_Down");
  h_Tstar_M1200_PU_Up->Write("Tstar_M1200_CMS_PU_Up");


  //Tstar_1300->cd();
h_Tstar_M1300->Write("Tstar_M1300");
  h_Tstar_M1300_bTag_bc_Down->Write("Tstar_M1300_CMS_bTag_bc_Down");
  h_Tstar_M1300_bTag_bc_Up->Write("Tstar_M1300_CMS_bTag_bc_Up");
  h_Tstar_M1300_bTag_udsg_Up->Write("Tstar_M1300_CMS_bTag_udsg_bc_Up");
  h_Tstar_M1300_bTag_udsg_Down->Write("Tstar_M1300_CMS_bTag_udsg_bc_Down");
  h_Tstar_M1300_JEC_Down->Write("Tstar_M1300_CMS_JEC_Down");
  h_Tstar_M1300_JEC_Up->Write("Tstar_M1300_CMS_JEC_Up");
  h_Tstar_M1300_JER_Down->Write("Tstar_M1300_CMS_JER_Down");
  h_Tstar_M1300_JER_Up->Write("Tstar_M1300_CMS_JER_Up");
  h_Tstar_M1300_MuonID_Down->Write("Tstar_M1300_CMS_MuonID_Down");
  h_Tstar_M1300_MuonID_Up->Write("Tstar_M1300_CMS_MuonID_Up");
  h_Tstar_M1300_MuonTrigger_Down->Write("Tstar_M1300_CMS_MuonTrigger_Down");
  h_Tstar_M1300_MuonTrigger_Up->Write("Tstar_M1300_CMS_MuonTrigger_Up");
  h_Tstar_M1300_PU_Down->Write("Tstar_M1300_CMS_PU_Down");
  h_Tstar_M1300_PU_Up->Write("Tstar_M1300_CMS_PU_Up");


  //Tstar_1400->cd();
h_Tstar_M1400->Write("Tstar_M1400");
  h_Tstar_M1400_bTag_bc_Down->Write("Tstar_M1400_CMS_bTag_bc_Down");
  h_Tstar_M1400_bTag_bc_Up->Write("Tstar_M1400_CMS_bTag_bc_Up");
  h_Tstar_M1400_bTag_udsg_Up->Write("Tstar_M1400_CMS_bTag_udsg_bc_Up");
  h_Tstar_M1400_bTag_udsg_Down->Write("Tstar_M1400_CMS_bTag_udsg_bc_Down");
  h_Tstar_M1400_JEC_Down->Write("Tstar_M1400_CMS_JEC_Down");
  h_Tstar_M1400_JEC_Up->Write("Tstar_M1400_CMS_JEC_Up");
  h_Tstar_M1400_JER_Down->Write("Tstar_M1400_CMS_JER_Down");
  h_Tstar_M1400_JER_Up->Write("Tstar_M1400_CMS_JER_Up");
  h_Tstar_M1400_MuonID_Down->Write("Tstar_M1400_CMS_MuonID_Down");
  h_Tstar_M1400_MuonID_Up->Write("Tstar_M1400_CMS_MuonID_Up");
  h_Tstar_M1400_MuonTrigger_Down->Write("Tstar_M1400_CMS_MuonTrigger_Down");
  h_Tstar_M1400_MuonTrigger_Up->Write("Tstar_M1400_CMS_MuonTrigger_Up");
  h_Tstar_M1400_PU_Down->Write("Tstar_M1400_CMS_PU_Down");
  h_Tstar_M1400_PU_Up->Write("Tstar_M1400_CMS_PU_Up");

  // Tstar_1500->cd();
h_Tstar_M1500->Write("Tstar_M1500");
  h_Tstar_M1500_bTag_bc_Down->Write("Tstar_M1500_CMS_bTag_bc_Down");
  h_Tstar_M1500_bTag_bc_Up->Write("Tstar_M1500_CMS_bTag_bc_Up");
  h_Tstar_M1500_bTag_udsg_Up->Write("Tstar_M1500_CMS_bTag_udsg_bc_Up");
  h_Tstar_M1500_bTag_udsg_Down->Write("Tstar_M1500_CMS_bTag_udsg_bc_Down");
  h_Tstar_M1500_JEC_Down->Write("Tstar_M1500_CMS_JEC_Down");
  h_Tstar_M1500_JEC_Up->Write("Tstar_M1500_CMS_JEC_Up");
  h_Tstar_M1500_JER_Down->Write("Tstar_M1500_CMS_JER_Down");
  h_Tstar_M1500_JER_Up->Write("Tstar_M1500_CMS_JER_Up");
  h_Tstar_M1500_MuonID_Down->Write("Tstar_M1500_CMS_MuonID_Down");
  h_Tstar_M1500_MuonID_Up->Write("Tstar_M1500_CMS_MuonID_Up");
  h_Tstar_M1500_MuonTrigger_Down->Write("Tstar_M1500_CMS_MuonTrigger_Down");
  h_Tstar_M1500_MuonTrigger_Up->Write("Tstar_M1500_CMS_MuonTrigger_Up");
  h_Tstar_M1500_PU_Down->Write("Tstar_M1500_CMS_PU_Down");
  h_Tstar_M1500_PU_Up->Write("Tstar_M1500_CMS_PU_Up");

  //Tstar_1600->cd();
h_Tstar_M1600->Write("Tstar_M1600");
  h_Tstar_M1600_bTag_bc_Down->Write("Tstar_M1600_CMS_bTag_bc_Down");
  h_Tstar_M1600_bTag_bc_Up->Write("Tstar_M1600_CMS_bTag_bc_Up");
  h_Tstar_M1600_bTag_udsg_Up->Write("Tstar_M1600_CMS_bTag_udsg_bc_Up");
  h_Tstar_M1600_bTag_udsg_Down->Write("Tstar_M1600_CMS_bTag_udsg_bc_Down");
  h_Tstar_M1600_JEC_Down->Write("Tstar_M1600_CMS_JEC_Down");
  h_Tstar_M1600_JEC_Up->Write("Tstar_M1600_CMS_JEC_Up");
  h_Tstar_M1600_JER_Down->Write("Tstar_M1600_CMS_JER_Down");
  h_Tstar_M1600_JER_Up->Write("Tstar_M1600_CMS_JER_Up");
  h_Tstar_M1600_MuonID_Down->Write("Tstar_M1600_CMS_MuonID_Down");
  h_Tstar_M1600_MuonID_Up->Write("Tstar_M1600_CMS_MuonID_Up");
  h_Tstar_M1600_MuonTrigger_Down->Write("Tstar_M1600_CMS_MuonTrigger_Down");
  h_Tstar_M1600_MuonTrigger_Up->Write("Tstar_M1600_CMS_MuonTrigger_Up");
  h_Tstar_M1600_PU_Down->Write("Tstar_M1600_CMS_PU_Down");
  h_Tstar_M1600_PU_Up->Write("Tstar_M1600_CMS_PU_Up");

 

  fileInputs_signal->Close();
 */




  //********************************* SETUP DATACARD.TXT ************************************************************************************
  ostringstream str;
  str << BaseName;
  string nn = str.str();
  const char * p = nn.c_str();

  std::ofstream textFile(p);
  textFile << "imax 1   number of channels" << std::endl;
  textFile << "jmax *   number of backgrounds" << std::endl;
  textFile << "kmax *   number of nuisance parameters" << std::endl;
  textFile << "-----------------" << std::endl;
  textFile << "bin            mTstar                                                                         "  << std::endl;
  textFile << "observation "<< -1  << std::endl;
  textFile << "-----------------" << std::endl;
  textFile << "shapes * * datacards.root cms_workspace:$PROCESS"                           << std::endl;
   textFile << "---------------------------------------------------------------------------------------------"  << std::endl;
  textFile << "bin                          mTstar      mTstar                                               "  << std::endl;
  textFile << "process                      Tstar_800   expo                                             "  << std::endl;
  textFile << "process                      0           1                                                    "  << std::endl;
  textFile << "rate     "
           << "                        " << h_Tstar_M700->GetSumOfWeights() << "   2395                    "  << std::endl;
  textFile << "----------------------------------------------------------------------------------------------"  << std::endl;
  
  textFile << "CMS_bTag_bc           lnN    1.02     -                                                       "  << std::endl;
  textFile << "CMS_bTag_udsg_bc      lnN    1.05     -                                                       "  << std::endl;
  textFile << "CMS_JEC               lnN    1.76     -                                                       "  << std::endl;
  textFile << "CMS_JER               lnN    1.05     -                                                       "  << std::endl;
  textFile << "CMS_MuonID            lnN    1.02     -                                                       "  << std::endl;
  textFile << "CMS_MuonTrigger       lnN    1.01     -                                                       "  << std::endl;
  textFile << "CMS_PU                lnN    1.03     -                                                       "  << std::endl;
  textFile << "lumi_13TeV            lnN   1.027     -                                                       "  << std::endl;
  textFile << "----------------------------------------------------------------------------------------------"  << std::endl;
  textFile << "norm                  param   3477.4   542                                                    "  << std::endl;
  textFile << "lambda                param  -0.00494  0.00019                                                   "  << std::endl;
  textFile << "gaus_mean_800         param  658.89    16.3                                                      "  << std::endl;
  textFile << "gaus_sigma_800        param  127.5     83                                                        "  << std::endl;
  textFile << "land_mean_800         param  999.58    15                                                        "  << std::endl;
  textFile << "land_sigma_800        param  115      25.8                                                       "  << std::endl;
  textFile << std::endl;

  // *******************************************
 }
