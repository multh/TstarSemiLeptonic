//CreateDatacards.C

//************************************************************************
//
//Macro to create Datacards for combine-tool
//  Use a fit on Data to reduce systematic Errors
//    Create workdirectory with RooFit to save all objects used by combine
//      Save Datacards for all Signals
//
//************************************************************************

using namespace RooFit; 

void CreateDatacards() {

//******************* Read in Data/MC Files *******************************************

//Read in Data File 
TFile *Data = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Test/uhh2.AnalysisModuleRunner.DATA.SingleMuData.root");

//Read in Signal Files 
TFile *Tstar_M700  = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Test/uhh2.AnalysisModuleRunner.MC.Tstar_M-700.root");
TFile *Tstar_M800  = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Test/uhh2.AnalysisModuleRunner.MC.Tstar_M-800.root");
TFile *Tstar_M900  = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Test/uhh2.AnalysisModuleRunner.MC.Tstar_M-900.root");
TFile *Tstar_M1000 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Test/uhh2.AnalysisModuleRunner.MC.Tstar_M-1000.root");
TFile *Tstar_M1100 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Test/uhh2.AnalysisModuleRunner.MC.Tstar_M-1100.root");
TFile *Tstar_M1200 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Test/uhh2.AnalysisModuleRunner.MC.Tstar_M-1200.root");
TFile *Tstar_M1300 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Test/uhh2.AnalysisModuleRunner.MC.Tstar_M-1300.root");
TFile *Tstar_M1400 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Test/uhh2.AnalysisModuleRunner.MC.Tstar_M-1400.root");
TFile *Tstar_M1500 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Test/uhh2.AnalysisModuleRunner.MC.Tstar_M-1500.root");
TFile *Tstar_M1600 = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Test/uhh2.AnalysisModuleRunner.MC.Tstar_M-1600.root");

TFile *TTbar     = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Test/uhh2.AnalysisModuleRunner.MC.TTbar_Tune.root");
TFile *WJets     = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Test/uhh2.AnalysisModuleRunner.MC.WJets_Pt.root");
TFile *ZJets     = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Test/uhh2.AnalysisModuleRunner.MC.ZJets_HT.root");
TFile *QCD       = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Test/uhh2.AnalysisModuleRunner.MC.QCD.root");
TFile *Diboson   = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Test/uhh2.AnalysisModuleRunner.MC.Diboson.root");
TFile *SingleTop = new TFile("/nfs/dust/cms/user/multh/RunII_80X_v3/Selection/Test/uhh2.AnalysisModuleRunner.MC.SingleT.root");

/*
 TH1F *h1    = (TH1F*)TTbar     ->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 TH1F *h2    = (TH1F*)WJets     ->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 TH1F *h3    = (TH1F*)ZJets     ->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 TH1F *h4    = (TH1F*)QCD       ->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 TH1F *h5    = (TH1F*)Diboson   ->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 TH1F *h6    = (TH1F*)SingleTop ->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
*/

 TH1F *h1    = (TH1F*)TTbar     ->Get("chi2min__HypHists/M_Tstar_comb");
 TH1F *h2    = (TH1F*)WJets     ->Get("chi2min__HypHists/M_Tstar_comb");
 TH1F *h3    = (TH1F*)ZJets     ->Get("chi2min__HypHists/M_Tstar_comb");
 TH1F *h4    = (TH1F*)QCD       ->Get("chi2min__HypHists/M_Tstar_comb");
 TH1F *h5    = (TH1F*)Diboson   ->Get("chi2min__HypHists/M_Tstar_comb");
 TH1F *h6    = (TH1F*)SingleTop ->Get("chi2min__HypHists/M_Tstar_comb");

//Create Vector for BKG Hists
 TH1F* histos[6]={h1,h2,h3,h4,h5,h6};
for (int i=0;i<6;++i){
         histos[i]->Sumw2(); // *Very* Important
        }

//Merge All BKG Hists
TList *list = new TList; 
list->Add(h1); 
list->Add(h2);
 list->Add(h3);
list->Add(h4);
list->Add(h5);
list->Add(h6);

TH1D *bkg = (TH1D*)h1->Clone("h"); 
bkg->Reset(); 
bkg->Merge(list); 


// TH1D *h_TTbar        = (TH1D*)TTbar->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 TH1D *h_Tstar_700    = (TH1D*)Tstar_M700->Get("chi2min__HypHists/M_Tstar_comb");
 TH1D *h_Tstar_800    = (TH1D*)Tstar_M800->Get("chi2min__HypHists/M_Tstar_comb");
 TH1D *h_Tstar_900    = (TH1D*)Tstar_M900->Get("chi2min__HypHists/M_Tstar_comb");
 TH1D *h_Tstar_1000   = (TH1D*)Tstar_M1000->Get("chi2min__HypHists/M_Tstar_comb");
 TH1D *h_Tstar_1100   = (TH1D*)Tstar_M1100->Get("chi2min__HypHists/M_Tstar_comb");
 TH1D *h_Tstar_1200   = (TH1D*)Tstar_M1200->Get("chi2min__HypHists/M_Tstar_comb");
 TH1D *h_Tstar_1300   = (TH1D*)Tstar_M1300->Get("chi2min__HypHists/M_Tstar_comb");
 TH1D *h_Tstar_1400   = (TH1D*)Tstar_M1400->Get("chi2min__HypHists/M_Tstar_comb");
 TH1D *h_Tstar_1500   = (TH1D*)Tstar_M1500->Get("chi2min__HypHists/M_Tstar_comb");
 TH1D *h_Tstar_1600   = (TH1D*)Tstar_M1600->Get("chi2min__HypHists/M_Tstar_comb");
 
 TH1D *h_Data         = (TH1D*)Data->Get("chi2min_ttag__HypHists/M_Tstar_comb");

 cout<<"Data SumWeight: "<< h_Data->GetSumOfWeights() <<endl;
 cout<<"bkg SumWeight: "<< bkg->GetSumOfWeights() <<endl;
 cout<<"bkg SumWeight: "<< bkg->GetSumOfWeights() <<endl;



//***************** Fit with RooFit **************************************************************************************** 
   RooWorkspace cms_workspace("cms_workspace");
 
 // Define PDFs for Signal and BKG
   //Setup Variables    
   RooRealVar InvMass("InvMass","M_{T^{*} [GeV/c^{2}]}",1000,400,2000);
   RooRealVar lambda("lambda","lambda",-7,30);
   RooRealVar lambda2("lambda2","lambda2",-10,10);
   RooRealVar lambda3("lambda3","lambda3",-20,20);



   //PDF for Background 
  RooGenericPdf Background("Background","Background","TMath::Power(InvMass/25, lambda+lambda2*log(InvMass/25)+lambda3*log(InvMass/25)*log(InvMass/25))",RooArgSet(InvMass,lambda,lambda2, lambda3));
  
   // RooGenericPdf Background("Background","Background","TMath::Power(InvMass/100, (lambda+lambda2*log(InvMass/100)))",RooArgSet(InvMass,lambda,lambda2));
    
   //Add PDFs for Signals to workspace  
   cms_workspace.factory("RooGaussian:gx_700(InvMass[400,2000],gaus_mean_700[500,800],gaus_sigma_700[50,200])");
   cms_workspace.factory("RooLandau:lx_700(InvMass[400,2000],land_mean_700[500,2000],land_sigma_700[50,300])");
   cms_workspace.factory("SUM:Tstar_700(g1frac_700[0.45]*gx_700,p1frac_700[0.55]*lx_700)");
   
   cms_workspace.factory("RooGaussian:gx_800(InvMass[400,2000],gaus_mean_800[600,1300],gaus_sigma_800[50,200])");
   cms_workspace.factory("RooLandau:lx_800(InvMass[400,2000],land_mean_800[500,2000],land_sigma_800[50,600])");
   cms_workspace.factory("SUM:Tstar_800(g1frac_800[0.4]*gx_800,p1frac_800[0.6]*lx_800)");
   
   cms_workspace.factory("RooGaussian:gx_900(InvMass[400,2000],gaus_mean_900[650,1000],gaus_sigma_900[150,600])");
   cms_workspace.factory("RooLandau:lx_900(InvMass[400,2000],land_mean_900[500,1100],land_sigma_900[50,200])");
   cms_workspace.factory("SUM:Tstar_900(g1frac_900[0.75]*gx_900,p1frac_900[0.25]*lx_900)");
   
   cms_workspace.factory("RooGaussian:gx_1000(InvMass[400,2000],gaus_mean_1000[600,1200],gaus_sigma_1000[150,650])");
   cms_workspace.factory("RooLandau:lx_1000(InvMass[400,2000],land_mean_1000[500,2000],land_sigma_1000[50,200])");
   cms_workspace.factory("SUM:Tstar_1000(g1frac_1000[0.3]*gx_1000,p1frac_1000[0.7]*lx_1000)");
 
   cms_workspace.factory("RooGaussian:gx_1100(InvMass[400,2000],gaus_mean_1100[400,2000],gaus_sigma_1100[50,950])");
   cms_workspace.factory("RooLandau:lx_1100(InvMass[400,2000],land_mean_1100[800,2000],land_sigma_1100[50,950])");
   cms_workspace.factory("SUM:Tstar_1100(g1frac_1100[0.35]*gx_1100,p1frac_1100[0.65]*lx_1100)");
 
   cms_workspace.factory("RooGaussian:gx_1200(InvMass[400,2000],gaus_mean_1200[800,2000],gaus_sigma_1200[150,950])");
   cms_workspace.factory("RooLandau:lx_1200(InvMass[400,2000],land_mean_1200[500,2000],land_sigma_1200[50,200])");
   cms_workspace.factory("SUM:Tstar_1200(g1frac_1200[0.55]*gx_1200,p1frac_1200[0.45]*lx_1200)");
 
   cms_workspace.factory("RooGaussian:gx_1300(InvMass[400,2000],gaus_mean_1300[400,2000],gaus_sigma_1300[50,550])");
   cms_workspace.factory("RooLandau:lx_1300(InvMass[400,2000],land_mean_1300[1000,2000],land_sigma_1300[50,350])");
   cms_workspace.factory("SUM:Tstar_1300(g1frac_1300[0.7]*gx_1300,p1frac_1300[0.3]*lx_1300)");

   cms_workspace.factory("RooGaussian:gx_1400(InvMass[400,2000],gaus_mean_1400[1000,1600],gaus_sigma_1400[50,550])");
   cms_workspace.factory("RooLandau:lx_1400(InvMass[400,2000],land_mean_1400[500,2000],land_sigma_1400[50,980])");
   cms_workspace.factory("SUM:Tstar_1400(g1frac_1400[0.4]*gx_1400,p1frac_1400[0.6]*lx_1400)");

   cms_workspace.factory("RooGaussian:gx_1500(InvMass[400,2000],gaus_mean_1500[1300,1700],gaus_sigma_1500[50,350])");
   cms_workspace.factory("RooLandau:lx_1500(InvMass[400,2000],land_mean_1500[500,2000],land_sigma_1500[200,600])");
   cms_workspace.factory("SUM:Tstar_1500(g1frac_1500[0.4]*gx_1500,p1frac_1500[0.6]*lx_1500)");

   cms_workspace.factory("RooGaussian:gx_1600(InvMass[400,2000],gaus_mean_1600[1400,1800],gaus_sigma_1600[50,350])");
   cms_workspace.factory("RooLandau:lx_1600(InvMass[400,2000],land_mean_1600[500,2000],land_sigma_1600[50,600])");
   cms_workspace.factory("SUM:Tstar_1600(g1frac_1600[0.4]*gx_1600,p1frac_1600[0.6]*lx_1600)");

   //Add PDF for Background to workspace
   cms_workspace.import(Background);
   RooAbsPdf * pdf_Background = cms_workspace.pdf("Background");   // access object from workspace
     pdf_Background->Print();

   RooAbsPdf * pdf_Tstar_700 = cms_workspace.pdf("Tstar_700");   // access object from workspace
   RooAbsPdf * pdf_Tstar_800 = cms_workspace.pdf("Tstar_800");   // access object from workspace
   RooAbsPdf * pdf_Tstar_900 = cms_workspace.pdf("Tstar_900");   // access object from workspace
   RooAbsPdf * pdf_Tstar_1000 = cms_workspace.pdf("Tstar_1000");   // access object from workspace
   RooAbsPdf * pdf_Tstar_1100 = cms_workspace.pdf("Tstar_1100");   // access object from workspace
   RooAbsPdf * pdf_Tstar_1200 = cms_workspace.pdf("Tstar_1200");   // access object from workspace
   RooAbsPdf * pdf_Tstar_1300 = cms_workspace.pdf("Tstar_1300");   // access object from workspace
   RooAbsPdf * pdf_Tstar_1400 = cms_workspace.pdf("Tstar_1400");   // access object from workspace
   RooAbsPdf * pdf_Tstar_1500 = cms_workspace.pdf("Tstar_1500");   // access object from workspace
   RooAbsPdf * pdf_Tstar_1600 = cms_workspace.pdf("Tstar_1600");   // access object from workspace
   RooRealVar * InvMass1       = cms_workspace.var("InvMass");   // access object from workspace

 // create dataset
   RooDataHist * data_obs    = new RooDataHist("data_obs","data_obs",*InvMass1,h_Data); 
   RooDataHist * bkg_h       = new RooDataHist("bkg_h","bkg_h",*InvMass1,h1);
   RooDataHist * merge_h     = new RooDataHist("merge_h","merge_h",*InvMass1,bkg);
   RooDataHist * Tstar_700_h = new RooDataHist("Tstar_700_h","Tstar_700_h",*InvMass1,h_Tstar_700);
   RooDataHist * Tstar_800_h = new RooDataHist("Tstar_800_h","Tstar_800_h",*InvMass1,h_Tstar_800); 
   RooDataHist * Tstar_900_h = new RooDataHist("Tstar_900_h","Tstar_900_h",*InvMass1,h_Tstar_900); 
   RooDataHist * Tstar_1000_h = new RooDataHist("Tstar_1000_h","Tstar_1000_h",*InvMass1,h_Tstar_1000); 
   RooDataHist * Tstar_1100_h = new RooDataHist("Tstar_1100_h","Tstar_1100_h",*InvMass1,h_Tstar_1100); 
   RooDataHist * Tstar_1200_h = new RooDataHist("Tstar_1200_h","Tstar_1200_h",*InvMass1,h_Tstar_1200); 
   RooDataHist * Tstar_1300_h = new RooDataHist("Tstar_1300_h","Tstar_1300_h",*InvMass1,h_Tstar_1300); 
   RooDataHist * Tstar_1400_h = new RooDataHist("Tstar_1400_h","Tstar_1400_h",*InvMass1,h_Tstar_1400); 
   RooDataHist * Tstar_1500_h = new RooDataHist("Tstar_1500_h","Tstar_1500_h",*InvMass1,h_Tstar_1500); 
   RooDataHist * Tstar_1600_h = new RooDataHist("Tstar_1600_h","Tstar_1600_h",*InvMass1,h_Tstar_1600); 
   
  
   //Create Canvas 
   new TCanvas(); 

   //RooFit plotting capabilities 
   RooPlot * plot = InvMass1->frame(Title(" "));
   plot->GetXaxis()->SetTitleOffset(1.2);
   plot->GetYaxis()->SetTitleOffset(1.2);
   plot->SetXTitle("M_{T*} [GeV/c^{2}]");
   plot->SetYTitle("Ereignisse");
 
 
 // now fit the data set 
   RooFitResult * r_bkg   = pdf_Background ->fitTo(*data_obs, Minimizer("Minuit2","Migrad"),SumW2Error(kFALSE), Save(1) );   //*data_obs for Bug-Fix
     
   RooFitResult * r_Tstar700   = pdf_Tstar_700  ->fitTo(*Tstar_700_h,  Minimizer("Minuit2","Migrad"),SumW2Error(kFALSE), Save(1) );
   RooFitResult * r_Tstar800   = pdf_Tstar_800  ->fitTo(*Tstar_800_h,  Minimizer("Minuit2","Migrad"),SumW2Error(kFALSE), Save(1) ); 
   RooFitResult * r_Tstar900   = pdf_Tstar_900  ->fitTo(*Tstar_900_h,  Minimizer("Minuit2","Migrad"),SumW2Error(kFALSE), Save(1) ); 
   RooFitResult * r_Tstar1000  = pdf_Tstar_1000 ->fitTo(*Tstar_1000_h, Minimizer("Minuit2","Migrad"),SumW2Error(kFALSE), Save(1) ); 
   RooFitResult * r_Tstar1100  = pdf_Tstar_1100 ->fitTo(*Tstar_1100_h, Minimizer("Minuit2","Migrad"),SumW2Error(kFALSE), Save(1) ); 
   RooFitResult * r_Tstar1200  = pdf_Tstar_1200 ->fitTo(*Tstar_1200_h, Minimizer("Minuit2","Migrad"),SumW2Error(kFALSE), Save(1) ); 
   RooFitResult * r_Tstar1300  = pdf_Tstar_1300 ->fitTo(*Tstar_1300_h, Minimizer("Minuit2","Migrad"),SumW2Error(kFALSE), Save(1) ); 
   RooFitResult * r_Tstar1400  = pdf_Tstar_1400 ->fitTo(*Tstar_1400_h, Minimizer("Minuit2","Migrad"),SumW2Error(kFALSE), Save(1) ); 
   RooFitResult * r_Tstar1500  = pdf_Tstar_1500 ->fitTo(*Tstar_1500_h, Minimizer("Minuit2","Migrad"),SumW2Error(kFALSE), Save(1) ); 
   RooFitResult * r_Tstar1600  = pdf_Tstar_1600 ->fitTo(*Tstar_1600_h, Minimizer("Minuit2","Migrad"),SumW2Error(kFALSE), Save(1) ); 
  
   
   // plot PDFs on the same RooPlot object we have plotted the data 
   /*
   data_obs ->plotOn(plot,DataError(RooAbsData::None),XErrorSize(0),MarkerColor(kWhite));
   //merge_h->plotOn(plot,DataError(RooAbsData::None),XErrorSize(0),MarkerColor(kWhite));

   pdf_Background ->plotOn(plot,VisualizeError(*r_bkg,1),FillColor(kGray),Name("error"));
   pdf_Background ->plotOn(plot,RooFit::Name("pdf"));
  
   data_obs->plotOn(plot,RooFit::Name("daten"));
   //merge_h->plotOn(plot,RooFit::Name("daten"));

 //Create Legend for RooPlot
  leg = new TLegend(0.1,0.7,0.48,0.9);
   leg->AddEntry(plot->findObject("daten"),"MC-Background","pel");
   leg->AddEntry(plot->findObject("pdf"),"Fit-Function","l");
   leg->AddEntry(plot->findObject("error"),"#pm 1 #sigma Error band","f");
   */
   
 // plot PDFs on the same RooPlot object we have plotted the data 
   
     Tstar_1100_h     ->plotOn(plot,MarkerColor(kBlack));
      Tstar_1500_h    ->plotOn(plot,MarkerColor(kBlue));
        pdf_Tstar_1100   ->plotOn(plot,VisualizeError(*r_Tstar1100,1),FillColor(kGray),Name("error"));
      pdf_Tstar_1500  ->plotOn(plot,VisualizeError(*r_Tstar1500,1),FillColor(kGray),Name("error"));

      pdf_Tstar_1100 ->plotOn(plot,LineColor(kRed),RooFit::Name("Fit_1100"));
      pdf_Tstar_1500 ->plotOn(plot,LineColor(kBlue),RooFit::Name("Fit_1500"));
  
    Tstar_1100_h->plotOn(plot,RooFit::Name("Tstar_1100"));
     Tstar_1500_h->plotOn(plot,RooFit::Name("Tstar_1500"));

 //Create Legend for RooPlot
  leg = new TLegend(0.1,0.7,0.48,0.9);
  leg->AddEntry(plot->findObject("Tstar_1100"),"T* (1100 GeV/c^{2})","pel");
  leg->AddEntry(plot->findObject("Fit_1100"),"Fit-Function (1100 GeV/c^{2})","l");
   
  
  leg->AddEntry(plot->findObject("Tstar_1500"),"T* (1500 GeV/c^{2})","pel");
  leg->AddEntry(plot->findObject("Fit_1500"),"Fit-Function (1500 GeV/c^{2})","l");
 
   
//Draw PDFs and Legend 
   plot->Draw();
  leg->Draw("same");
 

//*********************** import data in workspace (IMPORTANT for saving it ) *******************************************
   cms_workspace.import(*data_obs); 

//write workspace in the file (recreate file if already existing)
   cms_workspace.writeToFile("datacards.root");
     cout << "model written to file " << endl;
 
//Print Result of Background-Fit 
     r_Tstar800 -> Print();
       cout << "\nResult of Binned Likelihood fit with ROOTFIT\n";




 //********************************* SETUP DATACARD.TXT ************************************************************************************

       TString Signal_num[10]   = {"700","800","900","1000","1100","1200","1300","1400","1500","1600"};
       RooDataHist * Signal_h[10] = {Tstar_700_h, Tstar_800_h, Tstar_900_h, Tstar_1000_h, Tstar_1100_h, Tstar_1200_h, Tstar_1300_h, Tstar_1400_h, Tstar_1500_h, Tstar_1600_h};

for(int i=0; i<10;++i){

   RooRealVar * gaus_mean  = cms_workspace.var("gaus_mean_"+Signal_num[i]);    // access object from workspace
   RooRealVar * gaus_sigma = cms_workspace.var("gaus_sigma_"+Signal_num[i]);   // access object from workspace
   RooRealVar * land_mean  = cms_workspace.var("land_mean_"+Signal_num[i]);    // access object from workspace
   RooRealVar * land_sigma = cms_workspace.var("land_sigma_"+Signal_num[i]);   // access object from workspace

   RooRealVar * lambda_fit      = cms_workspace.var("lambda");            // access object from workspace
   RooRealVar * lambda2_fit     = cms_workspace.var("lambda2");           // access object from workspace
   RooRealVar * lambda3_fit     = cms_workspace.var("lambda3");           // access object from workspace
 
 TString BaseName = "datacards_"+Signal_num[i]+".txt";
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
  textFile << "observation "<< data_obs->sum(false)<< std::endl;
  textFile << "-----------------" << std::endl;
  textFile << "shapes * * datacards.root cms_workspace:$PROCESS"                           << std::endl;
   textFile << "---------------------------------------------------------------------------------------------"  << std::endl;
  textFile << "bin                          mTstar      mTstar                                               "  << std::endl;
  textFile << "process                      Tstar_"<<Signal_num[i]<<"   Background                                             "  << std::endl;
  textFile << "process                      0           1                                                    "  << std::endl;
  textFile << "rate     "
           << "                  " <<Signal_h[i]->sum(false)<< "     "<<data_obs->sum(false)<<"              "  << std::endl;
  textFile << "----------------------------------------------------------------------------------------------"  << std::endl;
  
  //  textFile << "CMS_bTag_bc           lnN    1.05     -                                                       "  << std::endl;
  //textFile << "CMS_bTag_udsg_bc      lnN    1.04     -                                                       "  << std::endl;
  //textFile << "CMS_JEC               lnN    1.4     -                                                       "  << std::endl;
  //textFile << "CMS_JER               lnN    1.1     -                                                       "  << std::endl;
  //textFile << "CMS_MuonID            lnN    1.015     -                                                       "  << std::endl;
  //textFile << "CMS_MuonTrigger       lnN    1.01     -                                                       "  << std::endl;
  //textFile << "CMS_PU                lnN    1.05     -                                                       "  << std::endl;
  //textFile << "lumi_13TeV            lnN    1.027    -                                                       "  << std::endl;
  textFile << "----------------------------------------------------------------------------------------------"  << std::endl;
  textFile << "lambda                param  " <<lambda_fit    ->getVal()<< "   "<<lambda_fit    ->getError()<<"    "  << std::endl;
  textFile << "lambda2               param  " <<lambda2_fit   ->getVal()<< "   "<<lambda2_fit   ->getError()<<"    "  << std::endl;
  textFile << "lambda3               param  " <<lambda3_fit   ->getVal()<< "   "<<lambda3_fit   ->getError()<<"    "  << std::endl;
  textFile << "gaus_mean_"<<Signal_num[i]<<"         param  " <<gaus_mean ->getVal()<< "     "<<gaus_mean ->getError()<<"    "  << std::endl;
  textFile << "gaus_sigma_"<<Signal_num[i]<<"        param  " <<gaus_sigma->getVal()<< "     "<<gaus_sigma ->getError()<<"    "  << std::endl;
  textFile << "land_mean_"<<Signal_num[i]<<"         param  " <<land_mean ->getVal()<< "     "<<land_mean ->getError()<<"    "  << std::endl;
  textFile << "land_sigma_"<<Signal_num[i]<<"        param  " <<land_sigma->getVal()<< "     "<<land_sigma ->getError()<<"    "  << std::endl;
  textFile << "rate                  rateParam       mTstar Background   1                                                     " <<std::endl;
  textFile << std::endl;

  // *******************************************
  
    }
}
