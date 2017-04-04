#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"

#include <string>

namespace uhh2examples {

class TstarPreSelectionHists : public uhh2::Hists {
 public:
  TstarPreSelectionHists(uhh2::Context & ctx, const std::string & dirname);

  virtual void fill(const uhh2::Event & ev) override;

  virtual ~TstarPreSelectionHists();
};

}

