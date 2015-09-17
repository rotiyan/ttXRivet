#include "Rivet/Analysis.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/HeavyHadrons.hh"
#include "Rivet/Projections/VetoedFinalState.hh"
#include "Rivet/Projections/ChargedLeptons.hh"
#include "Rivet/Projections/MissingMomentum.hh"
#include "Rivet/Projections/IdentifiedFinalState.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Projections/ZFinder.hh"
#include "Rivet/Projections/WFinder.hh"
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

      IdentifiedFinalState muons(FinalState(-4.2,4.2,10*GeV));
      muons.acceptId(PID::MUON);
      muons.acceptId(PID::ANTIMUON);
 
      addProjection(electrons, "EFS");
      addProjection(muons,"MUFS");
      
      ChargedLeptons lfs(FinalState(-4.2,4.2,10*GeV));
      addProjection(lfs,"LFS");

      FinalState zfs;
      Cut zeefscut = (Cuts::abseta <4.2) && (Cuts::pT>10*GeV);
      ZFinder zeeFinder(zfs,zeefscut,PID::ELECTRON,5.0*GeV,115.0*GeV,0.2,ZFinder::CLUSTERNODECAY,ZFinder::NOTRACK);
      addProjection(zeeFinder,"zeeFinder");

      ZFinder zmumuFinder(zfs,zeefscut,PID::MUON,5.0*GeV,115.0*GeV,0.2,ZFinder::NOCLUSTER,ZFinder::NOTRACK);
      addProjection(zmumuFinder,"zmumuFinder");

      WFinder welFinder(zfs,zeefscut,PID::ELECTRON,5.0*GeV,115.0*GeV,25.0*GeV,0.1);//WFinder::CLUSTERNODECAY,WFinder::NOTRACK,WFinder::TRANSMASS);
      addProjection(welFinder,"welFinder");

      WFinder wmuFinder(zfs,zeefscut,PID::MUON,5.0*GeV,115.0*GeV,25.0*GeV,0.1);//,WFinder::CLUSTERNODECAY,WFinder::NOTRACK,WFinder::TRANSMASS);
      addProjection(wmuFinder,"wmuFinder");


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
    
      _h_weight     = bookHisto1D("weight",200,-20,20);
      _h_evnt_MET_before   = bookHisto1D("MET_before",200,0,800);
      _h_evnt_MET_after = bookHisto1D("MET_after",200,0,800);
      _h_evnt_njets = bookHisto1D("evnt_njets",20,-0.5,19.5);
      _h_evnt_HT    = bookHisto1D("evnt_HT",200,100,900);
      _h_evnt_nEl   = bookHisto1D("evnt_nEL",20,-0.5,19.5);
      _h_evnt_nMu   = bookHisto1D("evnt_nMu",20,-0.5,19.5);
      _h_3el_evnt_m3e= bookHisto1D("3elevnt_m3e",120,0,120);
      _h_4el_evnt_m4e= bookHisto1D("4elevnt_m4e",120,0,120);

      //
      _h_njets = bookHisto1D("jet_l_mult", 11, -0.5, 10.5);
      _h_nBjets= bookHisto1D("jet_b_Mult",11,-0.4,10.5);
      //
      _h_jet_1_pT = bookHisto1D("jet_1_pT", 100,10,410);
      _h_jet_2_pT = bookHisto1D("jet_2_pT", 100,10,410);
      _h_jet_3_pT = bookHisto1D("jet_3_pT", 100,10,410);
      _h_jet_4_pT = bookHisto1D("jet_4_pT", 100,10,410);
      //
      _h_bjet_1_pT = bookHisto1D("jetb_1_pT", 100,10,410);
      _h_bjet_2_pT = bookHisto1D("jetb_2_pT", 100,10,410);
      //
      _h_ljet_1_pT = bookHisto1D("jetl_1_pT", 100,10,410);
      _h_ljet_2_pT = bookHisto1D("jetl_2_pT", 100,10,410);
      //
      _h_W_had_mass = bookHisto1D("W_had_mass", 120, 5, 115);
      _h_W_had_pt   = bookHisto1D("W_had_pt",100,10.0,410);
      _h_W_had_eta  = bookHisto1D("W_had_eta",50,-4,4);
      _h_W_had_phi  = bookHisto1D("W_hadd_phi",50,0,6);
      //
      _h_zee_mass   = bookHisto1D("Z_ee_mass",120,5,115);
      _h_zee_pt     = bookHisto1D("Z_ee_pt",100,0,400);
      _h_zee_eta    = bookHisto1D("Z_ee_eta",50,-5,5);
      _h_zee_phi    = bookHisto1D("Z_ee_phi",50,0,6);
      _h_zel_pt     = bookHisto1D("Zel_pt",100,0,400);
      _h_zel_eta    = bookHisto1D("Zel_eta",50,-5,5);
      _h_zel_phi    = bookHisto1D("Zel_phi",50,0,6);
      //
      _h_zmumu_mass = bookHisto1D("Z_mumu_mass",120,5,115);
      _h_zmumu_pt   = bookHisto1D("Z_mumu_pt",100,0,400);
      _h_zmumu_eta  = bookHisto1D("Z_mumu_eta",50,-5,5);
      _h_zmumu_phi  = bookHisto1D("Z_mumu_phi",50,0,6);
      _h_zmu_pt     = bookHisto1D("Zmu_pt",100,0,400);
      _h_zmu_eta    = bookHisto1D("Zmu_eta",50,-5,5);
      _h_zmu_phi    = bookHisto1D("Zmu_phi",50,0,6);
      //
      _h_wenu_mass  = bookHisto1D("W_enu_mass",120,5,115);
      _h_wenu_pt    = bookHisto1D("W_enu_pt",100,0,400);
      _h_wenu_mt    = bookHisto1D("W_enu_mt",200,0,400);
      _h_wenu_eta   = bookHisto1D("W_enu_eta",50,-5,5);
      _h_wenu_phi   = bookHisto1D("W_enu_phi",50,0,6);
      _h_wel_pt     = bookHisto1D("W_el_pt",100,0,400);
      _h_wel_eta    = bookHisto1D("W_el_eta",50,-5,5);
      _h_wel_phi    = bookHisto1D("W_el_phi",50,0,6);
      //
      _h_wmunu_mass = bookHisto1D("W_munu_mass",120,5,115);
      _h_wmunu_pt   = bookHisto1D("W_munu_pt",100,0,400);
      _h_wmunu_mt   = bookHisto1D("W_munu_mt",100,0,400);
      _h_wmunu_eta  = bookHisto1D("W_munu_eta",50,-5,5);
      _h_wmunu_phi  = bookHisto1D("W_munu_phi",50,0,6);
      _h_wmu_pt     = bookHisto1D("W_mu_pt",100,0,400);
      _h_wmu_eta    = bookHisto1D("W_mu_eta",50,-5,5);
      _h_wmu_phi    = bookHisto1D("W_mu_phi",50,0,6);
      //
      _h_t_mass     = bookHisto1D("t_mass", 150, 130, 430);
      _h_t_mass_W_cut = bookHisto1D("t_mass_W_cut", 150, 130, 430);
      _h_t_pt       = bookHisto1D("t_pt",100,0,200);
      _h_t_pt_W_cut = bookHisto1D("t_pt_W_cut",100,0,200);
      _h_t_lep_mass = bookHisto1D("t_lep_mass",150,130,430);
      _h_t_lep_mass_W_cut = bookHisto1D("t_lep_mass_W_cut",150,130,430);
      _h_t_lep_pt   = bookHisto1D("t_lep_pt",100,0,200);
      _h_t_lep_pt_W_cut= bookHisto1D("t_lep_pt_W_cut",100,0,200);
      //
      _h_top_dR     = bookHisto1D("top_dR",100,0.0,7.0);
      _h_top_dEta   = bookHisto1D("top_dEta",100,0.0,7.0);
      _h_top_dPhi   = bookHisto1D("top_dPhi",100,0.0,7.0);
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
      const IdentifiedFinalState & muons     = applyProjection<IdentifiedFinalState>(event, "MUFS");
      const ZFinder & zeeFinder     = applyProjection<ZFinder>(event,"zeeFinder");
      const ZFinder & zmumuFinder   = applyProjection<ZFinder>(event,"zmumuFinder");
      const WFinder & welFinder     = applyProjection<WFinder>(event,"welFinder");
      const WFinder & wmuFinder     = applyProjection<WFinder>(event,"wmuFinder");

      if(zeeFinder.bosons().size()==0 && zmumuFinder.bosons().size()==0)
      {
          MSG_INFO("ZeeFinder size: "<<zeeFinder.size());
          MSG_INFO("ZmumuFinder size: "<<zmumuFinder.size());
          MSG_INFO("Veto Event");
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
      _h_evnt_MET_before->fill(met.vectorEt().mod(),weight);
      MSG_INFO("Vector ET = " << met.vectorEt().mod() << " GeV");
 
      const FastJets& jetpro = applyProjection<FastJets>(event, "Jets");
      const Jets jets = jetpro.jetsByPt(20*GeV);
 
      double ht = 0.0;
      foreach (const Jet& j, jets) { ht += j.pT(); }
      _h_evnt_HT->fill(ht/GeV, weight);
 
      if (met.vectorEt().mod() < 30*GeV && (welFinder.bosons().size()<1 || wmuFinder.bosons().size()<1)) 
      {
        MSG_INFO("Event failed missing ET cut, or couldn't find leptonically decaying W candidate");
        vetoEvent;
      }
      const Particles bhadrons = sortByPt(applyProjection<HeavyHadrons>(event, "BCHadrons").bHadrons());
 

      // Use the "Jets" projection to check that there are at least 4 jets of
      // any pT. Getting the jets sorted by pT ensures that the first jet is the
      // hardest, and so on. We apply no pT cut here only because we want to
      // plot all jet pTs to help optimise our jet pT cut.
  
     if(jets.size()<4)
      {
          MSG_INFO("Event failed jet multiplicity cut");
          vetoEvent;
      }
      
      Jets bjets, ljets;
      foreach (const Jet& jet, jets) {
        // // Don't count jets that overlap with the hard leptons
        bool isolated = true;
        foreach (const Particle& lepton, lfs.chargedLeptons()) 
        {
          if (deltaR(jet.momentum(), lepton.momentum()) < 0.4) 
          {
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
      _h_nBjets->fill(bjets.size(),weight);
      _h_njets->fill(jets.size(),weight);

      MSG_INFO("Number of l-jets = " << ljets.size());
      if (bjets.size() < 2) {
        MSG_INFO("Event failed post-lepton-isolation b-tagging cut");
        vetoEvent;
      }
      if (ljets.size() < 2) {
        MSG_INFO("Event failed since not enough light jets remaining after lepton-isolation");
        vetoEvent;
      }
   
      //Make all the plots from here
      //
      MSG_INFO("Event passed all cuts: Filling histograms");
      
      _h_evnt_MET_after->fill(met.vectorEt().mod(),weight);
      _h_weight->fill(weight);
      _h_evnt_nEl->fill(electrons.size(),weight);
      _h_evnt_nMu->fill(muons.size(),weight);

      _sumofweight += event.weight();


      if(zeeFinder.bosons().size()>0)
      {
          FourMomentum zeeMom = zeeFinder.bosons()[0].momentum();
          _h_zee_mass->fill(zeeMom.mass()/GeV,weight);
          _h_zee_pt->fill(zeeMom.pT()/GeV,weight);
          _h_zee_eta->fill(zeeMom.eta(),weight);
          _h_zee_phi->fill(zeeMom.phi(),weight);
          foreach(const Particle& p, zeeFinder.constituents())
          {
              _h_zel_pt->fill(p.momentum().pT()/GeV,weight);
              _h_zel_eta->fill(p.momentum().eta(),weight);
              _h_zel_phi->fill(p.momentum().phi(),weight);
          }

      }

      if(zmumuFinder.bosons().size()>0)
      {
          FourMomentum zmumuMom = zmumuFinder.bosons()[0].momentum();
          _h_zmumu_mass->fill(zmumuMom.mass()/GeV,weight);
          _h_zmumu_pt->fill(zmumuMom.pT()/GeV,weight);
          _h_zmumu_eta->fill(zmumuMom.eta(),weight);
          _h_zmumu_phi->fill(zmumuMom.phi(),weight);
          foreach(const Particle &p, zmumuFinder.constituents())
          {
              _h_zmu_pt->fill(p.momentum().pT()/GeV,weight);
              _h_zmu_eta->fill(p.momentum().eta(),weight);
              _h_zmu_phi->fill(p.momentum().phi(),weight);
          }
      }

      FourMomentum W_lep(10.*sqrtS(),0,0,0);
      if(welFinder.bosons().size()>0)
      {
          FourMomentum wenuMom = welFinder.bosons()[0].momentum();
          W_lep = wenuMom;

          _h_wenu_mass->fill(wenuMom.mass()/GeV,weight);
          _h_wenu_pt->fill(wenuMom.pT()/GeV,weight);
          _h_wenu_mt->fill(welFinder.mT()/GeV,weight);
          _h_wenu_eta->fill(wenuMom.eta(),weight);
          _h_wenu_phi->fill(wenuMom.phi(),weight);
          foreach(const Particle& p, welFinder.constituentLeptons())
          {
              _h_wel_pt->fill(p.momentum().pT()/GeV,weight);
              _h_wel_eta->fill(p.momentum().eta(),weight);
              _h_wel_phi->fill(p.momentum().phi(),weight);
          }
      }

      if(wmuFinder.bosons().size()>0)
      {
          FourMomentum wmunuMom = wmuFinder.bosons()[0].momentum();
          W_lep = wmunuMom;

          _h_wmunu_mass->fill(wmunuMom.mass()/GeV,weight);
          _h_wmunu_pt->fill(wmunuMom.pT()/GeV,weight);
          _h_wmunu_mt->fill(wmuFinder.mT()/GeV,weight);
          _h_wmunu_eta->fill(wmunuMom.eta(),weight);
          _h_wmunu_phi->fill(wmunuMom.phi(),weight);
          foreach(const Particle &p, wmuFinder.constituentLeptons())
          {
              _h_wmu_pt->fill(p.momentum().pT()/GeV,weight);
              _h_wmu_eta->fill(p.momentum().eta(),weight);
              _h_wmu_phi->fill(p.momentum().phi(),weight);
          }
      }

 
      // Update passed-cuts counter and fill all-jets histograms
      _h_jet_1_pT->fill(jets[0].pT()/GeV, weight);
      _h_jet_2_pT->fill(jets[1].pT()/GeV, weight);
      _h_jet_3_pT->fill(jets[2].pT()/GeV, weight);
      _h_jet_4_pT->fill(jets[3].pT()/GeV, weight);

     
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

      const float target_topMass = 173.21*GeV;

      _h_W_had_mass->fill(W.mass()/GeV, weight);
      _h_W_had_pt->fill(W.pt()/GeV,weight);
      _h_W_had_eta->fill(W.eta(),weight);
      _h_W_had_phi->fill(W.phi(),weight);

      FourMomentum t_had(10*sqrtS(),0.0,0.0,0.0);
      FourMomentum t_lep(10*sqrtS(),0.0,0.0,0.0);
      if(fabs(target_topMass - t1.mass()) < fabs(target_topMass - t2.mass()))
      {
          _h_t_mass->fill(t1.mass()/GeV, weight);
          _h_t_pt->fill(t1.pT()/GeV,weight);
          t_had = t1;
      }
      else
      {
        _h_t_mass->fill(t2.mass()/GeV, weight);
        _h_t_pt->fill(t2.pT()/GeV,weight);
        t_had = t2;
      }

      //Find the leptonic top

      const FourMomentum t1_lep = W_lep + bjets[0].momentum();
      const FourMomentum t2_lep = W_lep + bjets[1].momentum();
      
      if(fabs(target_topMass - t1_lep.mass()) < fabs(target_topMass - t2_lep.mass()))
      {
          _h_t_lep_mass->fill(t1_lep.mass()/GeV,weight);
          _h_t_lep_pt->fill(t1_lep.pT()/GeV,weight);
          t_lep = t1_lep;
      }
      else
      {
          _h_t_lep_mass->fill(t2_lep.mass()/GeV,weight);
          _h_t_lep_pt->fill(t2_lep.pT()/GeV,weight);
          t_lep = t2_lep;
      }

      //Around a 10 GeV top mass window fill the delta distributions
      if(fabs(target_topMass -t_had.mass()) <10 && fabs(target_topMass - t_lep.mass()) <10)
      {
          _h_top_dR->fill(deltaR(t_had,t_lep),weight);
          _h_top_dEta->fill(deltaEta(t_had,t_lep),weight);
          _h_top_dPhi->fill(deltaPhi(t_had,t_lep),weight);
      }


      // Placing a cut on the well-known W mass helps to reduce backgrounds
      if (inRange(W.mass()/GeV, 75.0, 85.0)) 
      {
        MSG_INFO("W found with mass " << W.mass()/GeV << " GeV");
        if(fabs(target_topMass - t1.mass()) < fabs(target_topMass - t2.mass()))
        {
            _h_t_mass_W_cut->fill(t1.mass()/GeV, weight);
            _h_t_pt_W_cut->fill(t1.pT()/GeV,weight);
        }
        else
        {
            _h_t_mass_W_cut->fill(t2.mass(), weight);
            _h_t_pt_W_cut->fill(t2.pT()/GeV,weight);
        }

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
        MSG_INFO("CROSS SSECTION:"<<crossSection());
        MSG_INFO("Sum of weights:"<<sumOfWeights());
      double norm = crossSection()/sumOfWeights();

      scale(_h_evnt_MET_before,norm);
      scale(_h_evnt_MET_after,norm);
      scale(_h_evnt_njets,norm);
      scale(_h_evnt_HT,norm);
      scale(_h_evnt_nEl,norm);
      scale(_h_evnt_nMu,norm);
      scale(_h_3el_evnt_m3e,norm);
      scale(_h_4el_evnt_m4e,norm);
      scale(_h_njets,norm);
      scale(_h_nBjets,norm);
      scale(_h_jet_1_pT,norm);
      scale(_h_jet_2_pT,norm);
      scale(_h_jet_3_pT,norm);
      scale(_h_jet_4_pT,norm);
      scale(_h_bjet_1_pT,norm);
      scale(_h_bjet_2_pT,norm);
      scale(_h_ljet_1_pT,norm);
      scale(_h_ljet_2_pT,norm);
      scale(_h_W_had_mass,norm);
      scale(_h_W_had_pt,norm);
      scale(_h_W_had_eta,norm);
      scale(_h_W_had_phi,norm);
      scale(_h_zee_mass,norm);
      scale(_h_zee_pt,norm);
      scale(_h_zee_eta,norm);
      scale(_h_zee_phi,norm);
      scale(_h_zel_pt,norm);
      scale(_h_zel_eta,norm);
      scale(_h_zel_phi,norm);
      scale(_h_zmumu_mass,norm);
      scale(_h_zmumu_pt,norm);
      scale(_h_zmumu_eta,norm);
      scale(_h_zmumu_phi,norm);
      scale(_h_zmu_pt,norm);
      scale(_h_zmu_eta,norm);
      scale(_h_zmu_phi,norm);
      scale(_h_wenu_mass,norm);
      scale(_h_wenu_pt,norm);
      scale(_h_wenu_eta,norm);
      scale(_h_wenu_phi,norm);
      scale(_h_wel_pt,norm);
      scale(_h_wel_eta,norm);
      scale(_h_wel_phi,norm);
      scale(_h_wmunu_mass,norm);
      scale(_h_wmunu_pt,norm);
      scale(_h_wmunu_eta,norm);
      scale(_h_wmunu_phi,norm);
      scale(_h_wmu_pt,norm);
      scale(_h_wmu_eta,norm);
      scale(_h_wmu_phi,norm);
      scale(_h_t_mass,norm);
      scale(_h_t_pt,norm);
      scale(_h_t_mass_W_cut,norm);
      scale(_h_t_pt_W_cut,norm);
      scale(_h_t_lep_mass,norm);
      scale(_h_t_lep_mass_W_cut,norm);
      scale(_h_t_lep_pt,norm);
      scale(_h_t_lep_pt_W_cut,norm);
      scale(_h_top_dR,norm);
      scale(_h_top_dEta,norm);
      scale(_h_top_dPhi,norm);
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

    Histo1DPtr _h_weight;
    Histo1DPtr _h_evnt_MET_before, _h_evnt_MET_after;
    Histo1DPtr _h_evnt_njets;
    Histo1DPtr _h_evnt_HT;
    Histo1DPtr _h_evnt_nEl;
    Histo1DPtr _h_evnt_nMu;
    Histo1DPtr _h_3el_evnt_m3e;
    Histo1DPtr _h_4el_evnt_m4e;
    Histo1DPtr _h_njets;
    Histo1DPtr _h_nBjets;
    Histo1DPtr _h_jet_1_pT, _h_jet_2_pT, _h_jet_3_pT, _h_jet_4_pT;
    Histo1DPtr _h_bjet_1_pT, _h_bjet_2_pT;
    Histo1DPtr _h_ljet_1_pT, _h_ljet_2_pT;
    Histo1DPtr _h_zee_mass,_h_zee_pt,_h_zee_eta,_h_zee_phi;
    Histo1DPtr _h_zel_pt,_h_zel_eta,_h_zel_phi;
    Histo1DPtr _h_zmumu_mass,_h_zmumu_pt,_h_zmumu_eta,_h_zmumu_phi;
    Histo1DPtr _h_zmu_pt,_h_zmu_eta,_h_zmu_phi;
    Histo1DPtr _h_wenu_mass,_h_wenu_pt,_h_wenu_mt,_h_wenu_eta,_h_wenu_phi;
    Histo1DPtr _h_wel_pt,_h_wel_eta,_h_wel_phi;
    Histo1DPtr _h_wmunu_mass,_h_wmunu_pt,_h_wmunu_mt,_h_wmunu_eta,_h_wmunu_phi;
    Histo1DPtr _h_wmu_pt,_h_wmu_eta,_h_wmu_phi;
    Histo1DPtr _h_W_had_mass,_h_W_had_pt,_h_W_had_eta,_h_W_had_phi;
    Histo1DPtr _h_t_mass, _h_t_mass_W_cut;
    Histo1DPtr _h_t_pt, _h_t_pt_W_cut;
    Histo1DPtr _h_t_eta,_h_t_eta_W_cut;
    Histo1DPtr _h_t_lep_mass, _h_t_lep_mass_W_cut;
    Histo1DPtr _h_t_lep_pt, _h_t_lep_pt_W_cut;
    Histo1DPtr _h_top_dR,_h_top_dEta,_h_top_dPhi;
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
