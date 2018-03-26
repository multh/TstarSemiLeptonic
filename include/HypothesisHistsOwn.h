#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/TstarSemiLeptonic/include/TstarReconstructionHypothesisDiscriminators.h"
#include "UHH2/TstarSemiLeptonic/include/TstarReconstructionHypothesis.h"
#include "UHH2/TstarSemiLeptonic/include/TStarGen.h"

/** \brief Common histograms for reconstruction hypotheses
 *
 * hyps_name is the name of the reconstruction hypothesis collection, for instance "HighMassReconstruction"
 * discriminator_name is the name of the discriminator used to choose the best reconstruction hypothesis, for instance "Chi2"
 */
class HypothesisHistsOwn: public uhh2::Hists {
public:
    HypothesisHistsOwn(uhh2::Context & ctx, const std::string & dirname, const std::string & hyps_name, const std::string & discriminator_name);
    bool is_data;
    virtual void fill(const uhh2::Event & ev) override;

protected:
    TH1F *Discriminator_sum, *Discriminator_1, *Discriminator_2, *Discriminator_3, *Discriminator_4, *Discriminator_5;
    TH1F * M_TstarhadTstarlep_rec,  *M_Tstarlep_rec, *M_Tstarhad_rec, *M_Tstar_comb, *Pt_Tstarlep_rec, *Pt_Tstarhad_rec, *Pt_TstarhadTstarlep_rec,  *M_TstarAntiTstar_resolution, *M_Tstar_resolution, *Pt_toplep_rec, *Pt_tophad_rec, *M_toplep_rec, *M_tophad_rec, *Number_tophad_jets, *Number_toplep_jets,  *M_TstarhadTstarlep_Diff, *M_TstarhadTstarlep_Diff_rel, * M_Wlep_rec, *M_toplep_Wlep, *M_Tstarlep_Wlep, *M_Tstar_comb_Wlep, *DeltaR_Lepton, *DeltaR_Neutrino, *Number_gluonlep_jets, *Number_gluonhad_jets ;

    TH1F * M_TstarAntiTstar_gen, *Pt_TstarAntiTstar_gen, *M_Whad_gen ;
    
    TH1F *Pt_Diff_gluonhad_tophad, *Pt_Diff_gluonlep_toplep, *Pt_Diff_gluonhad_bhad, *Pt_Diff_gluonlep_blep, *Pt_Diff_gluonhad_blep, *Pt_Diff_gluonlep_bhad, *Pt_Diff_gluonlep_Wlep;

    TH1F * DeltaPhi_TstarhadTstarlep, *DeltaPhi_TophadGluonhad, *DeltaPhi_ToplepGluonlep, *DeltaPhi_TophadToplep,  *DeltaPhi_GluonGluon;
    
    TH1F * DeltaPhi_TstarAntiTstar_gen, *DeltaPhi_TopGluon_gen,*DeltaPhi_AntiTopAntiGluon_gen, *DeltaPhi_TopAntiTop_gen, *DeltaPhi_GluonGluon_gen;
    
    TH1F *  DeltaEta_TstarhadTstarlep, *DeltaEta_TstarAntiTstar_gen, *DeltaEta_TophadGluonhad, *DeltaEta_ToplepGluonlep, *DeltaEta_TophadToplep,  *DeltaEta_GluonGluon, *DeltaEta_TopGluon_gen, *DeltaEta_AntiTopAntiGluon_gen, *DeltaEta_TopAntiTop_gen,  *DeltaEta_GluonGluon_gen, *DeltaR_blep, *DeltaR_gluon_lep, *DeltaR_gluon_had;

    TH1F * DeltaR_GluonGluon, *DeltaR_TopTop, *DeltaR_GluonTop_lep, *DeltaR_GluonTop_had, *DeltaR_GluonLep_TopHad, *DeltaR_GluonHad_TopLep;
    
    TH1F *  CSV_Lep_Signal, *CSV_Had_Signal, *CSV_Lep_Background, *CSV_Had_Background; 
    
    TH2F * M_TstarAntiTstar_gen_vs_M_TstarhadTstarlep_rec, *M_Top_gen_vs_M_Top_rec, *M_Tstar_gen_vs_M_Tstar_rec;
    
    uhh2::Event::Handle<std::vector<TstarReconstructionHypothesis>> h_hyps;
    uhh2::Event::Handle<TStarGen> h_tstargen;
    std::string m_discriminator_name;
    
};
