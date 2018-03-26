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
    TH1F* DecayChannel;
    TH1F* M_TstarTstar, *Pt_TstarTstar;
    TH1F* M_Tstar, *M_antiTstar, *M_Tstar_reco, *M_antiTstar_reco, *Pt_Tstar, *Pt_antiTstar, *phi_Tstar, *phi_antiTstar, *eta_Tstar, *eta_antiTstar, *Pt_Tstar_over_M_TstarTstar, *Pt_antiTstar_over_M_TstarTstar, *Pt_Tstar_over_shat, *Pt_antiTstar_over_shat;
    TH1F* M_top,*M_antitop, *Pt_top, *Pt_antitop, *eta_top, *eta_antitop, *phi_top, *phi_antitop, *diffabseta, *diffphi, *M_tAntiTstar_reco, *M_tTstar_reco, *Diff_Pt_gluon_top, *Diff_Pt_antigluon_antitop, *Diff_Pt_gluon_btop, *Diff_Pt_antigluon_bantitop, *Diff_Pt_gluon_WplusDecay1, *Diff_Pt_gluon_WplusDecay2, *Diff_Pt_antigluon_WminusDecay1, *Diff_Pt_antigluon_WminusDecay2;
    TH1F* Pt_gluon, *Pt_antigluon, *eta_gluon, *eta_antigluon, *phi_gluon, *phi_antigluon;
    TH1F* Pt_bottom, *Pt_antibottom, *eta_bottom, *eta_antibottom, *phi_bottom, *phi_antibottom;
    TH1F* deltaR_Tstar_decays, *deltaR_antiTstar_decays, *deltaR_top_decays, *deltaR_antitop_decays, *deltaR_gluon_antigluon;
    TH1F* deltaR_top_antitop, *deltaR_gluon_top, *deltaR_antigluon_antitop, *deltaR_antigluon_top, *deltaR_gluon_antitop;
    TH1F* deltaPhi_gluon_antigluon, *deltaPhi_top_antitop, *deltaPhi_gluon_top, *deltaPhi_antigluon_antitop, *deltaPhi_antigluon_top, *deltaPhi_gluon_antitop;
    TH2F* M_TstarTstar_vs_eta_Tstar, *M_TstarTstar_vs_eta_antiTstar, *  M_TstarTstar_vs_deltaR_Tstar, *M_TstarTstar_vs_deltaR_antiTstar;
    TH2F* shat_vs_deltaR_Tstar, *shat_vs_deltaR_antiTstar, *shat_vs_Pt_Tstar, *shat_vs_Pt_antiTstar, *Pt_Top_vs_deltaR_top, *Pt_antiTop_vs_deltaR_antitop;

    uhh2::Event::Handle<TStarGen> h_tstargen;
};
