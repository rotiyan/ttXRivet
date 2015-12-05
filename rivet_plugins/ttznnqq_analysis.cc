// -*- C++ -*-
#include "Rivet/Analysis.hh"
#include "Rivet/Tools/Logging.hh"
#include "Rivet/Projections/ChargedLeptons.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Projections/ZFinder.hh"
#include "Rivet/Projections/MissingMomentum.hh"
#include "Rivet/Projections/HeavyHadrons.hh"


// ROOT stuff
#include <vector>



namespace Rivet {

  /// @brief Book and fill a ROOT tree with simulated data.
  ///
  /// This does some things, e.g. access parton level information, which
  /// are not recommended in Rivet analyses, since the information is 
  /// unphysical and so cannot be compared to data, and also may be generator dependent.
  /// 
  class ttznnqq_analysis: public Analysis{
  public:
    ttznnqq_analysis() : Analysis("ttznnqq_analysis") { 
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


     _h_nn_met      =   bookHisto1D("nn_met",100,0,800);
     _h_nn_ht       =   bookHisto1D("nn_ht",100,0,900);
     _h_qq_met      =   bookHisto1D("qq_met",100,0,800);
     _h_qq_ht       =   bookHisto1D("qq_ht",100,0,900);
     _h_nn_njet     =   bookHisto1D("nn_njet",20,-0.5,19.5);
     _h_nn_jet_1_pt =   bookHisto1D("nn_jet_1_pt",100,10,410);
     _h_nn_bjet1_pt =   bookHisto1D("nn_bjet1_pt",100,10,410);
     _h_nn_jet_2_pt =   bookHisto1D("nn_jet_2_pt",100,10,410);
     _h_nn_bjet2_pt =   bookHisto1D("nn_bjet2_pt",100,10,410);
     _h_qq_njet     =   bookHisto1D("qq_njet",20,-0.5,19.5);
     _h_qq_jet_1_pt =   bookHisto1D("qq_jet_1_pt",100,20,410);
     _h_qq_bjet1_pt =   bookHisto1D("qq_bjet1_pt",100,20,410);
     _h_qq_jet_2_pt =   bookHisto1D("qq_jet_2_pt",100,20,410);
     _h_qq_bjet2_pt =   bookHisto1D("qq_bjet2_pt",100,20,410);
     _h_nn_zmass    =   bookHisto1D("nn_zmass",210,5,115);
     _h_nn_t_mass   =   bookHisto1D("nn_t_mass",150,130,430);
     _h_qq_zmass    =   bookHisto1D("qq_zmass",210,5,115);
     _h_qq_t_mass   =   bookHisto1D("qq_t_mass",150,130,430);

    }
    

    // Do the analysis
    void analyze(const Event& event) {
      bool hadronicZevent   = false;
      bool neutrinoZevent   = false;

      double _weight = event.weight();
      double _met, _ht=0,_njet,_jet1_pt,_jet2_pt;
      double _bjet1_pt,_bjet2_pt;
      double _zmass=0,_t_mass;

      const GenEvent& ev = *(event.genEvent());

      const MissingMomentum& met = applyProjection<MissingMomentum>(event, "MissingET");
      _met  = met.vectorEt().mod()/GeV;

      const Particles bhadrons = sortByPt(applyProjection<HeavyHadrons>(event, "BCHadrons").bHadrons());
      const FastJets& jetpro = applyProjection<FastJets>(event, "Jets");
      const Jets alljets = jetpro.jetsByPt(20*GeV);
      foreach (const Jet& j, alljets) { _ht += j.pT(); }
 

      const ZFinder & znunuFinder   = applyProjection<ZFinder>(event,"znunuFinder");
      const ChargedLeptons& lfs = applyProjection<ChargedLeptons>(event, "LFS");
      

      if(znunuFinder.size() !=0)
      {
          neutrinoZevent= true;
          _zmass = znunuFinder.bosons()[0].momentum().mass()/GeV;
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
      else
      {
          _jet1_pt  = alljets.at(0).pT()/GeV;
          _jet2_pt  = alljets.at(1).pT()/GeV;
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
      else
      {
        sort(bjets.begin(),bjets.end(),cmpMomByPt);
        _bjet1_pt = bjets.at(0).pT()/GeV;
        _bjet2_pt = bjets.at(1).pT()/GeV;
    
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
      for(size_t i =0 ; i < remainJets.size() ; ++i)
      {
          for(size_t j =0; j < remainJets.size(); ++j)
          {
              if( i !=j)
              {
                  const FourMomentum Wcand = remainJets[0].momentum() + remainJets[1].momentum();
                  if(fabs(Wcand.mass() - 80.4*GeV) < fabs(W.mass() - 80.04*GeV))
                  {
                      W = Wcand;
                  }
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
      _t_mass = t_had.mass()/GeV;


      //Fill histograms

      if(neutrinoZevent)
      {
          _h_nn_met->fill(_met,_weight);
          _h_nn_ht->fill(_ht,_weight);
          _h_nn_njet->fill(_njet,_weight);
          _h_nn_jet_1_pt->fill(_jet1_pt,_weight);
          _h_nn_bjet1_pt->fill(_bjet1_pt,_weight);
          _h_nn_jet_2_pt->fill(_jet2_pt,_weight);
          _h_nn_bjet2_pt->fill(_bjet2_pt,_weight);
          _h_nn_zmass->fill(_zmass,_weight);
          _h_nn_t_mass->fill(_t_mass,_weight);
      }
      if(hadronicZevent)
      {
          _h_qq_met->fill(_met,_weight);
          _h_qq_ht->fill(_ht,_weight);
          _h_qq_njet->fill(_njet,_weight);
          _h_qq_jet_1_pt->fill(_jet1_pt,_weight);
          _h_qq_bjet1_pt->fill(_bjet1_pt,_weight);
          _h_qq_jet_2_pt->fill(_jet2_pt,_weight);
          _h_qq_bjet2_pt->fill(_bjet2_pt,_weight);
          _h_qq_zmass->fill(_zmass,_weight);
          _h_qq_t_mass->fill(_t_mass,_weight);
      }
    }
  }
    
    
    void finalize() { 
      // Write the tree to file.
        
        double norm = crossSection()/sumOfWeights();

        scale(_h_nn_met,norm);
        scale(_h_nn_ht,norm);
        scale(_h_nn_njet,norm);
        scale(_h_nn_jet_1_pt,norm);
        scale(_h_nn_jet_2_pt,norm);
        scale(_h_nn_bjet1_pt,norm);
        scale(_h_nn_bjet2_pt,norm);
        scale(_h_nn_zmass,norm);
        scale(_h_nn_t_mass,norm);
 
        scale(_h_qq_met,norm);
        scale(_h_qq_ht,norm);
        scale(_h_qq_njet,norm);
        scale(_h_qq_jet_1_pt,norm);
        scale(_h_qq_jet_2_pt,norm);
        scale(_h_qq_bjet1_pt,norm);
        scale(_h_qq_bjet2_pt,norm);
        scale(_h_qq_zmass,norm);
        scale(_h_qq_t_mass,norm);


    }
    
    //@}

  private:
    Histo1DPtr _h_nn_met,_h_nn_ht;
    Histo1DPtr _h_qq_met,_h_qq_ht;
    Histo1DPtr _h_nn_njet,_h_nn_jet_1_pt,_h_nn_jet_2_pt,_h_nn_bjet1_pt,_h_nn_bjet2_pt;
    Histo1DPtr _h_qq_njet,_h_qq_jet_1_pt,_h_qq_jet_2_pt,_h_qq_bjet1_pt,_h_qq_bjet2_pt;
    Histo1DPtr _h_nn_zmass,_h_nn_t_mass;
    Histo1DPtr _h_qq_zmass,_h_qq_t_mass;

  };

  DECLARE_RIVET_PLUGIN(ttznnqq_analysis);

}
