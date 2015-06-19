// -*- C++ -*-
#include "Rivet/Analyses/MC_ParticleAnalysis.hh"
#include "Rivet/Projections/IdentifiedFinalState.hh"

namespace Rivet {


  /// @brief MC validation analysis for electrons
  class ELECTRONS : public MC_ParticleAnalysis {
  public:

    ELECTRONS()
      : MC_ParticleAnalysis("ELECTRONS", 2, "electron")
    {    }


  public:

    void init() {
      IdentifiedFinalState electrons;
      electrons.acceptIdPair(PID::ELECTRON);
      addProjection(electrons, "Electrons");

      MC_ParticleAnalysis::init();
    }


    void analyze(const Event& event) {
      const Particles es = applyProjection<FinalState>(event, "Electrons").particlesByPt(Cuts::pT > 0.5*GeV);
      MC_ParticleAnalysis::_analyze(event, es);
    }


    void finalize() {
      MC_ParticleAnalysis::finalize();
    }

  };


  // The hook for the plugin system
  DECLARE_RIVET_PLUGIN(ELECTRONS);

}
