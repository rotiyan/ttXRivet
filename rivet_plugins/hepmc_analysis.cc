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

        _h_el_pt    = bookHisto1D("el_pt",200,10,410);
        _h_el_eta   = bookHisto1D("el_eta",100,-5,5);
        _h_el_mult  = bookHisto1D("el_mult",10,-0.5,9.5);
        _h_m_ee     = bookHisto1D("m_ee",100,5,145);

        _h_mu_pt    = bookHisto1D("mu_pt",200,10,410);
        _h_mu_eta   = bookHisto1D("mu_eta",100,-5,5);
        _h_mu_mult  = bookHisto1D("mu_mult",10,-0.5,9.5);
        _h_m_mumu   = bookHisto1D("m_mumu",100,5,145);

        _h_t_mass   = bookHisto1D("t_mass",150,130,430);
        _h_t_pt     = bookHisto1D("t_pt",100,0,20);
        _h_t_eta    = bookHisto1D("t_eta",100,-5,5);
        _h_t_phi    = bookHisto1D("t_phi",50,0,6);
        _h_b1_pt    = bookHisto1D("b1_pt",100,0,400);
        _h_b2_pt    = bookHisto1D("b2_pt",100,0,400);
        _h_w_mass   = bookHisto1D("w_mass",120,5,115);
        _h_w_pt     = bookHisto1D("w_pt",100,0,400);
        _h_w_eta    = bookHisto1D("w_eta",100,-5,5);
        _h_w_phi    = bookHisto1D("w_phi",50,0,6);

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
      Particles ePlus,eMinus,muPlus,muMinus;
      Particles bPairContainer;
      Particles wPairContainer;
      Particles topPairContainer;

      for(size_t i = 0; i < genParticles.size(); ++i)
      {
          GenParticle * part = genParticles.at(i);
          if(fabs(part->pdg_id())==6 && part->momentum().perp()*GeV >10 && abs(part->momentum().eta()) <5)
          {
              //MSG_INFO("Status of top : "<<part->status() );
          }
          if(fabs(part->pdg_id()) ==11 && part->status()==1 )
          {
              GenVertex  * pv = part->production_vertex();
              for(GenVertex::particles_in_const_iterator iter = pv->particles_in_const_begin(); iter != pv->particles_in_const_end();++iter)
              {
                  if( abs((*iter)->pdg_id())!=24) //Make sure that the lepton parent is not a W
                  {
                      if(part->pdg_id()==11)
                          ePlus.push_back(Particle(part));
                      else if (part->pdg_id()==-11)
                          eMinus.push_back(Particle(part));
                      
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
                  if(abs((*iter)->pdg_id())!=24)
                  {
                      if(part->pdg_id()==13)
                          muMinus.push_back(Particle(part));
                      else if (part->pdg_id()==-13)
                          muPlus.push_back(Particle(part));
                  }
              }
          }
          if(fabs(part->pdg_id()==6))
          {
              GenVertex* ev = part->end_vertex();

              bool foundTopTo_b = false;
              bool foundTopTo_w = false;
              Particles b_fromTop,w_fromTop;
              for(GenVertex::particles_in_const_iterator iter = ev->particles_out_const_begin(); iter !=ev->particles_out_const_end(); ++iter)
              {
                  if(abs((*iter)->pdg_id()) ==6)
                      continue;

                  MSG_INFO("Daughters of top"<< (*iter)->pdg_id());
                  if(abs((*iter)->pdg_id())==5)
                  {
                      b_fromTop.push_back(Particle(*iter));
                      foundTopTo_b = true;
                  }
                  if(abs((*iter)->pdg_id())==24)
                  {
                      w_fromTop.push_back(Particle(*iter));
                      foundTopTo_w=true;
                  }
              }
              if(foundTopTo_b  && foundTopTo_w)
              {
                  topPairContainer.push_back(Particle(part));
                  bPairContainer.push_back(b_fromTop[0]);
                  wPairContainer.push_back(w_fromTop[0]);
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

      //b-s,w-s and top-s
      if(topPairContainer.size()==2)
      {
          _h_top_dEta->fill(deltaEta(topPairContainer[0],topPairContainer[1]),weight);
          _h_top_dPhi->fill(deltaPhi(topPairContainer[0],topPairContainer[1]),weight);
          _h_top_dR->fill(deltaR(topPairContainer[0],topPairContainer[1]),weight);
      }
      if(bPairContainer.size()==2)
      {
          _h_b_dEta->fill(deltaEta(bPairContainer[0],bPairContainer[1]),weight);
          _h_b_dPhi->fill(deltaPhi(bPairContainer[0],bPairContainer[1]),weight);
          _h_b_dR->fill(deltaR(bPairContainer[0],bPairContainer[1]),weight);
      }
      if(wPairContainer.size()==2)
      {
          _h_w_dEta->fill(deltaEta(wPairContainer[0],wPairContainer[1]),weight);
          _h_w_dPhi->fill(deltaPhi(wPairContainer[0],wPairContainer[1]));
          _h_w_dR->fill(deltaR(wPairContainer[0],wPairContainer[1]));
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

        scale(_h_t_mass,norm);
        scale(_h_t_pt,norm);
        scale(_h_t_eta,norm);
        scale(_h_t_phi,norm);
        scale(_h_b1_pt,norm);
        scale(_h_b2_pt,norm);
        scale(_h_w_mass,norm);
        scale(_h_w_pt,norm);
        scale(_h_w_eta,norm);
        scale(_h_w_phi,norm);

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

    Histo1DPtr _h_t_mass;
    Histo1DPtr _h_t_pt;
    Histo1DPtr _h_t_eta;
    Histo1DPtr _h_t_phi;
    Histo1DPtr _h_b1_pt;
    Histo1DPtr _h_b2_pt;
    Histo1DPtr _h_w_mass;
    Histo1DPtr _h_w_pt;
    Histo1DPtr _h_w_eta;
    Histo1DPtr _h_w_phi;

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
  DECLARE_RIVET_PLUGIN(hepmc_analysis);

}
