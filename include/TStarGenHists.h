#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/TstarSemiLeptonic/include/TStarGen.h"

/** \brief Histograms for tstar quantities on generator (parton) level
 * 
 * TTbarGen container has to be filled before calling this histogram class
 */
class TStarGenHists: public uhh2::Hists {
public:
    TStarGenHists(uhh2::Context & ctx, const std::string & dirname);

    virtual void fill(const uhh2::Event & t) override;

protected:
    TH1F* M_TStar_gen, *Pt_TStarTStar_gen, *shat, *M_tstar, *M_antitstar,*M_TStar_reco,*M_AntiTStar_reco,*M_tTStar_reco,*M_tAntiTStar_reco, *Pt_tstar, *Pt_antitstar, *Pt_top_over_shat, *Pt_antitop_over_shat, *Pt_top_over_M_ttbar, *Pt_antitop_over_M_ttbar, *y_tstar, *y_antitstar, *eta_TStar, *eta_AntiTStar, *diffabseta, *diffabsy, *deltaR_tstar_decays, *deltaR_antitstar_decays, *deltaR_top_decays, *deltaR_antitop_decays, *Pt_top, *Pt_antitop, *eta_top, *eta_antitop,*Pt_gluon, *Pt_antigluon, *eta_gluon, *eta_antigluon, *y_b, *y_antib, *M_top, *M_antitop, *Pt_Wplus, *Pt_Wminus, *eta_Wplus, *eta_Wminus, *y_Wplus, *y_Wminus, *M_Wplus, *M_Wminus, *cosThetastar_top_ttframe, *cosThetastar_antitop_ttframe, *Pt_top_ttframe, *Pt_antitop_ttframe, *DecayChannel, *Match_Gluon;

    TH2F* M_ttbar_vs_shat, *M_ttbar_vs_deltaR_top, *M_ttbar_vs_deltaR_antitop, *shat_vs_deltaR_top, *shat_vs_deltaR_antitop, *Pt_top_vs_deltaR_top, *Pt_antitop_vs_deltaR_antitop, *M_ttbar_vs_deltaR_Wplus, *M_ttbar_vs_deltaR_Wminus, *M_ttbar_vs_Pt_top, *M_ttbar_vs_Pt_antitop, *shat_vs_Pt_top, *shat_vs_Pt_antitop, *Pt_top_vs_Pt_antitop, *M_ttbar_vs_Pt_top_ttframe, *M_ttbar_vs_Pt_antitop_ttframe, *M_ttbar_vs_eta_top, *M_ttbar_vs_eta_antitop;
    uhh2::Event::Handle<TStarGen> h_tstargen;
};
