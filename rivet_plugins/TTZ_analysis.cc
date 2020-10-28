#include "Rivet/Analysis.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/VetoedFinalState.hh"
#include "Rivet/Projections/ChargedLeptons.hh"
#include "Rivet/Projections/DressedLeptons.hh"
#include "Rivet/Projections/HeavyHadrons.hh"
#include "Rivet/Projections/IdentifiedFinalState.hh"
#include "Rivet/Projections/MissingMomentum.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Projections/ZFinder.hh"
//#include "Rivet/AnalysisLoader.hh"
#include "Rivet/Projections/TauFinder.hh"
#include "Rivet/Projections/SmearedJets.hh"
#include "Rivet/Projections/SmearedParticles.hh"
#include "Rivet/Projections/SmearedMET.hh"

namespace Rivet {

  class TTZ_analysis: public Analysis {
  public:

    //Constructor
    TTZ_analysis() : Analysis("TTZ_analysis") { } 

    /// Set up projections and book histograms
    void init() {

      // A FinalState is used to select particles within |eta| < 4.2 and with pT
      // > 30 GeV, out of which the ChargedLeptons projection picks only the
      // electrons and muons, to be accessed later as "LFS".
      ChargedLeptons lfs(FinalState(Cuts::abseta < 5&& Cuts::pT > 10*GeV));
      declare(lfs, "LFS");
      
      IdentifiedFinalState photons(Cuts::abseta < 5, PID::PHOTON);

      IdentifiedFinalState truthelectrons(Cuts::abseta < 5 && Cuts::pT > 10*GeV, {{PID::ELECTRON, PID::POSITRON}});
      declare(truthelectrons, "Electrons0");
      DressedLeptons dressedelectrons(photons, truthelectrons, 0.2);
      declare(dressedelectrons, "Electrons1");
      SmearedParticles recoelectrons(dressedelectrons, ELECTRON_RECOEFF_ATLAS_RUN2, ELECTRON_SMEAR_ATLAS_RUN2);
      declare(recoelectrons, "Electrons2");

      IdentifiedFinalState truthmuons(Cuts::abseta < 5 && Cuts::pT > 10*GeV, {{PID::MUON, PID::ANTIMUON}});
      declare(truthmuons, "Muons0");
      DressedLeptons dressedmuons(photons, truthmuons, 0.2);
      declare(dressedmuons, "Muons1");
      SmearedParticles recomuons(dressedmuons, MUON_EFF_ATLAS_RUN2, MUON_SMEAR_ATLAS_RUN2);
      declare(recomuons, "Muons2");

      TauFinder truthtaus(TauFinder::DecayMode::ANY, Cuts::abseta < 5 && Cuts::pT > 10*GeV);
      declare(truthtaus, "Taus0");
      DressedLeptons dressedtaus(photons, truthtaus, 0.2);
      declare(dressedtaus, "Taus1");
      SmearedParticles recotaus(dressedtaus, TAU_EFF_ATLAS_RUN2, TAU_SMEAR_ATLAS_RUN2);
      declare(recotaus, "Taus2");
 

      // A second FinalState is used to select all particles in |eta| < 4.2,
      // with no pT cut. This is used to construct jets and measure missing
      // transverse energy.
      VetoedFinalState fs(FinalState(Cuts::abseta < 4));
      fs.addVetoOnThisFinalState(lfs);
      declare(FastJets(fs, FastJets::ANTIKT, 0.4), "Jets");
      declare(MissingMomentum(fs), "MissingET");

      // Booking of histograms
      book(_h["njets"], "njets", 11, -0.5, 10.5);
      //
      book(_h["diElMass"], "diElMass",130,0,130);
      book(_h["diElPt"], "diElPt",100,0,1000);
      book(_h["diMuMass"],"diMuMass",130,0,130);
      book(_h["diMuPt"],"diMuPt",100,0,1000);

      book(_h["ttZ_mass"],"ttZ_mass",520,0,13000);
      book(_h["ttZ_eta"],"ttZ_eta",100,-5,5);

      book(_h["jet_1_pT"], "jet_1_pT", 50, 20.0, 500.0);
      book(_h["jet_2_pT"], "jet_2_pT", 50, 20.0, 400.0);
      book(_h["jet_HT"],   "jet_HT", 50, 100.0, 2000.0);
      //
      book(_h["bjet_1_pT"], "bjet_1_pT", 50, 20.0, 400.0);
      book(_h["bjet_2_pT"], "bjet_2_pT", 50, 20.0, 300.0);
      //
      book(_h["ljet_1_pT"], "ljet_1_pT", 50, 20.0, 400.0);
      book(_h["ljet_2_pT"], "ljet_2_pT", 50, 20.0, 300.0);
      //
      book(_h["jetb_1_jetb_2_dR"],   "jetb_1_jetb_2_dR", 20, 0.0, 7.0);
      book(_h["jetb_1_jetb_2_deta"], "jetb_1_jetb_2_deta", 20, 0.0, 7.0);
      book(_h["jetb_1_jetb_2_dphi"], "jetb_1_jetb_2_dphi", 20, 0.0, M_PI);
      book(_h["jetb_1_jetl_1_dR"],   "jetb_1_jetl_1_dR", 20, 0.0, 7.0);
      book(_h["jetb_1_jetl_1_deta"], "jetb_1_jetl_1_deta", 20, 0.0, 7.0);
      book(_h["jetb_1_jetl_1_dphi"], "jetb_1_jetl_1_dphi", 20, 0.0, M_PI);
      book(_h["jetl_1_jetl_2_dR"],   "jetl_1_jetl_2_dR", 20, 0.0, 7.0);
      book(_h["jetl_1_jetl_2_deta"], "jetl_1_jetl_2_deta", 20, 0.0, 7.0);
      book(_h["jetl_1_jetl_2_dphi"], "jetl_1_jetl_2_dphi", 20, 0.0, M_PI);
    }


    void analyze(const Event& event) {
      // Use the "LFS" projection to require at least one hard charged
      // lepton. This is an experimental signature for the leptonically decaying
      // W. This helps to reduce pure QCD backgrounds.
      const ChargedLeptons& lfs = apply<ChargedLeptons>(event, "LFS");
      //const Particles& drss_electrons = apply<ParticleFinder>(event, "Electrons2").particlesByPt();
      //const Particles& drss_muons     = apply<DressedLeptons>(event, "Muons2").particlesByPt();
      const vector<DressedLepton>& drss_electrons = applyProjection<DressedLeptons>(event, "Electrons1").dressedLeptons();
      const vector<DressedLepton>& drss_muons     = applyProjection<DressedLeptons>(event, "Muons1").dressedLeptons();

      MSG_DEBUG("Charged lepton multiplicity = " << lfs.chargedLeptons().size());

      // Use the "Jets" projection to check how many jets with pT > 25 GeV there are
      // remove jets overlapping with any lepton (dR < 0.3)
      const FastJets& jetpro = apply<FastJets>(event, "Jets");
      const Jets jets = discardIfAnyDeltaRLess(jetpro.jetsByPt(25*GeV), lfs.chargedLeptons(), 0.3);

      int nLep = lfs.chargedLeptons().size();
      for (const Particle& lepton : lfs.chargedLeptons()) {
        //MSG_INFO("Lepton pT = " << lepton.pT());
      }

      FourMomentum *diEl4Mom = getBestZMass(drss_electrons);
      FourMomentum *diMu4Mom = getBestZMass(drss_muons);
      if (diEl4Mom || diMu4Mom)
      {
          // Sort the jets into b-jets and light jets. We expect one hard b-jet from
          // each top decay, so our 4 hardest jets should include two b-jets. The
          // Jet::bTagged() method is equivalent to perfect experimental
          // b-tagging, in a generator-independent way.
          Jets bjets, ljets;
          for (const Jet& jet : jets) {
            if (jet.bTagged())  bjets += jet;
            else                ljets += jet;
          }
          MSG_DEBUG("Number of b-jets = " << bjets.size());
          MSG_DEBUG("Number of l-jets = " << ljets.size());
          if (bjets.size() != 2) {
            MSG_DEBUG("Event failed post-lepton-isolation b-tagging cut");
            vetoEvent;
          }

          if (diEl4Mom)
	  {
	      _h["diElMass"]->fill(diEl4Mom->mass()/GeV);
              _h["diElPt"]->fill(diEl4Mom->pt()/GeV);
          }
          if (diMu4Mom)
          {
	       _h["diMuMass"]->fill(diMu4Mom->mass()/GeV);
	       _h["diMuPt"]->fill(diMu4Mom->pt()/GeV);
	  }
	     

	  _h["njets"]->fill(jets.size());
          if(jets.size()>1) _h["jet_1_pT"]->fill(jets[0].pT()/GeV);

          size_t nLeps = lfs.chargedLeptons().size();
          // Use a missing ET cut to bias toward events with a hard neutrino from
          // the leptonically decaying W. This helps to reduce pure QCD backgrounds.
          // not applied in all-hadronic mode
          const Vector3& met = apply<MissingMomentum>(event, "MissingET").vectorMissingPt();
          MSG_DEBUG("Vector pT = " << met.mod() << " GeV");
          if (_mode > 0 && met.mod() < 10*GeV) {
            MSG_DEBUG("Event failed missing ET cut");
            vetoEvent;
          }
          float ht =0.0;
          for (const Jet& j : jets) { ht += j.pT(); }
          _h["jet_HT"]->fill(ht/GeV);

	  
	  //Reconstruct the ttbar system for fully hadronic case
	  FourMomentum ttzvec = bjets[0].mom() + bjets[1].mom();
	  if (nLep==2 && ljets.size()>=4)
	  {
              ttzvec += ljets[0].mom() + ljets[1].mom() + ljets[2].mom() + ljets[3].mom();
              if (diEl4Mom ) { ttzvec += *diEl4Mom;}
    	      if (diMu4Mom ) { ttzvec += *diMu4Mom;}
	      _h["ttZ_mass"]->fill(ttzvec.mass()/GeV);
	      _h["ttZ_eta"]->fill(ttzvec.eta());
	  }

          // Plot the pTs of the identified jets.
          _h["bjet_1_pT"]->fill(bjets[0].pT()/GeV);
          _h["bjet_2_pT"]->fill(bjets[1].pT()/GeV);
          // need to check size to cater for dileptonic mode
          if (ljets.size() > 0)  _h["ljet_1_pT"]->fill(ljets[0].pT()/GeV);
          if (ljets.size() > 1)  _h["ljet_2_pT"]->fill(ljets[1].pT()/GeV);

          _h["jetb_1_jetb_2_dR"]->fill(deltaR(bjets[0].momentum(), bjets[1].momentum()));
          _h["jetb_1_jetb_2_deta"]->fill(fabs(bjets[0].eta()-bjets[1].eta()));
          _h["jetb_1_jetb_2_dphi"]->fill(deltaPhi(bjets[0].momentum(),bjets[1].momentum()));

          if (ljets.size() > 0) {
            _h["jetb_1_jetl_1_dR"]->fill(deltaR(bjets[0].momentum(), ljets[0].momentum()));
            _h["jetb_1_jetl_1_deta"]->fill(fabs(bjets[0].eta()-ljets[0].eta()));
            _h["jetb_1_jetl_1_dphi"]->fill(deltaPhi(bjets[0].momentum(),ljets[0].momentum()));
            if (ljets.size() > 1) {
              _h["jetl_1_jetl_2_dR"]->fill(deltaR(ljets[0].momentum(), ljets[1].momentum()));
              _h["jetl_1_jetl_2_deta"]->fill(fabs(ljets[0].eta()-ljets[1].eta()));
              _h["jetl_1_jetl_2_dphi"]->fill(deltaPhi(ljets[0].momentum(),ljets[1].momentum()));
            }
         }
      }
    }
    void finalize() {
      const double sf = crossSection() / sumOfWeights();
      for (auto hist : _h) { scale(hist.second, sf); }
    }
    FourMomentum * getBestZMass(const std::vector<DressedLepton> &cont)
    {
        FourMomentum *zCand=new FourMomentum(1000*TeV,0.,0.,0.);
        float targetMass = 91.2*GeV;
	
	bool hasCand = false;
        if (cont.size()>=2)
        {
	    std::vector<FourMomentum> diLep_FourMom;
            //Check if they are OS and compatible with Z-mass
            for(size_t i =0; i < cont.size(); ++i)
            {
                for(size_t j =i+1; j <cont.size(); ++j)
                {
                    if(cont[i].pid()*cont[j].pid()<0 && deltaR(cont[i],cont[j])>0.1) diLep_FourMom.push_back(cont[i].momentum() + cont[j].momentum());
                }
            } 
            for(auto vec: diLep_FourMom)
            {
                if(1<vec.mass()/GeV && 120>vec.mass()/GeV)
                {
                    MSG_DEBUG("diEl Mass diff:"<< fabs(vec.mass()-targetMass));
            	    if(fabs(vec.mass()-targetMass) < zCand->mass()-targetMass)
            	    {
            	      zCand = new FourMomentum(vec);
		      hasCand =true;
            	    }
                 }
              }
        }
	if (!hasCand) zCand=0;
	return zCand;
      }

    //@}

  protected:

      size_t _mode;


  private:

    // @name Histogram data members
    //@{
    map<string, Histo1DPtr> _h;
    //@}

  };



  // The hook for the plugin system
  DECLARE_RIVET_PLUGIN(TTZ_analysis);

}
