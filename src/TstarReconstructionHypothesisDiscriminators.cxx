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
    const double mass_thad = 177;
    const double mass_thad_sigma = 19;
    const double mass_tlep = 181;
    const double mass_tlep_sigma = 27;
    
    //T* values (Masspoint independend)
    const double mass_Tstar_diff_rel = 0.0074; //Average CorrectMatch
    const double mass_Tstar_diff_rel_sigma = 0.1189; //

    //Make use of topology
    const double deltaPhi_Tstar = 3.13;
    const double deltaPhi_sigma = 0.144;
    
    for(auto & hyp: hyps){
        double mass_thad_rec = inv_mass(hyp.tophad_v4());
        double mass_tlep_rec = inv_mass(hyp.toplep_v4());

	double mass_Tstar_had_rec = inv_mass(hyp.Tstarhad_v4());
	double mass_Tstar_lep_rec = inv_mass(hyp.Tstarlep_v4());
	double mass_Tstar_mean_rec = (mass_Tstar_had_rec + mass_Tstar_lep_rec)/2;

	double deltaPhi_Tstar_rec     = (hyp.Tstarhad_v4().phi()-hyp.Tstarlep_v4().phi());
	
	//Compute Chi2 Terms 
        double chi2_thad            = pow((mass_thad_rec - mass_thad) / mass_thad_sigma, 2);
        double chi2_tlep            = pow((mass_tlep_rec - mass_tlep) / mass_tlep_sigma, 2);
	double chi2_MTstar_diff_rel = pow(((mass_Tstar_had_rec - mass_Tstar_lep_rec)/mass_Tstar_mean_rec - mass_Tstar_diff_rel) / mass_Tstar_diff_rel_sigma, 2);
	double chi2_deltaPhi        = pow((deltaPhi_Tstar_rec - deltaPhi_Tstar)/deltaPhi_sigma ,2);
	
	//Make use of b-Jet in Events 
	/*
	double chi2_bTag_lep = 0;
	
	int size_lep = hyp.gluonlep_jets().size();
	for(int i=0; i<size_lep; ++i){
	double gluonlep_csv = hyp.gluonlep_jets().at(i).btag_combinedSecondaryVertex();
	double bTag_lep = 0;
	if(0   < gluonlep_csv && gluonlep_csv <= 0.1) bTag_lep = -8.59;
	if(0.1 < gluonlep_csv && gluonlep_csv <= 0.2) bTag_lep = -5.55;
	if(0.2 < gluonlep_csv && gluonlep_csv <= 0.3) bTag_lep = -3.38;
	if(0.3 < gluonlep_csv && gluonlep_csv <= 0.4) bTag_lep = -1.97;
	if(0.4 < gluonlep_csv && gluonlep_csv<= 0.5) bTag_lep = -1.00;
	if(0.5 < gluonlep_csv && gluonlep_csv<= 0.6) bTag_lep =  0.09;
	if(0.6 < gluonlep_csv && gluonlep_csv<= 0.7) bTag_lep =  1.03;
	if(0.7 < gluonlep_csv && gluonlep_csv<= 0.8) bTag_lep =  2.06;
	if(0.8 < gluonlep_csv && gluonlep_csv<= 0.9) bTag_lep =  3.42;
	if(0.9 < gluonlep_csv && gluonlep_csv<= 1)   bTag_lep =  5.71;

	chi2_bTag_lep = chi2_bTag_lep+bTag_lep;
	}

	double chi2_bTag_had = 0;
	
	int size_had = hyp.gluonhad_jets().size();
	for(int i=0; i<size_had; ++i){
	double gluonhad_csv = hyp.gluonhad_jets().at(i).btag_combinedSecondaryVertex();
	double bTag_had = 0;
	if(0   < gluonhad_csv && gluonhad_csv <= 0.1) bTag_had = -8.59;
	if(0.1 < gluonhad_csv && gluonhad_csv <= 0.2) bTag_had = -5.55;
	if(0.2 < gluonhad_csv && gluonhad_csv <= 0.3) bTag_had = -3.38;
	if(0.3 < gluonhad_csv && gluonhad_csv <= 0.4) bTag_had = -1.97;
	if(0.4 < gluonhad_csv && gluonhad_csv<= 0.5) bTag_had = -1.00;
	if(0.5 < gluonhad_csv && gluonhad_csv<= 0.6) bTag_had =  0.09;
	if(0.6 < gluonhad_csv && gluonhad_csv<= 0.7) bTag_had =  1.03;
	if(0.7 < gluonhad_csv && gluonhad_csv<= 0.8) bTag_had =  2.06;
	if(0.8 < gluonhad_csv && gluonhad_csv<= 0.9) bTag_had =  3.42;
	if(0.9 < gluonhad_csv && gluonhad_csv<= 1)   bTag_had =  5.71;

	chi2_bTag_had = chi2_bTag_had+bTag_had;
	}
	*/
	//##############################################################################################

        hyp.set_discriminator(config.discriminator_label, chi2_thad + chi2_tlep +chi2_MTstar_diff_rel+chi2_deltaPhi/*+(chi2_bTag_lep/size_lep + chi2_bTag_had/size_had)/2)*/); 
	hyp.set_discriminator(config.discriminator_label + "_tlep", chi2_tlep);
        hyp.set_discriminator(config.discriminator_label + "_thad", chi2_thad);
	hyp.set_discriminator(config.discriminator_label + "_MTstar_rel", chi2_MTstar_diff_rel);
	hyp.set_discriminator(config.discriminator_label + "_deltaPhi", chi2_deltaPhi);
	//hyp.set_discriminator(config.discriminator_label + "_bTag", (chi2_bTag_lep/size_lep+chi2_bTag_had/size_had)/2);
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
  const double mass_thad       = 177.;
  const double mass_thad_sigma =  19.;
  const double mass_tlep       = 181.;
  const double mass_tlep_sigma =  27.;

  //T* values
  const double mass_Tstar_diff_rel = 0.0074; //How to get
  const double mass_Tstar_diff_rel_sigma = 0.119; //How to get

  //Topology
  const double deltaPhi_Tstar = 3.13;
  const double deltaPhi_sigma = 0.144;

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
    double mass_Tstar_mean_rec = (mass_Tstar_had_rec + mass_Tstar_lep_rec)/2;

    double deltaPhi_Tstar_rec     = (hyp.Tstarhad_v4().phi()-hyp.Tstarlep_v4().phi());

    //Compute Chi2 Terms   
    const double chi2_thad            = pow((mass_thad_rec - mass_thad) / mass_thad_sigma, 2);
    const double chi2_tlep            = pow((mass_tlep_rec - mass_tlep) / mass_tlep_sigma, 2);
    const double chi2_MTstar_diff_rel = pow(((mass_Tstar_had_rec - mass_Tstar_lep_rec)/mass_Tstar_mean_rec - mass_Tstar_diff_rel) / mass_Tstar_diff_rel_sigma, 2);
    double chi2_deltaPhi              = pow((deltaPhi_Tstar_rec - deltaPhi_Tstar)/deltaPhi_sigma ,2);
 
    // Make use of b-Jet in Events
    /*
	double chi2_bTag_lep = 0;
	
	int size_lep = hyp.gluonlep_jets().size();
	for(int i=0; i<size_lep; ++i){
	double gluonlep_csv = hyp.gluonlep_jets().at(i).btag_combinedSecondaryVertex();
	double bTag_lep = 0;
	if(0   < gluonlep_csv && gluonlep_csv <= 0.1) bTag_lep = -8.59;
	if(0.1 < gluonlep_csv && gluonlep_csv <= 0.2) bTag_lep = -5.55;
	if(0.2 < gluonlep_csv && gluonlep_csv <= 0.3) bTag_lep = -3.38;
	if(0.3 < gluonlep_csv && gluonlep_csv <= 0.4) bTag_lep = -1.97;
	if(0.4 < gluonlep_csv && gluonlep_csv<= 0.5) bTag_lep = -1.00;
	if(0.5 < gluonlep_csv && gluonlep_csv<= 0.6) bTag_lep =  0.09;
	if(0.6 < gluonlep_csv && gluonlep_csv<= 0.7) bTag_lep =  1.03;
	if(0.7 < gluonlep_csv && gluonlep_csv<= 0.8) bTag_lep =  2.06;
	if(0.8 < gluonlep_csv && gluonlep_csv<= 0.9) bTag_lep =  3.42;
	if(0.9 < gluonlep_csv && gluonlep_csv<= 1)   bTag_lep =  5.71;

	chi2_bTag_lep = chi2_bTag_lep+bTag_lep;
	}

	double chi2_bTag_had = 0;
	
	int size_had = hyp.gluonhad_jets().size();
	for(int i=0; i<size_had; ++i){
	double gluonhad_csv = hyp.gluonhad_jets().at(i).btag_combinedSecondaryVertex();
	double bTag_had = 0;
	if(0   < gluonhad_csv && gluonhad_csv <= 0.1) bTag_had = -8.59;
	if(0.1 < gluonhad_csv && gluonhad_csv <= 0.2) bTag_had = -5.55;
	if(0.2 < gluonhad_csv && gluonhad_csv <= 0.3) bTag_had = -3.38;
	if(0.3 < gluonhad_csv && gluonhad_csv <= 0.4) bTag_had = -1.97;
	if(0.4 < gluonhad_csv && gluonhad_csv<= 0.5) bTag_had = -1.00;
	if(0.5 < gluonhad_csv && gluonhad_csv<= 0.6) bTag_had =  0.09;
	if(0.6 < gluonhad_csv && gluonhad_csv<= 0.7) bTag_had =  1.03;
	if(0.7 < gluonhad_csv && gluonhad_csv<= 0.8) bTag_had =  2.06;
	if(0.8 < gluonhad_csv && gluonhad_csv<= 0.9) bTag_had =  3.42;
	if(0.9 < gluonhad_csv && gluonhad_csv<= 1)   bTag_had =  5.71;

	chi2_bTag_had = chi2_bTag_had+bTag_had;
	}
    */
    //###############################################################################################

    hyp.set_discriminator(config.discriminator_label, chi2_thad + chi2_tlep + chi2_MTstar_diff_rel + chi2_deltaPhi/*+ (chi2_bTag_lep/size_lep + chi2_bTag_had/size_had)/2)*/); 
	hyp.set_discriminator(config.discriminator_label + "_tlep", chi2_tlep);
        hyp.set_discriminator(config.discriminator_label + "_thad", chi2_thad);
	hyp.set_discriminator(config.discriminator_label + "_MTstar_rel", chi2_MTstar_diff_rel);
	hyp.set_discriminator(config.discriminator_label + "_deltaPhi", chi2_deltaPhi);
	//hyp.set_discriminator(config.discriminator_label + "_bTag",(chi2_bTag_lep/size_lep + chi2_bTag_had/size_had)/2);
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
    //h_ttbargen = ctx.get_handle<TTbarGen>(config.ttbargen_name);
    h_tstargen = ctx.get_handle<TStarGen>(config.tstargen_name);
}

namespace {
// match particle p to one of the jets (Delta R < 0.4); 
// return the deltaR of the match.

template<typename T> // T should inherit from Particle
float match_dr(const Particle & p, const std::vector<T> & jets, int& index){
  float mindr = 999999;
  index = -1;
  for(unsigned int i=0; i<jets.size(); ++i){
    float dR = deltaR(p, jets.at(i));
    if( dR <0.4 && dR<mindr) { 
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

        if(lept_jets.size() != 1){
            hyp.set_discriminator(config.discriminator_label, 999999);
            continue;
        }
        if(hadr_jets.size() > 3){ // <= 3 is allowed ...
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


        //index lists of jets that can be matched to partons
        std::set<int> matched_hadr_jets;

        // match b jets
        int index_l, index_h;

        float correct_dr = match_dr(tstargen.BLep(), lept_jets, index_l);
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
            hyp.set_discriminator(config.discriminator_label, 999999);
	    continue;
        }


	//Match Lepton 
	//	if( deltaR(tstargen.ChargedLepton(), hyp.lepton().v4())>0.3){ hyp.set_discriminator(config.discriminator_label, 999999); continue;}

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
	
	int dummie_index;
	if(match_dr(tstargen.GluonHad(), gluonlep_jets, dummie_index) <= 0.4) {hyp.set_discriminator(config.discriminator_label, 999999); continue;}
	if(match_dr(tstargen.GluonLep(), gluonhad_jets, dummie_index) <= 0.4) {hyp.set_discriminator(config.discriminator_label, 999999); continue;}

	if(match_dr(tstargen.Q1(), lept_jets, dummie_index) <= 0.4) {hyp.set_discriminator(config.discriminator_label, 999999); continue;}
	if(match_dr(tstargen.Q2(), lept_jets, dummie_index) <= 0.4) {hyp.set_discriminator(config.discriminator_label, 999999); continue;}
	if(match_dr(tstargen.BHad(), lept_jets, dummie_index) <= 0.4) {hyp.set_discriminator(config.discriminator_label, 999999); continue;}
	if(match_dr(tstargen.BLep(), hadr_jets, dummie_index) <= 0.4) {hyp.set_discriminator(config.discriminator_label, 999999); continue;}

	if(match_dr(tstargen.Q1(), gluonhad_jets, dummie_index) <= 0.4) {hyp.set_discriminator(config.discriminator_label, 999999); continue;}
	if(match_dr(tstargen.Q2(), gluonhad_jets, dummie_index) <= 0.4) {hyp.set_discriminator(config.discriminator_label, 999999); continue;}
	if(match_dr(tstargen.BHad(), gluonhad_jets, dummie_index) <= 0.4) {hyp.set_discriminator(config.discriminator_label, 999999); continue;}

	if(match_dr(tstargen.BLep(), gluonlep_jets, dummie_index) <= 0.4) {hyp.set_discriminator(config.discriminator_label, 999999); continue;}

	if(match_dr(tstargen.Q1(), gluonlep_jets, dummie_index) <= 0.4) {hyp.set_discriminator(config.discriminator_label, 999999); continue;}
	if(match_dr(tstargen.Q2(), gluonlep_jets, dummie_index) <= 0.4) {hyp.set_discriminator(config.discriminator_label, 999999); continue;}
	if(match_dr(tstargen.BHad(), gluonlep_jets, dummie_index) <= 0.4) {hyp.set_discriminator(config.discriminator_label, 999999); continue;}

	if(match_dr(tstargen.BLep(), gluonhad_jets, dummie_index) <= 0.4) {hyp.set_discriminator(config.discriminator_label, 999999); continue;}
	
        //add deltaR between reconstructed and true neutrino
	if(deltaR(tstargen.Neutrino(), hyp.neutrino_v4())>0.4) {hyp.set_discriminator(config.discriminator_label, 999999); continue;}
	   correct_dr += deltaR(tstargen.Neutrino(), hyp.neutrino_v4());

	 hyp.set_discriminator(config.discriminator_label, correct_dr);
    }
    return true;
}
