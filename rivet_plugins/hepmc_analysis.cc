// -*- C++ -*-
#include "Rivet/Analysis.hh"
#include "Rivet/Projections/ZFinder.hh"
#include "Rivet/Projections/ChargedLeptons.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/IdentifiedFinalState.hh"
#include "Rivet/Projections/LeadingParticlesFinalState.hh"
#include "Rivet/Projections/UnstableFinalState.hh"
#include "Rivet/Projections/HadronicFinalState.hh"
#include "Rivet/Projections/VetoedFinalState.hh"
#include "Rivet/Projections/DressedLeptons.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Tools/BinnedHistogram.hh"
#include "Rivet/Projections/ChargedFinalState.hh"
#include "Rivet/Projections/MissingMomentum.hh"
#include "Rivet/Projections/VisibleFinalState.hh"
#include "Rivet/Tools/RivetMT2.hh"




/// @todo Include more projections as required, e.g. ChargedFinalState, FastJets, ZFinder...

namespace Rivet {

  using namespace Cuts;

  class hepmc_analysis: public Analysis {
  public:

    /// Constructor
    hepmc_analysis()
      : Analysis("hepmc_analysis")
    {    }


    /// @name Analysis methods
    //@{

    /// Book histograms and initialise projections before the run
    void init() {
        
      const FinalState fs(Cuts::abseta < 4.5);
      addProjection(fs, "ALL_FS");

      // A FinalState is used to select particles within |eta| < 2.5 and with pT
      // > 10 GeV, out of which the ChargedLeptons projection picks only the
      // electrons and muons, to be accessed later as "LFS".
      ChargedLeptons lfs(FinalState(-2.5, 2.5, 10*GeV));
      addProjection(lfs, "LFS");



      /// Get electrons from truth record
      IdentifiedFinalState elec_fs((Cuts::abseta < 2.5) & (Cuts::pT > 10*GeV));
      elec_fs.acceptIdPair(PID::ELECTRON);
      addProjection(elec_fs, "ELEC_FS");

      /// Get muons which pass the initial kinematic cuts:
      IdentifiedFinalState muon_fs((Cuts::abseta < 2.5) & (Cuts::pT > 10*GeV));
      muon_fs.acceptIdPair(PID::MUON);
      addProjection(muon_fs, "MUON_FS");
      addProjection(MissingMomentum(fs), "MissingET");


      /// Get all neutrinos. These will not be used to form jets.
      /// We'll use the highest 2 pT neutrinos to calculate the MET
      IdentifiedFinalState neutrino_fs(Cuts::abseta < 4.5);
      neutrino_fs.acceptNeutrinos();
      addProjection(neutrino_fs, "NEUTRINO_FS");

      //Add a Zfinder projection
      Cut cut = (Cuts::abseta < 2.5) & (Cuts::pT > 10*GeV);
      
      ZFinder elZfinder(fs, cut, PID::ELECTRON, 1*GeV, 115*GeV, 0.2, ZFinder::CLUSTERNODECAY, ZFinder::TRACK);
      addProjection(elZfinder, "elZFinder");
      
      ZFinder muZfinder(fs,cut, PID::MUON,1*GeV, 115*GeV, 0.2, ZFinder::CLUSTERNODECAY, ZFinder::TRACK);
      addProjection(muZfinder, "muZFinder");


      // Final state used as input for jet-finding.
      // We include everything except the muons and neutrinos
      VetoedFinalState jet_input(fs);
      jet_input.vetoNeutrinos();
      jet_input.addVetoPairId(PID::MUON);
      addProjection(jet_input, "JET_INPUT");

      // Get the jets
      FastJets jets(jet_input, FastJets::ANTIKT, 0.4);
      addProjection(jets, "JETS");

      /// @todo Book histograms here, e.g.:
      // _h_XXXX = bookProfile1D(1, 1, 1);
      // _h_YYYY = bookHisto1D(2, 1, 1);
      h_njets	 = bookHisto1D("jet_mult", 11, -0.5, 10.5);
      h_nljets   = bookHisto1D("ljet_mult",11, -0.5, 10.5);
      h_nbjets   = bookHisto1D("bjet_mult",11, -0.5, 10.5);
      h_nChrgLeps= bookHisto1D("chrgLep_mult",11,-0.5,10.5);
      h_PDG_nEl  = bookHisto1D("PDG_nEL",11,-0.5,10.5);
      h_PDG_nMu  = bookHisto1D("PDG_nMu",11,-0.5,10.5);

      h_MET       = bookHisto1D("MET",100,10,200);
      h_b1_b2_dEta= bookHisto1D("b1_b2-dEta",100,-3.14,3.14);
      h_b1_b2_dPhi= bookHisto1D("b1_b2-dPhi",100,-3.14,3.14);
      h_b1_b2_dR  = bookHisto1D("b1_b2-dR",100,-4,4);

      h_t1_t2_dEta= bookHisto1D("t1_t2-dEta",100,-3.14,3.14);
      h_t1_t2_dPhi= bookHisto1D("t1_t2-dPhi",100,-3.14,3.14);
      h_t1_t2_dR  = bookHisto1D("t1_t2-dR",100,-4,4);

      h_el_pt     = bookHisto1D("el_pt",250,0,500);
      h_el_eta    = bookHisto1D("el_eta",100,-4,4);
      h_el_phi    = bookHisto1D("el_phi",100,0,8);
      h_diEl_mass = bookHisto1D("diEl_mass",100,20,140);
      h_diEl_PDG_mass = bookHisto1D("diEl_PDG_mass",100,20,140);

      h_mu_pt     = bookHisto1D("mu_pt",250,0,500);
      h_mu_eta    = bookHisto1D("mu_eta",100,-4,4);
      h_mu_phi    = bookHisto1D("mu_phi",100,0,8);
      h_diMu_mass = bookHisto1D("diMu_mass",100,20,140);
      h_diMu_PDG_mass = bookHisto1D("diMu_PDG_mass",100,20,140);

      h_Zboson_pt = bookHisto1D("zbos_pt",100,10,120);
      h_Zboson_eta= bookHisto1D("zbos_eta",100,-4,4);
      h_Zboson_phi= bookHisto1D("zbos_phi",100,0,8);
      h_Zboson_b1_dr = bookHisto1D("zbos_b1_dr",100,0,3.14);
      h_Zboson_b2_dr = bookHisto1D("zbos_b2_dr",100,0,3.14);



      h_top_mass  = bookHisto1D("top_mass",400,100,500);
      h_top_pt	  = bookHisto1D("top_pt",450,50,500);
      h_top_eta   = bookHisto1D("top_eta",100,-4,4);
      h_top_phi   = bookHisto1D("top_phi",100,0,8);
 
      h_top_PDG_mass  = bookHisto1D("top_PDG_mass",400,100,500);
      h_top_PDG_pt	  = bookHisto1D("top_PDG_pt",450,50,500);
      h_top_PDG_eta   = bookHisto1D("top_PDG_eta",100,-4,4);
      h_top_PDG_phi   = bookHisto1D("top_PDG_phi",50,-4,4);


      h_w_mass    = bookHisto1D("w_mass",200,40,140);
      h_w_pt	  = bookHisto1D("w_pt",200,10,200);
      h_w_eta	  = bookHisto1D("w_eta",100,-4,4);
      h_w_phi     = bookHisto1D("w_phi",100,0,8);

      h_w_PDG_mass    = bookHisto1D("w_PDG_mass",200,40,140);
      h_w_PDG_pt	  = bookHisto1D("w_PDG_pt",200,10,200);
      h_w_PDG_eta	  = bookHisto1D("w_PDG_eta",100,-4,4);
      h_w_PDG_phi     = bookHisto1D("w_PDG_phi",50,-4,4);

      h_z_PDG_mass    = bookHisto1D("z_PDG_mass",200,40,140);
      h_z_PDG_pt	  = bookHisto1D("z_PDG_pt",200,10,200);
      h_z_PDG_eta	  = bookHisto1D("z_PDG_eta",100,-4,4);
      h_z_PDG_phi     = bookHisto1D("z_PDG_phi",50,-4,4);

      h_el_PDG_pt     = bookHisto1D("el_PDG_pt",200,20,200);
      h_el_PDG_eta    = bookHisto1D("el_PDG_eta",100,-4,4);
      h_el_PDG_phi    = bookHisto1D("el_PDG_phi",50,-4,4);

      h_mu_PDG_pt     = bookHisto1D("mu_PDG_pt",200,20,200);
      h_mu_PDG_eta    = bookHisto1D("mu_PDG_eta",100,-4,4);
      h_mu_PDG_phi    = bookHisto1D("mu_PDG_phi",50,-4,4);

    }


    /// Perform the per-event analysis
    void analyze(const Event& event) {
      const double weight = event.weight();

      //DO PDG analysis
      vector<HepMC::GenParticle*> genParticles = particles(event.genEvent());


      vector<HepMC::GenParticle*> ePlus;
      vector<HepMC::GenParticle*> eMinus;
      vector<HepMC::GenParticle*> muPlus;
      vector<HepMC::GenParticle*> muMinus;

      for(size_t i = 0; i < genParticles.size(); ++i)
      {
          GenParticle * part = genParticles.at(i);
          if(fabs(part->pdg_id())==6 )
          {
              MSG_INFO("Status of top : "<<part->status() );
          }
          if(part->status()==3) //Unstable particles

          if(part->status()==1) //Select only stable particles
          {
              if(part->momentum().eta() < 4 and part->momentum().perp() > 20*GeV)
              {

                  if(part->pdg_id()==6 || part->pdg_id()==-6)
                  {
                      h_top_PDG_mass->fill(part->momentum().m()*GeV,weight);
                      h_top_PDG_pt->fill(part->momentum().perp()*GeV,weight);
                      h_top_PDG_eta->fill(part->momentum().eta(),weight);
                      h_top_PDG_phi->fill(part->momentum().phi(),weight);
                  }

                  if(part->pdg_id() == PID::WPLUSBOSON || part->pdg_id() == PID::WMINUSBOSON)
                  {
                      h_w_PDG_mass->fill(part->momentum().m()*GeV,weight);
                      h_w_PDG_pt->fill(part->momentum().perp()*GeV,weight);
                      h_w_PDG_eta->fill(part->momentum().eta(),weight);
                      h_w_PDG_phi->fill(part->momentum().phi(),weight);
                  }
                  if(part->pdg_id() == PID::Z0BOSON)
                  {
                     h_z_PDG_mass->fill(part->momentum().m()*GeV,weight);
                     h_z_PDG_pt->fill(part->momentum().perp()*GeV,weight);
                     h_z_PDG_eta->fill(part->momentum().eta(),weight);
                     h_z_PDG_phi->fill(part->momentum().phi(),weight);
                  }
                  if(part->pdg_id() ==PID::ELECTRON || part->pdg_id() == PID::POSITRON)
                  {
                      h_el_PDG_pt->fill(part->momentum().perp()*GeV,weight);
                      h_el_PDG_eta->fill(part->momentum().eta(),weight);
                      h_el_PDG_phi->fill(part->momentum().phi(),weight);
                  }
                  if(part->pdg_id() ==PID::MUON || part->pdg_id() ==PID::ANTIMUON)
                  {
                      h_mu_PDG_pt->fill(part->momentum().perp()*GeV,weight);
                      h_mu_PDG_eta->fill(part->momentum().eta(),weight);
                      h_mu_PDG_phi->fill(part->momentum().phi(),weight);
                  }

                  if(part->pdg_id() == PID::ELECTRON)
                  {
                      eMinus.push_back(part);
                  }
                  if(part->pdg_id() == PID::POSITRON)
                  {
                      ePlus.push_back(part);
                  }
                  if(part->pdg_id() ==PID::MUON)
                  {
                      muMinus.push_back(part);
                  }
                  if(part->pdg_id() ==PID::ANTIMUON)
                  {
                      muPlus.push_back(part);
                  }
              }
          }
      }
      //Make diElectron and diMuon mass distributions
      h_PDG_nEl->fill(ePlus.size() + eMinus.size(),weight);
      h_PDG_nMu->fill(muPlus.size() + muMinus.size(),weight);


      //End of HEPMC record analysis 
 

      // Use a missing ET cut to bias toward events with a hard neutrino from
      // the leptonically decaying W. This helps to reduce pure QCD backgrounds.
      const MissingMomentum& met = applyProjection<MissingMomentum>(event, "MissingET");
      MSG_DEBUG("Vector ET = " << met.vectorEt().mod() << " GeV");
      if (met.vectorEt().mod() < 30*GeV) {
        MSG_DEBUG("Event failed missing ET cut");
        vetoEvent;
      }

      //veto event if there is no charge leptons in the acceptance
      const ChargedLeptons& lfs = applyProjection<ChargedLeptons>(event, "LFS");
      MSG_DEBUG("Charged lepton multiplicity = " << lfs.chargedLeptons().size());
      foreach (const Particle& lepton, lfs.chargedLeptons()) {
        MSG_DEBUG("Lepton pT = " << lepton.pT());
      }
      if (lfs.chargedLeptons().empty()) {
        MSG_DEBUG("Event failed lepton multiplicity cut");
        vetoEvent;
      }
      h_nChrgLeps->fill(lfs.chargedLeptons().size(),weight);


      
      //veto Event if there is no Z in the acceptance

      const ZFinder& elZfinder = applyProjection<ZFinder>(event, "elZFinder");
      const ZFinder& muZfinder = applyProjection<ZFinder>(event, "muZFinder");
      if (elZfinder.bosons().size() != 1 || muZfinder.bosons().size()!=1) 
          vetoEvent;


      if(ePlus.size() ==1 and eMinus.size()==1)
      {
          h_diEl_PDG_mass->fill( (FourMomentum(ePlus.at(0)->momentum()) + FourMomentum(eMinus.at(0)->momentum())).mass()*GeV,weight);
      }
      if(muMinus.size()==1 and muPlus.size()==1)
      {
          h_diMu_PDG_mass->fill( (FourMomentum(muPlus.at(0)->momentum()) + FourMomentum(muMinus.at(0)->momentum())).mass()*GeV,weight);
      }



      /// Get the various sets of final state particles
      const Particles& elecFS = applyProjection<IdentifiedFinalState>(event, "ELEC_FS").particlesByPt();
      const Particles& muonFS = applyProjection<IdentifiedFinalState>(event, "MUON_FS").particlesByPt();
      const Particles& neutrinoFS = applyProjection<IdentifiedFinalState>(event, "NEUTRINO_FS").particlesByPt();

      // Get all jets with pT > 25 GeV
      const Jets& jets = applyProjection<FastJets>(event, "JETS").jetsByPt(20.0*GeV);

      // Keep any jets that pass the initial rapidity cut
      vector<const Jet*> central_jets;
      foreach(const Jet& j, jets) {
        if (j.absrap() < 2.4) central_jets.push_back(&j);
      }

      // For each of the jets that pass the rapidity cut, only keep those that are not
      // too close to any leptons
      vector<const Jet*> good_jets;
      foreach(const Jet* j, central_jets) {
        bool goodJet = true;

        foreach (const Particle& e, elecFS) {
          double elec_jet_dR = deltaR(e.momentum(), j->momentum());
          if (elec_jet_dR < 0.4) { goodJet = false; break; }
        }
        if (!goodJet) continue;
        if (!goodJet) continue;

        foreach (const Particle& m, muonFS) {
          double muon_jet_dR = deltaR(m.momentum(), j->momentum());
          if (muon_jet_dR < 0.4) { goodJet = false; break; }
        }
        if (!goodJet) continue;

        good_jets.push_back(j);
      }

      // Get b hadrons with pT > 5 GeV
      /// @todo This is a hack -- replace with UnstableFinalState
      vector<HepMC::GenParticle*> B_hadrons;
      vector<HepMC::GenParticle*> allParticles = particles(event.genEvent());
      for (size_t i = 0; i < allParticles.size(); i++) {
        GenParticle* p = allParticles[i];
        if (!PID::isHadron(p->pdg_id()) || !PID::hasBottom(p->pdg_id())) continue;
        if (p->momentum().perp() < 5*GeV) continue;
        B_hadrons.push_back(p);
      }

      // For each of the good jets, check whether any are b-jets (via dR matching)
      vector<const Jet*> b_jets;
      vector<const Jet*> l_jets;
      foreach(const Jet* j, good_jets) {
        bool isbJet = false;
        foreach(HepMC::GenParticle* b, B_hadrons) {
          if (deltaR(j->momentum(), FourMomentum(b->momentum())) < 0.3) isbJet = true;
        }
        if (isbJet)
        {
           b_jets.push_back(j);
        }
        else
        {
            l_jets.push_back(j);
        }
      }

     // Get the MET by taking the vector sum of all neutrinos
     /// @todo Use MissingMomentum instead?
     double MET = 0;
     FourMomentum p_MET;
     foreach (const Particle& p, neutrinoFS) {
       p_MET = p_MET + p.momentum();
     }
     MET = p_MET.pT();

     /*
      * Start doing the Analysis
      */
     double diElectronMass = 0;
     if(elecFS.size() >=2)
     {
         if(charge(elecFS[0]) != charge(elecFS[1]))
         {
             diElectronMass = (elecFS[0].momentum() + elecFS[1].momentum()).mass();
             h_el_pt->fill(elecFS[0].momentum().pT()*GeV,weight);
             h_el_pt->fill(elecFS[1].momentum().pT()*GeV,weight);

             h_el_eta->fill(elecFS[0].momentum().eta(),weight);
             h_el_eta->fill(elecFS[1].momentum().eta(),weight);

             h_el_phi->fill(elecFS[0].momentum().phi(),weight);
             h_el_phi->fill(elecFS[1].momentum().phi(),weight);
         }
     }
     double diMuonMass = 0;
     if(muonFS.size() >=2)
     {
         if(charge(muonFS[0]) !=charge(muonFS[1]))
         {
             diMuonMass = (muonFS[0].momentum() + muonFS[1].momentum()).mass();
             
             h_mu_pt->fill(muonFS[0].momentum().pT()*GeV,weight);
             h_mu_pt->fill(muonFS[1].momentum().pT()*GeV,weight);

             h_mu_eta->fill(muonFS[0].momentum().eta(),weight);
             h_mu_eta->fill(muonFS[1].momentum().eta(),weight);

             h_mu_phi->fill(muonFS[0].momentum().phi(),weight);
             h_mu_phi->fill(muonFS[1].momentum().phi(),weight);
         }
     }

     if(diElectronMass !=0 || diMuonMass !=0)
     {
         h_MET->fill(MET*GeV,weight);
         if(diElectronMass !=0) 
             h_diEl_mass->fill(diElectronMass*GeV,weight);
         if(diMuonMass !=0)
             h_diMu_mass->fill(diMuonMass*GeV,weight); 

         if(good_jets.size() <4)
             vetoEvent;
               
          MSG_DEBUG("Number of b-jets = " << b_jets.size());
          MSG_DEBUG("Number of l-jets = " << l_jets.size());
          
          //Veto the event if there are no sufficient jets
          if (b_jets.size() != 2) {
            MSG_DEBUG("Event failed post-lepton-isolation b-tagging cut");
            vetoEvent;
          }
          if (l_jets.size() < 2) {
            MSG_DEBUG("Event failed since not enough light jets remaining after lepton-isolation");
            vetoEvent;
          }


         //Do b-jet histograms

         h_nbjets->fill(b_jets.size(),weight);
         for(size_t i = 0; i < b_jets.size(); ++i) 
         {
             for(size_t j =i+1 ; j < b_jets.size(); ++j)
             {
                 const Jet* b1 = b_jets[i];
                 const Jet* b2 = b_jets[j];

                 h_b1_b2_dEta->fill(deltaEta(b1->momentum(),b2->momentum()),weight);
                 h_b1_b2_dPhi->fill(deltaPhi(b1->momentum(),b2->momentum()),weight);
                 h_b1_b2_dR->fill(deltaR(b1->momentum(),b2->momentum()),weight);

                 if(elZfinder.bosons().size()!=0)
                 {
                     FourMomentum zmom = elZfinder.bosons()[0].momentum();
                     h_Zboson_b1_dr->fill(deltaR(b1->momentum(),zmom),weight);
                     h_Zboson_b2_dr->fill(deltaR(b2->momentum(),zmom),weight);
                     h_Zboson_pt->fill(zmom.pT()*GeV,weight);
                     h_Zboson_eta->fill(zmom.eta(),weight);
                     h_Zboson_phi->fill(zmom.phi(),weight);
                 }
                 else if(muZfinder.bosons().size()!=0)
                 {
                     FourMomentum zmom = muZfinder.bosons()[0].momentum();
                     h_Zboson_b1_dr->fill(deltaR(b1->momentum(),zmom),weight);
                     h_Zboson_b2_dr->fill(deltaR(b2->momentum(),zmom),weight);
                     h_Zboson_pt->fill(zmom.pT()*GeV,weight);
                     h_Zboson_eta->fill(zmom.eta(),weight);
                     h_Zboson_phi->fill(zmom.phi(),weight);
                 }
             }
         }

         // Construct the hadronically decaying W momentum 4-vector from pairs of
         // non-b-tagged jets. The pair which best matches the W mass is used. We start
         // with an always terrible 4-vector estimate which should always be "beaten" by
         // a real jet pair.
         FourMomentum W(10*sqrtS(), 0, 0, 0);
         for (size_t i = 0; i < l_jets.size()-1; ++i) 
         {
           for (size_t j = i + 1; j < l_jets.size(); ++j) 
           {
             const FourMomentum Wcand = l_jets[i]->momentum() + l_jets[j]->momentum();
             MSG_TRACE(i << "," << j << ": candidate W mass = " << Wcand.mass()/GeV
                       << " GeV, vs. incumbent candidate with " << W.mass()/GeV << " GeV");
             if (fabs(Wcand.mass() - 80.4*GeV) < fabs(W.mass() - 80.4*GeV))
             {
               W = Wcand;
             }
           }
         }
         MSG_DEBUG("Candidate W mass = " << W.mass() << " GeV");

         // There are two b-jets with which this can be combined to make the
         // hadronically decaying top, one of which is correct and the other is
         // not... but we have no way to identify which is which, so we construct
         // both possible top momenta and fill the histograms with both.
         const FourMomentum t1 = W + b_jets[0]->momentum();
         const FourMomentum t2 = W + b_jets[1]->momentum();

         h_w_mass->fill(W.mass(),weight);
         h_w_pt->fill(W.pT()*GeV,weight);
         h_w_eta->fill(W.eta(),weight);
         h_w_phi->fill(W.phi(),weight);

         h_top_mass->fill(t1.mass()*GeV,weight);
         h_top_mass->fill(t2.mass()*GeV,weight);

         h_top_pt->fill(t1.pT()*GeV,weight);
         h_top_pt->fill(t2.pT()*GeV,weight);
         
         h_top_eta->fill(t1.eta(),weight);
         h_top_eta->fill(t2.eta(),weight);

         h_top_phi->fill(t1.phi(),weight);
         h_top_phi->fill(t2.phi(),weight);


          /*vector<const Jet*> w1;
        

          h_top_mass->fill(pjjj1.mass()*GeV,weight);
          h_top_mass->fill(pjjj2.mass()*GeV,weight);
          h_top_pt->fill(pjjj1.pT()*GeV,weight);
          h_top_pt->fill(pjjj2.pT()*GeV,weight);
          h_top_eta->fill(pjjj1.eta(),weight);
          h_top_eta->fill(pjjj2.eta(),weight);
          h_top_phi->fill(pjjj1.phi(),weight);
          h_top_phi->fill(pjjj2.phi(),weight);

          h_t1_t2_dR->fill(deltaR(pjjj1,pjjj2),weight);
          h_t1_t2_dEta->fill(deltaEta(pjjj1,pjjj2),weight);
          h_t1_t2_dPhi->fill(deltaPhi(pjjj1,pjjj2),weight);*/
       }
     }
     
    /// Normalise histograms etc., after the run
    void finalize() 
    {
        float norm  = crossSection()/sumOfWeights();
        scale(h_nChrgLeps,norm);
        scale(h_PDG_nEl,norm);
        scale(h_PDG_nMu,norm);
        scale(h_njets,norm);
        scale(h_nljets,norm);
        scale(h_nljets,norm);

        //kinematic variables
        scale( h_b1_pt,norm);
        scale( h_b2_pt,norm);
        scale( h_l1_pt,norm);
        scale( h_l2_pt,norm);

        scale( h_MET,norm);

        scale( h_el_pt,norm);
        scale( h_el_eta,norm);
        scale( h_el_phi,norm);
        scale( h_diEl_mass,norm); 
        scale( h_diEl_PDG_mass,norm);

        scale( h_mu_pt,norm);
        scale( h_mu_eta,norm);
        scale( h_mu_phi,norm);
        scale( h_diMu_mass,norm);
        scale( h_diMu_PDG_mass,norm);

        scale( h_Zboson_pt,norm);
        scale( h_Zboson_eta,norm);
        scale( h_Zboson_phi,norm);
        scale( h_Zboson_b1_dr,norm);
        scale( h_Zboson_b2_dr,norm);


        scale( h_b1_b2_dEta,norm);
        scale( h_b1_b2_dPhi,norm);
        scale( h_b1_b2_dR,norm);

        scale( h_top_mass,norm);
        scale( h_top_pt,norm);
        scale( h_top_eta,norm);
        scale( h_top_phi,norm);

        scale( h_top_PDG_mass,norm);
        scale( h_top_PDG_pt,norm);
        scale( h_top_PDG_eta,norm);
        scale( h_top_PDG_phi,norm);


        scale( h_t1_t2_dEta,norm);
        scale( h_t1_t2_dPhi,norm);
        scale( h_t1_t2_dR,norm);


        scale( h_w_mass,norm);
        scale( h_w_pt,norm);
        scale( h_w_eta,norm);
        scale( h_w_phi,norm);

        scale( h_w_PDG_mass,norm);
        scale( h_w_PDG_pt,norm);
        scale( h_w_PDG_eta,norm);
        scale( h_w_PDG_phi,norm);

        scale( h_z_PDG_mass,norm);
        scale( h_z_PDG_pt,norm);
        scale( h_z_PDG_eta,norm);
        scale( h_z_PDG_phi,norm);

        scale( h_el_PDG_pt,norm);
        scale( h_el_PDG_eta,norm);
        scale( h_el_PDG_phi,norm);

        scale( h_mu_PDG_pt,norm);
        scale( h_mu_PDG_eta,norm);
        scale( h_mu_PDG_phi,norm);
    }
    //@}


  private:

    // Data members like post-cuts event weight counters go here


    /// @name Histograms
    //@{
    Profile1DPtr _h_XXXX;
    Histo1DPtr _h_YYYY;
    
    //Counters
    Histo1DPtr h_njets;
    Histo1DPtr h_nChrgLeps;
    Histo1DPtr h_PDG_nEl;
    Histo1DPtr h_PDG_nMu;
    Histo1DPtr h_nbjets;
    Histo1DPtr h_nljets;

   //kinematic variables
   Histo1DPtr h_b1_pt;
   Histo1DPtr h_b2_pt;
   Histo1DPtr h_l1_pt;
   Histo1DPtr h_l2_pt;

   Histo1DPtr h_MET;

   Histo1DPtr h_el_pt;
   Histo1DPtr h_el_eta;
   Histo1DPtr h_el_phi;
   Histo1DPtr h_diEl_mass; 
   Histo1DPtr h_diEl_PDG_mass;

   Histo1DPtr h_mu_pt;
   Histo1DPtr h_mu_eta;
   Histo1DPtr h_mu_phi;
   Histo1DPtr h_diMu_mass;
   Histo1DPtr h_diMu_PDG_mass;

   Histo1DPtr h_Zboson_pt;
   Histo1DPtr h_Zboson_eta;
   Histo1DPtr h_Zboson_phi;
   Histo1DPtr h_Zboson_b1_dr;
   Histo1DPtr h_Zboson_b2_dr;

   Histo1DPtr h_b1_b2_dEta;
   Histo1DPtr h_b1_b2_dPhi;
   Histo1DPtr h_b1_b2_dR;

   Histo1DPtr h_top_mass;
   Histo1DPtr h_top_pt;
   Histo1DPtr h_top_eta;
   Histo1DPtr h_top_phi;

   Histo1DPtr h_top_PDG_mass;
   Histo1DPtr h_top_PDG_pt;
   Histo1DPtr h_top_PDG_eta;
   Histo1DPtr h_top_PDG_phi;


   Histo1DPtr h_t1_t2_dEta;
   Histo1DPtr h_t1_t2_dPhi;
   Histo1DPtr h_t1_t2_dR;


   Histo1DPtr h_w_mass;
   Histo1DPtr h_w_pt;
   Histo1DPtr h_w_eta;
   Histo1DPtr h_w_phi;

   Histo1DPtr h_w_PDG_mass;
   Histo1DPtr h_w_PDG_pt;
   Histo1DPtr h_w_PDG_eta;
   Histo1DPtr h_w_PDG_phi;

   Histo1DPtr h_z_PDG_mass;
   Histo1DPtr h_z_PDG_pt;
   Histo1DPtr h_z_PDG_eta;
   Histo1DPtr h_z_PDG_phi;

   Histo1DPtr h_el_PDG_pt;
   Histo1DPtr h_el_PDG_eta;
   Histo1DPtr h_el_PDG_phi;

   Histo1DPtr h_mu_PDG_pt;
   Histo1DPtr h_mu_PDG_eta;
   Histo1DPtr h_mu_PDG_phi;

   //@}


  };



  // The hook for the plugin system
  DECLARE_RIVET_PLUGIN(hepmc_analysis);

}
