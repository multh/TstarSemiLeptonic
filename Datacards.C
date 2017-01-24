  TString BaseName = "datacards.txt";
  TString rootFileName = "datacards.root";
  TFile * fileInputs = new TFile(rootFileName,"recreate"); 
  TH1F *histData    = (TH1F*)fileInputs->Get("data_obs");
 TH1F *Tstar_M1200    = (TH1F*)fileInputs->Get("Tstar_M1200");
 TH1F *TT    = (TH1F*)fileInputs->Get("TT");
TH1F *QCD    = (TH1F*)fileInputs->Get("QCD");
TH1F *WJets    = (TH1F*)fileInputs->Get("WJets");
TH1F *ZJets    = (TH1F*)fileInputs->Get("ZJets");
TH1F *SingleTop    = (TH1F*)fileInputs->Get("SingleTop");
TH1F *Diboson   = (TH1F*)fileInputs->Get("Diboson");

//fileInputs->Close();

  ostringstream str;
  str << BaseName;
  string nn = str.str();
  const char * p = nn.c_str();

  std::ofstream textFile(p);
  textFile << "imax 1   number of channels" << std::endl;
  textFile << "jmax *   number of backgrounds" << std::endl;
  textFile << "kmax *   number of nuisance parameters" << std::endl;
  textFile << "-----------------" << std::endl;
  textFile << "observation " << histData->GetSumOfWeights() << std::endl;
  textFile << "-----------------" << std::endl;
  textFile << "shapes * * " << rootFileName << " $PROCESS    " << std::endl;
  textFile << "-----------------" << std::endl;
  textFile << "bin                                mt         mt     mt     mt     mt     mt     mt" << std::endl;
  textFile << "process                         Tstar_M1200    TT     W      Z  SingleTop QCD   Diboson" << std::endl;
  textFile << "process                             0         1      2      3      4      5       6" << std::endl;
  textFile << "rate                           "
           << Tstar_M700->GetSumOfWeights() << "  "
           << TT->GetSumOfWeights() << "  "
           << WJets->GetSumOfWeights() << "  "
           << ZJets->GetSumOfWeights() << "  "
           << SingleTop->GetSumOfWeights()<<" "
           << QCD->GetSumOfWeights()<<" "
           << Diboson->GetSumOfWeights()  << std::endl;
  textFile << "-----------------------------" << std::endl;
  textFile << "CMS_eff_m_trig              lnN   1.01   1.01   1.01   1.011  1.012  1.01    1.009 "  << std::endl;
  textFile << "CMS_eff_m_ID                lnN   1.02   1.02   1.02   1.02   1.02   1.02    1.01 "  << std::endl;
  textFile << "CMS_JEC                     lnN   1.76   1.2    1.61   1.57   4.67    7.9     2.8 "  << std::endl;
  textFile << "CMS_ScaleVar                lnN   -      1.42    -      -      -      -        -   "  << std::endl;
  textFile << "CMS_PDF                     lnN   -      1.016  1.05   1.054  1.02    -        -   "  << std::endl;
  textFile << "lumi_13TeV                  lnN   1.027  1.027  1.027  1.027  1.027  1.027   1.027"  << std::endl;
  textFile << "xs_ttbar                    lnN     -    1.50    -       -      -      -       -  "  << std::endl;
  textFile << "xs_WJets                    lnN     -      -    1.5      -      -      -       -  "  << std::endl;
  textFile << "xs_ZJets                    lnN     -      -     -     1.5      -      -       -  "  << std::endl;
  textFile << "xs_SingleTop                lnN     -      -     -       -    1.5      -       -  "  << std::endl;
  textFile << "xs_QCD                      lnN     -      -     -       -      -      2       -  "  << std::endl;
  textFile << "xs_Diboson                  lnN     -      -     -       -      -      -      1.5 "  << std::endl;
  textFile << std::endl;
   
