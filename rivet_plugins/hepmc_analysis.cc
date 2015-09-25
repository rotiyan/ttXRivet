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
        _h_m_mumu    = bookHisto1D("m_mumu",100,5,145);
        
    }


    /// Perform the per-event analysis
    void analyze(const Event& event) {
      const double weight = event.weight();

      //DO PDG analysis
      vector<HepMC::GenParticle*> genParticles = particles(event.genEvent());


      Particles ePlus,eMinus,muPlus,muMinus;

      for(size_t i = 0; i < genParticles.size(); ++i)
      {
          GenParticle * part = genParticles.at(i);
          if(fabs(part->pdg_id())==6 )
          {
              //MSG_INFO("Status of top : "<<part->status() );
          }
          if(fabs(part->pdg_id()) ==11 && part->status()==1 && part->momentum().perp()*GeV > 10)
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
                      MSG_INFO("pt: "<<part->momentum().perp()*GeV);
                      MSG_INFO("eta: "<<part->momentum().eta());
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
      }
      MSG_INFO("Electron Multiplicity: "<<ePlus.size() + eMinus.size() );
      _h_el_mult->fill(ePlus.size() + eMinus.size(),weight);
      _h_mu_mult->fill(muPlus.size() + muMinus.size(),weight);
      std::sort(ePlus.begin(),ePlus.end(),cmpMomByPt);
      std::sort(eMinus.begin(),eMinus.end(),cmpMomByPt);
      std::sort(muPlus.begin(),muPlus.end(),cmpMomByPt);
      std::sort(muMinus.begin(),muMinus.end(),cmpMomByPt);
      if(ePlus.size() >=1 && eMinus.size() >=1)
      {
          _h_m_ee->fill((ePlus[0].momentum() + eMinus[0].momentum()).mass(),weight);
      }
      if(muPlus.size() >=1 && muMinus.size() >=1)
      {
          _h_m_mumu->fill((muPlus[0].momentum() + muMinus[0].momentum()).mass(),weight);
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
    }
    //@}


  private:

    // Data members like post-cuts event weight counters go here
    Histo1DPtr _h_el_pt, _h_el_eta;
    Histo1DPtr _h_mu_pt, _h_mu_eta;
    Histo1DPtr _h_el_mult,_h_mu_mult;
    Histo1DPtr _h_m_ee,_h_m_mumu;

  };



  // The hook for the plugin system
  DECLARE_RIVET_PLUGIN(hepmc_analysis);

}
