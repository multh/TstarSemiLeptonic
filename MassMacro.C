//MassMacro.C


//***************************************************************************************
//
//Small Macro for Signal Shapes Normalized to Integral and showed in one Canvas
//
//****************************************************************************************



void MassMacro() {
 // open a file and get a histogram

const int n_sig = 3;

const TString  signal_name[n_sig] = {"Tstar_M-700", "Tstar_M-900", "Tstar_M-1600"};

TString  File_Dir = "/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Nominal/03Feb2017_Relaunch_17Jan2018/Muons/Changed_Reco/";
TString  Hist_Dir = "chi2min__HypHists/";

TH1F * h_Tstarhad[n_sig];
TH1F * h_Tstarlep[n_sig];

for(int i =0; i<n_sig; i++){
TFile *  signal = new TFile(File_Dir + "uhh2.AnalysisModuleRunner.MC." + signal_name[i] + ".root");

 h_Tstarhad[i] = (TH1F*)signal->Get(Hist_Dir + "M_Tstarhad_rec");
 h_Tstarlep[i] = (TH1F*)signal->Get(Hist_Dir + "M_Tstarlep_rec");


}


 gStyle->SetOptStat(0);
 int bin_up = 730;
 int bin_down = 610;

TLegend * leg = new TLegend(0.1,0.7,0.48,0.9);

TCanvas* c1= new TCanvas("c1","c1",bin_up,bin_down);
for(int i = 0; i<n_sig; i++){

  h_Tstarhad[i]->Scale(1./(h_Tstarhad[i]->Integral()));
  h_Tstarhad[i]->SetTitle("");
  h_Tstarhad[i]->SetLineColor(kRed + 2*i);
  h_Tstarhad[i]->GetXaxis()->SetTitle("M_{T*}^{had} [GeV]");

leg->AddEntry(h_Tstarhad[i], "T* (M="+signal_name[i]+" GeV)");

  h_Tstarhad[i]->Draw("hist same");
}

 leg->Draw();
}
