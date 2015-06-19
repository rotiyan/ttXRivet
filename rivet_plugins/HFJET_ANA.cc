// -*- C++ -*-
#include "Rivet/Analysis.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/UnstableFinalState.hh"
#include "Rivet/Projections/PrimaryHadrons.hh"
#include "Rivet/Projections/HeavyHadrons.hh"
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




  class HFJET_ANA: public Analysis {
  public:

    /// Constructor
    HFJET_ANA()
      : Analysis("HFJET_ANA")
    {    }


  public:

    /// @name Analysis methods
    //@{

    /// Book histograms and initialise projections before the run
    void init() {

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
      FastJets fj(FinalState(-5, 5), FastJets::ANTIKT, 0.4);
      fj.useInvisibles();


      _h_ptCJetLead = bookHisto1D("ptCJetLead", linspace(5, 0, 20, false) + logspace(25, 20, 200));
      _h_ptCHadrLead = bookHisto1D("ptCHadrLead", linspace(5, 0, 10, false) + logspace(25, 10, 200));
      _h_ptFracC = bookHisto1D("ptfracC", 50, 0, 1.5);
      _h_eFracC = bookHisto1D("efracC", 50, 0, 1.5);

      _h_ptBJetLead = bookHisto1D("ptBJetLead", linspace(5, 0, 20, false) + logspace(25, 20, 200));
      _h_ptBHadrLead = bookHisto1D("ptBHadrLead", linspace(5, 0, 10, false) + logspace(25, 10, 200));
      _h_ptFracB = bookHisto1D("ptfracB", 50, 0, 1.5);
      _h_eFracB = bookHisto1D("efracB", 50, 0, 1.5);
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
 

      // Get jets and heavy hadrons
      const Particles chadrons = sortByPt(applyProjection<HeavyHadrons>(event, "BCHadrons").cHadrons());
      MSG_DEBUG("# b hadrons = " << bhadrons.size() << ", # c hadrons = " << chadrons.size());

      // Max HF hadron--jet axis dR to be regarded as a jet tag
      const double MAX_DR = 0.3;

      // Tag the leading b and c jets with a deltaR < 0.3 match
      // b-tagged jet are excluded from also being considered as c-tagged
      /// @todo Do this again with the ghost match?
      MSG_DEBUG("Getting b/c-tags");
      bool gotLeadingB = false, gotLeadingC = false;;
      foreach (const Jet& j, jets) {
        if (!gotLeadingB) {
          FourMomentum leadBJet, leadBHadr;
          double dRmin = MAX_DR;
          foreach (const Particle& b, bhadrons) {
            const double dRcand = min(dRmin, deltaR(j, b));
            if (dRcand < dRmin) {
              dRmin = dRcand;
              leadBJet = j.momentum();
              leadBHadr = b.momentum();
              MSG_DEBUG("New closest b-hadron jet tag candidate: dR = " << dRmin
                        << " for jet pT = " << j.pT()/GeV << " GeV, "
                        << " b hadron pT = " << b.pT()/GeV << " GeV, PID = " << b.pid());
            }
          }
          if (dRmin < MAX_DR) {
            // A jet has been tagged, so fill the histos and break the loop
            _h_ptBJetLead->fill(leadBJet.pT()/GeV, weight);
            _h_ptBHadrLead->fill(leadBHadr.pT()/GeV, weight);
            _h_ptFracB->fill(leadBHadr.pT() / leadBJet.pT(), weight);
            _h_eFracB->fill(leadBHadr.E() / leadBJet.E(), weight);
            gotLeadingB = true;
            continue; // escape this loop iteration so the same jet isn't c-tagged
          }
        }
        if (!gotLeadingC) {
          FourMomentum leadCJet, leadCHadr;
          double dRmin = MAX_DR;
          foreach (const Particle& c, chadrons) {
            const double dRcand = min(dRmin, deltaR(j, c));
            if (dRcand < dRmin) {
              dRmin = dRcand;
              leadCJet = j.momentum();
              leadCHadr = c.momentum();
              MSG_DEBUG("New closest c-hadron jet tag candidate: dR = " << dRmin
                        << " for jet pT = " << j.pT()/GeV << " GeV, "
                        << " c hadron pT = " << c.pT()/GeV << " GeV, PID = " << c.pid());
            }
          }
          if (dRmin < MAX_DR) {
            // A jet has been tagged, so fill the histos and break the loop
            _h_ptCJetLead->fill(leadCJet.pT()/GeV, weight);
            _h_ptCHadrLead->fill(leadCHadr.pT()/GeV, weight);
            _h_ptFracC->fill(leadCHadr.pT() / leadCJet.pT(), weight);
            _h_eFracC->fill(leadCHadr.E() / leadCJet.E(), weight);
            gotLeadingB = true;
          }
        }
      }

    }


    /// Normalise histograms etc., after the run
    void finalize() {
      double norm=crossSection()/sumOfWeights(); 
      scale(_h_ptCJetLead,norm);
      scale(_h_ptCHadrLead,norm);
      scale(_h_ptFracC,norm);
      scale(_h_eFracC,norm);
      scale(_h_ptBJetLead,norm);
      scale(_h_ptBHadrLead,norm);
      scale(_h_ptFracB,norm);
      scale(_h_eFracB,norm);
    }

    //@}

  private:

    /// @name Histograms
    //@{
    Histo1DPtr _h_ptCJetLead, _h_ptCHadrLead, _h_ptFracC, _h_eFracC;
    Histo1DPtr _h_ptBJetLead, _h_ptBHadrLead, _h_ptFracB, _h_eFracB;
    float _sumofweight;
    //@}


  };



  // The hook for the plugin system
  DECLARE_RIVET_PLUGIN(HFJET_ANA);

}
