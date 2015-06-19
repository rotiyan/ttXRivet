// -*- C++ -*-
#include "Rivet/Analysis.hh"
#include "Rivet/Projections/ZFinder.hh"
#include "Rivet/Projections/ChargedLeptons.hh"
#include "Rivet/Projections/VetoedFinalState.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/VetoedFinalState.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/AnalysisLoader.hh"

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

  


  /// @brief MC validation analysis for Z events
  class ZINC : public Analysis {
  public:

    /// Default constructor
    ZINC()
      : Analysis("ZINC")
    {    }


    /// @name Analysis methods
    //@{

    /// Book histograms
    void init() {
      FinalState myFs(FinalState(-4.2,4.2,0*GeV));
      Cut cut = (Cuts::abseta < 4.5 & Cuts::pT > 10*GeV);
      ZFinder zfinder(myFs, cut, PID::ELECTRON, 0.0*GeV, 115.0*GeV, 0.2, ZFinder::CLUSTERNODECAY, ZFinder::TRACK);
      addProjection(zfinder, "ZFinder");

      ChargedLeptons lfs(myFs);
      addProjection(lfs, "LFS");
     
      // FS for isolation excludes chargedLeptons
      VetoedFinalState vfs(myFs);
      vfs.addVetoOnThisFinalState(lfs);
      addProjection(vfs, "VFS");


      IdentifiedFinalState electrons(FinalState(-4.2, 4.2, 10*GeV));
      electrons.acceptId(PID::ELECTRON);
      electrons.acceptId(PID::POSITRON);
 
      addProjection(electrons, "EFS");
      

      addProjection(HeavyHadrons(Cuts::abseta < 5 && Cuts::pT > 5*GeV), "BCHadrons");

      VetoedFinalState fs(FinalState(-4.2, 4.2, 0*GeV));
      fs.addVetoOnThisFinalState(lfs);
      addProjection(FastJets(fs, FastJets::ANTIKT, 0.4), "Jets");
      addProjection(MissingMomentum(fs), "MissingET");
      
      _sumofweight =0;

 

      _h_Z_mass = bookHisto1D("Z_mass", 100, 0.0, 116.0);
      _h_Z_pT = bookHisto1D("Z_pT", logspace(100, 1.0, 0.5*sqrtS()/GeV));
      _h_Z_pT_peak = bookHisto1D("Z_pT_peak", 25, 0.0, 25.0);
      _h_Z_y = bookHisto1D("Z_y", 40, -4.0, 4.0);
      _h_Z_phi = bookHisto1D("Z_phi", 25, 0.0, TWOPI);
      _h_lepton_pT = bookHisto1D("lepton_pT", logspace(100, 10.0, 0.25*sqrtS()/GeV));
      _h_lepton_eta = bookHisto1D("lepton_eta", 40, -4.0, 4.0);
      _h_leptonEcone2 = bookHisto1D("leptoncone20",100,0,1);
      _h_leptonEcone4 = bookHisto1D("leptoncone40",100,0,1);

    }



    /// Do the analysis
    void analyze(const Event & e) {
      const ZFinder& zfinder = applyProjection<ZFinder>(e, "ZFinder");
      if (zfinder.bosons().size()!=1) {
        vetoEvent;
      }
      
      const ChargedLeptons& lfs = applyProjection<ChargedLeptons>(e, "LFS");
      const IdentifiedFinalState & electrons = applyProjection<IdentifiedFinalState>(e, "EFS");
      MSG_INFO("Electron multiplicity = " << electrons.size());
      foreach (const Particle& el , electrons.particles()) {
        MSG_INFO("Electron pT = " << el.pT());
      }
      if (electrons.size()<3) {
        MSG_INFO("Event failed lepton multiplicity cut");
        vetoEvent;
      }
      
      const FinalState& fs = applyProjection<FinalState>(e, "VFS");

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

      const MissingMomentum& met = applyProjection<MissingMomentum>(e, "MissingET");
      MSG_INFO("Vector ET = " << met.vectorEt().mod() << " GeV");
      if (met.vectorEt().mod() < 30*GeV) {
        MSG_INFO("Event failed missing ET cut");
        vetoEvent;
      }
      const Particles bhadrons = sortByPt(applyProjection<HeavyHadrons>(e, "BCHadrons").bHadrons());


      const FastJets& jetpro = applyProjection<FastJets>(e, "Jets");
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
      _sumofweight += e.weight();
 

      const double weight = e.weight();


      FourMomentum zmom(zfinder.bosons()[0].momentum());
      _h_Z_mass->fill(zmom.mass()/GeV, weight);
      _h_Z_pT->fill(zmom.pT()/GeV, weight);
      _h_Z_pT_peak->fill(zmom.pT()/GeV, weight);
      _h_Z_y->fill(zmom.rapidity(), weight);
      _h_Z_phi->fill(zmom.phi(), weight);
      foreach (const Particle& l, zfinder.constituents()) {
        _h_lepton_pT->fill(l.pT()/GeV, weight);
        _h_lepton_eta->fill(l.eta(), weight);
        // Find Isolation As the econe/e_lepton
        const double elepton = l.E();
        double econe2 = 0.0;
        double econe4 = 0.0;
        foreach (const Particle& p, fs.particles()) {
            if (deltaR(l, p.momentum()) < 0.2) {
                econe2 += p.E();
               // Veto as soon as E_cone gets larger
             }
             else if(deltaR(l,p.momentum()) <0.4)
             {
                econe4 +=p.E();
             }
         }
         _h_leptonEcone2->fill(econe2/elepton,weight);
         _h_leptonEcone4->fill(econe4/elepton,weight);
       }
    }


    /// Finalize
    void finalize() {
      double norm = crossSection()/sumOfWeights();
      scale(_h_Z_mass,norm);
      scale(_h_Z_pT,norm);
      scale(_h_Z_pT_peak,norm);
      scale(_h_Z_y,norm);
      scale(_h_Z_phi,norm);
      scale(_h_lepton_pT,norm);
      scale(_h_lepton_eta,norm);
    }

    //@}


  private:

    /// @name Histograms
    //@{
    Histo1DPtr _h_Z_mass;
    Histo1DPtr _h_Z_pT;
    Histo1DPtr _h_Z_pT_peak;
    Histo1DPtr _h_Z_y;
    Histo1DPtr _h_Z_phi;
    Histo1DPtr _h_lepton_pT;
    Histo1DPtr _h_lepton_eta;
    Histo1DPtr _h_leptonEcone2;
    Histo1DPtr _h_leptonEcone4;
    float _sumofweight;
    //@}

  };



  // The hook for the plugin system
  DECLARE_RIVET_PLUGIN(ZINC);

}
