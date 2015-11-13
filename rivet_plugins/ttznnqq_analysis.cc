// -*- C++ -*-
#include "Rivet/Analysis.hh"
#include "Rivet/Tools/Logging.hh"
#include "Rivet/Projections/ChargedLeptons.hh"
//#include "Rivet/Projections/TotalVisibleMomentum.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Projections/ZFinder.hh"
#include "Rivet/Projections/MissingMomentum.hh"


// ROOT stuff
#include "TTree.h"
#include "TFile.h"
#include "TString.h"

#include <vector>

namespace Rivet {


  /// @brief Book and fill a ROOT tree with simulated data.
  ///
  /// This does some things, e.g. access parton level information, which
  /// are not recommended in Rivet analyses, since the information is 
  /// unphysical and so cannot be compared to data, and also may be generator dependent.
  /// 
  class RootAnalysis : public Analysis {
  public:

    RootAnalysis() : Analysis("ROOTANALYSIS") { 
      // Choose cuts
      _treeFileName = "rivetTree.root";
    }
    
    
    void init() {
      const FinalState fs(-4.0, 4.0, 0.0*GeV);
      addProjection(fs, "FS");
      addProjection(ChargedLeptons(fs), "ChLeptons");
      addProjection(FastJets(fs, FastJets::ANTIKT, 0.4), "Jets");

      addProjection(MissingMomentum(fs), "MissingET");
      
      FinalState zfs;
      Cut zeefscut = (Cuts::abseta <4.0)& (Cuts::pT>10*GeV);
      ZFinder znunuFinder(zfs,zeefscut,PID::NU_E,60.*GeV,120.0*GeV,0.2,ZFinder::CLUSTERNODECAY,ZFinder::NOTRACK);
      addProjection(znunuFinder,"znunuFinder");

      /// Veto neutrinos, antineutrinos and LSP
      //VetoedFinalState vfs(fs);
      //vfs
      //  .addVetoDetail(NU_E, 10.0*GeV, 50.0*GeV)
      //  .addVetoPairId(NU_MU)
       // .addVetoPairId(NU_TAU)
       // .addVetoId(1000022); // Assumes that neutralino_1 is the LSP
      //addProjection(vfs, "VFS");
      //addProjection(TotalVisibleMomentum(vfs), "TotalVisMom");
      
      // Set up ROOT file structure
      _treeFile = new TFile(_treeFileName, "recreate");
      _rivetTree= new TTree("Rivet Tree", "Rivet Example Tree");

      _rivetTree->Branch("nevt", &_nevt, "nevt/I");
      _rivetTree->Branch("weight",&_weight,"weight/F");

      _jet_pt   = new std::vector<float>();
      _rivetTree->Branch("jet_pt","vector<float>",&_jet_pt);
      
      _jet_eta  = new std::vector<float>();
      _rivetTree->Branch("jet_eta","vector<float>",&_jet_eta);

      _jet_phi  = new std::vector<float>();
      _rivetTree->Branch("jet_phi","vector<float>",&_jet_phi);

      _jet_m    = new std::vector<float>();
      _rivetTree->Branch("jet_m","vector<float>",&_jet_m);

      _jet_e    = new std::vector<float>();
      
      // Jets      
      _rivetTree->Branch("njet", &_njet, "njet/I");
      //met
      _rivetTree->Branch("met",&_met,"met/F");
      _rivetTree->Branch("ht",&_ht,"ht/F");
      _rivetTree->Branch("nnevent",&_nnevent,"nnevent/I");
      _rivetTree->Branch("qqevent",&_qqevent,"qqevent/I");
      _rivetTree->Branch("zmass",&_zmass,"zmass/F");

      _metaTree = new TTree("Meta data "," Meta data tree");
      _metaTree->Branch("crossSection",&_crosssection,"crossSection/F");
      _metaTree->Branch("sumWeights",&_sumWeights,"sumWeights/F");
    }
    

    // Do the analysis
    void analyze(const Event& event) {
      //Reset the variables
    _nevt       = 0;
    _met        = 0;
    _weight     = 0;
    _nnevent    = 0;
    _qqevent    = 0;
    _njet       = 0; 
    
    /// Four momentum of the jets
    _jet_pt->resize(0);
    _jet_eta->resize(0);
    _jet_phi->resize(0);
    _jet_m->resize(0);

    //Start event

      bool hadronicZevent   = false;
      bool neutrinoZevent   = false;

      _weight = event.weight();


      const GenEvent& ev = *(event.genEvent());
      _nevt = ev.event_number();

      const MissingMomentum& met = applyProjection<MissingMomentum>(event, "MissingET");
      _met  = met.vectorEt().mod()/GeV;
      
      if (met.vectorEt().mod() < 30*GeV )
      {
        MSG_INFO("Event failed missing ET cut: MET = "<<_met);
        vetoEvent;
      }

      const FastJets& jetpro = applyProjection<FastJets>(event, "Jets");
      const Jets alljets = jetpro.jetsByPt(20*GeV);
 
      double ht = 0.0;
      foreach (const Jet& j, alljets) { ht += j.pT(); }
      MSG_INFO("HT : "<<ht);

      const ZFinder & znunuFinder   = applyProjection<ZFinder>(event,"znunuFinder");
      if(znunuFinder.size() !=0)
      {
          neutrinoZevent= true;
          _zmass = znunuFinder.bosons()[0].momentum().mass()/GeV;
          _nnevent = 1;
      }
    
      foreach (const Jet &j,alljets){_ht += j.pT()/GeV;}
      _njet = alljets.size();
    
      Jet zjet1,zjet2; //Z->qq jets
      float deltaZMass = 30;
      float PDG_zmass      = 91.1876*GeV;
      foreach(const Jet &j1, alljets)
      {
          MSG_INFO("jet pt : "<<j1.pT()/GeV);
          _jet_pt->push_back(j1.pT()/GeV);
          _jet_eta->push_back(j1.eta());
          _jet_phi->push_back(j1.phi());
          _jet_m->push_back(j1.mass()/GeV);

          foreach(const Jet &j2,alljets)
          {
              if(j1.momentum() != j2.momentum())
              {
                  FourMomentum cmbMom = (j1.momentum() + j2.momentum());
                  if(abs(cmbMom.mass() - PDG_zmass) < deltaZMass)
                  {
                      zjet1 = j1;
                      zjet2  = j2;
                      deltaZMass = abs(cmbMom.mass() -PDG_zmass);
                  }
              }
          }
      }
      float Zmass = (zjet1.momentum() + zjet2.momentum()).mass()/GeV;
      if(Zmass > 60 && Zmass < 120)
      {
          hadronicZevent= true;
          _zmass = Zmass;
          _qqevent = 1;
      }

      if(neutrinoZevent|| hadronicZevent)
      {
          _rivetTree->Fill();
      }
    }
    
    
    void finalize() { 
      // Write the tree to file.
      _rivetTree->Write();

      _crosssection = crossSection();
      _sumWeights   = sumOfWeights();
      _metaTree->Fill();
      _metaTree->Write();
    }
    
    //@}


  private:

    /// The tree
    TTree* _rivetTree;
    TTree* _metaTree;
    
    /// The file for the Tree
    TFile* _treeFile;

    /// The filename
    TString _treeFileName;


    /// @name The ntuple variables.
    //@{
    /// Event number
    int _nevt;
    float _met;
    float _ht;
    float _zmass;
    float _weight;
    int _nnevent;
    int _qqevent;
    int _njet; 
    
    /// Four momentum of the jets
    std::vector<float>* _jet_pt;
    std::vector<float>* _jet_eta;
    std::vector<float>* _jet_phi;
    std::vector<float>* _jet_m;
    std::vector<float>* _jet_e;

    float _crosssection;
    float _sumWeights;

  };
  // This global object acts as a hook for the plugin system
  AnalysisBuilder<RootAnalysis> plugin_RootAnalysis;
}
