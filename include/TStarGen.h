#pragma once

#include "UHH2/core/include/GenParticle.h"
#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"

#include <vector>


/** \brief ttbar generator truth information
 * 
 * Interpret a vector of GenParticle as ttbar event, providing easier access to
 * the various components in the ttbar decay chain.
 * 
 * The class can either be used directly by passing the genparticles vector;
 * another option is to use the TTbarGenProducer (see below), which writes the
 * result to the event container, where it can be accessed later.
 */
class TStarGen {
public:
  
  /** construct from genparticles.
   * 
   * The event should be an actual ttbar event, i.e.:
   *   - there are exactly two tops: one top and one anti-top
   *   - each top must have exactl two daughters
   *   - one of the top daughters must be a W
   *   - the Ws must have exactly two daughters
   * 
   * Note that it is allowed that more particles than those belonging to the ttbar system
   * are in genparts; those are ignored.
   * 
   * In case one of these conditions is not fulfilled, the behavior
   * depends on the throw_on_failure parameter: if it is true (the default), a runtime_error
   * is thrown with an explanation what failed. If it is false, no exception is thrown, but
   * not all contents is valid; most will return a 0 vector. The one thing guaranteed is that the
   * decaychannel will be e_notfound. If using throw_on_failure = false, it is thus a good idea
   * to check the decaychannel.
   */
  explicit TStarGen(const std::vector<GenParticle> & genparts, bool throw_on_failure = true);
  
  enum E_DecayChannel{
    e_ee, 
    e_emu,
    e_mumu,
    e_tautau,
    e_etau,
    e_mutau,
    e_ehad,
    e_muhad,
    e_tauhad,  
    e_had,
    e_notfound
  };
  
  GenParticle TStar() const;
  GenParticle AntiTStar() const;
  GenParticle gTStar() const;
  GenParticle wTStar() const;
  GenParticle bTStar() const;
  GenParticle tTStar() const;
  GenParticle tAntiTStar() const;
  GenParticle gAntiTStar() const;
  GenParticle wAntiTStar() const;
  GenParticle bAntiTStar() const;
  GenParticle wPlusDecay1() const;
  GenParticle wPlusDecay2() const;
  GenParticle wMinusDecay1() const;
  GenParticle wMinusDecay2() const;

  E_DecayChannel DecayChannel() const;

  bool IsTopHadronicDecay() const;
  bool IsAntiTopHadronicDecay() const;
  bool IsSemiLeptonicDecay() const; 

  //only for l+jets decays
  GenParticle TopLep() const; 
  GenParticle TopHad() const;
  GenParticle BLep() const;
  GenParticle BHad() const; 
  GenParticle WLep() const;
  GenParticle WHad() const; 
  GenParticle ChargedLepton() const;
  GenParticle Neutrino() const;
  GenParticle Q1() const;
  GenParticle Q2() const; 
  GenParticle GluonHad() const; 
  GenParticle GluonLep() const; 
  
 private:
   
  GenParticle m_Gluon;
 GenParticle m_TStar;
  GenParticle m_gTStar; 
  GenParticle m_bTStar;
  GenParticle m_wTStar;
  GenParticle m_tTStar;
  GenParticle m_AntiTStar;
  GenParticle m_tAntiTStar; 
  GenParticle m_gAntiTStar; 
  GenParticle m_bAntiTStar; 
  GenParticle m_wAntiTStar; 
  GenParticle m_wPlusDecay1;
  GenParticle m_wPlusDecay2;
  GenParticle m_wMinusDecay1;
  GenParticle m_wMinusDecay2;

  E_DecayChannel m_type;
};


class TStarGenProducer: public uhh2::AnalysisModule {
public:
    explicit TStarGenProducer(uhh2::Context & ctx, const std::string & name = "tstargen", bool throw_on_failure = true);
    virtual bool process(uhh2::Event & event) override;
    
private:
    uhh2::Event::Handle<TStarGen> h_tstargen;
    bool throw_on_failure;
};
