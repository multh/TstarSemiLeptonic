#include "UHH2/TstarSemiLeptonic/include/TstarPDFHists.h"
#include "UHH2/TstarSemiLeptonic/include/HypothesisHistsOwn.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/Utils.h"
#include "UHH2/common/include/JetIds.h"
#include <math.h>
#include <sstream>

#include "TH1F.h"
#include "TH2D.h"
#include <iostream>

using namespace std;
using namespace uhh2;
using namespace uhh2examples;


TstarPDFHists::TstarPDFHists(Context & ctx, const string & dirname, bool use_pdf_weights_): Hists(ctx, dirname), use_pdf_weights(use_pdf_weights_){  

is_mc = ctx.get("dataset_type") == "MC";
 //For Mass reconstruction
  h_hyps = ctx.get_handle<std::vector<TstarReconstructionHypothesis>>("TstarReconstruction");
  m_discriminator_name ="Chi2";

  double bins_mtstar[31] = {0,66.66,133.3,200,266.66,333.3,400,466.66,533.33,600,666.66,733.33,800,866.66,933.33,1000,1066.66,1133.33,1200,1266.66,1333.33,1400,1466.66,1533.33,1600,1666.66,1733.33,1800,1866.66,1933.33,2000};
 
  for(int i=0; i<100; i++){
    stringstream ss_name;
    ss_name << "M_comb_PDF_"  << i+1 ;
    stringstream ss_title;
    ss_title << "M_{comb} [GeV] for PDF No. "  << i+1 << " out of 100" ;
    
    string s_name = ss_name.str();
    string s_title = ss_title.str();
   
    const char* char_name = s_name.c_str();
    const char* char_title = s_title.c_str();
 
    histo_names[i] = s_name;
 
    book<TH1F>(char_name, char_title, 30,bins_mtstar);
  }

}

void TstarPDFHists::fill(const Event & event){
  double weight = event.weight;

  if(is_mc){
   if(event.muons->size() == 1){   
     std::vector<TstarReconstructionHypothesis> hyps = event.get(h_hyps); 
     const TstarReconstructionHypothesis* hyp = get_best_hypothesis( hyps, m_discriminator_name );

      double mTstarlep_rec = 0;
      double mTstarhad_rec = 0;
      double mTstarmed_rec = 0;
      
      if( (hyp->Tstarlep_v4()).isTimelike() ) mTstarlep_rec = (hyp->Tstarlep_v4()).M();
      else mTstarlep_rec = sqrt( -(hyp->Tstarlep_v4()).mass2());
      if( (hyp->Tstarhad_v4()).isTimelike() ) mTstarhad_rec = (hyp->Tstarhad_v4()).M();
      else mTstarhad_rec = sqrt( -(hyp->Tstarhad_v4()).mass2());
      
      mTstarmed_rec = (mTstarhad_rec + mTstarlep_rec) / 2;

      if(event.genInfo->systweights().size()){
	for(int i=0; i<100; i++){
	  if(use_pdf_weights){

	    double pdf_weight = event.genInfo->systweights().at(i+9);
	    double fillweight = weight * pdf_weight/event.genInfo->originalXWGTUP();
	    
	    const char* name = histo_names[i].c_str();
	    hist(name)->Fill(mTstarmed_rec,fillweight);
	  }
	}
      }//systweights filled
    } //Tstar reconstructable
  } //is_mc
}

TstarPDFHists::~TstarPDFHists(){}
