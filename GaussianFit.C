// make a simple Gaussian Fit in ROOT and RooFit


using namespace RooFit; 

void GaussianFit() { 
TFile *TTbar = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Nominal/uhh2.AnalysisModuleRunner.MC.TTbar.root");

TFile *Data = new TFile("/nfs/dust/cms/user/multh/RunII_76X_v1/Selection/FINAL/Nominal/uhh2.AnalysisModuleRunner.DATA.SingleMuDATA.root");

 TH1D *h_TTbar    = (TH1D*)TTbar->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");
 TH1D *h_Data    = (TH1D*)TTbar->Get("chi2min_ttag_comb__HypHists/M_Tstar_comb");

 TF1 * f1  = new TF1("f1","([0]*TMath::Exp(-x*[1]))",400,2000);
   f1->SetLineColor(kBlue);
   f1->SetParameters(100,0,1);

   // Neyman chi2 fit
   TFitResultPtr r1 = h_TTbar->Fit(f1,"S","",450,2000);

   TF1 * f2  = new TF1("f2","([0]*TMath::Exp(-x*[1]))",400,2000);
   f2->SetLineColor(kBlue-3);
   f2->SetParameters(100,0,1);

   // Pearson chi2 fit
   TFitResultPtr r2 = h_TTbar->Fit(f2,"P + S","",450,2000);

  TF1 * f3  = new TF1("f3","([0]*TMath::Exp(-x*[1]))",400,2000);
   f3->SetLineColor(kRed);
   f3->SetParameters(100,0,1);

   // Binnel likelihood fit
   TFitResultPtr r3 = h_TTbar->Fit(f3,"L + S","",450,2000);


   TLegend * l = new TLegend(0.65,0.55,0.88,0.7);
   l->AddEntry(f1,"Neyman chi2","l");
   l->AddEntry(f2,"Person chi2","l");
   l->AddEntry(f3,"Binned ML  ","l");
   l->Draw();

   // do now the fit with RooFit

   RooWorkspace cms_Tstar_workspace("cms_Tstar_workspace");
   // define a Gaussian pdf
   //RooRealVar lambda("lambda", "slope", -0.1, -5., 0.);

   //= new RooExponential("expo", "exponential PDF",x, lambda);
   cms_Tstar_workspace.factory("RooExponential:expo(x[450,2000],lambda[-0.007,-0.001])");
   // create extend pdf with number of events
   //w.factory("ExtendPdf:model(expo,nevt[100,0,100000])");   

   RooAbsPdf * pdf = cms_Tstar_workspace.pdf("expo");   // access object from workspace
   RooRealVar * MassTstar = cms_Tstar_workspace.var("MassTstar");   // access object from workspace
   

   // generate n gaussian measurement for a Gaussian(x, 0, 1);
   // RooDataSet * data = pdf->generate( *x);
   //data->SetName("unbinData");  

   // create dataset
   RooDataHist * TTbar = new RooDataHist("TTbar","TTbar",*MassTstar,h_TTbar); 
   RooDataHist * data  = new RooDataHist("data","data",*MassTstar,h_Data); 

   new TCanvas(); 
   // RooFit plotting capabilities 
   RooPlot * pl = MasTstar->frame(Title("Exponential Fit of TTbar")); 
   TTbar->plotOn(pl); 
   pl->Draw(); 

   //w.var("sigma")->setVal(1);
   //w.var("mu")->setVal(0);

   // now fit the data set 
   RooFitResult * r4 = pdf->fitTo(*TTbar, Minimizer("Minuit2","Migrad"), Save(1) ); 
 

   // plot the pdf on the same RooPlot object we have plotted the data 
   pdf->plotOn(pl);
   pdf->paramOn(pl, Layout(0.6,0.9,0.85));

   pl->Draw();

   // import data in workspace (IMPORTANT for saving it )
   cms_Tstar_workspace.import(*TTbar); 

   cms_Tstar_workspace.Print();

   // write workspace in the file (recreate file if already existing)
   cms_Tstar_workspace.writeToFile("WorkspaceExpo.root", true);

   cout << "model written to file " << endl;

   std::cout << "\nResult of Neyman chi2 \n";
   r1->Print();
   std::cout << "\nResult of Pearson chi2 \n";
   r2->Print();
   std::cout << "\nResult of Binned Likelihood \n";
   r3->Print();
   std::cout << "\nResult of Binned Likelihood fit with ROOTFIT\n";
   r4->Print();


}
