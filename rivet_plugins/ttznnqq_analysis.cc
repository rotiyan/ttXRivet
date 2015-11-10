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

  class ttw_analysis: public Analysis {
  public:

    /// Constructor
    ttw_analysis()
      : Analysis("ttznnqq_analysis")
    {    }


    /// @name Analysis methods
    //@{

    /// Book histograms and initialise projections before the run
    void init() {

        addProjection(FastJets(FinalState(-4,4,0*GeV),FastJets::ANTIKT,0.4),"Jets");
        addProjection(MissingMomentum(FinalState(-4,4,0*GeV)),"MissingET");


        _h_znunu_MET= bookHisto1D("znunu_MET",100,50,450);
        _h_zqq_MET  = bookHisto1D("zqq_MET",100,50,450);
        _h_znunu_HT = bookHisto1D("znunu_HT",500,50,2050);
        _h_zqq_HT   = bookHisto1D("zqq_HT",500,50,2050);
        _h_t1_mass  = bookHisto1D("t1_mass",150,130,430);
        _h_t2_mass  = bookHisto1D("t2_mass",150,130,430);
        _h_t1_pt    = bookHisto1D("t1_pt",100,50,450);
        _h_t2_pt    = bookHisto1D("t2_pt",100,50,450);
        _h_t1_eta   = bookHisto1D("t1_eta",100,-5,5);
        _h_t2_eta   = bookHisto1D("t2_eta",100,-5,5);
        _h_t1_phi   = bookHisto1D("t1_phi",50,0,6);
        _h_t2_phi   = bookHisto1D("t2_phi",50,0,6);
        _h_b1_pt    = bookHisto1D("b1_pt",100,0,400);
        _h_b1_eta   = bookHisto1D("b1_eta",100,-5,5);
        _h_b1_phi   = bookHisto1D("b1_phi",100,-5,5);
        _h_b2_pt    = bookHisto1D("b2_pt",100,0,400);
        _h_b2_eta   = bookHisto1D("b2_eta",100,-5,5);
        _h_b2_phi   = bookHisto1D("b2_phi",100,-5,5);
        _h_w1_mass  = bookHisto1D("w1_mass",100,0,120);
        _h_w2_mass  = bookHisto1D("w2_mass",100,0,120);
        _h_w1_pt    = bookHisto1D("w1_pt",100,0,400);
        _h_w2_pt    = bookHisto1D("w2_pt",100,0,400);
        _h_w1_eta   = bookHisto1D("w1_eta",100,-5,5);
        _h_w2_eta   = bookHisto1D("w2_eta",100,-5,5);
        _h_w1_phi   = bookHisto1D("w1_phi",100,-5,5);
        _h_w2_phi   = bookHisto1D("w2_phi",100,-5,5);

        
        _h_e_dEta   = bookHisto1D("zel_dEta",100,0,7);
        _h_e_dPhi   = bookHisto1D("zel_dPhi",100,0,7);
        _h_e_dR     = bookHisto1D("zel_dR",100,0,7);

        _h_mu_dEta  = bookHisto1D("zmu_dEta",100,0,7);
        _h_mu_dPhi  = bookHisto1D("zmu_dPhi",100,0,7);
        _h_mu_dR    = bookHisto1D("zmu_dR",100,0,7);

        _h_top_dEta = bookHisto1D("top_dEta",100,0,7);
        _h_top_dPhi = bookHisto1D("top_dPhi",100,0,7);
        _h_top_dR   = bookHisto1D("top_dR",100,0,7);

        _h_w_dEta   = bookHisto1D("w_dEta",100,0,7);
        _h_w_dPhi   = bookHisto1D("w_dPhi",100,0,7);
        _h_w_dR     = bookHisto1D("w_dR",100,0,7);
        
        _h_b_dEta   = bookHisto1D("b_dEta",100,0,7);
        _h_b_dPhi   = bookHisto1D("b_dPhi",100,0,7);
        _h_b_dR     = bookHisto1D("b_dR",100,0,7);

        _h_zBosons_nunu_pt = bookHisto1D("znunu_pt",100,0,400);
        _h_zBosons_nunu_eta= bookHisto1D("znunu_eta",100,-5,5);
        _h_zBosons_nunu_phi= bookHisto1D("znunu_phi",100,-5,5);

        _h_zBosons_qq_pt = bookHisto1D("zqq_pt",100,0,400);
        _h_zBosons_qq_eta= bookHisto1D("zqq_eta",100,-5,5);
        _h_zBosons_qq_phi= bookHisto1D("zqq_phi",100,-5,5);
 
        
    }


    /// Perform the per-event analysis
    void analyze(const Event& event) {

      const MissingMomentum &met= applyProjection<MissingMomentum>(event,"MissingET");
      const double event_met    = met.vectorEt().mod()*GeV;
  
      
      const FastJets & jetProj  = applyProjection<FastJets>(event,"Jets");
      const Jets alljets        = jetProj.jetsByPt(20*GeV);
      double event_ht           = 0;
      foreach(const Jet &j, alljets){ event_ht += j.pT()*GeV;}

      const double weight = event.weight();
      MSG_INFO("#----------------Event--------------#");

      //DO PDG analysis
      vector<HepMC::GenParticle*> genParticles = particles(event.genEvent());
      Particles zCands,wCands,bCands,topCands;

      foreach(const GenParticle *part, particles(event.genEvent()))
      {
          if(part->momentum().perp()*GeV >10 && fabs(part->momentum().eta()) <2.5)
          {
              //Select W-bosons
              if(fabs(part->pdg_id()) == 24)
              {
                  wCands.push_back(Particle(part));
              }
              if(fabs(part->pdg_id()) ==23)
              {
                  zCands.push_back(Particle(part));
              }
              if(fabs(part->pdg_id()) == 5)
              {
                  bCands.push_back(Particle(part));
              }
              if(fabs(part->pdg_id())==6)
              {
                  topCands.push_back(Particle(part));
              }
          }
      }
      
      Particles wBosons, zBosons_nunu,zBosons_qq, topQuarks, bQuarks;

      foreach (const Particle &W, wCands)
      {
          bool topToBWFound = false;
          foreach (const Particle &b, bCands)
          {
              GenVertex *bVert      = b.genParticle()->production_vertex();
              GenVertex *wVert      = W.genParticle()->production_vertex();
              for(GenVertex::particles_in_const_iterator bvIter = bVert->particles_in_const_begin(); bvIter != bVert->particles_in_const_end(); ++bvIter)
              {
                  for(GenVertex::particles_in_const_iterator wvIter = wVert->particles_in_const_begin();wvIter != wVert->particles_in_const_end(); ++wvIter)
                  {
                      GenParticle *bParent  = (*bvIter);
                      GenParticle *wParent  = (*wvIter);

                      foreach (const Particle &topQ, topCands)
                      {
                          if(topQ.genParticle()->barcode() == bParent->barcode() && topQ.genParticle()->barcode() == wParent->barcode())
                          {
                              topToBWFound = true;
                              //You found top->b,w vertex
                              topQuarks.push_back(topQ);
                              bQuarks.push_back(b);
                          }
                      }
                  }
              }
          }
          if(topToBWFound)
          {
              wBosons.push_back(W);
          }
      }


      foreach (const Particle &Z, zCands)
      {
          bool znuDecay     = false;
          bool zqqDecay     = false;
          
          GenVertex *zEndVert   = Z.genParticle()->end_vertex();
          for(GenVertex::particles_out_const_iterator ziter = zEndVert->particles_out_const_begin(); ziter != zEndVert->particles_out_const_end(); ++ziter)
          {
              int zchPdg =  abs((*ziter)->pdg_id());
              if(zchPdg ==12 || zchPdg ==14) 
              {
                  znuDecay = true;
                  break;
              }
              if(zchPdg ==1 || zchPdg ==2 || zchPdg ==3 || zchPdg ==4 || zchPdg ==5)
              {
                  zqqDecay = true;
              }
          }
          if(znuDecay)
          {
              zBosons_nunu.push_back(Z);
          }
          if(zqqDecay)
          {
              zBosons_qq.push_back(Z);
          }
      }

      sortByPt(topQuarks);
      sortByPt(bQuarks);
      sortByPt(wBosons);
      sortByPt(zBosons_nunu);
      sortByPt(zBosons_qq);

      if(topQuarks.size()==2 && wBosons.size()==2 && bQuarks.size()==2 && (zBosons_nunu.size() + zBosons_qq.size()) ==1 );
      {
          MSG_INFO("WCANDS size: "<< wCands.size());
          MSG_INFO("ZBOSONS Size: "<<zBosons_nunu.size() + zBosons_qq.size());
          MSG_INFO("WBOSONS Size: "<<wBosons.size());
          MSG_INFO("bQuarks Size: "<<wBosons.size());
          MSG_INFO("topQuarks Size: "<<topQuarks.size());
      }

      if(topQuarks.size()==2 && wBosons.size()==2 && bQuarks.size()==2 && (zBosons_nunu.size() + zBosons_qq.size())==1)
      {
          _h_top_dEta->fill(deltaEta(topQuarks[0],topQuarks[1]),weight);
          _h_top_dPhi->fill(deltaPhi(topQuarks[0],topQuarks[1]),weight);
          _h_top_dR->fill(deltaR(topQuarks[0],topQuarks[1]),weight);
        
          _h_t1_mass->fill(topQuarks[0].momentum().mass()*GeV,weight);
          _h_t1_pt->fill(topQuarks[0].momentum().perp()*GeV,weight);
          _h_t1_eta->fill(topQuarks[0].momentum().eta(),weight);
          _h_t1_phi->fill(topQuarks[0].momentum().phi(),weight);
          _h_t2_mass->fill(topQuarks[1].momentum().mass()*GeV,weight);
          _h_t2_pt->fill(topQuarks[1].momentum().perp()*GeV,weight);
          _h_t2_eta->fill(topQuarks[1].momentum().eta(),weight);
          _h_t2_phi->fill(topQuarks[1].momentum().phi(),weight);
          

          _h_b_dEta->fill(deltaEta(bQuarks[0],bQuarks[1]),weight);
          _h_b_dPhi->fill(deltaPhi(bQuarks[0],bQuarks[1]),weight);
          _h_b_dR->fill(deltaR(bQuarks[0],bQuarks[1]),weight);
          _h_b1_pt->fill(bQuarks[0].momentum().perp()*GeV,weight);
          _h_b1_eta->fill(bQuarks[0].momentum().eta(),weight);
          _h_b1_phi->fill(bQuarks[0].momentum().phi(),weight);
          _h_b2_pt->fill(bQuarks[1].momentum().perp()*GeV,weight);
          _h_b2_eta->fill(bQuarks[1].momentum().eta(),weight);
          _h_b2_phi->fill(bQuarks[1].momentum().phi(),weight);

          _h_w_dEta->fill(deltaEta(wBosons[0],wBosons[1]),weight);
          _h_w_dPhi->fill(deltaPhi(wBosons[0],wBosons[1]),weight);
          _h_w_dR->fill(deltaR(wBosons[0],wBosons[1]),weight);
          _h_w1_mass->fill(wBosons[0].momentum().mass()*GeV,weight);
          _h_w1_pt->fill(wBosons[0].momentum().perp()*GeV,weight);
          _h_w1_eta->fill(wBosons[0].momentum().eta(),weight);
          _h_w1_phi->fill(wBosons[0].momentum().phi(),weight);
          _h_w2_mass->fill(wBosons[1].momentum().mass()*GeV,weight);
          _h_w2_pt->fill(wBosons[1].momentum().perp()*GeV,weight);
          _h_w2_eta->fill(wBosons[1].momentum().eta(),weight);
          _h_w2_phi->fill(wBosons[1].momentum().phi(),weight);


          if(zBosons_nunu.size()>=1)
          {
              _h_zBosons_nunu_pt->fill(zBosons_nunu[0].momentum().perp()*GeV,weight);
              _h_zBosons_nunu_eta->fill(zBosons_nunu[0].momentum().eta(),weight);
              _h_zBosons_nunu_phi->fill(zBosons_nunu[0].momentum().phi(),weight);
              _h_znunu_MET->fill(event_met,weight);
              _h_znunu_HT->fill(event_ht,weight);
          }
          else if (zBosons_qq.size()>=1)
          {
              _h_zBosons_qq_pt->fill(zBosons_qq[0].momentum().perp()*GeV,weight);
              _h_zBosons_qq_eta->fill(zBosons_qq[0].momentum().eta(),weight);
              _h_zBosons_qq_phi->fill(zBosons_qq[0].momentum().phi(),weight);
              _h_zqq_MET->fill(event_met,weight);
              _h_zqq_HT->fill(event_ht,weight);
          }
      }
    }
     
    /// Normalise histograms etc., after the run
    void finalize() 
    {
        float norm  = crossSection()/sumOfWeights();
        scale(_h_znunu_MET,norm);
        scale(_h_zqq_MET,norm);
        scale(_h_znunu_HT,norm);
        scale(_h_zqq_HT,norm);
        scale(_h_t1_mass,norm);
        scale(_h_t2_mass,norm);
        scale(_h_t1_pt,norm);
        scale(_h_t2_pt,norm);
        scale(_h_t1_eta,norm);
        scale(_h_t2_eta,norm);
        scale(_h_t1_phi,norm);
        scale(_h_t2_phi,norm);
        scale(_h_b1_pt,norm);
        scale(_h_b1_eta,norm);
        scale(_h_b1_phi,norm);
        scale(_h_b2_pt,norm);
        scale(_h_b2_eta,norm);
        scale(_h_b2_phi,norm);
        scale(_h_w1_mass,norm);
        scale(_h_w2_mass,norm);
        scale(_h_w1_pt,norm);
        scale(_h_w2_pt,norm);
        scale(_h_w1_eta,norm);
        scale(_h_w2_eta,norm);
        scale(_h_w1_phi,norm);
        scale(_h_w2_phi,norm);

        //Delta distributions
        scale(_h_e_dEta,norm);
        scale(_h_e_dPhi,norm);
        scale(_h_e_dR,norm);
        scale(_h_mu_dEta,norm);
        scale(_h_mu_dPhi,norm);
        scale(_h_mu_dR,norm);

        scale(_h_top_dEta,norm);
        scale(_h_top_dPhi,norm);
        scale(_h_top_dR,norm);
        scale(_h_b_dEta,norm);
        scale(_h_b_dPhi,norm);
        scale(_h_b_dR,norm);
        scale(_h_w_dEta,norm);
        scale(_h_w_dPhi,norm);
        scale(_h_w_dR,norm);

        scale(_h_zBosons_nunu_pt,norm);
        scale(_h_zBosons_nunu_eta,norm);
        scale(_h_zBosons_nunu_phi,norm);
        scale(_h_zBosons_qq_pt,norm);
        scale(_h_zBosons_qq_eta,norm);
        scale(_h_zBosons_qq_phi,norm);
    }
    //@}


  private:

    // Data members like post-cuts event weight counters go here
    Histo1DPtr _h_znunu_MET,_h_zqq_MET;
    Histo1DPtr _h_znunu_HT,_h_zqq_HT;
    Histo1DPtr _h_t1_mass;
    Histo1DPtr _h_t2_mass;
    Histo1DPtr _h_t1_pt;
    Histo1DPtr _h_t2_pt;
    Histo1DPtr _h_t1_eta;
    Histo1DPtr _h_t2_eta;
    Histo1DPtr _h_t1_phi;
    Histo1DPtr _h_t2_phi;
    Histo1DPtr _h_b1_pt;
    Histo1DPtr _h_b1_eta;
    Histo1DPtr _h_b1_phi;
    Histo1DPtr _h_b2_pt;
    Histo1DPtr _h_b2_eta;
    Histo1DPtr _h_b2_phi;
    Histo1DPtr _h_w1_mass;
    Histo1DPtr _h_w2_mass;
    Histo1DPtr _h_w1_pt;
    Histo1DPtr _h_w2_pt;
    Histo1DPtr _h_w1_eta;
    Histo1DPtr _h_w2_eta;
    Histo1DPtr _h_w1_phi;
    Histo1DPtr _h_w2_phi;

    Histo1DPtr _h_e_dEta;
    Histo1DPtr _h_e_dPhi;
    Histo1DPtr _h_e_dR;
    Histo1DPtr _h_mu_dEta;
    Histo1DPtr _h_mu_dPhi;
    Histo1DPtr _h_mu_dR;

    Histo1DPtr _h_top_dEta;
    Histo1DPtr _h_top_dPhi;
    Histo1DPtr _h_top_dR;
    Histo1DPtr _h_b_dEta;
    Histo1DPtr _h_b_dPhi;
    Histo1DPtr _h_b_dR;
    Histo1DPtr _h_w_dEta;
    Histo1DPtr _h_w_dPhi;
    Histo1DPtr _h_w_dR;

    Histo1DPtr _h_zBosons_nunu_pt;
    Histo1DPtr _h_zBosons_nunu_eta;
    Histo1DPtr _h_zBosons_nunu_phi;
    Histo1DPtr _h_zBosons_qq_pt;
    Histo1DPtr _h_zBosons_qq_eta;
    Histo1DPtr _h_zBosons_qq_phi;

  };



  // The hook for the plugin system
  DECLARE_RIVET_PLUGIN(ttw_analysis);

}
