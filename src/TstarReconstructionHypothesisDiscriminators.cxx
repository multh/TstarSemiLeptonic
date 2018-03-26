#include "UHH2/TstarSemiLeptonic/include/TstarReconstructionHypothesisDiscriminators.h"
#include "UHH2/core/include/Utils.h"

#include <set>

using namespace uhh2;
using namespace std;

//**************************************************************************
//
//Macro to estimate Best Hypothesis for T*-System
//   Use different Chi2-Terms in case of Top-Tag
//     Correct Match Function implemented for Reco-Studies/Mass-Resolutions
//
//**************************************************************************


namespace {
// invariant mass of a lorentzVector, but save for timelike / spacelike vectors
float inv_mass(const LorentzVector & p4){
    if(p4.isTimelike()){
            return p4.mass();
    }
    else{
        return -sqrt(-p4.mass2());
    }
}
}


//***************** Search for Best Hypothesis **************************************************************************************************

const TstarReconstructionHypothesis * get_best_hypothesis(const std::vector<TstarReconstructionHypothesis> & hyps, const std::string & label){
   const TstarReconstructionHypothesis * best = nullptr;
    float current_best_disc = numeric_limits<float>::infinity();

    for(const auto & hyp : hyps){
       if(!hyp.has_discriminator(label))
	continue;

        auto disc = hyp.discriminator(label);
	 if(disc < current_best_disc){
            best = &hyp;
            current_best_disc = disc;
        }
    }
    if(std::isfinite(current_best_disc)){
        return best;
    }
    else{
      std::cout<<"Nullpointer Best Hyp!"<<std::endl;
      return nullptr;
    }
}
////*************************************************************************************************************************************************

//**************** Chi2 Analysis for Events without Top-Tag *****************************************************************************************

TstarChi2Discriminator::TstarChi2Discriminator(Context & ctx, const std::string & rechyps_name, const cfg & config_): config(config_){
    h_hyps = ctx.get_handle<vector<TstarReconstructionHypothesis>>(rechyps_name);
}

bool TstarChi2Discriminator::process(uhh2::Event & event){

    auto & hyps = event.get(h_hyps);

    //Top-Quark values
    const double mass_thad = 173.4;
    const double mass_thad_sigma = 20.23;
    const double mass_tlep = 170.8;
    const double mass_tlep_sigma = 23.68;
    
    //T* values (Masspoint independend)
    const double mass_Tstar_diff_rel = 0.0026; //Average CorrectMatch
    const double mass_Tstar_diff_rel_sigma = 0.051; //

    //Make use of topology
    const double deltaPhi_Tstar = 3.139;
    const double deltaPhi_sigma = 0.084;


    for(auto & hyp: hyps){
/*
        auto gluonlep_jets = hyp.gluonlep_jets();
        auto gluonhad_jets = hyp.gluonhad_jets();
   
        if(gluonhad_jets.size() != 1 || gluonlep_jets.size() != 1){
    	   hyp.set_discriminator(config.discriminator_label, 100);
	   hyp.set_discriminator(config.discriminator_label + "_tlep", 100);
           hyp.set_discriminator(config.discriminator_label + "_thad", 100);
           hyp.set_discriminator(config.discriminator_label + "_MTstar_rel", 100);
           hyp.set_discriminator(config.discriminator_label + "_deltaPhi", 100);
           continue;
 	}
*/

        double mass_thad_rec = inv_mass(hyp.tophad_v4());
        double mass_tlep_rec = inv_mass(hyp.toplep_v4());

	double mass_Tstar_had_rec = inv_mass(hyp.Tstarhad_v4());
	double mass_Tstar_lep_rec = inv_mass(hyp.Tstarlep_v4());
	double mass_Tstar_mean_rec = (mass_Tstar_had_rec + mass_Tstar_lep_rec);

	double deltaPhi_Tstar_rec     = (hyp.Tstarhad_v4().phi()-hyp.Tstarlep_v4().phi());


	//Compute Chi2 Terms 
        double chi2_thad            = pow((mass_thad_rec - mass_thad) / mass_thad_sigma, 2);
        double chi2_tlep            = pow((mass_tlep_rec - mass_tlep) / mass_tlep_sigma, 2);
	double chi2_MTstar_diff_rel = pow(((mass_Tstar_had_rec - mass_Tstar_lep_rec)/mass_Tstar_mean_rec - mass_Tstar_diff_rel) / mass_Tstar_diff_rel_sigma, 2);
	double chi2_deltaPhi        = pow((deltaPhi_Tstar_rec - deltaPhi_Tstar)/deltaPhi_sigma ,2);

	//##############################################################################################

        hyp.set_discriminator(config.discriminator_label, chi2_thad + chi2_tlep +chi2_MTstar_diff_rel + chi2_deltaPhi); 
	hyp.set_discriminator(config.discriminator_label + "_tlep", chi2_tlep);
        hyp.set_discriminator(config.discriminator_label + "_thad", chi2_thad);
	hyp.set_discriminator(config.discriminator_label + "_MTstar_rel", chi2_MTstar_diff_rel);
	hyp.set_discriminator(config.discriminator_label + "_deltaPhi", chi2_deltaPhi);
    }  
    return true;
}
////****************************************************************************************************************************************************************



//********************* Chi2 Analysis for Events with Top-Tag ******************************************************************************************************

TstarChi2DiscriminatorTTAG::TstarChi2DiscriminatorTTAG(Context & ctx, const std::string & rechyps_name, const cfg & config_): config(config_){
  h_hyps = ctx.get_handle<vector<TstarReconstructionHypothesis>>(rechyps_name);
}

bool TstarChi2DiscriminatorTTAG::process(uhh2::Event& event){
auto & hyps = event.get(h_hyps);

//Top-Quark values
  const double mass_thad       = 194.9;
  const double mass_thad_sigma =  21.34;
  const double mass_tlep       = 169.3;
  const double mass_tlep_sigma =  24.05;

  //T* values
  const double mass_Tstar_diff_rel = 0.012; //How to get
  const double mass_Tstar_diff_rel_sigma = 0.076; //How to get

  //Topology
  const double deltaPhi_Tstar = 3.147;
  const double deltaPhi_sigma = 0.09;

  //Run over all Hypothesis 
  for(auto & hyp: hyps){
    if(!hyp.tophad_topjet_ptr())
      throw std::runtime_error("Chi2DiscriminatorTTAG::process -- null pointer for TopJet associated to hadronic-top");

    //Top-Quark Lorentz-Vector
    LorentzVector tjet_subjet_sum;
    for(const auto& subj : hyp.tophad_topjet_ptr()->subjets()) tjet_subjet_sum += subj.v4();

    const double mass_tlep_rec = inv_mass(hyp.toplep_v4());
    const double mass_thad_rec = inv_mass(tjet_subjet_sum);

    double mass_Tstar_had_rec = inv_mass(hyp.Tstarhad_v4());
    double mass_Tstar_lep_rec = inv_mass(hyp.Tstarlep_v4());
    double mass_Tstar_mean_rec = (mass_Tstar_had_rec + mass_Tstar_lep_rec);

    double deltaPhi_Tstar_rec     = (hyp.Tstarhad_v4().phi()-hyp.Tstarlep_v4().phi());


    //Compute Chi2 Terms   
    double chi2_thad            = pow((mass_thad_rec - mass_thad) / mass_thad_sigma, 2);
    double chi2_tlep            = pow((mass_tlep_rec - mass_tlep) / mass_tlep_sigma, 2);
    double chi2_MTstar_diff_rel = pow(((mass_Tstar_had_rec - mass_Tstar_lep_rec)/mass_Tstar_mean_rec - mass_Tstar_diff_rel) / mass_Tstar_diff_rel_sigma, 2);
    double chi2_deltaPhi        = pow((deltaPhi_Tstar_rec - deltaPhi_Tstar)/deltaPhi_sigma ,2);
 
    //###############################################################################################

    hyp.set_discriminator(config.discriminator_label, chi2_thad + chi2_tlep + chi2_MTstar_diff_rel); // + chi2_deltaPhi); 
	hyp.set_discriminator(config.discriminator_label + "_tlep", chi2_tlep);
        hyp.set_discriminator(config.discriminator_label + "_thad", chi2_thad);
	hyp.set_discriminator(config.discriminator_label + "_MTstar_rel", chi2_MTstar_diff_rel);
	hyp.set_discriminator(config.discriminator_label + "_deltaPhi", chi2_deltaPhi);
 }
 return true;
}
//************************************************************************************************************************************************************************


TstarTopDRMCDiscriminator::TstarTopDRMCDiscriminator(Context & ctx, const std::string & rechyps_name, const cfg & config_): config(config_){
    h_hyps = ctx.get_handle<vector<TstarReconstructionHypothesis>>(rechyps_name);
    h_ttbargen = ctx.get_handle<TTbarGen>(config.ttbargen_name);
}

bool TstarTopDRMCDiscriminator::process(uhh2::Event & event){
    auto & hyps = event.get(h_hyps);
    const auto & ttbargen = event.get(h_ttbargen);
    for(auto & hyp: hyps){
        auto deltar_sum = deltaR(ttbargen.Top(), hyp.top_v4()) + deltaR(ttbargen.Antitop(), hyp.antitop_v4());
        hyp.set_discriminator(config.discriminator_label, deltar_sum);
    }
    return true;
}


//******************* Correct Match for Reco-Studies/Shape and Resolution of Chi2-Variables 
TstarCorrectMatchDiscriminator::TstarCorrectMatchDiscriminator(Context & ctx, const std::string & rechyps_name, const cfg & config_): config(config_){
    h_hyps = ctx.get_handle<vector<TstarReconstructionHypothesis>>(rechyps_name);
    h_tstargen = ctx.get_handle<TStarGen>(config.tstargen_name);
}

namespace {
// match particle p to one of the jets (Delta R < 0.4); 
// return the deltaR of the match.

template<typename T> // T should inherit from Particle
float match_dr(const Particle & p, const std::vector<T> & jets, int& index){
  float mindr = 100;
  index = -1;
  for(unsigned int i=0; i<jets.size(); ++i){
    float dR = deltaR(p, jets.at(i));
    float pt = abs(1- (p.v4().pt()/jets.at(i).pt()));
    if( dR <0.2 && dR<mindr) {//  dR <0.4
      //    cout<<"Enter mindr: Found dR AND pT match! "<<endl;
      //   cout<<"pt match (jet "<<i<<"): "<<pt<<endl;
      mindr=dR;
      index=i;
    }
  }
  return mindr;
}

template<typename T> // T should inherit from Particle
float match_dr_gluon(const Particle & p, const std::vector<T> & jets, int& index){
  float mindr = 100;
  index = -1;
  for(unsigned int i=0; i<jets.size(); ++i){
    float dR = deltaR(p, jets.at(i));
    float pt = abs(1- (p.v4().pt()/jets.at(i).pt()));
    if( dR <0.1 && dR<mindr) {//  dR <0.4
      //    cout<<"Enter mindr: Found dR AND pT match! "<<endl;
      //   cout<<"pt match (jet "<<i<<"): "<<pt<<endl;
      mindr=dR;
      index=i;
    }
  }
  return mindr;
}


}

bool TstarCorrectMatchDiscriminator::process(uhh2::Event & event){

     auto & hyps = event.get(h_hyps);
     //  const auto & ttbargen = event.get(h_ttbargen);
    const auto & tstargen = event.get(h_tstargen);
    auto dec = tstargen.DecayChannel();
    if(dec != TStarGen::e_muhad){
        for(auto & hyp: hyps){
            hyp.set_discriminator(config.discriminator_label, 999999);
	    hyp.set_Match_Flow(11);    //Is not muhad decay channel
        }
        return true;
    }
  
    // note that it is allowed that two partons from the hadronic ttbar decay match the same jet.
    for(auto & hyp: hyps){

      hyp.set_discriminator(config.discriminator_label, 999999);

     
        auto hadr_jets = hyp.tophad_jets();
        auto lept_jets = hyp.toplep_jets();
	auto gluonlep_jets = hyp.gluonlep_jets();
	auto gluonhad_jets = hyp.gluonhad_jets();

        if(lept_jets.size() < 1){
            hyp.set_discriminator(config.discriminator_label, 999900);
	    hyp.set_Match_Flow(10);    //Number of top lep jets not equal to 1
            continue;
        }
        if(hadr_jets.size() > 4){ // <= 3 is allowed ...
            hyp.set_discriminator(config.discriminator_label, 999800);
	    hyp.set_Match_Flow(9);    //Number of top hadr jets > 3
            continue;
        }
	
       if(gluonlep_jets.size() < 1){ 
          hyp.set_discriminator(config.discriminator_label, 999700);
	  hyp.set_Match_Flow(8);    //Number of gluon lep jets == 0
          continue;
        }
        if(gluonhad_jets.size() < 1){ 
          hyp.set_discriminator(config.discriminator_label, 999600);
	  hyp.set_Match_Flow(7);    //Number of gluon hadr jets == 0
          continue;
        }
	

        //index lists of jets that can be matched to partons
        std::set<int> matched_hadr_jets,  matched_lep_jets;

        // match b jets
        int index_l, index_h;

        float correct_dr = match_dr_gluon(tstargen.BLep(), lept_jets, index_l);
	if(index_l >= 0)  matched_lep_jets.insert(index_l);

        if(matched_lep_jets.size() != lept_jets.size()){
            hyp.set_discriminator(config.discriminator_label, 999500);
	    hyp.set_Match_Flow(5);    //Not all lep jets are matched
	    continue;
        }

	correct_dr += match_dr(tstargen.BHad(), hadr_jets, index_h);
        if(index_h >= 0) matched_hadr_jets.insert(index_h);

        //match quarks from W decays
        correct_dr += match_dr(tstargen.Q1(), hadr_jets, index_h);
	if(index_h >= 0) matched_hadr_jets.insert(index_h);

	correct_dr += match_dr(tstargen.Q2(), hadr_jets, index_h);
        if(index_h >= 0) matched_hadr_jets.insert(index_h);

        // if not all jets of the hadronic side of the reconstruction could be matched: infinite
        // value:
        if(matched_hadr_jets.size() != hadr_jets.size()){
            hyp.set_discriminator(config.discriminator_label, 999400);
	    hyp.set_Match_Flow(6);    //Not all hadr jets are matched
	    continue;
        }

	//Match Lepton 
	if( deltaR(tstargen.ChargedLepton(), hyp.lepton().v4())>0.4){
	  hyp.set_discriminator(config.discriminator_label, 999300);
	  hyp.set_Match_Flow(4);    //No match for charged lepton
	  continue;
	}

	int index_gl;
	int index_gh;
        std::set<int> matched_gluonlep_jets;
	std::set<int> matched_gluonhad_jets;

        //match Gluons from T* decays
        correct_dr += match_dr_gluon(tstargen.GluonHad(), gluonhad_jets, index_gh);
        if(index_gh >= 0) matched_gluonhad_jets.insert(index_gh);

	if(matched_gluonhad_jets.size() != gluonhad_jets.size()){
            hyp.set_discriminator(config.discriminator_label, 999200);
	    hyp.set_Match_Flow(3);    //Not all had gluon jets are matched
	    continue;
        }

	correct_dr += match_dr_gluon(tstargen.GluonLep(), gluonlep_jets, index_gl);
        if(index_gl >= 0) matched_gluonlep_jets.insert(index_gl);
         
	
	// if not all jets of the hadronic side of the reconstruction could be matched: infinite
        // value:
	if(matched_gluonlep_jets.size() != gluonlep_jets.size()){
            hyp.set_discriminator(config.discriminator_label, 999100);
	    hyp.set_Match_Flow(2);    //Not all lep gluon jets are matched
	    continue;
        }

	//check deltaR between Gen Objects
	if(deltaR(tstargen.GluonHad(), tstargen.GluonLep())<0.4){hyp.set_discriminator(config.discriminator_label, 999999);}
	if(deltaR(tstargen.GluonHad(), tstargen.BHad())<0.4){hyp.set_discriminator(config.discriminator_label, 999999);}
	if(deltaR(tstargen.GluonHad(), tstargen.Q1())<0.4){hyp.set_discriminator(config.discriminator_label, 999999);}
	if(deltaR(tstargen.GluonHad(), tstargen.Q2())<0.4){hyp.set_discriminator(config.discriminator_label, 999999);}

	//	if(deltaR(tstargen.BHad(), tstargen.Q1())<0.4){hyp.set_discriminator(config.discriminator_label, 999999);}
	//	if(deltaR(tstargen.BHad(), tstargen.Q2())<0.4){hyp.set_discriminator(config.discriminator_label, 999999);}

	if(deltaR(tstargen.GluonLep(), tstargen.BLep())<0.4){hyp.set_discriminator(config.discriminator_label, 999999);}
	if(deltaR(tstargen.GluonLep(), tstargen.BHad())<0.4){hyp.set_discriminator(config.discriminator_label, 999999);}
	if(deltaR(tstargen.GluonLep(), tstargen.Q1())<0.4){hyp.set_discriminator(config.discriminator_label, 999999);}
	if(deltaR(tstargen.GluonLep(), tstargen.Q2())<0.4){hyp.set_discriminator(config.discriminator_label, 999999);}
	if(deltaR(tstargen.BLep(), tstargen.BHad())<0.4){hyp.set_discriminator(config.discriminator_label, 999999);}

        //add deltaR between reconstructed and true neutrino
	
	if(deltaR(tstargen.Neutrino(), hyp.neutrino_v4())>1.2) {
	  hyp.set_discriminator(config.discriminator_label, 999000);
	 hyp.set_Match_Flow(1);
	  continue;
	}
	

	correct_dr += deltaR(tstargen.Neutrino(), hyp.neutrino_v4());

	 hyp.set_discriminator(config.discriminator_label, correct_dr);
	 hyp.set_Match_Flow(0);    //Default value
    }
    return true;
}




//******************* Correct Match for Reco-Studies/Shape and Resolution of Chi2-Variables 
TstarCorrectMatchDiscriminatorTTAG::TstarCorrectMatchDiscriminatorTTAG(Context & ctx, const std::string & rechyps_name, const cfg & config_): config(config_){
    h_hyps = ctx.get_handle<vector<TstarReconstructionHypothesis>>(rechyps_name);
    //h_ttbargen = ctx.get_handle<TTbarGen>(config.ttbargen_name);
    h_tstargen = ctx.get_handle<TStarGen>(config.tstargen_name);
}

bool TstarCorrectMatchDiscriminatorTTAG::process(uhh2::Event & event){
  
  auto & hyps = event.get(h_hyps);
  const auto & tstargen = event.get(h_tstargen);
  auto dec = tstargen.DecayChannel();
  
  if(dec != TStarGen::e_muhad){
    for(auto & hyp: hyps){
      hyp.set_discriminator(config.discriminator_label, 999999);
    }
    return true;
  }
  
  // note that it is allowed that two partons from the hadronic ttbar decay match the same jet.
  for(auto & hyp: hyps){
    hyp.set_discriminator(config.discriminator_label, 999999);
    
    auto tophad = hyp.tophad_v4();
    
    if(deltaR(tstargen.TopHad(), tophad) > 0.8) {hyp.set_discriminator(config.discriminator_label, 999999); continue;}
    
    
    auto lept_jets = hyp.toplep_jets();
    auto gluonlep_jets = hyp.gluonlep_jets();
    auto gluonhad_jets = hyp.gluonhad_jets();
    
    if(lept_jets.size() != 1){
      hyp.set_discriminator(config.discriminator_label, 999999);
      continue;
    }
    if(gluonlep_jets.size() != 1){ 
      hyp.set_discriminator(config.discriminator_label, 999999);
      continue;
    }
    if(gluonhad_jets.size() != 1){ 
      hyp.set_discriminator(config.discriminator_label, 999999);
      continue;
    }
    
    
    // match b jets
    int index_l;
    float correct_dr =  match_dr(tstargen.BLep(), lept_jets, index_l);
    
    
    //Match Lepton 
    if( deltaR(tstargen.ChargedLepton(), hyp.lepton().v4())>0.4){ hyp.set_discriminator(config.discriminator_label, 999999); continue;}
    
    int index_gl;
    int index_gh;
    std::set<int> matched_gluonlep_jets;
    std::set<int> matched_gluonhad_jets;
    
    //match Gluons from T* decays
    correct_dr += match_dr(tstargen.GluonHad(), gluonhad_jets, index_gh);
    if(index_gh >= 0) matched_gluonhad_jets.insert(index_gh);
    
    correct_dr += match_dr(tstargen.GluonLep(), gluonlep_jets, index_gl);
    if(index_gl >= 0) matched_gluonlep_jets.insert(index_gl);
    
    
    if(matched_gluonhad_jets.size() != gluonhad_jets.size()){
      hyp.set_discriminator(config.discriminator_label, 999999);
      continue;
    }
    
    // if not all jets of the hadronic side of the reconstruction could be matched: infinite
    // value:
    if(matched_gluonlep_jets.size() != gluonlep_jets.size()){
      hyp.set_discriminator(config.discriminator_label, 999999);
      continue;
    }
    
    
    //isolation of Jets for Testing Kinematics
    
    //add deltaR between reconstructed and true neutrino
    if(deltaR(tstargen.Neutrino(), hyp.neutrino_v4())>1.2) {hyp.set_discriminator(config.discriminator_label, 999999); continue;}
    correct_dr += deltaR(tstargen.Neutrino(), hyp.neutrino_v4());
    
    hyp.set_discriminator(config.discriminator_label, correct_dr);

  }
  return true;
}
