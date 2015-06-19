#include "Rivet/Analysis.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/HeavyHadrons.hh"
#include "Rivet/Projections/VetoedFinalState.hh"
#include "Rivet/Projections/ChargedLeptons.hh"
#include "Rivet/Projections/MissingMomentum.hh"
#include "Rivet/Projections/IdentifiedFinalState.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/AnalysisLoader.hh"

namespace Rivet {

  
  class TTBAR : public Analysis {
  public:

    /// Minimal constructor
    TTBAR() : Analysis("TTBAR_ANA")
    {
    }


    /// @name Analysis methods
    //@{

    /// Set up projections and book histograms
    void init() {

      // A FinalState is used to select particles within |eta| < 4.2 and with pT
      // > 30 GeV, out of which the ChargedLeptons projection picks only the
      // electrons and muons, to be accessed later as "LFS".
      IdentifiedFinalState electrons(FinalState(-4.2, 4.2, 10*GeV));
      electrons.acceptId(PID::ELECTRON);
      electrons.acceptId(PID::POSITRON);
 
      addProjection(electrons, "EFS");
      
      ChargedLeptons lfs(FinalState(-4.2,4.2,10*GeV));
      addProjection(lfs,"LFS");


      addProjection(HeavyHadrons(Cuts::abseta < 5 && Cuts::pT > 5*GeV), "BCHadrons");


      // A second FinalState is used to select all particles in |eta| < 4.2,
      // with no pT cut. This is used to construct jets and measure missing
      // transverse energy.
      VetoedFinalState fs(FinalState(-4.2, 4.2, 0*GeV));
      fs.addVetoOnThisFinalState(lfs);
      addProjection(FastJets(fs, FastJets::ANTIKT, 0.4), "Jets");
      addProjection(MissingMomentum(fs), "MissingET");
      
      VetoedFinalState vfs(FinalState(-4.2,4.2,0*GeV));
      vfs.addVetoOnThisFinalState(lfs);
      addProjection(vfs, "VFS");
      

      _sumofweight =0;

      _h_evnt_MET   = bookHisto1D("MET",500,0,500);
      _h_evnt_njets = bookHisto1D("evnt_njets",20,-0.5,19.5);
      _h_evnt_HT    = bookHisto1D("evnt_HT",logspace(50,100.0,200.0));
      _h_evnt_nEl   = bookHisto1D("evnt_nEL",20,-0.5,19.5);
      _h_evnt_nLep  = bookHisto1D("evnt_nLep",20,-0.5,19.5);
      _h_evnt_nMu   = bookHisto1D("evnt_nMu",20,-0.5,19.5);
      _h_3el_evnt_m3e= bookHisto1D("3elevnt_m3e",120,0,120);
      _h_4el_evnt_m4e= bookHisto1D("4elevnt_m4e",120,0,120);

      // Booking of histograms
      _h_njets = bookHisto1D("jet_mult", 11, -0.5, 10.5);
      _h_nBjets= bookHisto1D("jet_bMult",11,-0.4,10.5);
      //
      _h_jet_1_pT = bookHisto1D("jet_1_pT", logspace(50, 20.0, 500.0));
      _h_jet_2_pT = bookHisto1D("jet_2_pT", logspace(50, 20.0, 400.0));
      _h_jet_3_pT = bookHisto1D("jet_3_pT", logspace(50, 20.0, 300.0));
      _h_jet_4_pT = bookHisto1D("jet_4_pT", logspace(50, 20.0, 200.0));
      _h_jet_HT   = bookHisto1D("jet_HT", logspace(50, 100.0, 2000.0));
      //
      _h_bjet_1_pT = bookHisto1D("jetb_1_pT", logspace(50, 20.0, 400.0));
      _h_bjet_2_pT = bookHisto1D("jetb_2_pT", logspace(50, 20.0, 300.0));
      //
      _h_ljet_1_pT = bookHisto1D("jetl_1_pT", logspace(50, 20.0, 400.0));
      _h_ljet_2_pT = bookHisto1D("jetl_2_pT", logspace(50, 20.0, 300.0));
      //
      _h_W_had_mass = bookHisto1D("W_had_mass", 75, 30, 180);
      _h_W_had_pt   = bookHisto1D("W_had_pt",100,20.0,100);
      _h_W_had_eta  = bookHisto1D("W_had_eta",100,-4,4);
      _h_t_mass = bookHisto1D("t_mass", 150, 130, 430);
      _h_t_mass_W_cut = bookHisto1D("t_mass_W_cut", 150, 130, 430);
      //
      _h_jetb_1_jetb_2_dR   = bookHisto1D("jetb_1_jetb_2_dR", 20, 0.0, 7.0);
      _h_jetb_1_jetb_2_deta = bookHisto1D("jetb_1_jetb_2_deta", 20, 0.0, 7.0);
      _h_jetb_1_jetb_2_dphi = bookHisto1D("jetb_1_jetb_2_dphi", 20, 0.0, M_PI);
      _h_jetb_1_jetl_1_dR   = bookHisto1D("jetb_1_jetl_1_dR", 20, 0.0, 7.0);
      _h_jetb_1_jetl_1_deta = bookHisto1D("jetb_1_jetl_1_deta", 20, 0.0, 7.0);
      _h_jetb_1_jetl_1_dphi = bookHisto1D("jetb_1_jetl_1_dphi", 20, 0.0, M_PI);
      _h_jetl_1_jetl_2_dR   = bookHisto1D("jetl_1_jetl_2_dR", 20, 0.0, 7.0);
      _h_jetl_1_jetl_2_deta = bookHisto1D("jetl_1_jetl_2_deta", 20, 0.0, 7.0);
      _h_jetl_1_jetl_2_dphi = bookHisto1D("jetl_1_jetl_2_dphi", 20, 0.0, M_PI);
      _h_jetb_1_W_dR        = bookHisto1D("jetb_1_W_dR", 20, 0.0, 7.0);
      _h_jetb_1_W_deta      = bookHisto1D("jetb_1_W_deta", 20, 0.0, 7.0);
      _h_jetb_1_W_dphi      = bookHisto1D("jetb_1_W_dphi", 20, 0.0, M_PI);
      _h_jetb_1_l_dR        = bookHisto1D("jetb_1_l_dR", 20, 0.0, 7.0);
      _h_jetb_1_l_deta      = bookHisto1D("jetb_1_l_deta", 20, 0.0, 7.0);
      _h_jetb_1_l_dphi      = bookHisto1D("jetb_1_l_dphi", 20, 0.0, M_PI);
      _h_jetb_1_l_mass      = bookHisto1D("jetb_1_l_mass", 40, 0.0, 500.0);
    }


    void analyze(const Event& event) {
      const double weight = event.weight();

      // Use the "LFS" projection to require at least one hard charged
      // lepton. This is an experimental signature for the leptonically decaying
      // W. This helps to reduce pure QCD backgrounds.
      
      const ChargedLeptons& lfs = applyProjection<ChargedLeptons>(event, "LFS");
      const IdentifiedFinalState & electrons = applyProjection<IdentifiedFinalState>(event, "EFS");
      MSG_INFO("Electron multiplicity = " << electrons.size());
      _h_evnt_nEl->fill(electrons.size(),weight);
      foreach (const Particle& el , electrons.particles()) {
        MSG_INFO("Electron pT = " << el.pT());
      }
      if (electrons.size()<3) {
        MSG_INFO("Event failed lepton multiplicity cut");
        vetoEvent;
      }
      
      // Get all charged particles
      const FinalState& fs = applyProjection<FinalState>(event, "VFS");

      float n_iso_el=0;
      foreach (const Particle& l, electrons.particles()) {
          // Find Isolation As the econe/e_lepton
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
      
      // Use a missing ET cut to bias toward events with a hard neutrino from
      // the leptonically decaying W. This helps to reduce pure QCD backgrounds.
      const MissingMomentum& met = applyProjection<MissingMomentum>(event, "MissingET");
      _h_evnt_MET->fill(met.vectorEt().mod(),weight);
      MSG_INFO("Vector ET = " << met.vectorEt().mod() << " GeV");
      if (met.vectorEt().mod() < 30*GeV) {
        MSG_INFO("Event failed missing ET cut");
        vetoEvent;
      }
      const Particles bhadrons = sortByPt(applyProjection<HeavyHadrons>(event, "BCHadrons").bHadrons());
 

      // Use the "Jets" projection to check that there are at least 4 jets of
      // any pT. Getting the jets sorted by pT ensures that the first jet is the
      // hardest, and so on. We apply no pT cut here only because we want to
      // plot all jet pTs to help optimise our jet pT cut.
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
        // // Don't count jets that overlap with the hard leptons
        bool isolated = true;
        foreach (const Particle& lepton, lfs.chargedLeptons()) {
          if (deltaR(jet.momentum(), lepton.momentum()) < 0.4) {
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

      //Make all the plots from here
      //
 
      // Update passed-cuts counter and fill all-jets histograms
      _h_jet_1_pT->fill(alljets[0].pT()/GeV, weight);
      _h_jet_2_pT->fill(alljets[1].pT()/GeV, weight);
      _h_jet_3_pT->fill(alljets[2].pT()/GeV, weight);
      _h_jet_4_pT->fill(alljets[3].pT()/GeV, weight);

      _h_njets->fill(jets.size(), weight);
      _h_jet_HT->fill(ht/GeV, weight);
      _h_nBjets->fill(bjets.size(),weight);


      // Plot the pTs of the identified jets.
      _h_bjet_1_pT->fill(bjets[0].pT(), weight);
      _h_bjet_2_pT->fill(bjets[1].pT(), weight);
      _h_ljet_1_pT->fill(ljets[0].pT(), weight);
      _h_ljet_2_pT->fill(ljets[1].pT(), weight);

      // Construct the hadronically decaying W momentum 4-vector from pairs of
      // non-b-tagged jets. The pair which best matches the W mass is used. We start
      // with an always terrible 4-vector estimate which should always be "beaten" by
      // a real jet pair.
      FourMomentum W(10*sqrtS(), 0, 0, 0);
      for (size_t i = 0; i < ljets.size()-1; ++i) {
        for (size_t j = i + 1; j < ljets.size(); ++j) {
          const FourMomentum Wcand = ljets[i].momentum() + ljets[j].momentum();
          MSG_TRACE(i << "," << j << ": candidate W mass = " << Wcand.mass()/GeV
                    << " GeV, vs. incumbent candidate with " << W.mass()/GeV << " GeV");
          if (fabs(Wcand.mass() - 80.4*GeV) < fabs(W.mass() - 80.4*GeV)) {
            W = Wcand;
          }
        }
      }
      MSG_INFO("Candidate W mass = " << W.mass() << " GeV");

      // There are two b-jets with which this can be combined to make the
      // hadronically decaying top, one of which is correct and the other is
      // not... but we have no way to identify which is which, so we construct
      // both possible top momenta and fill the histograms with both.
      const FourMomentum t1 = W + bjets[0].momentum();
      const FourMomentum t2 = W + bjets[1].momentum();
      _h_W_had_mass->fill(W.mass(), weight);
      _h_W_had_pt->fill(W.mass(),weight);
      _h_W_had_eta->fill(W.eta(),weight);
      _h_t_mass->fill(t1.mass(), weight);
      _h_t_mass->fill(t2.mass(), weight);

      // Placing a cut on the well-known W mass helps to reduce backgrounds
      if (inRange(W.mass()/GeV, 75.0, 85.0)) {
        MSG_INFO("W found with mass " << W.mass()/GeV << " GeV");
        _h_t_mass_W_cut->fill(t1.mass(), weight);
        _h_t_mass_W_cut->fill(t2.mass(), weight);

        _h_jetb_1_jetb_2_dR->fill(deltaR(bjets[0].momentum(), bjets[1].momentum()),weight);
        _h_jetb_1_jetb_2_deta->fill(fabs(bjets[0].eta()-bjets[1].eta()),weight);
        _h_jetb_1_jetb_2_dphi->fill(deltaPhi(bjets[0].momentum(),bjets[1].momentum()),weight);

        _h_jetb_1_jetl_1_dR->fill(deltaR(bjets[0].momentum(), ljets[0].momentum()),weight);
        _h_jetb_1_jetl_1_deta->fill(fabs(bjets[0].eta()-ljets[0].eta()),weight);
        _h_jetb_1_jetl_1_dphi->fill(deltaPhi(bjets[0].momentum(),ljets[0].momentum()),weight);

        _h_jetl_1_jetl_2_dR->fill(deltaR(ljets[0].momentum(), ljets[1].momentum()),weight);
        _h_jetl_1_jetl_2_deta->fill(fabs(ljets[0].eta()-ljets[1].eta()),weight);
        _h_jetl_1_jetl_2_dphi->fill(deltaPhi(ljets[0].momentum(),ljets[1].momentum()),weight);

        _h_jetb_1_W_dR->fill(deltaR(bjets[0].momentum(), W),weight);
        _h_jetb_1_W_deta->fill(fabs(bjets[0].eta()-W.eta()),weight);
        _h_jetb_1_W_dphi->fill(deltaPhi(bjets[0].momentum(),W),weight);

        FourMomentum l=lfs.chargedLeptons()[0].momentum();
        _h_jetb_1_l_dR->fill(deltaR(bjets[0].momentum(), l),weight);
        _h_jetb_1_l_deta->fill(fabs(bjets[0].eta()-l.eta()),weight);
        _h_jetb_1_l_dphi->fill(deltaPhi(bjets[0].momentum(),l),weight);
        _h_jetb_1_l_mass->fill(FourMomentum(bjets[0].momentum()+l).mass(), weight);
      }

    }


    void finalize() {
      double norm = crossSection()/sumOfWeights();
      scale(_h_evnt_MET,norm);
      scale(_h_evnt_njets,norm);
      scale(_h_evnt_HT,norm);
      scale(_h_evnt_nEl,norm);
      scale(_h_evnt_nLep,norm);
      scale(_h_evnt_nMu,norm);
      scale(_h_3el_evnt_m3e,norm);
      scale(_h_4el_evnt_m4e,norm);
      scale(_h_njets,norm);
      scale(_h_nBjets,norm);
      scale(_h_jet_1_pT,norm);
      scale(_h_jet_2_pT,norm);
      scale(_h_jet_3_pT,norm);
      scale(_h_jet_4_pT,norm);
      scale(_h_jet_HT,norm);
      scale(_h_bjet_1_pT,norm);
      scale(_h_bjet_2_pT,norm);
      scale(_h_ljet_1_pT,norm);
      scale(_h_ljet_2_pT,norm);
      scale(_h_W_had_mass,norm);
      scale(_h_W_had_pt,norm);
      scale(_h_W_had_eta,norm);
      scale(_h_W_lep_mass,norm);
      scale(_h_W_lep_pt,norm);
      scale(_h_W_lep_mt,norm);
      scale(_h_W_lep_eta,norm);
      scale(_h_t_mass,norm);
      scale(_h_t_mass_W_cut,norm);
      scale(_h_jetb_1_jetb_2_dR,norm);
      scale(_h_jetb_1_jetb_2_deta,norm);
      scale(_h_jetb_1_jetb_2_dphi,norm);
      scale(_h_jetb_1_jetl_1_dR,norm);
      scale(_h_jetb_1_jetl_1_deta,norm);
      scale(_h_jetb_1_jetl_1_dphi,norm);
      scale(_h_jetl_1_jetl_2_dR,norm);
      scale(_h_jetl_1_jetl_2_deta,norm);
      scale(_h_jetl_1_jetl_2_dphi,norm);
      scale(_h_jetb_1_W_dR,norm);
      scale(_h_jetb_1_W_deta,norm);
      scale(_h_jetb_1_W_dphi,norm);
      scale(_h_jetb_1_l_dR,norm);
      scale(_h_jetb_1_l_deta,norm);
      scale(_h_jetb_1_l_dphi,norm);
      scale(_h_jetb_1_l_mass,norm);
    }

    //@}


  private:

    // @name Histogram data members
    //@{

    Histo1DPtr _h_evnt_MET;
    Histo1DPtr _h_evnt_njets;
    Histo1DPtr _h_evnt_HT;
    Histo1DPtr _h_evnt_nEl;
    Histo1DPtr _h_evnt_nLep;
    Histo1DPtr _h_evnt_nMu;
    Histo1DPtr _h_3el_evnt_m3e;
    Histo1DPtr _h_4el_evnt_m4e;
    Histo1DPtr _h_njets;
    Histo1DPtr _h_nBjets;
    Histo1DPtr _h_jet_1_pT, _h_jet_2_pT, _h_jet_3_pT, _h_jet_4_pT;
    Histo1DPtr _h_jet_HT;
    Histo1DPtr _h_bjet_1_pT, _h_bjet_2_pT;
    Histo1DPtr _h_ljet_1_pT, _h_ljet_2_pT;
    Histo1DPtr _h_W_had_mass;
    Histo1DPtr _h_W_had_pt;
    Histo1DPtr _h_W_had_eta;
    Histo1DPtr _h_W_lep_mass;
    Histo1DPtr _h_W_lep_mt;
    Histo1DPtr _h_W_lep_pt;
    Histo1DPtr _h_W_lep_eta;
    Histo1DPtr _h_t_mass, _h_t_mass_W_cut;
    Histo1DPtr _h_t_pt, _h_t_pt_W_cut;
    Histo1DPtr _h_t_eta,_h_t_eta_W_cut;
    Histo1DPtr _h_jetb_1_jetb_2_dR, _h_jetb_1_jetb_2_deta, _h_jetb_1_jetb_2_dphi;
    Histo1DPtr _h_jetb_1_jetl_1_dR, _h_jetb_1_jetl_1_deta, _h_jetb_1_jetl_1_dphi;
    Histo1DPtr _h_jetl_1_jetl_2_dR, _h_jetl_1_jetl_2_deta, _h_jetl_1_jetl_2_dphi;
    Histo1DPtr _h_jetb_1_W_dR, _h_jetb_1_W_deta, _h_jetb_1_W_dphi;
    Histo1DPtr _h_jetb_1_l_dR, _h_jetb_1_l_deta, _h_jetb_1_l_dphi,_h_jetb_1_l_mass;

    float _sumofweight;
    //@}

  };



  // The hook for the plugin system
  DECLARE_RIVET_PLUGIN(TTBAR);

}
