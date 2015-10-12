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
      : Analysis("ttw_analysis")
    {    }


    /// @name Analysis methods
    //@{

    /// Book histograms and initialise projections before the run
    void init() {

        _h_el_pt    = bookHisto1D("el_pt",200,10,410);
        _h_el_eta   = bookHisto1D("el_eta",100,-5,5);
        _h_el_mult  = bookHisto1D("el_mult",10,-0.5,9.5);
        _h_m_ee     = bookHisto1D("m_ee",100,5,145);

        _h_mu_pt    = bookHisto1D("mu_pt",200,10,410);
        _h_mu_eta   = bookHisto1D("mu_eta",100,-5,5);
        _h_mu_mult  = bookHisto1D("mu_mult",10,-0.5,9.5);
        _h_m_mumu   = bookHisto1D("m_mumu",100,5,145);

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
        
    }


    /// Perform the per-event analysis
    void analyze(const Event& event) {
      const double weight = event.weight();
      MSG_INFO("#----------------Event--------------#");

      //DO PDG analysis
      vector<HepMC::GenParticle*> genParticles = particles(event.genEvent());
      Particles electrons,muons
      Particles wCands,bCands,topCands;

      foreach(const GenParticle *part, particles(event.genEvent()))
      {
          if(part->momentum().perp()*GeV >10 && fabs(part->momentum().eta()) <2.5)
          {
              if(fabs(part->pdg_id()) ==11 && part->status()==1 && part->momentum().perp()*GeV >10 )
              {
                  GenVertex  * pv = part->production_vertex();
                  for(GenVertex::particles_in_const_iterator iter = pv->particles_in_const_begin(); iter != pv->particles_in_const_end();++iter)
                  {
                      if(abs((*iter)->pdg_id())!=5) //Make sure that the lepton parent is not a b
                      {
                          electrons.push_back(Particle(part));
                          _h_el_pt->fill(part->momentum().perp()*GeV,weight);
                          _h_el_eta->fill(part->momentum().eta(),weight);
                      }
                  }
              }
              if(fabs(part->pdg_id())==13 && part->status()==1 && part->momentum().perp()*GeV >10)
              {
                  GenVertex *pv = part->production_vertex();
                  for(GenVertex::particles_in_const_iterator iter = pv->particles_in_const_begin(); iter!= pv->particles_in_const_end(); ++iter)
                  {
                      if(abs((*iter)->pdg_id())!=5)
                      {
                          muons.push_back(Particle(part));
                          _h_mu_pt->fill(part->momentum().perp()*GeV,weight);
                          _h_mu_eta->fill(part->momentum().eta(),weight);
                      }
                  }
              }
              //Select W-bosons
              if(fabs(part->pdg_id()) == 24)
              {
                  wCands.push_back(Particle(part));
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
      
      //Electrons and muons
      _h_el_mult->fill(ePlus.size() + eMinus.size(),weight);
      _h_mu_mult->fill(muPlus.size() + muMinus.size(),weight);
      std::sort(ePlus.begin(),ePlus.end(),cmpMomByPt);
      std::sort(eMinus.begin(),eMinus.end(),cmpMomByPt);
      std::sort(muPlus.begin(),muPlus.end(),cmpMomByPt);
      std::sort(muMinus.begin(),muMinus.end(),cmpMomByPt);
      if(ePlus.size() >=1 && eMinus.size() >=1)
      {
          _h_m_ee->fill((ePlus[0].momentum() + eMinus[0].momentum()).mass(),weight);
          _h_e_dEta->fill(deltaEta(ePlus[0],eMinus[0]),weight);
          _h_e_dPhi->fill(deltaPhi(ePlus[0],eMinus[0]),weight);
          _h_e_dR->fill(deltaR(ePlus[0],eMinus[0]),weight);
      }
      if(muPlus.size() >=1 && muMinus.size() >=1)
      {
          _h_m_mumu->fill((muPlus[0].momentum() + muMinus[0].momentum()).mass(),weight);
          _h_mu_dEta->fill(deltaEta(muPlus[0],muMinus[0]),weight);
          _h_mu_dPhi->fill(deltaPhi(muPlus[0],muMinus[0]),weight);
          _h_mu_dR->fill(deltaR(muPlus[0],muMinus[0]),weight);
      }

      Particles wBosons, topQuarks, bQuarks;

      foreach( const Particle& topQ, topCands)
      {
          foreach (const Particle &W, wCands)
          {
              foreach (const Particle &b, bCands)
              {
                  GenVertex *bVert = b.genParticle()->production_vertex();
                  GenVertex *wVert = W.genParticle()->production_vertex();
                  for(GenVertex::particles_in_const_iterator bvIter = bVert->particles_in_const_begin(); bvIter != bVert->particles_in_const_end(); ++bvIter)
                  {
                      for(GenVertex::particles_in_const_iterator wvIter = wVert->particles_in_const_begin();wvIter != wVert->particles_in_const_end(); ++wvIter)
                      {
                          GenParticle *bParent  = (*bvIter);
                          GenParticle *wParent  = (*wvIter);


                          if(topQ.genParticle()->barcode() == bParent->barcode() && topQ.genParticle()->barcode() == wParent->barcode())
                          {
                              //You found top->b,w vertex
                              topQuarks.push_back(topQ);
                              wBosons.push_back(W);
                              bQuarks.push_back(b);
                          }
                      }
                  }
              }
          }
      }

      sortByPt(topQuarks);
      sortByPt(bQuarks);
      sortByPt(wBosons);

      if(topQuarks.size()==2 && wBosons.size()==2 && bQuarks.size()==2)
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
      }

                      
    }
     
    /// Normalise histograms etc., after the run
    void finalize() 
    {
        float norm  = crossSection()/sumOfWeights();
        scale(_h_el_pt,norm);
        scale(_h_el_eta,norm);
        scale(_h_mu_pt,norm);
        scale(_h_mu_eta,norm);
        scale(_h_el_mult,norm);
        scale(_h_mu_mult,norm);
        scale(_h_m_ee,norm);
        scale(_h_m_mumu,norm);

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
    }
    //@}


  private:

    // Data members like post-cuts event weight counters go here
    Histo1DPtr _h_el_pt, _h_el_eta;
    Histo1DPtr _h_mu_pt, _h_mu_eta;
    Histo1DPtr _h_el_mult,_h_mu_mult;
    Histo1DPtr _h_m_ee,_h_m_mumu;

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

  };



  // The hook for the plugin system
  DECLARE_RIVET_PLUGIN(ttw_analysis);

}
