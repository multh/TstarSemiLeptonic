#include "UHH2/TstarSemiLeptonic/include/TStarGen.h"    
using namespace std;
using namespace uhh2;

TStarGen::TStarGen(const vector<GenParticle> & genparticles, bool throw_on_failure): m_type(e_notfound) {    //: m_type(e_notfound) specifies Decay Channel?
  int n_TStar = 0, n_AntiTStar = 0;
  for(unsigned int i=0; i<genparticles.size(); ++i) {
    const GenParticle & genp = genparticles[i];
    if (abs(genp.pdgId()) == 9000005){                     //Identify T*
      auto t = genp.daughter(&genparticles, 1);        //Hypothesis: First daughter as top
      auto g = genp.daughter(&genparticles, 2);        //Hypothesis: Second daughter gluon

      //Check Hypothesis 
      if(!t || !g){                                    //No two daughters  
	if(throw_on_failure) throw runtime_error("TStarGen: TStar has not ==2 daughters");
	return;
      }
      if(abs(t->pdgId()) != 6){                        //Switch particles, if top hypothesis is wrong
	std::swap(t, g);
	cout<<"swap Particles"<<endl;
      }
      if(abs(t->pdgId()) != 6){                        //No top daughter: Return failure 
	if(throw_on_failure) throw runtime_error("TStarGen: TSTar has no Top daughter");
	return;
      }
      if(abs(g->pdgId()) != 21){                       //No gluon daughter: Return failure
	if(throw_on_failure) throw runtime_error("TStarGen: TSTar has no Gluon daughter");
	return;
      }
            
      // now get top daughters:              
      auto w = t->daughter(&genparticles, 1);        //Hypothesis: First daughter as W
      auto b = t->daughter(&genparticles, 2);        //Hypothesis: Second daughter as b
      
      //Check Hypothesis
      if(!w || !b){                                  //No two daughters 
	if(throw_on_failure) throw runtime_error("TStarGen: top has not ==2 daughters");
	return;
      }
      if(abs(w->pdgId()) != 24){                     //Switch particles, if W hypothesis is wrong
	std::swap(w, b);
	cout<<"swap Particles"<<endl;
      }
      if(abs(w->pdgId()) != 24){                     //No W daughter: Return failure 
	if(throw_on_failure) throw runtime_error("TStarGen: top has no W daughter");
	return;
      }


      // now get w daughters:                 
      auto wd1 = w->daughter(&genparticles, 1);      
      auto wd2 = w->daughter(&genparticles, 2);

      
      if(!wd1 || !wd2){                              //No two daughters
	if(throw_on_failure) throw runtime_error("TStarGen: W has not == 2 daughters");
	return;
      }
      
      // now that we collected everything, fill the member variables. 
      // Use different member variables according to T* charge.

      if(genp.pdgId() == 9000005){
	m_TStar       = genp;
	m_tTStar      = *t;
	m_gTStar      = *g;
	m_wTStar      = *w;
	m_bTStar      = *b;
	m_wPlusDecay1 = *wd1;
	m_wPlusDecay2 = *wd2;
	++n_TStar;
      }
      else{
	m_AntiTStar    = genp;
	m_tAntiTStar   = *t;
	m_gAntiTStar   = *g;
	m_wAntiTStar   = *w;
	m_bAntiTStar   = *b;
	m_wMinusDecay1 = *wd1;
	m_wMinusDecay2 = *wd2;
	++n_AntiTStar;
      }
    }
    
  }
   
    //If no TStar and AntiTStar in Event, throw error
    if(n_TStar != 1 || n_AntiTStar != 1){
        if(throw_on_failure)  throw runtime_error("TStarGen: did not find exactly one TStar and one AntiTStar in the event");
        return;
    }
    
    // calculate decay channel by counting the number of charged leptons
    // in the W daughters:
    int n_e = 0, n_m = 0, n_t = 0;
    for(const auto & wd : {m_wPlusDecay1, m_wPlusDecay2, m_wMinusDecay1, m_wMinusDecay2}){
        int id = abs(wd.pdgId());
        if(id == 11) ++n_e;
        else if(id == 13) ++n_m;
	else if(id == 15) ++n_t;

    }

    // dilepton channels:
    if(n_e == 2){                   //di-electron channel
      m_type = e_ee;
    }
    else if(n_e == 1 && n_m == 1){  //electron-muon channel
      m_type = e_emu;
    }
    
    else if(n_e == 1 && n_t == 1){  //electron-tau channel
      m_type = e_etau;
    }
    else if(n_m == 2){              //di-muon channel
      m_type = e_mumu;
    }
    else if(n_m == 1 && n_t == 1){  //muon-tau channel
      m_type = e_mutau;
    }
    else if(n_t == 2){              //tau channel
      m_type = e_tautau;
    }
    
    // lepton+jet channels:
    else if(n_e == 1){              //electron+jets channel
      m_type = e_ehad;
    }
    else if(n_m == 1){              //muon+jets channel
      m_type = e_muhad;
    }
    else if(n_t == 1){              //tau+jets channel
      m_type = e_tauhad;
    }
    
    // hadronic:
    else{ 
      m_type = e_had;               //full hadronic channel
    }
}   
    

//Save member variables as GenParticle objects
GenParticle TStarGen::TStar() const{   
    return m_TStar;
}

GenParticle TStarGen::tTStar() const{ 
    return m_tTStar;
}

GenParticle TStarGen::gTStar() const{
    return m_gTStar;
}

GenParticle TStarGen::wTStar() const{
    return m_wTStar;
}

GenParticle TStarGen::bTStar() const{
    return m_bTStar;
}


GenParticle TStarGen::AntiTStar() const{
    return m_AntiTStar;
}
GenParticle TStarGen::tAntiTStar() const{
    return m_tAntiTStar;
}

GenParticle TStarGen::gAntiTStar() const{
    return m_gAntiTStar;
}

GenParticle TStarGen::wAntiTStar() const{
    return m_wAntiTStar;
}

GenParticle TStarGen::bAntiTStar() const{
    return m_bAntiTStar;
}

GenParticle TStarGen::wPlusDecay1() const{
    return m_wPlusDecay1;
}
GenParticle TStarGen::wPlusDecay2() const{
    return m_wPlusDecay2;
}
GenParticle TStarGen::wMinusDecay1() const{
    return m_wMinusDecay1;
}
GenParticle TStarGen::wMinusDecay2() const{
    return m_wMinusDecay2;
}


TStarGen::E_DecayChannel TStarGen::DecayChannel()  const{  
    return m_type;
}

bool TStarGen::IsTopHadronicDecay()  const{
    return abs(m_wPlusDecay1.pdgId()) <= 5;
}

bool TStarGen::IsAntiTopHadronicDecay()  const{
    return abs(m_wMinusDecay1.pdgId()) <= 5;
}

bool TStarGen::IsSemiLeptonicDecay() const{
   return m_type == e_ehad ||  m_type == e_muhad ||m_type == e_tauhad;  
}


namespace {
    
bool is_charged_lepton(const GenParticle & gp){
    int id = abs(gp.pdgId());
    return id == 11 || id == 13 || id == 15;
}

bool is_neutrino(const GenParticle & gp){
    int id = abs(gp.pdgId());
    return id == 12 || id == 14 || id == 16;
}

}


GenParticle TStarGen::ChargedLepton() const{
    if (m_type != e_ehad &&  m_type != e_muhad && m_type!= e_tauhad){
        throw runtime_error("TStarGen::ChargedLepton called, but this is no l+jets ttbar event!");
    }
    for(const auto & wd : {m_wPlusDecay1, m_wPlusDecay2, m_wMinusDecay1, m_wMinusDecay2}){
        if(is_charged_lepton(wd)) return wd;
    }
    throw logic_error("logic error in TStarGen::ChargedLepton");
}

GenParticle TStarGen::Neutrino() const{
   if (m_type != e_ehad &&  m_type != e_muhad && m_type!= e_tauhad){
        throw runtime_error("TStarGen::ChargedLepton Neutrino called, but this is no l+jets ttbar event!");
    }
    for(const auto & wd : {m_wPlusDecay1, m_wPlusDecay2, m_wMinusDecay1, m_wMinusDecay2}){
        if(is_neutrino(wd)) return wd;
    }
    throw logic_error("logic error in TTbarGen::Neutrino");
}

GenParticle TStarGen::TopLep() const{
    if(ChargedLepton().charge()>0) return tTStar();
    else return tAntiTStar();
}

GenParticle TStarGen::TopHad() const{
    if(ChargedLepton().charge()<0) return tTStar();
    else return tAntiTStar();
}


GenParticle TStarGen::GluonHad() const{
  if(ChargedLepton().charge()<0) return gTStar();
  else return gAntiTStar();  
}

GenParticle TStarGen::GluonLep() const{
  if(ChargedLepton().charge()>0) return gTStar();
  else return gAntiTStar();  
}


GenParticle TStarGen::BLep() const{
    if(ChargedLepton().charge()>0) return bTStar();
    else return bAntiTStar();
}

GenParticle TStarGen::BHad() const{
    if(ChargedLepton().charge()<0) return bTStar();
    else return bAntiTStar();
}

GenParticle TStarGen::WLep() const{
    if(ChargedLepton().charge()>0) return wTStar();
    else return wAntiTStar();
}

GenParticle TStarGen::WHad() const{
    if(ChargedLepton().charge()<0) return wTStar();
    else return wAntiTStar();
}

GenParticle TStarGen::Q1() const{
    if(ChargedLepton().charge()>0) return wMinusDecay1();
    else return wPlusDecay1();
}

GenParticle TStarGen::Q2() const{
    if(ChargedLepton().charge()>0) return wMinusDecay2();
    else return wPlusDecay2();
}



TStarGenProducer::TStarGenProducer(uhh2::Context & ctx, const std::string & name, bool throw_on_failure_): throw_on_failure(throw_on_failure_){
    h_tstargen = ctx.get_handle<TStarGen>(name);
}

bool TStarGenProducer::process(Event & event){
  event.set(h_tstargen, TStarGen(*event.genparticles, throw_on_failure));
    return true;
}

