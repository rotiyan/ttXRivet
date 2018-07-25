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



//MARIA (ToDo)
// RIVETanalysis: add histos for ttW_pt/eta/rap, tt_eta/rap (pt already exists)
// For the analysis, will spit into two ttW channels: 3l (with dilepton tt: TopDil_Lep1, TopDil_Lep2) and 2lSS (with lep+jets tt: TopLJets_Lep, TopLJets_Had)


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

        addProjection(FastJets(FinalState(-2.5,2.5,25*GeV),FastJets::ANTIKT,0.4),"Jets");
        addProjection(MissingMomentum(FinalState(-4,4,0*GeV)),"MissingET");


        _h_wPlus_MET= bookHisto1D("wPlus_MET",100,50,450);
        _h_wMinus_MET=bookHisto1D("wMinus_MET",100,50,450);
        _h_wPlus_HT = bookHisto1D("wPlus_HT",100,50,1050);
        _h_wMinus_HT= bookHisto1D("wMinus_HT",100,50,1050);
        _h_wPlus_nJets = bookHisto1D("wPlus_nJets",11,-0.5,10.5);
        _h_wMinus_nJets= bookHisto1D("wMinus_nJets",11,-0.5,10.5);
        _h_nJets    = bookHisto1D("event_nJets",11,-0.5,10.5);
	    _h_matchedjets_N = bookHisto1D("event_nMatchedJets",11,-0.5,10.5);
	    _h_matchedjets_pT    = bookHisto1D("matchedjets_pT",100,50,450);
        _h_ttbar_pt = bookHisto1D("ttbar_pt",150,130,430);
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

	//MARIA
        _h_lep1_mass  = bookHisto1D("lep1_mass",100,0,120);
        _h_lep2_mass  = bookHisto1D("lep2_mass",100,0,120);
        _h_lep1_pt    = bookHisto1D("lep1_pt",100,0,400);
        _h_lep2_pt    = bookHisto1D("lep2_pt",100,0,400);
        _h_lep1_eta   = bookHisto1D("lep1_eta",100,-5,5);
        _h_lep2_eta   = bookHisto1D("lep2_eta",100,-5,5);
        _h_lep1_phi   = bookHisto1D("lep1_phi",100,-5,5);
        _h_lep2_phi   = bookHisto1D("lep2_phi",100,-5,5);

        _h_lightq1_mass  = bookHisto1D("lightq1_mass",100,0,120);
        _h_lightq2_mass  = bookHisto1D("lightq2_mass",100,0,120);
        _h_lightq1_pt    = bookHisto1D("lightq1_pt",100,0,400);
        _h_lightq2_pt    = bookHisto1D("lightq2_pt",100,0,400);
        _h_lightq1_eta   = bookHisto1D("lightq1_eta",100,-5,5);
        _h_lightq2_eta   = bookHisto1D("lightq2_eta",100,-5,5);
        _h_lightq1_phi   = bookHisto1D("lightq1_phi",100,-5,5);
        _h_lightq2_phi   = bookHisto1D("lightq2_phi",100,-5,5);
   
        
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

	//MARIA
        _h_lep_dEta   = bookHisto1D("lep_dEta",100,0,7);
        _h_lep_dPhi   = bookHisto1D("lep_dPhi",100,0,7);
        _h_lep_dR     = bookHisto1D("lep_dR",100,0,7);
        _h_lightq_dEta   = bookHisto1D("lightq_dEta",100,0,7);
        _h_lightq_dPhi   = bookHisto1D("lightq_dPhi",100,0,7);
        _h_lightq_dR     = bookHisto1D("lightq_dR",100,0,7);
        
        _h_b_dEta   = bookHisto1D("b_dEta",100,0,7);
        _h_b_dPhi   = bookHisto1D("b_dPhi",100,0,7);
        _h_b_dR     = bookHisto1D("b_dR",100,0,7);

        _h_wPlusME_pt = bookHisto1D("wPlus_pt",100,0,400);
        _h_wPlusME_eta= bookHisto1D("WPlus_eta",100,-5,5);
        _h_wPlusME_phi= bookHisto1D("WPlus_phi",100,-5,5);

        _h_wMinusME_pt = bookHisto1D("wMinus_pt",100,0,400);
        _h_wMinusME_eta= bookHisto1D("WMinus_eta",100,-5,5);
        _h_wMinusME_phi= bookHisto1D("WMinus_phi",100,-5,5);
 
        
    }


    /// Perform the per-event analysis
    void analyze(const Event& event) {

      const double weight = event.weight();

      MSG_INFO("#----------------Event--------------#");

      //DO PDG analysis
      vector<const HepMC::GenParticle*> genParticles = particles(event.genEvent());
      Particles wCands,bCands,topCands;

      foreach(const GenParticle *part, particles(event.genEvent()))
      {
          if(part->momentum().perp()*GeV >10 && fabs(part->momentum().eta()) <2.5)
          {
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
      
      Particles wBosons, wBosonsME, topQuarks, bQuarks, LepfromWTop, LightQuarkfromWTop;

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


      foreach (const Particle &W, wCands)
      {
          bool wlepDecay = false;
	      bool whadDecay = false; //MARIA
          bool noTopParent = false;
          //GenVertex *wVert      = W.genParticle()->production_vertex();
          GenVertex *wEndVert   = W.genParticle()->end_vertex();

          foreach (const Particle &topW, wBosons)
          {
              if(topW.genParticle() != W.genParticle())
              {
                  noTopParent = true;
              }
          }

          /*for(GenVertex::particles_in_const_iterator wvIter = wVert->particles_in_const_begin(); wvIter != wVert->particles_in_const_end(); ++wvIter)
          {
              GenParticle *wParent = (*wvIter);
              if(abs(wParent->pdg_id())!=6 || abs(wParent->pdg_id())!= 24);
              {
                  noTopParent = true;
                  break;
              }
          }*/
          
          for(GenVertex::particles_out_const_iterator witer = wEndVert->particles_out_const_begin(); witer != wEndVert->particles_out_const_end(); ++witer)
          {
              int wchPdg =  abs((*witer)->pdg_id());
              if(wchPdg ==11 || wchPdg ==12 || wchPdg ==13 || wchPdg ==14) 
              {
                  wlepDecay = true;
		         if (!noTopParent) 
                 {
                    LepfromWTop.push_back(*witer);//MARIA (two entries per event)
                    break; //Why break ?
                 }
              }
	          else if(wchPdg ==1 || wchPdg ==2 || wchPdg ==3 || wchPdg ==4) { //MARIA (two entries per event)
                  whadDecay = true;
		          LightQuarkfromWTop.push_back(*witer);//will match with particle-level jets
                  break;
              }
          }

	      //associated W from ME
          if(wlepDecay && noTopParent)
          {
              wBosonsME.push_back(W);
          }
	  
      }//end Wcand loop
    
      sortByPt(topQuarks);
      sortByPt(bQuarks);
      sortByPt(wBosons);
      sortByPt(wBosonsME);
      sortByPt(LepfromWTop);//MARIA
      sortByPt(LightQuarkfromWTop);//MARIA



      const MissingMomentum &met= applyProjection<MissingMomentum>(event,"MissingET");
      const double event_met    = met.vectorEt().mod()*GeV;
  
      
      const FastJets & jetProj  = applyProjection<FastJets>(event,"Jets");
      const Jets alljets        = jetProj.jetsByPt(25*GeV);
      double event_ht           = 0;
      foreach(const Jet &j, alljets){ event_ht += j.pT()*GeV;}

      _h_nJets->fill(alljets.size(),weight);

      // dR (quarks & jets) -- bQuarks,
      Jets _lightjetsMatchedToLightQ; 
      foreach (const Jet& _jet, alljets) {
	if (fabs(_jet.eta()) < 2.5) {
	  // jet B-hadron matching
	  foreach (const Particle &quark, LightQuarkfromWTop) {
	    FourMomentum _quarkfm = quark.momentum();
	    double _quark_jet_dR = deltaR(_jet.momentum(), _quarkfm);
	    if(_quark_jet_dR < 0.4) {
	      _lightjetsMatchedToLightQ.push_back(_jet);
	      _h_matchedjets_pT->fill(_jet.momentum().pT()/GeV, weight);
	    }
	    continue;
	  }
	}
      }
      _h_matchedjets_N->fill(_lightjetsMatchedToLightQ.size(),weight);

    
      MSG_INFO("WCandSize: "<<wCands.size() );
      MSG_INFO("wBosonsSize: "<<wBosons.size());
      MSG_INFO("bQuarksSize: "<<bQuarks.size());
      MSG_INFO("wBosonsMESize" <<wBosonsME.size());
      MSG_INFO("LepFromWTOP" <<LepfromWTop.size());
      MSG_INFO("LightQuarkfromWTop" <<LightQuarkfromWTop.size());

      if(topQuarks.size()==2 && wBosons.size()==2 && bQuarks.size()==2 && wBosonsME.size()==1 && (LepfromWTop.size() >=1 && LightQuarkfromWTop.size() >=2 ) )
      {
          MSG_INFO("WCANDS size: "<< wCands.size());
          MSG_INFO("WBOSONSME Size: "<<wBosonsME.size());
          MSG_INFO("WBOSONS Size: "<<wBosons.size());
          MSG_INFO("bQuarks Size: "<<wBosons.size());
          MSG_INFO("topQuarks Size: "<<topQuarks.size());
	      MSG_INFO("LepfromWTop Size: "<<LepfromWTop.size());
	      MSG_INFO("LightQuarkfromWTop Size: "<<LightQuarkfromWTop.size());
      }

      if(topQuarks.size()==2 && wBosons.size()==2 && bQuarks.size()==2 && wBosonsME.size()==1 && (LepfromWTop.size() >=1 && LightQuarkfromWTop.size() >=2) )
      {
          _h_top_dEta->fill(deltaEta(topQuarks[0],topQuarks[1]),weight);
          _h_top_dPhi->fill(deltaPhi(topQuarks[0],topQuarks[1]),weight);
          _h_top_dR->fill(deltaR(topQuarks[0],topQuarks[1]),weight);
        
          _h_ttbar_pt->fill( (topQuarks[0].momentum() + topQuarks[1].momentum()).perp()*GeV,weight);
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

	  //MARIA
          _h_lep_dEta->fill(deltaEta(LepfromWTop[0],LepfromWTop[1]),weight);
          _h_lep_dPhi->fill(deltaPhi(LepfromWTop[0],LepfromWTop[1]),weight);
          _h_lep_dR->fill(deltaR(LepfromWTop[0],LepfromWTop[1]),weight);
          _h_lep1_mass->fill(LepfromWTop[0].momentum().mass()*GeV,weight);
          _h_lep1_pt->fill(LepfromWTop[0].momentum().perp()*GeV,weight);
          _h_lep1_eta->fill(LepfromWTop[0].momentum().eta(),weight);
          _h_lep1_phi->fill(LepfromWTop[0].momentum().phi(),weight);
          _h_lep2_mass->fill(LepfromWTop[1].momentum().mass()*GeV,weight);
          _h_lep2_pt->fill(LepfromWTop[1].momentum().perp()*GeV,weight);
          _h_lep2_eta->fill(LepfromWTop[1].momentum().eta(),weight);
          _h_lep2_phi->fill(LepfromWTop[1].momentum().phi(),weight);

	  //MARIA
          _h_lightq_dEta->fill(deltaEta(LightQuarkfromWTop[0],LightQuarkfromWTop[1]),weight);
          _h_lightq_dPhi->fill(deltaPhi(LightQuarkfromWTop[0],LightQuarkfromWTop[1]),weight);
          _h_lightq_dR->fill(deltaR(LightQuarkfromWTop[0],LightQuarkfromWTop[1]),weight);
          _h_lightq1_mass->fill(LightQuarkfromWTop[0].momentum().mass()*GeV,weight);
          _h_lightq1_pt->fill(LightQuarkfromWTop[0].momentum().perp()*GeV,weight);
          _h_lightq1_eta->fill(LightQuarkfromWTop[0].momentum().eta(),weight);
          _h_lightq1_phi->fill(LightQuarkfromWTop[0].momentum().phi(),weight);
          _h_lightq2_mass->fill(LightQuarkfromWTop[1].momentum().mass()*GeV,weight);
          _h_lightq2_pt->fill(LightQuarkfromWTop[1].momentum().perp()*GeV,weight);
          _h_lightq2_eta->fill(LightQuarkfromWTop[1].momentum().eta(),weight);
          _h_lightq2_phi->fill(LightQuarkfromWTop[1].momentum().phi(),weight);


          if(wBosonsME[0].genParticle()->pdg_id()==24)
          {
              _h_wPlusME_pt->fill(wBosonsME[0].momentum().perp()*GeV,weight);
              _h_wPlusME_eta->fill(wBosonsME[0].momentum().eta(),weight);
              _h_wPlusME_phi->fill(wBosonsME[0].momentum().phi(),weight);

              _h_wPlus_nJets->fill(alljets.size(),weight);
              _h_wPlus_MET->fill(event_met,weight);
              _h_wPlus_HT->fill(event_ht,weight);
          }
          else if (wBosonsME[0].genParticle()->pdg_id()==-24)
          {
              _h_wMinusME_pt->fill(wBosonsME[0].momentum().perp()*GeV,weight);
              _h_wMinusME_eta->fill(wBosonsME[0].momentum().eta(),weight);
              _h_wMinusME_phi->fill(wBosonsME[0].momentum().phi(),weight);

              _h_wMinus_nJets->fill(alljets.size(),weight);
              _h_wMinus_MET->fill(event_met,weight);
              _h_wMinus_HT->fill(event_ht,weight);
          }
      }
    }
     
    /// Normalise histograms etc., after the run
    void finalize() 
    {
        float norm  = crossSection()/sumOfWeights();
        scale(_h_wPlus_MET,norm);
        scale(_h_wMinus_MET,norm);
        scale(_h_wPlus_HT,norm);
        scale(_h_wMinus_HT,norm);
        scale(_h_wPlus_nJets,norm);
        scale(_h_wMinus_nJets,norm);
        scale(_h_ttbar_pt,norm);
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

	//MARIA
        scale(_h_lep1_mass,norm);
        scale(_h_lep2_mass,norm);
        scale(_h_lep1_pt,norm);
        scale(_h_lep2_pt,norm);
        scale(_h_lep1_eta,norm);
        scale(_h_lep2_eta,norm);
        scale(_h_lep1_phi,norm);
        scale(_h_lep2_phi,norm);
        scale(_h_lightq1_mass,norm);
        scale(_h_lightq2_mass,norm);
        scale(_h_lightq1_pt,norm);
        scale(_h_lightq2_pt,norm);
        scale(_h_lightq1_eta,norm);
        scale(_h_lightq2_eta,norm);
        scale(_h_lightq1_phi,norm);
        scale(_h_lightq2_phi,norm);

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
	//MARIA
        scale(_h_lep_dEta,norm);
        scale(_h_lep_dPhi,norm);
        scale(_h_lep_dR,norm);
        scale(_h_lightq_dEta,norm);
        scale(_h_lightq_dPhi,norm);
        scale(_h_lightq_dR,norm);

        scale(_h_wPlusME_pt,norm);
        scale(_h_wPlusME_eta,norm);
        scale(_h_wPlusME_phi,norm);
        scale(_h_wMinusME_pt,norm);
        scale(_h_wMinusME_eta,norm);
        scale(_h_wMinusME_phi,norm);

	    scale(_h_nJets,norm);
	    scale(_h_matchedjets_N,norm);
	    scale(_h_matchedjets_pT,norm);
    }
    //@}


  private:

    // Data members like post-cuts event weight counters go here
    Histo1DPtr _h_wPlus_MET,_h_wMinus_MET;
    Histo1DPtr _h_wPlus_HT,_h_wMinus_HT;
    Histo1DPtr _h_wPlus_nJets,_h_wMinus_nJets,_h_nJets;
    Histo1DPtr _h_matchedjets_N,_h_matchedjets_pT;
    Histo1DPtr _h_ttbar_pt;
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

    //MARIA
    Histo1DPtr _h_lep1_mass;
    Histo1DPtr _h_lep2_mass;
    Histo1DPtr _h_lep1_pt;
    Histo1DPtr _h_lep2_pt;
    Histo1DPtr _h_lep1_eta;
    Histo1DPtr _h_lep2_eta;
    Histo1DPtr _h_lep1_phi;
    Histo1DPtr _h_lep2_phi;

    Histo1DPtr _h_lightq1_mass;
    Histo1DPtr _h_lightq2_mass;
    Histo1DPtr _h_lightq1_pt;
    Histo1DPtr _h_lightq2_pt;
    Histo1DPtr _h_lightq1_eta;
    Histo1DPtr _h_lightq2_eta;
    Histo1DPtr _h_lightq1_phi;
    Histo1DPtr _h_lightq2_phi;

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

    //MARIA
    Histo1DPtr _h_lep_dEta;
    Histo1DPtr _h_lep_dPhi;
    Histo1DPtr _h_lep_dR;
    Histo1DPtr _h_lightq_dEta;
    Histo1DPtr _h_lightq_dPhi;
    Histo1DPtr _h_lightq_dR;

    Histo1DPtr _h_wPlusME_pt;
    Histo1DPtr _h_wPlusME_eta;
    Histo1DPtr _h_wPlusME_phi;
    Histo1DPtr _h_wMinusME_pt;
    Histo1DPtr _h_wMinusME_eta;
    Histo1DPtr _h_wMinusME_phi;

  };



  // The hook for the plugin system
  DECLARE_RIVET_PLUGIN(ttw_analysis);

}
