// -*- C++ -*-
#include "Rivet/Analysis.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/ChargedFinalState.hh"
#include "Rivet/Projections/HeavyHadrons.hh"
#include "Rivet/Projections/VetoedFinalState.hh"
#include "Rivet/Projections/ChargedLeptons.hh"
#include "Rivet/Projections/MissingMomentum.hh"
#include "Rivet/Projections/IdentifiedFinalState.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/AnalysisLoader.hh"

namespace Rivet {

  


  /// Generic analysis looking at various distributions of final state particles
  class GENERIC : public Analysis {
  public:

    /// Constructor
    GENERIC()
      : Analysis("GENERIC")
    {    }


  public:

    /// @name Analysis methods
    //@{

    /// Book histograms and initialise projections before the run
    void init() {

      // Projections
      const FinalState cnfs(-5.0, 5.0, 500*MeV);
      addProjection(cnfs, "FS");
      addProjection(ChargedFinalState(-5.0, 5.0, 500*MeV), "CFS");

      

      IdentifiedFinalState electrons(FinalState(-4.2, 4.2, 10*GeV));
      electrons.acceptId(PID::ELECTRON);
      electrons.acceptId(PID::POSITRON);
 
      addProjection(electrons, "EFS");
      
      ChargedLeptons lfs(FinalState(-4.2,4.2,10*GeV));
      addProjection(lfs,"LFS");


      addProjection(HeavyHadrons(Cuts::abseta < 5 && Cuts::pT > 5*GeV), "BCHadrons");

      VetoedFinalState fs(FinalState(-4.2, 4.2, 0*GeV));
      fs.addVetoOnThisFinalState(lfs);
      addProjection(FastJets(fs, FastJets::ANTIKT, 0.4), "Jets");
      addProjection(MissingMomentum(fs), "MissingET");
      
      VetoedFinalState vfs(FinalState(-4.2,4.2,0*GeV));
      vfs.addVetoOnThisFinalState(lfs);
      addProjection(vfs, "VFS");
      

      _sumofweight =0;

      // @todo Choose E/pT ranged based on input energies... can't do anything about kin. cuts, though
      _histMult   = bookHisto1D("Mult", 200, -0.5, 299.5);
      _histMultCh = bookHisto1D("MultCh", 100, -0.5, 199.5);

      _histPt   = bookHisto1D("Pt", 300, 0, 30);
      _histPtCh = bookHisto1D("PtCh", 300, 0, 30);

      _histE   = bookHisto1D("E", 100, 0, 200);
      _histECh = bookHisto1D("ECh", 100, 0, 200);

      _histEtaSumEt = bookProfile1D("EtaSumEt", 25, 0, 5);

      _histEta    = bookHisto1D("Eta", 50, -5, 5);
      _histEtaCh  = bookHisto1D("EtaCh", 50, -5, 5);
      _tmphistEtaPlus = Histo1D(25, 0, 5);
      _tmphistEtaMinus = Histo1D(25, 0, 5);
      _tmphistEtaChPlus = Histo1D(25, 0, 5);
      _tmphistEtaChMinus = Histo1D(25, 0, 5);

      _histRapidity    = bookHisto1D("Rapidity", 50, -5, 5);
      _histRapidityCh  = bookHisto1D("RapidityCh", 50, -5, 5);
      _tmphistRapPlus = Histo1D(25, 0, 5);
      _tmphistRapMinus = Histo1D(25, 0, 5);
      _tmphistRapChPlus = Histo1D(25, 0, 5);
      _tmphistRapChMinus = Histo1D(25, 0, 5);

      _histPhi    = bookHisto1D("Phi", 50, 0, TWOPI);
      _histPhiCh  = bookHisto1D("PhiCh", 50, 0, TWOPI);

      _histEtaPMRatio = bookScatter2D("EtaPMRatio");
      _histEtaChPMRatio = bookScatter2D("EtaChPMRatio");
      _histRapidityPMRatio = bookScatter2D("RapidityPMRatio");
      _histRapidityChPMRatio = bookScatter2D("RapidityChPMRatio");
    }



    /// Perform the per-event analysis
    void analyze(const Event& event) {

      const double weight = event.weight();

     const ChargedLeptons& lfs = applyProjection<ChargedLeptons>(event, "LFS");
      const IdentifiedFinalState & electrons = applyProjection<IdentifiedFinalState>(event, "EFS");
      MSG_INFO("Electron multiplicity = " << electrons.size());
      foreach (const Particle& el , electrons.particles()) {
        MSG_INFO("Electron pT = " << el.pT());
      }
      if (electrons.size()<3) {
        MSG_INFO("Event failed lepton multiplicity cut");
        vetoEvent;
      }
      
      const FinalState& fs = applyProjection<FinalState>(event, "VFS");

      float n_iso_el=0;
      foreach (const Particle& l, electrons.particles()) {
	        const double elepton = l.E();
         double econe2 = 0.0;
         double econe4 = 0.0;
         foreach (const Particle& p, fs.particles()) 
         {
             if (deltaR(l, p.momentum()) < 0.2) {
                 econe2 += p.E();
              }
              else if(deltaR(l,p.momentum()) <0.4)
             {
                econe4 +=p.E();
             }
         }
         if(econe2/elepton<0.5)
         {
             n_iso_el++;
         }
      }

      const MissingMomentum& met = applyProjection<MissingMomentum>(event, "MissingET");
      MSG_INFO("Vector ET = " << met.vectorEt().mod() << " GeV");
      if (met.vectorEt().mod() < 30*GeV) {
        MSG_INFO("Event failed missing ET cut");
        vetoEvent;
      }
      const Particles bhadrons = sortByPt(applyProjection<HeavyHadrons>(event, "BCHadrons").bHadrons());


      const FastJets& jetpro = applyProjection<FastJets>(event, "Jets");
      const Jets alljets = jetpro.jetsByPt();
      if (alljets.size() < 4) {
        MSG_INFO("Event failed jet multiplicity cut");
        vetoEvent;
      }

      const Jets jets = jetpro.jetsByPt(20*GeV);
      double ht = 0.0;
      foreach (const Jet& j, jets) { ht += j.pT(); }

      Jets bjets, ljets;
      foreach (const Jet& jet, jets) {
        bool isolated = true;
        foreach (const Particle& lepton, lfs.chargedLeptons()) {
          if (deltaR(jet.momentum(), lepton.momentum()) < 0.3) {
            isolated = false;
            break;
          }
        }
        if (!isolated) {
          MSG_INFO("Jet failed lepton isolation cut");
          break;
        }
       foreach (const Particle& b, bhadrons) {
            if (deltaR(jet,b) < 0.3){
    	 	bjets.push_back(jet);
            } else {
                ljets.push_back(jet);
            }
         }
       }
      MSG_INFO("Number of b-jets = " << bjets.size());
      MSG_INFO("Number of l-jets = " << ljets.size());
      if (bjets.size() != 2) {
        MSG_INFO("Event failed post-lepton-isolation b-tagging cut");
        vetoEvent;
      }
      if (ljets.size() < 2) {
        MSG_INFO("Event failed since not enough light jets remaining after lepton-isolation");
        vetoEvent;
      }
      _sumofweight += event.weight();
 

      // Charged + neutral final state
      const FinalState& cnfs = applyProjection<FinalState>(event, "FS");
      MSG_DEBUG("Total multiplicity = " << cnfs.size());
      _histMult->fill(cnfs.size(), weight);
      foreach (const Particle& p, cnfs.particles()) {
        const double eta = p.eta();
        _histEta->fill(eta, weight);
        _histEtaSumEt->fill(fabs(eta), p.Et(), weight);
        if (eta > 0) _tmphistEtaPlus.fill(fabs(eta), weight);
        else _tmphistEtaMinus.fill(fabs(eta), weight);
        //
        const double rapidity = p.rapidity();
        _histRapidity->fill(rapidity, weight);
        if (rapidity > 0) _tmphistRapPlus.fill(fabs(rapidity), weight);
        else _tmphistRapMinus.fill(fabs(rapidity), weight);
        //
        _histPt->fill(p.pT()/GeV, weight);
        _histE->fill(p.E()/GeV, weight);
        _histPhi->fill(p.phi(), weight);
      }

      const FinalState& cfs = applyProjection<FinalState>(event, "CFS");
      MSG_DEBUG("Total charged multiplicity = " << cfs.size());
      _histMultCh->fill(cfs.size(), weight);
      foreach (const Particle& p, cfs.particles()) {
        const double eta = p.eta();
        _histEtaCh->fill(eta, weight);
        if (eta > 0) {
          _tmphistEtaChPlus.fill(fabs(eta), weight);
        } else {
          _tmphistEtaChMinus.fill(fabs(eta), weight);
        }
        const double rapidity = p.rapidity();
        _histRapidityCh->fill(rapidity, weight);
        if (rapidity > 0) {
          _tmphistRapChPlus.fill(fabs(rapidity), weight);
        } else {
          _tmphistRapChMinus.fill(fabs(rapidity), weight);
        }
        _histPtCh->fill(p.pT()/GeV, weight);
        _histECh->fill(p.E()/GeV, weight);
        _histPhiCh->fill(p.phi(), weight);
      }

    }


    /// Finalize
    void finalize() {
      double norm=crossSection()/sumOfWeights(); 
      scale(_histMult,norm);
      scale(_histMultCh,norm);
      scale(_histEta,norm);
      scale(_histEtaCh,norm);
      scale(_histRapidity,norm);
      scale(_histRapidityCh,norm);
      scale(_histPt,norm);
      scale(_histPtCh,norm);
      scale(_histE,norm);
      scale(_histECh,norm);
      scale(_histPhi,norm);
      scale(_histPhiCh,norm);
      divide(_tmphistEtaPlus, _tmphistEtaMinus, _histEtaPMRatio);
      divide(_tmphistEtaChPlus, _tmphistEtaChMinus, _histEtaChPMRatio);
      divide(_tmphistRapPlus, _tmphistRapMinus, _histRapidityPMRatio);
      divide(_tmphistRapChPlus, _tmphistRapChMinus, _histRapidityChPMRatio);
    }

    //@}


  private:

    /// @name Histograms
    //@{
    Histo1DPtr _histMult, _histMultCh;
    Profile1DPtr _histEtaSumEt;
    Histo1DPtr _histEta, _histEtaCh;
    Histo1DPtr _histRapidity, _histRapidityCh;
    Histo1DPtr _histPt, _histPtCh;
    Histo1DPtr _histE, _histECh;
    Histo1DPtr _histPhi, _histPhiCh;
    Scatter2DPtr _histEtaPMRatio;
    Scatter2DPtr _histEtaChPMRatio;
    Scatter2DPtr _histRapidityPMRatio;
    Scatter2DPtr _histRapidityChPMRatio;
    //@}

    /// @name Temporary histos used to calculate eta+/eta- ratio plots
    //@{
    Histo1D _tmphistEtaPlus, _tmphistEtaMinus;
    Histo1D _tmphistEtaChPlus, _tmphistEtaChMinus;
    Histo1D _tmphistRapPlus, _tmphistRapMinus;
    Histo1D _tmphistRapChPlus, _tmphistRapChMinus;
    float _sumofweight;
    //@}

  };


  // The hook for the plugin system
  DECLARE_RIVET_PLUGIN(GENERIC);

}
