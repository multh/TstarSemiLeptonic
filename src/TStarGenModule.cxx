#include <iostream>
#include <memory>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/TstarSemiLeptonic/include/TStarGen.h"     //write class for TStar
#include "UHH2/common/include/PrintingModules.h"
#include "UHH2/TstarSemiLeptonic/include/TStarGenHists.h" //write class for TStar

using namespace std;
using namespace uhh2;

namespace uhh2examples {

/** \brief Example for calculating and accessing the TStarGen interpretation
 * 
 */
class TStarGenModule: public AnalysisModule {
public:
    
    explicit TStarGenModule(Context & ctx);
    virtual bool process(Event & event) override;

private:
    std::unique_ptr<AnalysisModule> printer;
    std::unique_ptr<AnalysisModule> tstargenprod;
    std::unique_ptr<Hists> h_tstargenhists;
    Event::Handle<TStarGen> h_tstargen;
};


TStarGenModule::TStarGenModule(Context & ctx){
  // printer.reset(new GenParticlesPrinter(ctx));
    tstargenprod.reset(new TStarGenProducer(ctx, "tstargen", false));
    h_tstargen = ctx.get_handle<TStarGen>("tstargen");
    h_tstargenhists.reset(new TStarGenHists(ctx, "tstargenhists"));
}


bool TStarGenModule::process(Event & event) {
  //printer->process(event);
    tstargenprod->process(event);
    const auto & tstargen = event.get(h_tstargen);
    cout << "Decay channel is " << int(tstargen.DecayChannel()) << endl;

     h_tstargenhists->fill(event);
    
    return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(TStarGenModule)

}
