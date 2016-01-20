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

namespace Rivet {

  
  class ttll_study: public Analysis {
  public:

    /// Minimal constructor
    ttll_study() : Analysis("ttll_study")
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
      electrons.acceptTauDecays(true);
      addProjection(electrons,"electrons");

      //Projection to find prompt muons
      IdentifiedFinalState mu_id(lepfs);
      mu_id.acceptIdPair(PID::MUON);
      PromptFinalState muons(mu_id);
      muons.acceptTauDecays(true);
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

      //Histogramming 
      _h_2lee4j_nBjets     = bookHisto1D("2lee4j_nBjets",10,-0.5,9.5);
      _h_2lee4j_nLjets     = bookHisto1D("2lee4j_nLjets",10,-0.5,9.5);
      _h_2lee4j_nJets      = bookHisto1D("2lee4j_nJets",15,-0.5,14.5);
      _h_2lee4j_jet_1_pT   = bookHisto1D("2lee4j_jet_1_pT",400,0,1000);
      _h_2lee4j_jet_1_eta  = bookHisto1D("2lee4j_jet_1_eta",40,-4,4);
      _h_2lee4j_jet_2_pT   = bookHisto1D("2lee4j_jet_2_pT",400,0,1000);

      _h_2lee4j_nLep       = bookHisto1D("2lee4j_nLep",5,-0.5,4.5);
      _h_2lee4j_nEl        = bookHisto1D("2lee4j_nEl",5,-0.5,4.5);
      _h_2lee4j_nMu        = bookHisto1D("2lee4j_nMu",5,-0.5,4.5);
      
      _h_2lee4j_el_pT      = bookHisto1D("2lee4j_elPt",200,0,400);
      _h_2lee4j_el_eta     = bookHisto1D("2lee4j_elEta",40,-4,4);

      _h_2lmumu4j_nBjets     = bookHisto1D("2lmumu4j_nBjets",10,-0.5,9.5);
      _h_2lmumu4j_nLjets     = bookHisto1D("2lmumu4j_nLjets",10,-0.5,9.5);
      _h_2lmumu4j_nJets      = bookHisto1D("2lmumu4j_nJets",15,-0.5,14.5);
      _h_2lmumu4j_jet_1_pT   = bookHisto1D("2lmumu4j_jet_1_pT",400,0,1000);
      _h_2lmumu4j_jet_1_eta  = bookHisto1D("2lmumu4j_jet_1_eta",40,-4,4);
      _h_2lmumu4j_jet_2_pT   = bookHisto1D("2lmumu4j_jet_2_pT",400,0,1000);

      _h_2lmumu4j_nLep       = bookHisto1D("2lmumu4j_nLep",5,-0.5,4.5);
      _h_2lmumu4j_nEl        = bookHisto1D("2lmumu4j_nEl",5,-0.5,4.5);
      _h_2lmumu4j_nMu        = bookHisto1D("2lmumu4j_nMu",5,-0.5,4.5);
      
      _h_2lmumu4j_mu_pT      = bookHisto1D("2lmumu4j_muPt",200,0,400);
      _h_2lmumu4j_mu_eta     = bookHisto1D("2lmumu4j_muEta",40,-4,4);

      _h_2lemu4j_nBjets     = bookHisto1D("2lemu4j_nBjets",10,-0.5,9.5);
      _h_2lemu4j_nLjets     = bookHisto1D("2lemu4j_nLjets",10,-0.5,9.5);
      _h_2lemu4j_nJets      = bookHisto1D("2lemu4j_nJets",15,-0.5,14.5);
      _h_2lemu4j_jet_1_pT   = bookHisto1D("2lemu4j_jet_1_pT",400,0,1000);
      _h_2lemu4j_jet_1_eta  = bookHisto1D("2lemu4j_jet_1_eta",40,-4,4);
      _h_2lemu4j_jet_2_pT   = bookHisto1D("2lemu4j_jet_2_pT",400,0,1000);

      _h_2lemu4j_nLep       = bookHisto1D("2lemu4j_nLep",5,-0.5,4.5);
      _h_2lemu4j_nEl        = bookHisto1D("2lemu4j_nEl",5,-0.5,4.5);
      _h_2lemu4j_nMu        = bookHisto1D("2lemu4j_nMu",5,-0.5,4.5);
      
      _h_2lemu4j_el_pT      = bookHisto1D("2lemu4j_elPt",200,0,400);
      _h_2lemu4j_el_eta     = bookHisto1D("2lemu4j_elEta",40,-4,4);
      _h_2lemu4j_mu_pT      = bookHisto1D("2lemu4j_muPt",200,0,400);
      _h_2lemu4j_mu_eta     = bookHisto1D("2lemu4j_muEta",40,-4,4);

      _h_2lee5j_nBjets     = bookHisto1D("2lee5j_nBjets",10,-0.5,9.5);
      _h_2lee5j_nLjets     = bookHisto1D("2lee5j_nLjets",10,-0.5,9.5);
      _h_2lee5j_nJets      = bookHisto1D("2lee5j_nJets",15,-0.5,14.5);
      _h_2lee5j_jet_1_pT   = bookHisto1D("2lee5j_jet_1_pT",400,0,1000);
      _h_2lee5j_jet_1_eta  = bookHisto1D("2lee5j_jet_1_eta",40,-4,4);
      _h_2lee5j_jet_2_pT   = bookHisto1D("2lee5j_jet_2_pT",400,0,1000);

      _h_2lee5j_nLep       = bookHisto1D("2lee5j_nLep",5,-0.5,4.5);
      _h_2lee5j_nEl        = bookHisto1D("2lee5j_nEl",5,-0.5,4.5);
      _h_2lee5j_nMu        = bookHisto1D("2lee5j_nMu",5,-0.5,4.5);
      
      _h_2lee5j_el_pT      = bookHisto1D("2lee5j_elPt",200,0,400);
      _h_2lee5j_el_eta     = bookHisto1D("2lee5j_elEta",40,-4,4);

      _h_2lmumu5j_nBjets     = bookHisto1D("2lmumu5j_nBjets",10,-0.5,9.5);
      _h_2lmumu5j_nLjets     = bookHisto1D("2lmumu5j_nLjets",10,-0.5,9.5);
      _h_2lmumu5j_nJets      = bookHisto1D("2lmumu5j_nJets",15,-0.5,14.5);
      _h_2lmumu5j_jet_1_pT   = bookHisto1D("2lmumu5j_jet_1_pT",400,0,1000);
      _h_2lmumu5j_jet_1_eta  = bookHisto1D("2lmumu5j_jet_1_eta",40,-4,4);
      _h_2lmumu5j_jet_2_pT   = bookHisto1D("2lmumu5j_jet_2_pT",400,0,1000);

      _h_2lmumu5j_nLep       = bookHisto1D("2lmumu5j_nLep",5,-0.5,4.5);
      _h_2lmumu5j_nEl        = bookHisto1D("2lmumu5j_nEl",5,-0.5,4.5);
      _h_2lmumu5j_nMu        = bookHisto1D("2lmumu5j_nMu",5,-0.5,4.5);
      
      _h_2lmumu5j_mu_pT      = bookHisto1D("2lmumu5j_muPt",200,0,400);
      _h_2lmumu5j_mu_eta     = bookHisto1D("2lmumu5j_muEta",40,-4,4);

      _h_2lemu5j_nBjets     = bookHisto1D("2lemu5j_nBjets",10,-0.5,9.5);
      _h_2lemu5j_nLjets     = bookHisto1D("2lemu5j_nLjets",10,-0.5,9.5);
      _h_2lemu5j_nJets      = bookHisto1D("2lemu5j_nJets",15,-0.5,14.5);
      _h_2lemu5j_jet_1_pT   = bookHisto1D("2lemu5j_jet_1_pT",400,0,1000);
      _h_2lemu5j_jet_1_eta  = bookHisto1D("2lemu5j_jet_1_eta",40,-4,4);
      _h_2lemu5j_jet_2_pT   = bookHisto1D("2lemu5j_jet_2_pT",400,0,1000);

      _h_2lemu5j_nLep       = bookHisto1D("2lemu5j_nLep",5,-0.5,4.5);
      _h_2lemu5j_nEl        = bookHisto1D("2lemu5j_nEl",5,-0.5,4.5);
      _h_2lemu5j_nMu        = bookHisto1D("2lemu5j_nMu",5,-0.5,4.5);
      
      _h_2lemu5j_el_pT      = bookHisto1D("2lemu5j_elPt",200,0,400);
      _h_2lemu5j_el_eta     = bookHisto1D("2lemu5j_elEta",40,-4,4);
      _h_2lemu5j_mu_pT      = bookHisto1D("2lemu5j_muPt",200,0,400);
      _h_2lemu5j_mu_eta     = bookHisto1D("2lemu5j_muEta",40,-4,4);

      _h_3l_nBjets     = bookHisto1D("3l_nBjets",10,-0.5,9.5);
      _h_3l_nLjets     = bookHisto1D("3l_nLjets",10,-0.5,9.5);
      _h_3l_nJets      = bookHisto1D("3l_nJets",15,-0.5,14.5);
      _h_3l_jet_1_pT   = bookHisto1D("3l_jet_1_pT",400,0,1000);
      _h_3l_jet_1_eta  = bookHisto1D("3l_jet_1_eta",40,-4,4);
      _h_3l_jet_2_pT   = bookHisto1D("3l_jet_2_pT",400,0,1000);

      _h_3l_nLep       = bookHisto1D("3l_nLep",5,-0.5,4.5);
      _h_3l_nEl        = bookHisto1D("3l_nEl",5,-0.5,4.5);
      _h_3l_nMu        = bookHisto1D("3l_nMu",5,-0.5,4.5);
      
      _h_3l_el_pT      = bookHisto1D("3l_elPt",200,0,400);
      _h_3l_el_eta     = bookHisto1D("3l_elEta",40,-4,4);
      _h_3l_mu_pT      = bookHisto1D("3l_muPt",200,0,400);
      _h_3l_mu_eta     = bookHisto1D("3l_muEta",40,-4,4);
      _h_3l_tau_pT     = bookHisto1D("3l_tauPt",200,0,400);
      _h_3l_tau_eta    = bookHisto1D("3l_tauEta",40,-4,4);

      _h_2l_1tau_nBjets     = bookHisto1D("2l_1tau_nBjets",10,-0.5,9.5);
      _h_2l_1tau_nLjets     = bookHisto1D("2l_1tau_nLjets",10,-0.5,9.5);
      _h_2l_1tau_nJets      = bookHisto1D("2l_1tau_nJets",15,-0.5,14.5);
      _h_2l_1tau_jet_1_pT   = bookHisto1D("2l_1tau_jet_1_pT",400,0,1000);
      _h_2l_1tau_jet_1_eta  = bookHisto1D("2l_1tau_jet_1_eta",40,-4,4);
      _h_2l_1tau_jet_2_pT   = bookHisto1D("2l_1tau_jet_2_pT",400,0,1000);

      _h_2l_1tau_nLep       = bookHisto1D("2l_1tau_nLep",5,-0.5,4.5);
      _h_2l_1tau_nEl        = bookHisto1D("2l_1tau_nEl",5,-0.5,4.5);
      _h_2l_1tau_nMu        = bookHisto1D("2l_1tau_nMu",5,-0.5,4.5);
      
      _h_2l_1tau_el_pT      = bookHisto1D("2l_1tau_elPt",200,0,400);
      _h_2l_1tau_el_eta     = bookHisto1D("2l_1tau_elEta",40,-4,4);
      _h_2l_1tau_mu_pT      = bookHisto1D("2l_1tau_muPt",200,0,400);
      _h_2l_1tau_mu_eta     = bookHisto1D("2l_1tau_muEta",40,-4,4);
      _h_2l_1tau_tau_pT     = bookHisto1D("2l_1tau_tauPt",200,0,400);
      _h_2l_1tau_tau_eta    = bookHisto1D("2l_1tau_tauEta",40,-4,4);


      _sumofweight =1;
      nEvents = 0;
      _sumWeight_2lee4j=1;
      _sumWeight_2lmumu5j=1;
      _sumWeight_2lemu4j=1;
      _sumWeight_2lee5j=1;
      _sumWeight_2lmumu5j=1;
      _sumWeight_2lemu5j=1;
      _sumWeight_2l1tau=1;


    }


    void analyze(const Event& event) {
      const double weight = event.weight();

      // Use the "LFS" projection to require at least one hard charged
      // lepton. This is an experimental signature for the leptonically decaying
      // W. This helps to reduce pure QCD backgrounds.
      
      const ChargedLeptons& lfs     = applyProjection<ChargedLeptons>(event, "LFS");
      const ZFinder & zeeFinder     = applyProjection<ZFinder>(event,"zeeFinder");
      const ZFinder & zmumuFinder   = applyProjection<ZFinder>(event,"zmumuFinder");
      const WFinder & welFinder     = applyProjection<WFinder>(event,"welFinder");
      const WFinder & wmuFinder     = applyProjection<WFinder>(event,"wmuFinder");

      const MissingMomentum& met = applyProjection<MissingMomentum>(event, "MissingET");

      /*if(zeeFinder.bosons().size()==0 && zmumuFinder.bosons().size()==0)
      {
          MSG_INFO("ZeeFinder size: "<<zeeFinder.size());
          MSG_INFO("ZmumuFinder size: "<<zmumuFinder.size());
          MSG_INFO("Veto Event");
          vetoEvent;
      }*/

      Particles elVec,muVec,tauVec;
      //Count the total number of leptons
      //
      //

      foreach (const Particle & el, applyProjection<PromptFinalState>(event,"electrons").particlesByPt())
      {
          if(el.pT()/GeV > 10 && el.abseta() <2.5)
          {
              elVec.push_back(el);
          }
      }
      foreach (const Particle &mu, applyProjection<PromptFinalState>(event,"muons").particlesByPt())
      {
          if(mu.pT()/GeV >10 && mu.abseta() <2.5)
          {
              muVec.push_back(mu);
          }
      }
      
      /*foreach (const Particle& lepton, lfs.chargedLeptons()) 
      {
          if(lepton.pT() > 10*GeV &&lepton.abseta() < 2.5)// && !lepton.fromBottom()) //!lepton.fromDecay()) //Make sure the lepton is not from tau or hadron decays
          {
              if(lepton.abspid()== PID::ELECTRON)
              {
                  elVec.push_back(lepton);
              }
              else if (lepton.abspid() == PID::MUON)
              {
                  muVec.push_back(lepton);
              }
          }
      }*/
      const TauFinder &tauhad = applyProjection<TauFinder>(event,"TauHadronic");
      foreach (const Particle &tau, tauhad.taus())
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

      elVec = sortByPt(elVec);
      muVec = sortByPt(muVec);
      tauVec= sortByPt(tauVec);

      int nLep = elVec.size() + muVec.size() + tauVec.size();
      int elqsum=0;
      int muqsum=0;
      int emuqsum=0;

      foreach(const Particle& el, elVec)
      {
          elqsum += el.charge();
      }
      foreach(const Particle &mu, muVec)
      {
          muqsum += mu.charge();
      }

      Jets jets;
      foreach (const Jet &jet , applyProjection<FastJets>(event, "Jets").jetsByPt(25*GeV))
      {
          if(fabs(jet.eta()) <2.5)
              jets.push_back(jet);
      }
      double ht = 0.0;
      foreach (const Jet& j, jets) { ht += j.pT(); }
 
      const Particles bhadrons = sortByPt(applyProjection<HeavyHadrons>(event, "BCHadrons").bHadrons());
    
      Jets bjets, ljets, alljets;
      foreach (const Jet& jet, jets) 
      {
          alljets.push_back(jet);
          /*foreach (const Particle& b, bhadrons) 
          {
              if (deltaR(jet,b) < 0.3)
              {
                  bjets.push_back(jet);
              }
              else 
              {
                  ljets.push_back(jet);
              }
          }*/
          if(jet.bTagged())
          {
              bjets.push_back(jet);
          }
          else
          {
              ljets.push_back(jet);
          }
     }
     alljets    =   sortByPt(alljets);
     bjets      =   sortByPt(bjets);
     ljets      =   sortByPt(ljets);

     
     //2l0tau
     if(tauVec.size()==0 && bjets.size() >=1)
     {
         if(alljets.size()==4)
         {
             MSG_INFO(elVec.size()<<" , " <<muVec.size());
             //2lee4j
            //if(abs(elqsum) ==2 && elVec.size()==2 )// && elVec[0].pT()/GeV > 25 && elVec[1].pT()/GeV>20)
            if(elVec.size()>=2 && elVec[0].pT()/GeV >25 && elVec[1].pT()/GeV > 20 && abs(elqsum)==2)
            {
                _sumWeight_2lee4j += event.weight();
                MSG_INFO("Filling 2lee4j Histograms");

                _h_2lee4j_nBjets->fill(bjets.size(),weight);
                _h_2lee4j_nLjets->fill(ljets.size(),weight);
                _h_2lee4j_nJets->fill(alljets.size(),weight);
                
                _h_2lee4j_jet_1_pT->fill(alljets[0].pT()/GeV,weight); 
                _h_2lee4j_jet_1_eta->fill(alljets[0].eta(),weight);
                _h_2lee4j_jet_2_pT->fill(alljets[1].pT()/GeV,weight);

                _h_2lee4j_nLep->fill(elVec.size() + muVec.size(),weight);
                _h_2lee4j_nEl->fill(elVec.size(),weight);
                _h_2lee4j_nMu->fill(muVec.size(),weight);
                
                _h_2lee4j_el_pT->fill(elVec[0].pT()/GeV,weight);
                _h_2lee4j_el_eta->fill(elVec[0].eta(),weight);
            }
            //2lmumu4j
            if(muVec.size() ==2 && abs(muqsum)==2 && muVec.size() ==2 && muVec[0].pT()/GeV > 25 && muVec[1].pT()/GeV >20)
            {
                MSG_INFO("Filling 2lmumu4j histograms");
                _sumWeight_2lmumu4j += event.weight();

                _h_2lmumu4j_nBjets->fill(bjets.size(),weight);
                _h_2lmumu4j_nLjets->fill(ljets.size(),weight);
                _h_2lmumu4j_nJets->fill(alljets.size(),weight);
                
                _h_2lmumu4j_jet_1_pT->fill(alljets[0].pT()/GeV,weight); 
                _h_2lmumu4j_jet_1_eta->fill(alljets[0].eta(),weight);
                _h_2lmumu4j_jet_2_pT->fill(alljets[1].pT()/GeV,weight);

                _h_2lmumu4j_nLep->fill(elVec.size() + muVec.size(),weight);
                _h_2lmumu4j_nEl->fill(elVec.size(),weight);
                _h_2lmumu4j_nMu->fill(muVec.size(),weight);
                
                _h_2lmumu4j_mu_pT->fill(muVec[0].pT()/GeV,weight);
                _h_2lmumu4j_mu_eta->fill(muVec[0].eta(),weight);
            }
            //2lemu4j
            if(abs(emuqsum)==2 && elVec.size()==1 && muVec.size()==1 && elVec[0].pT()/GeV >20 && muVec[0].pT()/GeV >20)
            {
                bool accept = false;
                if(elVec[0].pT()/GeV > muVec[0].pT()/GeV && elVec[0].pT()/GeV >25 && muVec[0].pT()/GeV >20)
                {
                    accept = true;
                }
                else if (elVec[0].pT()/GeV < muVec[0].pT()/GeV && muVec[0].pT()/GeV>25 && elVec[0].pT()/GeV >20)
                {
                    accept = true;
                }
                if(accept)
                { 
                    _sumWeight_2lemu4j += event.weight();

                    MSG_INFO("Filling 2lemu4j histograms");
                    _h_2lemu4j_nBjets->fill(bjets.size(),weight);
                    _h_2lemu4j_nLjets->fill(ljets.size(),weight);
                    _h_2lemu4j_nJets->fill(alljets.size(),weight);
                    
                    _h_2lemu4j_jet_1_pT->fill(alljets[0].pT()/GeV,weight); 
                    _h_2lemu4j_jet_1_eta->fill(alljets[0].eta(),weight);
                    _h_2lemu4j_jet_2_pT->fill(alljets[1].pT()/GeV,weight);

                    _h_2lemu4j_nLep->fill(elVec.size() + muVec.size(),weight);
                    _h_2lemu4j_nEl->fill(elVec.size(),weight);
                    _h_2lemu4j_nMu->fill(muVec.size(),weight);
                    
                    _h_2lemu4j_el_pT->fill(elVec[0].pT()/GeV,weight);
                    _h_2lemu4j_el_eta->fill(elVec[0].eta(),weight);
                    _h_2lemu4j_mu_pT->fill(muVec[0].pT()/GeV,weight);
                    _h_2lemu4j_mu_eta->fill(muVec[0].eta(),weight);
                }
            }
         }
         
         if(alljets.size()>=5)
         {
             MSG_INFO(elVec.size()<<" , " <<muVec.size());
             //2lee5j
            //if(abs(elqsum) ==2 && elVec.size()==2 )// && elVec[0].pT()/GeV > 25 && elVec[1].pT()/GeV>20)
            if(elVec.size()>=2 && elVec[0].pT()/GeV >25 && elVec[1].pT()/GeV > 20 && abs(elqsum)==2)
            {
                _sumWeight_2lee5j += event.weight();
                MSG_INFO("Filling 2lee5j Histograms");

                _h_2lee5j_nBjets->fill(bjets.size(),weight);
                _h_2lee5j_nLjets->fill(ljets.size(),weight);
                _h_2lee5j_nJets->fill(alljets.size(),weight);
                
                _h_2lee5j_jet_1_pT->fill(alljets[0].pT()/GeV,weight); 
                _h_2lee5j_jet_1_eta->fill(alljets[0].eta(),weight);
                _h_2lee5j_jet_2_pT->fill(alljets[1].pT()/GeV,weight);

                _h_2lee5j_nLep->fill(elVec.size() + muVec.size(),weight);
                _h_2lee5j_nEl->fill(elVec.size(),weight);
                _h_2lee5j_nMu->fill(muVec.size(),weight);
                
                _h_2lee5j_el_pT->fill(elVec[0].pT()/GeV,weight);
                _h_2lee5j_el_eta->fill(elVec[0].eta(),weight);
            }
            //2lmumu5j
            if(muVec.size() ==2 && abs(muqsum)==2 && muVec.size() ==2 && muVec[0].pT()/GeV > 25 && muVec[1].pT()/GeV >20)
            {
                MSG_INFO("Filling 2lmumu5j histograms");
                _sumWeight_2lmumu5j += event.weight();

                _h_2lmumu5j_nBjets->fill(bjets.size(),weight);
                _h_2lmumu5j_nLjets->fill(ljets.size(),weight);
                _h_2lmumu5j_nJets->fill(alljets.size(),weight);
                
                _h_2lmumu5j_jet_1_pT->fill(alljets[0].pT()/GeV,weight); 
                _h_2lmumu5j_jet_1_eta->fill(alljets[0].eta(),weight);
                _h_2lmumu5j_jet_2_pT->fill(alljets[1].pT()/GeV,weight);

                _h_2lmumu5j_nLep->fill(elVec.size() + muVec.size(),weight);
                _h_2lmumu5j_nEl->fill(elVec.size(),weight);
                _h_2lmumu5j_nMu->fill(muVec.size(),weight);
                
                _h_2lmumu5j_mu_pT->fill(muVec[0].pT()/GeV,weight);
                _h_2lmumu5j_mu_eta->fill(muVec[0].eta(),weight);
            }
            //2lemu5j
            if(abs(emuqsum)==2 && elVec.size()==1 && muVec.size()==1 && elVec[0].pT()/GeV >20 && muVec[0].pT()/GeV >20)
            {
                bool accept = false;
                if(elVec[0].pT()/GeV > muVec[0].pT()/GeV && elVec[0].pT()/GeV >25 && muVec[0].pT()/GeV >20)
                {
                    accept = true;
                }
                else if (elVec[0].pT()/GeV < muVec[0].pT()/GeV && muVec[0].pT()/GeV>25 && elVec[0].pT()/GeV >20)
                {
                    accept = true;
                }
                if(accept)
                { 
                    _sumWeight_2lemu5j += event.weight();

                    MSG_INFO("Filling 2lemu5j histograms");
                    _h_2lemu5j_nBjets->fill(bjets.size(),weight);
                    _h_2lemu5j_nLjets->fill(ljets.size(),weight);
                    _h_2lemu5j_nJets->fill(alljets.size(),weight);
                    
                    _h_2lemu5j_jet_1_pT->fill(alljets[0].pT()/GeV,weight); 
                    _h_2lemu5j_jet_1_eta->fill(alljets[0].eta(),weight);
                    _h_2lemu5j_jet_2_pT->fill(alljets[1].pT()/GeV,weight);

                    _h_2lemu5j_nLep->fill(elVec.size() + muVec.size(),weight);
                    _h_2lemu5j_nEl->fill(elVec.size(),weight);
                    _h_2lemu5j_nMu->fill(muVec.size(),weight);
                    
                    _h_2lemu5j_el_pT->fill(elVec[0].pT()/GeV,weight);
                    _h_2lemu5j_el_eta->fill(elVec[0].eta(),weight);
                    _h_2lemu5j_mu_pT->fill(muVec[0].pT()/GeV,weight);
                    _h_2lemu5j_mu_eta->fill(muVec[0].eta(),weight);
                }
            }
          }
        }
        //3l
        if( (elVec.size() + muVec.size()) ==3 
                && ((alljets.size()>=4 && bjets.size()>=1) || (alljets.size()==3 && bjets.size() >=2)))
        {
            if( abs(elqsum + muqsum + emuqsum) ==1)
            {
                std::pair<Particle,Particle> sslepPair;
                std::pair<Particle,Particle> oslepPair; //Opposite sign same flavor
                //find same sign leptons
                Particles Leptons = elVec;
                Leptons.insert(Leptons.end(),muVec.begin(),muVec.end());
                for(size_t i = 0; i < Leptons.size(); ++i)
                {
                    for(size_t j = i+1; j<Leptons.size(); ++j)
                    {
                        Particle lep1 = Leptons[i];
                        Particle lep2 = Leptons[j];
                        if(lep1.charge()*lep2.charge()==1)
                        {
                            sslepPair= std::make_pair(lep1,lep2);
                        }
                        if(lep1.charge()*lep2.charge()==-1 && lep1.pid() == abs(lep2.pid()))
                        {
                            oslepPair = std::make_pair(lep1,lep2);
                        }
                    }
                }

                if(sslepPair.first.pT()/GeV >20 && sslepPair.second.pT()/GeV >20 
                        && ( (oslepPair.first.momentum() + oslepPair.second.momentum()).mass()/GeV - 91.186) > 10 )
                {

                    MSG_INFO("Filling 3l histograms");
                    _sumWeight_3l   += event.weight();

                    _h_3l_nBjets->fill(bjets.size(),weight);
                    _h_3l_nLjets->fill(ljets.size(),weight);
                    _h_3l_nJets->fill(alljets.size(),weight);
                    
                    _h_3l_jet_1_pT->fill(alljets[0].pT()/GeV,weight); 
                    _h_3l_jet_1_eta->fill(alljets[0].eta(),weight);
                    _h_3l_jet_2_pT->fill(alljets[1].pT()/GeV,weight);

                    _h_3l_nLep->fill(elVec.size() + muVec.size(),weight);
                    _h_3l_nEl->fill(elVec.size(),weight);
                    _h_3l_nMu->fill(muVec.size(),weight);
                    
                    _h_3l_el_pT->fill(elVec[0].pT()/GeV,weight);
                    _h_3l_el_eta->fill(elVec[0].eta(),weight);
                    _h_3l_mu_pT->fill(muVec[0].pT()/GeV,weight);
                    _h_3l_mu_eta->fill(muVec[0].eta(),weight);
                    if(tauVec.size()>0)
                    {
                        _h_3l_tau_pT->fill(tauVec[0].pT()/GeV,weight);
                        _h_3l_tau_eta->fill(tauVec[0].eta(),weight);
                    }
                }
            }
        }

        //2l1tau
        if(tauVec.size()==1 && alljets.size()>=4 && bjets.size() >=1)
        {
            Particles lepVec = elVec;
            lepVec.insert(lepVec.end(), muVec.begin(), muVec.end());
            sortByPt(lepVec);

            if(abs(elqsum + muqsum + emuqsum) ==2 && lepVec[0].pT()/GeV > 25 && lepVec[1].pT()/GeV > 15)
            {
                MSG_INFO("Filling 2l1tau histograms");
                _sumWeight_2l1tau += event.weight();

                _h_2l_1tau_nBjets->fill(bjets.size(),weight);
                _h_2l_1tau_nLjets->fill(ljets.size(),weight);
                _h_2l_1tau_nJets->fill(alljets.size(),weight);
                
                _h_2l_1tau_jet_1_pT->fill(alljets[0].pT()/GeV,weight); 
                _h_2l_1tau_jet_1_eta->fill(alljets[0].eta(),weight);
                _h_2l_1tau_jet_2_pT->fill(alljets[1].pT()/GeV,weight);

                _h_2l_1tau_nLep->fill(elVec.size() + muVec.size(),weight);
                _h_2l_1tau_nEl->fill(elVec.size(),weight);
                _h_2l_1tau_nMu->fill(muVec.size(),weight);

                if(elVec.size()>0)
                {
                    _h_2l_1tau_el_pT->fill(elVec[0].pT()/GeV,weight);
                    _h_2l_1tau_el_eta->fill(elVec[0].eta(),weight);
                }
                if(muVec.size()>0)
                {
                    _h_2l_1tau_mu_pT->fill(muVec[0].pT()/GeV,weight);
                    _h_2l_1tau_mu_eta->fill(muVec[0].eta(),weight);
                }
                _h_2l_1tau_tau_pT->fill(tauVec[0].pT()/GeV,weight);
                _h_2l_1tau_tau_eta->fill(tauVec[0].eta(),weight);
            }
        }
    }


    void finalize() {
        MSG_INFO("CROSS SSECTION:"<<crossSection());
        MSG_INFO("Sum of weights:"<<_sumofweight);
        double norm = crossSection()/_sumofweight;

        MSG_INFO("Events 2lee4j: "<<_sumWeight_2lee4j);
        MSG_INFO("Events 2lmumu4j: "<<_sumWeight_2lmumu4j);
        MSG_INFO("Events 2lemu4j: "<<_sumWeight_2lemu4j);
        MSG_INFO("Events 2lee5j: "<<_sumWeight_2lee5j);
        MSG_INFO("Events 2lmumu5j: "<<_sumWeight_2lmumu5j);
        MSG_INFO("Events 2lemu5j: "<<_sumWeight_2lemu5j);
        MSG_INFO("Events 2l1tau: "<<_sumWeight_2l1tau);
        MSG_INFO("Events 3l: "<<_sumWeight_3l);
 
        
        scale(_h_2lee4j_nBjets     ,crossSection()/_sumWeight_2lee4j);
        scale(_h_2lee4j_nLjets     ,crossSection()/_sumWeight_2lee4j);
        scale(_h_2lee4j_nJets      ,crossSection()/_sumWeight_2lee4j);
        scale(_h_2lee4j_jet_1_pT   ,crossSection()/_sumWeight_2lee4j);
        scale(_h_2lee4j_jet_1_eta  ,crossSection()/_sumWeight_2lee4j);
        scale(_h_2lee4j_jet_2_pT   ,crossSection()/_sumWeight_2lee4j);

        scale(_h_2lee4j_nLep       ,crossSection()/_sumWeight_2lee4j);
        scale(_h_2lee4j_nEl        ,crossSection()/_sumWeight_2lee4j);
        scale(_h_2lee4j_nMu        ,crossSection()/_sumWeight_2lee4j);
        
        scale(_h_2lee4j_el_pT      ,crossSection()/_sumWeight_2lee4j);
        scale(_h_2lee4j_el_eta     ,crossSection()/_sumWeight_2lee4j);

        scale(_h_2lmumu4j_nBjets     ,crossSection()/_sumWeight_2lmumu4j);
        scale(_h_2lmumu4j_nLjets     ,crossSection()/_sumWeight_2lmumu4j);
        scale(_h_2lmumu4j_nJets      ,crossSection()/_sumWeight_2lmumu4j);
        scale(_h_2lmumu4j_jet_1_pT   ,crossSection()/_sumWeight_2lmumu4j);
        scale(_h_2lmumu4j_jet_1_eta  ,crossSection()/_sumWeight_2lmumu4j);
        scale(_h_2lmumu4j_jet_2_pT   ,crossSection()/_sumWeight_2lmumu4j);

        scale(_h_2lmumu4j_nLep       ,crossSection()/_sumWeight_2lmumu4j);
        scale(_h_2lmumu4j_nEl        ,crossSection()/_sumWeight_2lmumu4j);
        scale(_h_2lmumu4j_nMu        ,crossSection()/_sumWeight_2lmumu4j);
        
        scale(_h_2lmumu4j_mu_pT      ,crossSection()/_sumWeight_2lmumu4j);
        scale(_h_2lmumu4j_mu_eta     ,crossSection()/_sumWeight_2lmumu4j);

        scale(_h_2lemu4j_nBjets     ,crossSection()/_sumWeight_2lemu4j);
        scale(_h_2lemu4j_nLjets     ,crossSection()/_sumWeight_2lemu4j);
        scale(_h_2lemu4j_nJets      ,crossSection()/_sumWeight_2lemu4j);
        scale(_h_2lemu4j_jet_1_pT   ,crossSection()/_sumWeight_2lemu4j);
        scale(_h_2lemu4j_jet_1_eta  ,crossSection()/_sumWeight_2lemu4j);
        scale(_h_2lemu4j_jet_2_pT   ,crossSection()/_sumWeight_2lemu4j);

        scale(_h_2lemu4j_nLep       ,crossSection()/_sumWeight_2lemu4j);
        scale(_h_2lemu4j_nEl        ,crossSection()/_sumWeight_2lemu4j);
        scale(_h_2lemu4j_nMu        ,crossSection()/_sumWeight_2lemu4j);
        
        scale(_h_2lemu4j_el_pT      ,crossSection()/_sumWeight_2lemu4j);
        scale(_h_2lemu4j_el_eta     ,crossSection()/_sumWeight_2lemu4j);
        scale(_h_2lemu4j_mu_pT      ,crossSection()/_sumWeight_2lemu4j);
        scale(_h_2lemu4j_mu_eta     ,crossSection()/_sumWeight_2lemu4j);

        scale(_h_2lee5j_nBjets     ,crossSection()/_sumWeight_2lee5j);
        scale(_h_2lee5j_nLjets     ,crossSection()/_sumWeight_2lee5j);
        scale(_h_2lee5j_nJets      ,crossSection()/_sumWeight_2lee5j);
        scale(_h_2lee5j_jet_1_pT   ,crossSection()/_sumWeight_2lee5j);
        scale(_h_2lee5j_jet_1_eta  ,crossSection()/_sumWeight_2lee5j);
        scale(_h_2lee5j_jet_2_pT   ,crossSection()/_sumWeight_2lee5j);

        scale(_h_2lee5j_nLep       ,crossSection()/_sumWeight_2lee5j);
        scale(_h_2lee5j_nEl        ,crossSection()/_sumWeight_2lee5j);
        scale(_h_2lee5j_nMu        ,crossSection()/_sumWeight_2lee5j);
        
        scale(_h_2lee5j_el_pT      ,crossSection()/_sumWeight_2lee5j);
        scale(_h_2lee5j_el_eta     ,crossSection()/_sumWeight_2lee5j);

        scale(_h_2lmumu5j_nBjets     ,crossSection()/_sumWeight_2lmumu5j);
        scale(_h_2lmumu5j_nLjets     ,crossSection()/_sumWeight_2lmumu5j);
        scale(_h_2lmumu5j_nJets      ,crossSection()/_sumWeight_2lmumu5j);
        scale(_h_2lmumu5j_jet_1_pT   ,crossSection()/_sumWeight_2lmumu5j);
        scale(_h_2lmumu5j_jet_1_eta  ,crossSection()/_sumWeight_2lmumu5j);
        scale(_h_2lmumu5j_jet_2_pT   ,crossSection()/_sumWeight_2lmumu5j);

        scale(_h_2lmumu5j_nLep       ,crossSection()/_sumWeight_2lmumu5j);
        scale(_h_2lmumu5j_nEl        ,crossSection()/_sumWeight_2lmumu5j);
        scale(_h_2lmumu5j_nMu        ,crossSection()/_sumWeight_2lmumu5j);
        
        scale(_h_2lmumu5j_mu_pT      ,crossSection()/_sumWeight_2lmumu5j);
        scale(_h_2lmumu5j_mu_eta     ,crossSection()/_sumWeight_2lmumu5j);

        scale(_h_2lemu5j_nBjets     ,crossSection()/_sumWeight_2lemu5j);
        scale(_h_2lemu5j_nLjets     ,crossSection()/_sumWeight_2lemu5j);
        scale(_h_2lemu5j_nJets      ,crossSection()/_sumWeight_2lemu5j);
        scale(_h_2lemu5j_jet_1_pT   ,crossSection()/_sumWeight_2lemu5j);
        scale(_h_2lemu5j_jet_1_eta  ,crossSection()/_sumWeight_2lemu5j);
        scale(_h_2lemu5j_jet_2_pT   ,crossSection()/_sumWeight_2lemu5j);

        scale(_h_2lemu5j_nLep       ,crossSection()/_sumWeight_2lemu5j);
        scale(_h_2lemu5j_nEl        ,crossSection()/_sumWeight_2lemu5j);
        scale(_h_2lemu5j_nMu        ,crossSection()/_sumWeight_2lemu5j);
        
        scale(_h_2lemu5j_el_pT      ,crossSection()/_sumWeight_2lemu5j);
        scale(_h_2lemu5j_el_eta     ,crossSection()/_sumWeight_2lemu5j);
        scale(_h_2lemu5j_mu_pT      ,crossSection()/_sumWeight_2lemu5j);
        scale(_h_2lemu5j_mu_eta     ,crossSection()/_sumWeight_2lemu5j);

        scale(_h_3l_nBjets     ,crossSection()/_sumWeight_3l);
        scale(_h_3l_nLjets     ,crossSection()/_sumWeight_3l);
        scale(_h_3l_nJets      ,crossSection()/_sumWeight_3l);
        scale(_h_3l_jet_1_pT   ,crossSection()/_sumWeight_3l);
        scale(_h_3l_jet_1_eta  ,crossSection()/_sumWeight_3l);
        scale(_h_3l_jet_2_pT   ,crossSection()/_sumWeight_3l);

        scale(_h_3l_nLep       ,crossSection()/_sumWeight_3l);
        scale(_h_3l_nEl        ,crossSection()/_sumWeight_3l);
        scale(_h_3l_nMu        ,crossSection()/_sumWeight_3l);
        
        scale(_h_3l_el_pT      ,crossSection()/_sumWeight_3l);
        scale(_h_3l_el_eta     ,crossSection()/_sumWeight_3l);
        scale(_h_3l_mu_pT      ,crossSection()/_sumWeight_3l);
        scale(_h_3l_mu_eta     ,crossSection()/_sumWeight_3l);
        scale(_h_3l_tau_pT     ,crossSection()/_sumWeight_3l);
        scale(_h_3l_tau_eta    ,crossSection()/_sumWeight_3l); 

        scale(_h_2l_1tau_nBjets     ,crossSection()/_sumWeight_2l1tau);
        scale(_h_2l_1tau_nLjets     ,crossSection()/_sumWeight_2l1tau);
        scale(_h_2l_1tau_nJets      ,crossSection()/_sumWeight_2l1tau);
        scale(_h_2l_1tau_jet_1_pT   ,crossSection()/_sumWeight_2l1tau);
        scale(_h_2l_1tau_jet_1_eta  ,crossSection()/_sumWeight_2l1tau);
        scale(_h_2l_1tau_jet_2_pT   ,crossSection()/_sumWeight_2l1tau);

        scale(_h_2l_1tau_nLep       ,crossSection()/_sumWeight_2l1tau);
        scale(_h_2l_1tau_nEl        ,crossSection()/_sumWeight_2l1tau);
        scale(_h_2l_1tau_nMu        ,crossSection()/_sumWeight_2l1tau);
        
        scale(_h_2l_1tau_el_pT      ,crossSection()/_sumWeight_2l1tau);
        scale(_h_2l_1tau_el_eta     ,crossSection()/_sumWeight_2l1tau);
        scale(_h_2l_1tau_mu_pT      ,crossSection()/_sumWeight_2l1tau);
        scale(_h_2l_1tau_mu_eta     ,crossSection()/_sumWeight_2l1tau);
        scale(_h_2l_1tau_tau_pT     ,crossSection()/_sumWeight_2l1tau);
        scale(_h_2l_1tau_tau_eta    ,crossSection()/_sumWeight_2l1tau);



    }

    //@}


  private:

    // @name Histogram data members
    //@{
    Histo1DPtr _h_2lee4j_nBjets,_h_2lee4j_nLjets,_h_2lee4j_nJets;
    Histo1DPtr _h_2lee4j_jet_1_pT,_h_2lee4j_jet_1_eta, _h_2lee4j_jet_2_pT;

    Histo1DPtr _h_2lee4j_nLep,_h_2lee4j_nEl,_h_2lee4j_nMu;
    Histo1DPtr _h_2lee4j_el_pT,_h_2lee4j_el_eta;

    Histo1DPtr _h_2lmumu4j_nBjets,_h_2lmumu4j_nLjets,_h_2lmumu4j_nJets;
    Histo1DPtr _h_2lmumu4j_jet_1_pT,_h_2lmumu4j_jet_1_eta, _h_2lmumu4j_jet_2_pT;

    Histo1DPtr _h_2lmumu4j_nLep,_h_2lmumu4j_nEl,_h_2lmumu4j_nMu;
    Histo1DPtr _h_2lmumu4j_mu_pT,_h_2lmumu4j_mu_eta;

    Histo1DPtr _h_2lemu4j_nBjets,_h_2lemu4j_nLjets,_h_2lemu4j_nJets;
    Histo1DPtr _h_2lemu4j_jet_1_pT,_h_2lemu4j_jet_1_eta, _h_2lemu4j_jet_2_pT;

    Histo1DPtr _h_2lemu4j_nLep,_h_2lemu4j_nEl,_h_2lemu4j_nMu;
    Histo1DPtr _h_2lemu4j_el_pT,_h_2lemu4j_el_eta;
    Histo1DPtr _h_2lemu4j_mu_pT,_h_2lemu4j_mu_eta;



    Histo1DPtr _h_2lee5j_nBjets,_h_2lee5j_nLjets,_h_2lee5j_nJets;
    Histo1DPtr _h_2lee5j_jet_1_pT,_h_2lee5j_jet_1_eta, _h_2lee5j_jet_2_pT;

    Histo1DPtr _h_2lee5j_nLep,_h_2lee5j_nEl,_h_2lee5j_nMu;
    Histo1DPtr _h_2lee5j_el_pT,_h_2lee5j_el_eta;

    Histo1DPtr _h_2lmumu5j_nBjets,_h_2lmumu5j_nLjets,_h_2lmumu5j_nJets;
    Histo1DPtr _h_2lmumu5j_jet_1_pT,_h_2lmumu5j_jet_1_eta, _h_2lmumu5j_jet_2_pT;

    Histo1DPtr _h_2lmumu5j_nLep,_h_2lmumu5j_nEl,_h_2lmumu5j_nMu;
    Histo1DPtr _h_2lmumu5j_mu_pT,_h_2lmumu5j_mu_eta;

    Histo1DPtr _h_2lemu5j_nBjets,_h_2lemu5j_nLjets,_h_2lemu5j_nJets;
    Histo1DPtr _h_2lemu5j_jet_1_pT,_h_2lemu5j_jet_1_eta, _h_2lemu5j_jet_2_pT;

    Histo1DPtr _h_2lemu5j_nLep,_h_2lemu5j_nEl,_h_2lemu5j_nMu;
    Histo1DPtr _h_2lemu5j_el_pT,_h_2lemu5j_el_eta;
    Histo1DPtr _h_2lemu5j_mu_pT,_h_2lemu5j_mu_eta;

    Histo1DPtr _h_3l_nBjets,_h_3l_nLjets,_h_3l_nJets;
    Histo1DPtr _h_3l_jet_1_pT,_h_3l_jet_1_eta, _h_3l_jet_2_pT;

    Histo1DPtr _h_3l_nLep,_h_3l_nEl,_h_3l_nMu;
    Histo1DPtr _h_3l_el_pT,_h_3l_el_eta;
    Histo1DPtr _h_3l_mu_pT,_h_3l_mu_eta;
    Histo1DPtr _h_3l_tau_pT,_h_3l_tau_eta;
 
    Histo1DPtr _h_2l_1tau_nBjets,_h_2l_1tau_nLjets,_h_2l_1tau_nJets;
    Histo1DPtr _h_2l_1tau_jet_1_pT,_h_2l_1tau_jet_1_eta, _h_2l_1tau_jet_2_pT;

    Histo1DPtr _h_2l_1tau_nLep,_h_2l_1tau_nEl,_h_2l_1tau_nMu;
    Histo1DPtr _h_2l_1tau_el_pT,_h_2l_1tau_el_eta;
    Histo1DPtr _h_2l_1tau_mu_pT,_h_2l_1tau_mu_eta;
    Histo1DPtr _h_2l_1tau_tau_pT,_h_2l_1tau_tau_eta;


    float _sumofweight;
    float _sumWeight_2lee4j;
    float _sumWeight_2lmumu4j;
    float _sumWeight_2lemu4j;
    float _sumWeight_2lee5j;
    float _sumWeight_2lmumu5j;
    float _sumWeight_2lemu5j;
    float _sumWeight_2l1tau;
    float _sumWeight_3l;
    int nEvents;

    //@}

  };



  // The hook for the plugin system
  DECLARE_RIVET_PLUGIN(ttll_study);

}
