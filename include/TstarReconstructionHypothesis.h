#pragma once

#include "UHH2/core/include/Particle.h"
#include "UHH2/core/include/TopJet.h"
#include <map>

/**
 *  @short container class to store the results of the top quark reconstruction
 * 
 * The top quarks reconstruction only applied to semileptonic ttbar events. A
 * ReconstructionHypothesis then consists of finding the lepton, and assigning the jets of the event
 * to either the leptonically decaying top or the hadronically decaying top. In addition
 * to accessing these information (i.e., which jets are assigned to which side, etc.), each
 * hypothesis can have a number of associated *discriminators*. A discriminator is identified
 * by name and is a floating point value meant to measure how 'good' the hypothesis is according to some criterion;
 * see ReconstructionHypothesisDiscriminators.h for different criteria and to fill the discriminators.
 */
class TstarReconstructionHypothesis {
public:
  explicit TstarReconstructionHypothesis(){ m_tophad_topjet_ptr = 0; }

  LorentzVector toplep_v4() const{return m_toplep_v4;}
  LorentzVector tophad_v4() const{return m_tophad_v4;} 
  LorentzVector neutrino_v4() const{return m_neutrino_v4;} 
  Particle lepton() const{return m_lepton;}
  const std::vector<Jet>& toplep_jets() const{return m_toplep_jets;}
  const std::vector<Jet>& tophad_jets() const{return m_tophad_jets;}
  const TopJet* tophad_topjet_ptr() const{return m_tophad_topjet_ptr;}
  LorentzVector top_v4() const{ return m_lepton.charge() > 0 ? m_toplep_v4 : m_tophad_v4;}
  LorentzVector antitop_v4() const{ return m_lepton.charge() < 0 ? m_toplep_v4 : m_tophad_v4;}
  LorentzVector wlep_v4() const{ return m_neutrino_v4+m_lepton.v4();}
  LorentzVector blep_v4() const{return m_blep_v4;}
  LorentzVector bhad_v4() const{return m_bhad_v4;}

  const std::vector<Jet>& bhad_jets() const{return m_bhad_jets;}
  const std::vector<Jet>& blep_jets() const{return m_blep_jets;}

  const std::vector<Jet>& gluon_jets() const{return m_gluon_jets;}

  LorentzVector gluonhad_v4() const{return m_gluonhad_v4;}
  LorentzVector gluonlep_v4() const{return m_gluonlep_v4;}
  const std::vector<Jet>& gluonhad_jets() const{return m_gluonhad_jets;}
  const std::vector<Jet>& gluonlep_jets() const{return m_gluonlep_jets;}

  Particle gluonhad() const{return m_gluonhad;}
  Particle gluonlep() const{return m_gluonlep;}

  LorentzVector Tstarhad_v4() const{return m_gluonhad_v4+m_tophad_v4;}
  LorentzVector Tstarlep_v4() const{return m_gluonlep_v4+m_toplep_v4;} 

  int Match_Flow() const{return m_match_flow;}

  int Gluon_Had_num() const{return m_gluon_had_num;}
  int Gluon_Lep_num() const{return m_gluon_had_num;}

  /// get the discriminator value for this hypothesis; thows a runtime_error if it does not exist.
  float discriminator(const std::string & l) const {
      auto it = m_discriminators.find(l);
      if(it == m_discriminators.end()){
          throw std::runtime_error("ReconstructionHypothesis::discriminator: discriminator with label '" + l + "' not set");
      }
      return it->second;
  }
  
  /// test if a discriminator value with a certian label has already been added
  bool has_discriminator(const std::string & label) const {
      return m_discriminators.find(label) != m_discriminators.end();
  }
  std::string get_tophad_Jet(){return tophad_jet;}
  std::string get_toplep_Jet(){return toplep_jet;}

  std::string get_gluon_Jet(){return gluon_jet;}

  void set_blep_v4(LorentzVector v4){m_blep_v4=v4;}
  void set_bhad_v4(LorentzVector v4){m_bhad_v4=v4;}
  void add_bhad_jet(const Jet& j){m_bhad_jets.push_back(j);}
  void add_blep_jet(const Jet& j){m_blep_jets.push_back(j);}
  
  void set_tophad_jets(std::string jets){tophad_jet = jets;}
  void set_toplep_jets(std::string jets){toplep_jet = jets;}
  void set_neutrino_v4(LorentzVector v4){m_neutrino_v4=v4;}
  void set_toplep_v4(LorentzVector v4){m_toplep_v4=v4;}
  void set_tophad_v4(LorentzVector v4){m_tophad_v4=v4;} 
  void add_toplep_jet(const Jet& j){m_toplep_jets.push_back(j);}
  void add_tophad_jet(const Jet& j){m_tophad_jets.push_back(j);}

  void set_unusedJets(std::string jets){unused_jets = jets;}
  void set_unusedJets_lep(std::string jets){unused_jets_lep = jets;}
  void set_unusedJets_had(std::string jets){unused_jets_had = jets;}

  void set_tophad_topjet_ptr(const TopJet* const tjp){m_tophad_topjet_ptr = tjp;}
  void set_lepton(const Particle & l){m_lepton = l;}

  void set_gluonjets(std::string jets){gluon_jet = jets;}
  void add_gluon_jet(const Jet& j){m_gluon_jets.push_back(j);}

  void set_gluonhad_v4(LorentzVector v4){m_gluonhad_v4=v4;}
  void set_gluonlep_v4(LorentzVector v4){m_gluonlep_v4=v4;}
  void set_gluonhad_jets(std::string jets){gluonhad_jet = jets;}
  void set_gluonlep_jets(std::string jets){gluonlep_jet = jets;}
  void add_gluonhad_jet(const Jet& j){m_gluonhad_jets.push_back(j);}
  void add_gluonlep_jet(const Jet& j){m_gluonlep_jets.push_back(j);}

  void add_gluon_jets(const Jet& j){m_gluon_jets.push_back(j);}

  void set_discriminator(const std::string & label, float discr){
	//std::cout<<"Discriminator_Label: "<<label<<std::endl;
      m_discriminators[label] = discr;
  }
  void set_Match_Flow(const int match_flow){m_match_flow = match_flow;}
  void set_Gluon_Had_num(const int num_had){m_gluon_had_num = num_had;}
  void set_Gluon_Lep_num(const int num_lep){m_gluon_lep_num = num_lep;}


private:
  std::vector<LorentzVector> tophad_lorentz;
  std::vector<LorentzVector> toplep_lorentz;
  std::string unused_jets;
  std::string unused_jets_lep;
  std::string unused_jets_had;

  std::string gluon_jet;
  std::string tophad_jet;
  std::string toplep_jet;

  LorentzVector m_blep_v4;
  LorentzVector m_bhad_v4;
  LorentzVector m_toplep_v4;
  LorentzVector m_tophad_v4;
  LorentzVector m_neutrino_v4;
  
  LorentzVector m_gluonhad_v4;
  LorentzVector m_gluonlep_v4;

  int m_match_flow;
  int m_gluon_had_num;
  int m_gluon_lep_num;
  
  std::string gluonhad_jet;
  std::string gluonlep_jet;

  std::vector<Jet> m_gluonhad_jets;
  std::vector<Jet> m_gluonlep_jets;

  std::vector<Jet> m_bhad_jets;
  std::vector<Jet> m_blep_jets;


  std::vector<Jet> m_toplep_jets;
  std::vector<Jet> m_tophad_jets;
 
  std::vector<Jet> m_gluon_jets;

  const TopJet* m_tophad_topjet_ptr;
  Particle m_lepton;
  Particle m_gluonhad;
  Particle m_gluonlep;

  std::map<std::string, float> m_discriminators;
};

