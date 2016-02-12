#include "Rivet/Analysis.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/TauFinder.hh"
#include "Rivet/Projections/HeavyHadrons.hh"
#include "Rivet/Projections/VetoedFinalState.hh"
#include "Rivet/Projections/ChargedLeptons.hh"
#include "Rivet/Projections/PromptFinalState.hh"
#include "Rivet/Projections/ChargedFinalState.hh"
#include "Rivet/Projections/MissingMomentum.hh"
#include "Rivet/Projections/IdentifiedFinalState.hh"
#include "Rivet/Projections/UnstableFinalState.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Projections/ZFinder.hh"
#include "Rivet/Projections/WFinder.hh"
#include "Rivet/AnalysisLoader.hh"

#include <numeric>
#include <functional>
#include <vector>
#include "TTree.h"
#include "TFile.h"

namespace Rivet {

  
  class sherpa_ttZ_valid: public Analysis {
  public:

    /// Minimal constructor
    sherpa_ttZ_valid() : Analysis("sherpa_ttZ_valid")
    {
    }


    /// @name Analysis methods
    //@{

    /// Set up projections and book histograms
    void init() {
      // A FinalState is used to select particles within |eta| < 5 and with pT
      // > 30 GeV, out of which the ChargedLeptons projection picks only the
      // electrons and muons, to be accessed later as "LFS".
      ChargedLeptons lfs(ChargedFinalState(-5,5,0*GeV));
      addProjection(lfs,"LFS");

      FinalState lepfs;
      //Projection to find prompt electrons
      IdentifiedFinalState el_id(lepfs);
      el_id.acceptIdPair(PID::ELECTRON);
      PromptFinalState electrons(el_id);
      electrons.acceptTauDecays(false);
      addProjection(electrons,"electrons");

      //Projection to find prompt muons
      IdentifiedFinalState mu_id(lepfs);
      mu_id.acceptIdPair(PID::MUON);
      PromptFinalState muons(mu_id);
      muons.acceptTauDecays(false);
      addProjection(muons,"muons");

        
      FinalState zfs;
      Cut zeefscut = (Cuts::abseta <5 )& (Cuts::pT>10*GeV);
      //ZFinder zeeFinder(zfs,zeefscut,PID::ELECTRON,5.0*GeV,115.0*GeV,0.2,ZFinder::CLUSTERNODECAY,ZFinder::NOTRACK);
      ZFinder zeeFinder(zfs,zeefscut,PID::ELECTRON,5.0*GeV,115.0*GeV,0.1,ZFinder::CLUSTERALL,ZFinder::TRACK);
      addProjection(zeeFinder,"zeeFinder");

      //ZFinder zmumuFinder(zfs,zeefscut,PID::MUON,5.0*GeV,115.0*GeV,0.2,ZFinder::NOCLUSTER,ZFinder::NOTRACK);
      ZFinder zmumuFinder(zfs,zeefscut,PID::MUON,5.0*GeV,115.0*GeV,0.1,ZFinder::CLUSTERALL,ZFinder::TRACK);
      addProjection(zmumuFinder,"zmumuFinder");

      WFinder welFinder(zfs,zeefscut,PID::ELECTRON,5.0*GeV,115.0*GeV,25.0*GeV,0.1);//WFinder::CLUSTERNODECAY,WFinder::NOTRACK,WFinder::TRANSMASS);
      addProjection(welFinder,"welFinder");

      WFinder wmuFinder(zfs,zeefscut,PID::MUON,5.0*GeV,115.0*GeV,25.0*GeV,0.1);//,WFinder::CLUSTERNODECAY,WFinder::NOTRACK,WFinder::TRANSMASS);
      addProjection(wmuFinder,"wmuFinder");

      TauFinder tauhadronic(TauFinder::HADRONIC);
      addProjection(tauhadronic,"TauHadronic");


      addProjection(HeavyHadrons(Cuts::abseta < 5 && Cuts::pT > 5*GeV), "BCHadrons");


      // A second FinalState is used to select all particles in |eta| < 5,
      // with no pT cut. This is used to construct jets and measure missing
      // transverse energy.
      VetoedFinalState fs;
      fs.addVetoPairId(PID::MUON);
      fs.addVetoPairId(PID::ELECTRON);
      fs.addVetoPairId(PID::TAU);
      addProjection(FastJets(fs, FastJets::ANTIKT, 0.4), "Jets");
      addProjection(MissingMomentum(fs), "MissingET");
      
      VetoedFinalState vfs(FinalState(-5,5,0*GeV));
      vfs.addVetoOnThisFinalState(lfs);
      addProjection(vfs, "VFS");


      ////Define ttreee vectors
      
      evnt_weight = 0;
      jet_pt    = new std::vector<float> ();
      jet_eta   = new std::vector<float> ();
      jet_phi   = new std::vector<float> ();
      jet_e     = new std::vector<float> ();
      jet_label = new std::vector<float> ();

      el_pt     = new std::vector<float> ();
      el_eta    = new std::vector<float> ();
      el_phi    = new std::vector<float> ();
      el_e      = new std::vector<float> ();
      el_charge = new std::vector<float> ();

      mu_pt     = new std::vector<float> ();
      mu_eta    = new std::vector<float> ();
      mu_phi    = new std::vector<float> ();
      mu_e      = new std::vector<float> ();
      mu_charge = new std::vector<float> ();

      tau_pt    = new std::vector<float> ();
      tau_eta   = new std::vector<float> ();
      tau_phi   = new std::vector<float> ();
      tau_e     = new std::vector<float> ();
      tau_charge= new std::vector<float> ();




    
      outFile        = new TFile("analysis.root","RECREATE");
      _tree          = new TTree("sherpa_valid","sherpa_valid");
      _tree->OptimizeBaskets();
      _tree->SetAutoFlush(10000);
      
      _tree->Branch("evnt_weight",&evnt_weight,"evnt_weight/F"); 
      
      _tree->Branch("jet_pt","std::vector<float>",&jet_pt);
      _tree->Branch("jet_eta","std::vector<float>",&jet_eta);
      _tree->Branch("jet_phi","std::vector<float>",&jet_phi);
      _tree->Branch("jet_e","std::vector<float>",&jet_e);
      _tree->Branch("jet_label","std::vector<float>",&jet_label);

      _tree->Branch("el_pt","std::vector<float>",&el_pt);
      _tree->Branch("el_eta","std::vector<float>",&el_eta);
      _tree->Branch("el_phi","std::vector<float>",&el_phi);
      _tree->Branch("el_e","std::vector<float>",&el_e);
      _tree->Branch("el_charge","std::vector<float>",&el_charge);

      _tree->Branch("mu_pt","std::vector<float>",&mu_pt);
      _tree->Branch("mu_eta","std::vector<float>",&mu_eta);
      _tree->Branch("mu_phi","std::vector<float>",&mu_phi);
      _tree->Branch("mu_e","std::vector<float>",&mu_e);
      _tree->Branch("mu_charge","std::vector<float>",&mu_charge);

      _tree->Branch("tau_pt","std::vector<float>",&tau_pt);
      _tree->Branch("tau_eta","std::vector<float>",&tau_eta);
      _tree->Branch("tau_phi","std::vector<float>",&tau_phi);
      _tree->Branch("tau_e","std::vector<float>",&tau_e);
      _tree->Branch("tau_charge","std::vector<float>",&tau_charge);



    }


    void analyze(const Event& event) {
      const double weight = event.weight();

      evnt_weight   = weight;
    
      jet_pt->clear();
      jet_eta->clear();
      jet_phi->clear();
      jet_e->clear();
      jet_label->clear();

      el_pt->clear();
      el_eta->clear();
      el_phi->clear();
      el_e->clear();
      el_charge->clear();

      mu_pt->clear();
      mu_eta->clear();
      mu_phi->clear();
      mu_e->clear();
      mu_charge->clear();

      tau_pt->clear();
      tau_eta->clear();
      tau_phi->clear();
      tau_e->clear();
      tau_charge->clear();



      // Use the "LFS" projection to require at least one hard charged
      // lepton. This is an experimental signature for the leptonically decaying
      // W. This helps to reduce pure QCD backgrounds.
      
      const ChargedLeptons& lfs     = applyProjection<ChargedLeptons>(event, "LFS");
      
      Particles elVec,muVec,tauVec;
      foreach (const Particle & el, applyProjection<PromptFinalState>(event,"electrons").particlesByPt())
      {
          if(el.pT()/GeV > 10 && fabs(el.eta()) <2.5)
          {
              elVec.push_back(el);
          }
      }
      foreach (const Particle &mu, applyProjection<PromptFinalState>(event,"muons").particlesByPt())
      {
          if(mu.pT()/GeV >10 && fabs(mu.eta()) <2.5)
          {
              muVec.push_back(mu);
          }
      }
      const TauFinder &tauhad = applyProjection<TauFinder>(event,"TauHadronic");
      foreach (const Particle &tau, tauhad.taus())
      {
          if(tau.pT()/GeV >25 && fabs(tau.eta()) < 2.5)
          {
            int nProng = 0;
            foreach (Particle p , tau.children())
            {
              if (p.threeCharge()!=0) nProng++;
            }
            if(nProng ==2 || nProng ==3)
            {
              tauVec.push_back(tau);
            }
          }
      }

      Jets alljets;
      foreach (const Jet &jet , applyProjection<FastJets>(event, "Jets").jetsByPt(25*GeV))
      {
          if(fabs(jet.eta()) <2.5 && jet.pT()/GeV >25 )
          {
              alljets.push_back(jet);
          }
      }
    
      alljets    =   sortByPt(alljets);
      elVec = sortByPt(elVec);
      muVec = sortByPt(muVec);
      tauVec= sortByPt(tauVec);
      
      if((elVec.size() + muVec.size()) ==3) //Select 3 prompt leptons
      {
         foreach (const Particle &el, elVec)
         {
             el_pt->push_back(el.pT()/GeV);
             el_eta->push_back(el.eta());
             el_phi->push_back(el.phi());
             el_e->push_back(el.E()/GeV);
             el_charge->push_back(el.charge());
         }

         foreach (const Particle & mu, muVec)
         {
             mu_pt->push_back(mu.pT()/GeV);
             mu_eta->push_back(mu.eta());
             mu_phi->push_back(mu.phi());
             mu_e->push_back(mu.E()/GeV);
             mu_charge->push_back(mu.charge());
         }

         foreach (const Particle &tau, tauVec)
         {
             tau_pt->push_back(tau.pT()/GeV);
             tau_eta->push_back(tau.eta());
             tau_phi->push_back(tau.phi());
             tau_e->push_back(tau.E()/GeV);
             tau_charge->push_back(tau.charge());
         }

         foreach(const Jet &jet, alljets)
         {
             jet_pt->push_back(jet.pT()/GeV);
             jet_eta->push_back(jet.eta());
             jet_phi->push_back(jet.phi());
             jet_e->push_back(jet.E()/GeV);
             jet_label->push_back( (jet.bTagged()) ? 4 : 1 );
         }
      }
      _tree->Fill();
  }


    void finalize() {
        MSG_INFO("CROSS SSECTION:"<<crossSection());
        MSG_INFO("Writing File");
        //double norm = crossSection()/sumOfWeights();
        _tree->Write();
        outFile->Close();
    }

    //@}


  private:

    // @name Histogram data members
    //@{
    
    TFile * outFile;
    TTree* _tree;
    
    float evnt_weight; 
    
    std::vector<float>* jet_pt;
    std::vector<float>* jet_eta;
    std::vector<float>* jet_phi;
    std::vector<float>* jet_e;
    std::vector<float>* jet_label; // 4 for b-jet otherwise 1;

    std::vector<float>* el_pt;
    std::vector<float>* el_eta;
    std::vector<float>* el_phi;
    std::vector<float>* el_e;
    std::vector<float>* el_charge;

    std::vector<float>* mu_pt;
    std::vector<float>* mu_eta;
    std::vector<float>* mu_phi;
    std::vector<float>* mu_e;
    std::vector<float>* mu_charge;

    std::vector<float>* tau_pt;
    std::vector<float>* tau_eta;
    std::vector<float>* tau_phi;
    std::vector<float>* tau_e;
    std::vector<float>*   tau_charge;

    //
    //@}

  };



  // The hook for the plugin system
  DECLARE_RIVET_PLUGIN(sherpa_ttZ_valid);

}
