// -*- C++ -*-
#include "Rivet/Analysis.hh"
#include "Rivet/Tools/Logging.hh"
#include "Rivet/Projections/ChargedLeptons.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Projections/ZFinder.hh"
#include "Rivet/Projections/MissingMomentum.hh"
#include "Rivet/Projections/HeavyHadrons.hh"


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

      addProjection(HeavyHadrons(Cuts::abseta < 5 && Cuts::pT > 5*GeV), "BCHadrons");
 
      ChargedLeptons lfs(FinalState(-4.0,4.0,10*GeV));
      addProjection(lfs,"LFS");


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

      _jet_flav = new std::vector<float>();
      _rivetTree->Branch("jet_flav","vector<float>",&_jet_flav);

      _jet_e    = new std::vector<float>();
      
      // Jets      
      _rivetTree->Branch("njet", &_njet, "njet/I");
      //met
      _rivetTree->Branch("met",&_met,"met/F");
      _rivetTree->Branch("ht",&_ht,"ht/F");
      _rivetTree->Branch("nnevent",&_nnevent,"nnevent/I");
      _rivetTree->Branch("qqevent",&_qqevent,"qqevent/I");
      _rivetTree->Branch("zmass",&_zmass,"zmass/F");
      _rivetTree->Branch("tmass",&_tmass,"tmass/F");

      _metaTree = new TTree("Meta data "," Meta data tree");
      _metaTree->Branch("crossSection",&_crosssection,"crossSection/F");
      _metaTree->Branch("sumWeights",&_sumWeights,"sumWeights/F");
    }
    

    // Do the analysis
    void analyze(const Event& event) {
      //Reset the variables
    _nevt       = 0;
    _weight     = 0;
    _njet       = 0; 
    _met        = 0;
    _ht         = 0;
    _nnevent    = 0;
    _qqevent    = 0;
    _zmass      = 0;
    _tmass      = 0;
   
    /// Four momentum of the jets
    _jet_pt->resize(0);
    _jet_eta->resize(0);
    _jet_phi->resize(0);
    _jet_m->resize(0);
    _jet_flav->resize(0);

    //Start event

      bool hadronicZevent   = false;
      bool neutrinoZevent   = false;

      _weight = event.weight();


      const GenEvent& ev = *(event.genEvent());
      _nevt = ev.event_number();

      const MissingMomentum& met = applyProjection<MissingMomentum>(event, "MissingET");
      _met  = met.vectorEt().mod()/GeV;

      const Particles bhadrons = sortByPt(applyProjection<HeavyHadrons>(event, "BCHadrons").bHadrons());
      const FastJets& jetpro = applyProjection<FastJets>(event, "Jets");
      const Jets alljets = jetpro.jetsByPt(20*GeV);
 
      const ZFinder & znunuFinder   = applyProjection<ZFinder>(event,"znunuFinder");
      const ChargedLeptons& lfs = applyProjection<ChargedLeptons>(event, "LFS");
 
      if(znunuFinder.size() !=0)
      {
          neutrinoZevent= true;
          _zmass = znunuFinder.bosons()[0].momentum().mass()/GeV;
          _nnevent = 1;
      }
 
      if(neutrinoZevent)
      {
          if(met.vectorEt().mod() < 60*GeV)
          {
              MSG_INFO("Event failed missing ET cut: MET = "<<_met);
              vetoEvent;
          }
      }
      else if(met.vectorEt().mod() <30*GeV)
      {
          MSG_INFO("Event failed missing ET cut: MET="<<_met);
          vetoEvent;
      }

     
      _njet = alljets.size();
      if((_njet < 6 && !neutrinoZevent) || (_njet<4 && neutrinoZevent))
      {
          vetoEvent;
      }
 
      //Find b-jets
      Jets bjets,ljets;
      foreach (const Jet& jet, alljets) 
      {
          foreach (const Particle& b, bhadrons) 
          {
              if (deltaR(jet,b) < 0.3)
              {
    	          bjets.push_back(jet);
              }
              else
              {
                  ljets.push_back(jet);
              }
          }
      }
      if(bjets.size() <2 )
      {
          vetoEvent;
      }

      //Fill jet variables
      foreach (const Jet &j,alljets)
      {
          _ht += j.pT()/GeV;
          MSG_INFO("jet pt : "<<j.pT()/GeV);
          _jet_pt->push_back(j.pT()/GeV);
          _jet_eta->push_back(j.eta());
          _jet_phi->push_back(j.phi());
          _jet_m->push_back(j.mass()/GeV);

          bool isBjet =false;
          foreach(const Particle &b, bhadrons)
          {
              if(deltaR(j,b) <0.3)
              {
                  isBjet =true;
              }
          }
          _jet_flav->push_back((isBjet)?1:0);
      }

    
      Jets remainJets;
      if(neutrinoZevent)
      {
          remainJets = ljets;
      }
      else
      {
          Jet zjet1,zjet2; //Z->qq jets
          float deltaZMass = 30;
          float PDG_zmass      = 91.1876*GeV;
          foreach(const Jet &j1, ljets)
          {
              foreach(const Jet &j2,ljets)
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
              foreach (const Jet &myjet, ljets)
              {
                  if(myjet.pT() !=zjet1.pT() || myjet.pT() != zjet2.pT())
                  {
                      remainJets.push_back(myjet);
                  }
              }
          }
      }

      //Construct tops with the remain jets;
      //
 
      // Construct the hadronically decaying W momentum 4-vector from pairs of
      // non-b-tagged jets. The pair which best matches the W mass is used. We start
      // with an always terrible 4-vector estimate which should always be "beaten" by
      // a real jet pair.
      FourMomentum W(10*sqrtS(), 0, 0, 0);
      for (size_t i = 0; i < remainJets.size()-1; ++i) 
      {
          for (size_t j = i + 1; j < remainJets.size(); ++j) 
          {
              const FourMomentum Wcand = remainJets[i].momentum() + remainJets[j].momentum();
              MSG_TRACE(i << "," << j << ": candidate W mass = " << Wcand.mass()/GeV
                    << " GeV, vs. incumbent candidate with " << W.mass()/GeV << " GeV");
              if (fabs(Wcand.mass() - 80.4*GeV) < fabs(W.mass() - 80.4*GeV)) 
              {
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

      FourMomentum t_had(10*sqrtS(),0.0,0.0,0.0);
      if(fabs(target_topMass - t1.mass()) < fabs(target_topMass - t2.mass()))
      {
          t_had = t1;
      }
      else
      {
        t_had = t2;
      }
      _tmass = t_had.mass()/GeV;



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
    float _tmass;
    float _weight;
    int _nnevent;
    int _qqevent;
    int _njet; 
    
    /// Four momentum of the jets
    std::vector<float>* _jet_pt;
    std::vector<float>* _jet_eta;
    std::vector<float>* _jet_phi;
    std::vector<float>* _jet_m;
    std::vector<float>* _jet_flav;
    std::vector<float>* _jet_e;

    float _crosssection;
    float _sumWeights;

  };
  // This global object acts as a hook for the plugin system
  AnalysisBuilder<RootAnalysis> plugin_RootAnalysis;
}
