// -*- C++ -*-
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Analysis.hh"
#include "Rivet/Projections/HeavyHadrons.hh"
#include "Rivet/AnalysisLoader.hh"

#include "Rivet/Analysis.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/VetoedFinalState.hh"
#include "Rivet/Projections/ChargedLeptons.hh"
#include "Rivet/Projections/MissingMomentum.hh"
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

  class JETTAGS : public Analysis {
  public:
    JETTAGS()
      : Analysis("JETTAGS")
    {    }


    void init() {
      FinalState myFS;
      addProjection(FastJets(myFS, FastJets::ANTIKT, 0.4), "Jets04");
      addProjection(FastJets(myFS, FastJets::ANTIKT, 0.6), "Jets06");
      addProjection(HeavyHadrons(Cuts::abseta < 5 && Cuts::pT > 5*GeV), "BCHadrons");
 
      IdentifiedFinalState electrons(FinalState(-4.2, 4.2, 10*GeV));
      electrons.acceptId(PID::ELECTRON);
      electrons.acceptId(PID::POSITRON);
 
      addProjection(electrons, "EFS");
      
      ChargedLeptons lfs(FinalState(-4.2,4.2,10*GeV));
      addProjection(lfs,"LFS");


      VetoedFinalState fs(FinalState(-4.2, 4.2, 0*GeV));
      fs.addVetoOnThisFinalState(lfs);
      addProjection(FastJets(fs, FastJets::ANTIKT, 0.4), "Jets");
      addProjection(MissingMomentum(fs), "MissingET");
      
      VetoedFinalState vfs(FinalState(-4.2,4.2,0*GeV));
      vfs.addVetoOnThisFinalState(lfs);
      addProjection(vfs, "VFS");
      

      _sumofweight =0;


      
      _h_numBJets = bookHisto1D("numBJets", 6, -0.5, 5.5);
      _h_numLJets = bookHisto1D("numLJets", 6, -0.5, 5.5);
    }


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
 
      const Jets jets04 = applyProjection<FastJets>(event, "Jets04").jetsByPt(20*GeV);
      const Jets jets06 = applyProjection<FastJets>(event, "Jets06").jetsByPt(20*GeV);

      const Particles chadrons = sortByPt(applyProjection<HeavyHadrons>(event, "BCHadrons").cHadrons());
 

      vector<const Jet*> b_jets;
      vector<const Jet*> l_jets;

      foreach (const Jet& j, jets04) {
        bool isbJet = false; 
        bool isCJet = false;
      foreach (const Particle& b, bhadrons) {
          if (deltaR(j.momentum(), FourMomentum(b.momentum())) < 0.3)
          {
   	      b_jets.push_back(&j);
           }
          else{
            l_jets.push_back(&j);
        }

        _h_numBJets->fill(b_jets.size(), weight);
        _h_numLJets->fill(l_jets.size(),weight);
      }
    }
    }


    void finalize() {
        double norm = crossSection()/sumOfWeights();

        scale(_h_numBJets,norm);
        scale(_h_numLJets,norm);
    }


  private:

    Histo1DPtr _h_numBJets;
    Histo1DPtr  _h_numLJets;
    float _sumofweight;

  };


  // The hook for the plugin system
  DECLARE_RIVET_PLUGIN(JETTAGS);

}
