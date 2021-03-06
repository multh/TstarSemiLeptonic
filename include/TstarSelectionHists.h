#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/TstarSemiLeptonic/include/TStarGen.h"

#include <string>
#include <TH1F.h>
#include <TH2F.h>

class TstarSelectionHists : public uhh2::Hists {
 public:
  TstarSelectionHists(uhh2::Context& ctx, const std::string& dirname);
  virtual void fill(const uhh2::Event&) override;
 virtual ~TstarSelectionHists();

 private:
  TH1F* N_bJets_loose, *N_bJets_med, *N_bJets_tight;
  
};
