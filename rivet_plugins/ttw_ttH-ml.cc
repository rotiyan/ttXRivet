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
#include "Rivet/Projections/WFinder.hh"
#include "Rivet/AnalysisLoader.hh"

#include <numeric>
#include <functional>

/* 
 * Author : Rohin Narayan (narayan@cern.ch) 
 *
 *
 * This rivet can be compared to a  simple phasespace equivalent to the the region definitions in the ttH-ML analysis. 
 * The histograms need to be normalized to appropriate cross-section and total event weights. In an ATLAS environment
 * these histograms gets converted to ROOT format and the normalizations and handled by a subsequent script outside rivet.  
 *
 *
 */

namespace Rivet {

  
  class ttw_ttH: public Analysis {
  public:

    /// Minimal constructor
    ttw_ttH() : Analysis("ttw_ttH")
    {
    }

    /// Set up projections and book histograms
    void init() {
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

        
      TauFinder tauhadronic(TauFinder::HADRONIC);
      addProjection(tauhadronic,"TauHadronic");


      addProjection(HeavyHadrons(Cuts::abseta < 5 && Cuts::pT > 5*GeV), "BCHadrons");
      addProjection(FastJets(FinalState(-2.5,2.5,25*GeV),FastJets::ANTIKT,0.4),"Jets");
      addProjection(MissingMomentum(FinalState(-5,5,0*GeV)),"MissingET");


      //Histogramming 
      _h_sumOfWeights			= bookHisto1D("sumOfWeights",2,0,2);
      _h_2lSS0tau_MET			= bookHisto1D("2lSS0tau_MET",50,0,500);
      _h_2lSS1tau_MET			= bookHisto1D("2lSS1tau_MET",50,0,500);

      _h_2lSS0tau_region1_nJets  	= bookHisto1D("2lSS0tau_region1_nJets",10,-0.5,9.5);
      _h_2lSS0tau_region1_HT	    	= bookHisto1D("2lSS0tau_region1_HT",100,0,2000);
      _h_2lSS0tau_region1_nBjets  	= bookHisto1D("2lSS0tau_region1_nBjets",4,-0.5,3.5);
      _h_2lSS0tau_region1_bjet0pT 	= bookHisto1D("2lSS0tau_region1_bjet0Pt",50,0,500);
      _h_2lSS0tau_region1_lep0pT  	= bookHisto1D("2lSS0tau_region1_lep0Pt",40,0,800);
      _h_2lSS0tau_region1_lepJetMinDR 	= bookHisto1D("2lSS0tau_region1_lepJetminDR",5,0,0.5);
      _h_2lSS0tau_region1_DR_lep01 	= bookHisto1D("2lSS0tau_region1_DR_lep01",10,0,2*M_PI);
      _h_2lSS0tau_region1_DEta_lep01  	= bookHisto1D("2lSS0tau_region1_DEta_lep01",10,0,2*M_PI);
      _h_2lSS0tau_region1_DPhi_lep01 	= bookHisto1D("2lSS0tau_region1_DPhi_lep01",10,0,2*M_PI);

      _h_2lSS0tau_region2_nJets  	= bookHisto1D("2lSS0tau_region2_nJets",10,-0.5,9.5);
      _h_2lSS0tau_region2_HT	    	= bookHisto1D("2lSS0tau_region2_HT",100,0,2000);
      _h_2lSS0tau_region2_nBjets  	= bookHisto1D("2lSS0tau_region2_nBjets",4,-0.5,3.5);
      _h_2lSS0tau_region2_bjet0pT 	= bookHisto1D("2lSS0tau_region2_bjet0Pt",50,0,500);
      _h_2lSS0tau_region2_lep0pT  	= bookHisto1D("2lSS0tau_region2_lep0Pt",40,0,800);
      _h_2lSS0tau_region2_lepJetMinDR 	= bookHisto1D("2lSS0tau_region2_lepJetminDR",5,0,0.5);
      _h_2lSS0tau_region2_DR_lep01 	= bookHisto1D("2lSS0tau_region2_DR_lep01",10,0,2*M_PI);
      _h_2lSS0tau_region2_DEta_lep01	= bookHisto1D("2lSS0tau_region2_DEta_lep01",10,0,2*M_PI);
      _h_2lSS0tau_region2_DPhi_lep01 	= bookHisto1D("2lSS0tau_region2_DPhi_lep01",10,0,2*M_PI);

      _h_2lSS0tau_region3_nJets  	= bookHisto1D("2lSS0tau_region3_nJets",10,-0.5,9.5);
      _h_2lSS0tau_region3_HT	    	= bookHisto1D("2lSS0tau_region3_HT",100,0,2000);
      _h_2lSS0tau_region3_nBjets  	= bookHisto1D("2lSS0tau_region3_nBjets",4,-0.5,3.5);
      _h_2lSS0tau_region3_bjet0pT 	= bookHisto1D("2lSS0tau_region3_bjet0Pt",50,0,500);
      _h_2lSS0tau_region3_lep0pT  	= bookHisto1D("2lSS0tau_region3_lep0Pt",40,0,800);
      _h_2lSS0tau_region3_lepJetMinDR 	= bookHisto1D("2lSS0tau_region3_lepJetminDR",5,0,0.5);
      _h_2lSS0tau_region3_DR_lep01 	= bookHisto1D("2lSS0tau_region3_DR_lep01",10,0,2*M_PI);
      _h_2lSS0tau_region3_DEta_lep01	= bookHisto1D("2lSS0tau_region3_DEta_lep01",10,0,2*M_PI);
      _h_2lSS0tau_region3_DPhi_lep01 	= bookHisto1D("2lSS0tau_region3_DPhi_lep01",10,0,2*M_PI);


      _h_2lSS0tau_region4_nJets  	= bookHisto1D("2lSS0tau_region4_nJets",10,-0.5,9.5);
      _h_2lSS0tau_region4_HT	    	= bookHisto1D("2lSS0tau_region4_HT",100,0,2000);
      _h_2lSS0tau_region4_nBjets  	= bookHisto1D("2lSS0tau_region4_nBjets",4,-0.5,3.5);
      _h_2lSS0tau_region4_bjet0pT 	= bookHisto1D("2lSS0tau_region4_bjet0Pt",50,0,500);
      _h_2lSS0tau_region4_lep0pT  	= bookHisto1D("2lSS0tau_region4_lep0Pt",40,0,800);
      _h_2lSS0tau_region4_lepJetMinDR 	= bookHisto1D("2lSS0tau_region4_lepJetminDR",5,0,0.5);
      _h_2lSS0tau_region4_DR_lep01 	= bookHisto1D("2lSS0tau_region4_DR_lep01",10,0,2*M_PI);
      _h_2lSS0tau_region4_DEta_lep01	= bookHisto1D("2lSS0tau_region4_DEta_lep01",10,0,2*M_PI);
      _h_2lSS0tau_region4_DPhi_lep01 	= bookHisto1D("2lSS0tau_region4_DPhi_lep01",10,0,2*M_PI);

      _h_2lSS0tau_region5_nJets  	= bookHisto1D("2lSS0tau_region5_nJets",10,-0.5,9.5);
      _h_2lSS0tau_region5_HT	    	= bookHisto1D("2lSS0tau_region5_HT",100,0,2000);
      _h_2lSS0tau_region5_nBjets  	= bookHisto1D("2lSS0tau_region5_nBjets",4,-0.5,3.5);
      _h_2lSS0tau_region5_bjet0pT 	= bookHisto1D("2lSS0tau_region5_bjet0Pt",50,0,500);
      _h_2lSS0tau_region5_lep0pT  	= bookHisto1D("2lSS0tau_region5_lep0Pt",40,0,800);
      _h_2lSS0tau_region5_lepJetMinDR 	= bookHisto1D("2lSS0tau_region5_lepJetminDR",5,0,0.5);
      _h_2lSS0tau_region5_DR_lep01 	= bookHisto1D("2lSS0tau_region5_DR_lep01",10,0,2*M_PI);
      _h_2lSS0tau_region5_DEta_lep01	= bookHisto1D("2lSS0tau_region5_DEta_lep01",10,0,2*M_PI);
      _h_2lSS0tau_region5_DPhi_lep01 	= bookHisto1D("2lSS0tau_region5_DPhi_lep01",10,0,2*M_PI);

      _h_2lSS1tau_region6_nJets  	= bookHisto1D("2lSS1tau_region6_nJets",10,-0.5,9.5);
      _h_2lSS1tau_region6_HT	    	= bookHisto1D("2lSS1tau_region6_HT",100,0,2000);
      _h_2lSS1tau_region6_nBjets  	= bookHisto1D("2lSS1tau_region6_nBjets",4,-0.5,3.5);
      _h_2lSS1tau_region6_bjet0pT 	= bookHisto1D("2lSS1tau_region6_bjet0Pt",50,0,500);
      _h_2lSS1tau_region6_lep0pT  	= bookHisto1D("2lSS1tau_region6_lep0Pt",40,0,800);
      _h_2lSS1tau_region6_lepJetMinDR 	= bookHisto1D("2lSS1tau_region6_lepJetminDR",5,0,0.5);
      _h_2lSS1tau_region6_DR_lep01 	= bookHisto1D("2lSS1tau_region6_DR_lep01",10,0,2*M_PI);
      _h_2lSS1tau_region6_DEta_lep01	= bookHisto1D("2lSS1tau_region6_DEta_lep01",10,0,2*M_PI);
      _h_2lSS1tau_region6_DPhi_lep01 	= bookHisto1D("2lSS1tau_region6_DPhi_lep01",10,0,2*M_PI);
      _h_2lSS1tau_region6_tauPt		= bookHisto1D("2lSS1tau_region6_tauPt",50,0,500);


      _h_2lSS1tau_region7_nJets  	= bookHisto1D("2lSS1tau_region7_nJets",10,-0.5,9.5);
      _h_2lSS1tau_region7_HT	    	= bookHisto1D("2lSS1tau_region7_HT",100,0,2000);
      _h_2lSS1tau_region7_nBjets  	= bookHisto1D("2lSS1tau_region7_nBjets",4,-0.5,3.5);
      _h_2lSS1tau_region7_bjet0pT 	= bookHisto1D("2lSS1tau_region7_bjet0Pt",50,0,500);
      _h_2lSS1tau_region7_lep0pT  	= bookHisto1D("2lSS1tau_region7_lep0Pt",40,0,800);
      _h_2lSS1tau_region7_lepJetMinDR 	= bookHisto1D("2lSS1tau_region7_lepJetminDR",5,0,0.5);
      _h_2lSS1tau_region7_DR_lep01 	= bookHisto1D("2lSS1tau_region7_DR_lep01",10,0,2*M_PI);
      _h_2lSS1tau_region7_DEta_lep01	= bookHisto1D("2lSS1tau_region7_DEta_lep01",10,0,2*M_PI);
      _h_2lSS1tau_region7_DPhi_lep01 	= bookHisto1D("2lSS1tau_region7_DPhi_lep01",10,0,2*M_PI);
      _h_2lSS1tau_region7_tauPt		= bookHisto1D("2lSS1tau_region7_tauPt",50,0,500);



    }


    void analyze(const Event& event) {
      const double weight = event.weight();


      // Use the "LFS" projection to require at least one hard charged
      // lepton. This is an experimental signature for the leptonically decaying
      // W. This helps to reduce pure QCD backgrounds.
      
      const MissingMomentum& met = applyProjection<MissingMomentum>(event, "MissingET");
      const double event_met	 = met.vectorEt().mod();

      /*if(zeeFinder.bosons().size()==0 && zmumuFinder.bosons().size()==0)
      {
          MSG_INFO("ZeeFinder size: "<<zeeFinder.size());
          MSG_INFO("ZmumuFinder size: "<<zmumuFinder.size());
          MSG_INFO("Veto Event");
          vetoEvent;
      }*/

      Particles elVec,muVec,tauVec,lepVec;
      //Count the total number of leptons
      //
      //

      foreach (const Particle & el, applyProjection<PromptFinalState>(event,"electrons").particlesByPt())
      {
          if(el.pT()/GeV > 10 && fabs(el.eta()) <2.5)
          {
              elVec.push_back(el);
	      lepVec.push_back(el);
          }
      }
      foreach (const Particle &mu, applyProjection<PromptFinalState>(event,"muons").particlesByPt())
      {
          if(mu.pT()/GeV >10 && fabs(mu.eta()) <2.5)
          {
              muVec.push_back(mu);
 	      lepVec.push_back(mu);
          }
      }
      const TauFinder &tauhad = applyProjection<TauFinder>(event,"TauHadronic");
      foreach (const Particle &tau, tauhad.taus())
      {
          if(tau.pT()/GeV >25 )
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

      elVec = sortByPt(elVec);
      muVec = sortByPt(muVec);
      tauVec= sortByPt(tauVec);
      lepVec= sortByPt(lepVec);

      int nLep = lepVec.size();
      int elqsum=0;
      int muqsum=0;

      foreach(const Particle& el, elVec)
      {
          elqsum += el.charge();
      }
      foreach(const Particle &mu, muVec)
      {
          muqsum += mu.charge();
      }

      Jets alljets;
      foreach (const Jet &jet , applyProjection<FastJets>(event, "Jets").jetsByPt(25*GeV))
      {
          if(fabs(jet.eta()) <2.5 )
          {
              alljets.push_back(jet);
          }
      }
      double ht = 0.0;
      foreach (const Jet& j, alljets) { ht += j.pT(); }


      /* Identify b-jets */
      const Particles bhadrons = sortByPt(applyProjection<HeavyHadrons>(event, "BCHadrons").bHadrons());
    
      Jets bjets, ljets;
      foreach (const Jet& jet, alljets) 
      {
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
     
     float min_lj_deltaR=100;
     foreach (const Jet& jet, alljets)
     {
         foreach (const Particle & part, lepVec)
	 {
	     if(min_lj_deltaR > fabs(deltaR(jet,part))) {min_lj_deltaR = fabs(deltaR(jet,part)); }
	 }
     }


     
     //two light-leptons
     if(nLep==2)
     {
         //same sign + lepton pT 
         if(lepVec.at(0).charge()*lepVec.at(1).charge() >0 && lepVec.at(0).pT()/GeV >15 && lepVec.at(1).pT()/GeV > 10)
         {
              _h_2lSS0tau_region1_nJets->fill(alljets.size(),weight);
              _h_2lSS0tau_region1_HT->fill(ht,weight);
              _h_2lSS0tau_region1_nBjets->fill(bjets.size(),weight);
              _h_2lSS0tau_region1_lep0pT->fill(lepVec.at(0).pT()/GeV,weight);
              _h_2lSS0tau_region1_lepJetMinDR->fill(min_lj_deltaR,weight);
              _h_2lSS0tau_region1_DR_lep01->fill(fabs(deltaR(lepVec.at(0),lepVec.at(1))),weight);
              _h_2lSS0tau_region1_DEta_lep01->fill(fabs(deltaEta(lepVec.at(0),lepVec.at(1))),weight);
              _h_2lSS0tau_region1_DPhi_lep01->fill(fabs(deltaPhi(lepVec.at(0),lepVec.at(1))),weight);
 
	     // 0-tau
             if(tauVec.size()==0)
             {
		 _h_2lSS0tau_MET->fill(event_met/GeV,weight);
                 // 'Region-1'
                 if(bjets.size()==1 && alljets.size() >= 4)
                 {
      		     _h_2lSS0tau_region2_nJets->fill(alljets.size(),weight);
      		     _h_2lSS0tau_region2_HT->fill(ht,weight);
		     _h_2lSS0tau_region2_nBjets->fill(bjets.size(),weight);
		     _h_2lSS0tau_region2_bjet0pT->fill(bjets.at(0).pT()/GeV,weight);
		     _h_2lSS0tau_region2_lep0pT->fill(lepVec.at(0).pT()/GeV,weight);
		     _h_2lSS0tau_region2_lepJetMinDR->fill(min_lj_deltaR,weight);
		     _h_2lSS0tau_region2_DR_lep01->fill(fabs(deltaR(lepVec.at(0),lepVec.at(1))),weight);
		     _h_2lSS0tau_region2_DEta_lep01->fill(fabs(deltaEta(lepVec.at(0),lepVec.at(1))),weight);
		     _h_2lSS0tau_region2_DPhi_lep01->fill(fabs(deltaPhi(lepVec.at(0),lepVec.at(1))),weight);
                 }
                 // 'Region-2'
                 if(bjets.size()>=2 && alljets.size() >= 4)
                 {
      		     _h_2lSS0tau_region3_nJets->fill(alljets.size(),weight);
      		     _h_2lSS0tau_region3_HT->fill(ht,weight);
		     _h_2lSS0tau_region3_nBjets->fill(bjets.size(),weight);
		     _h_2lSS0tau_region3_bjet0pT->fill(bjets.at(0).pT()/GeV,weight);
		     _h_2lSS0tau_region3_lep0pT->fill(lepVec.at(0).pT()/GeV,weight);
		     _h_2lSS0tau_region3_lepJetMinDR->fill(min_lj_deltaR,weight);
		     _h_2lSS0tau_region3_DR_lep01->fill(fabs(deltaR(lepVec.at(0),lepVec.at(1))),weight);
		     _h_2lSS0tau_region3_DEta_lep01->fill(fabs(deltaEta(lepVec.at(0),lepVec.at(1))),weight);
		     _h_2lSS0tau_region3_DPhi_lep01->fill(fabs(deltaPhi(lepVec.at(0),lepVec.at(1))),weight);

                 }
                 // 'Region-3'
                 if(bjets.size()==1 && alljets.size() >= 3)
                 {
      		     _h_2lSS0tau_region4_nJets->fill(alljets.size(),weight);
      		     _h_2lSS0tau_region4_HT->fill(ht,weight);
		     _h_2lSS0tau_region4_nBjets->fill(bjets.size(),weight);
		     _h_2lSS0tau_region4_bjet0pT->fill(bjets.at(0).pT()/GeV,weight);
		     _h_2lSS0tau_region4_lep0pT->fill(lepVec.at(0).pT()/GeV,weight);
		     _h_2lSS0tau_region4_lepJetMinDR->fill(min_lj_deltaR,weight);
		     _h_2lSS0tau_region4_DR_lep01->fill(fabs(deltaR(lepVec.at(0),lepVec.at(1))),weight);
		     _h_2lSS0tau_region4_DEta_lep01->fill(fabs(deltaEta(lepVec.at(0),lepVec.at(1))),weight);
		     _h_2lSS0tau_region4_DPhi_lep01->fill(fabs(deltaPhi(lepVec.at(0),lepVec.at(1))),weight);

                 }
                 // 'Region-4'
                 if(bjets.size()>=2 && alljets.size() >= 3)
                 {
      		     _h_2lSS0tau_region5_nJets->fill(alljets.size(),weight);
      		     _h_2lSS0tau_region5_HT->fill(ht,weight);
		     _h_2lSS0tau_region5_nBjets->fill(bjets.size(),weight);
		     _h_2lSS0tau_region5_bjet0pT->fill(bjets.at(0).pT()/GeV,weight);
		     _h_2lSS0tau_region5_lep0pT->fill(lepVec.at(0).pT()/GeV,weight);
		     _h_2lSS0tau_region5_lepJetMinDR->fill(min_lj_deltaR,weight);
		     _h_2lSS0tau_region5_DR_lep01->fill(fabs(deltaR(lepVec.at(0),lepVec.at(1))),weight);
		     _h_2lSS0tau_region5_DEta_lep01->fill(fabs(deltaEta(lepVec.at(0),lepVec.at(1))),weight);
		     _h_2lSS0tau_region5_DPhi_lep01->fill(fabs(deltaPhi(lepVec.at(0),lepVec.at(1))),weight);
                 }
             }
	     // 1-tau
             else if (tauVec.size()>=1)
             {
	         _h_2lSS1tau_MET->fill(event_met/GeV,weight);
		 // 'Region-6'
		 _h_2lSS1tau_region6_nJets->fill(alljets.size(),weight);
      	         _h_2lSS1tau_region6_HT->fill(ht,weight);
	         _h_2lSS1tau_region6_nBjets->fill(bjets.size(),weight);
	         _h_2lSS1tau_region6_lep0pT->fill(lepVec.at(0).pT()/GeV,weight);
	         _h_2lSS1tau_region6_lepJetMinDR->fill(min_lj_deltaR,weight);
	         _h_2lSS1tau_region6_DR_lep01->fill(fabs(deltaR(lepVec.at(0),lepVec.at(1))),weight);
	         _h_2lSS1tau_region6_DEta_lep01->fill(fabs(deltaEta(lepVec.at(0),lepVec.at(1))),weight);
	         _h_2lSS1tau_region6_DPhi_lep01->fill(fabs(deltaPhi(lepVec.at(0),lepVec.at(1))),weight);
		 _h_2lSS1tau_region6_tauPt->fill(tauVec.at(0).pT()/GeV,weight);

	         // 'Region-7'
                 if(bjets.size() >= 1 && alljets.size() >= 3)
                 {
	             _h_2lSS1tau_region7_nJets->fill(alljets.size(),weight);
      	             _h_2lSS1tau_region7_HT->fill(ht,weight);
	             _h_2lSS1tau_region7_nBjets->fill(bjets.size(),weight);
	             _h_2lSS1tau_region7_bjet0pT->fill(bjets.at(0).pT()/GeV,weight);
	             _h_2lSS1tau_region7_lep0pT->fill(lepVec.at(0).pT()/GeV,weight);
	             _h_2lSS1tau_region7_lepJetMinDR->fill(min_lj_deltaR,weight);
	             _h_2lSS1tau_region7_DR_lep01->fill(fabs(deltaR(lepVec.at(0),lepVec.at(1))),weight);
	             _h_2lSS1tau_region7_DEta_lep01->fill(fabs(deltaEta(lepVec.at(0),lepVec.at(1))),weight);
	             _h_2lSS1tau_region7_DPhi_lep01->fill(fabs(deltaPhi(lepVec.at(0),lepVec.at(1))),weight);
		     _h_2lSS1tau_region7_tauPt->fill(tauVec.at(0).pT()/GeV,weight);
	          }
              }
          }
      }
  }


    void finalize() {
        MSG_INFO("CROSS SSECTION:"<<crossSection());
        MSG_INFO("Sum of weights:"<<sumOfWeights());

        _h_sumOfWeights->fill(1,sumOfWeights());
    }

    //@}


  private:

    // @name Histogram data members
    //@{
    //

    Histo1DPtr _h_sumOfWeights;
    Histo1DPtr _h_2lSS0tau_MET,_h_2lSS1tau_MET;

    Histo1DPtr  _h_2lSS0tau_region1_nJets,_h_2lSS0tau_region1_HT,_h_2lSS0tau_region1_nBjets,_h_2lSS0tau_region1_bjet0pT,_h_2lSS0tau_region1_lep0pT,_h_2lSS0tau_region1_lepJetMinDR,_h_2lSS0tau_region1_DR_lep01,_h_2lSS0tau_region1_DEta_lep01,_h_2lSS0tau_region1_DPhi_lep01;
    Histo1DPtr  _h_2lSS0tau_region2_nJets,_h_2lSS0tau_region2_HT,_h_2lSS0tau_region2_nBjets,_h_2lSS0tau_region2_bjet0pT,_h_2lSS0tau_region2_lep0pT,_h_2lSS0tau_region2_lepJetMinDR,_h_2lSS0tau_region2_DR_lep01,_h_2lSS0tau_region2_DEta_lep01,_h_2lSS0tau_region2_DPhi_lep01;
    Histo1DPtr  _h_2lSS0tau_region3_nJets,_h_2lSS0tau_region3_HT,_h_2lSS0tau_region3_nBjets,_h_2lSS0tau_region3_bjet0pT,_h_2lSS0tau_region3_lep0pT,_h_2lSS0tau_region3_lepJetMinDR,_h_2lSS0tau_region3_DR_lep01,_h_2lSS0tau_region3_DEta_lep01,_h_2lSS0tau_region3_DPhi_lep01;
    Histo1DPtr  _h_2lSS0tau_region4_nJets,_h_2lSS0tau_region4_HT,_h_2lSS0tau_region4_nBjets,_h_2lSS0tau_region4_bjet0pT,_h_2lSS0tau_region4_lep0pT,_h_2lSS0tau_region4_lepJetMinDR,_h_2lSS0tau_region4_DR_lep01,_h_2lSS0tau_region4_DEta_lep01,_h_2lSS0tau_region4_DPhi_lep01;
    Histo1DPtr  _h_2lSS0tau_region5_nJets,_h_2lSS0tau_region5_HT,_h_2lSS0tau_region5_nBjets,_h_2lSS0tau_region5_bjet0pT,_h_2lSS0tau_region5_lep0pT,_h_2lSS0tau_region5_lepJetMinDR,_h_2lSS0tau_region5_DR_lep01,_h_2lSS0tau_region5_DEta_lep01,_h_2lSS0tau_region5_DPhi_lep01;
    Histo1DPtr  _h_2lSS1tau_region6_nJets,_h_2lSS1tau_region6_HT,_h_2lSS1tau_region6_nBjets,_h_2lSS1tau_region6_bjet0pT,_h_2lSS1tau_region6_lep0pT,_h_2lSS1tau_region6_lepJetMinDR,_h_2lSS1tau_region6_DR_lep01,_h_2lSS1tau_region6_DEta_lep01,_h_2lSS1tau_region6_DPhi_lep01,_h_2lSS1tau_region6_tauPt;
    Histo1DPtr  _h_2lSS1tau_region7_nJets,_h_2lSS1tau_region7_HT,_h_2lSS1tau_region7_nBjets,_h_2lSS1tau_region7_bjet0pT,_h_2lSS1tau_region7_lep0pT,_h_2lSS1tau_region7_lepJetMinDR,_h_2lSS1tau_region7_DR_lep01,_h_2lSS1tau_region7_DEta_lep01,_h_2lSS1tau_region7_DPhi_lep01,_h_2lSS1tau_region7_tauPt;



    //@}

  };



  // The hook for the plugin system
  DECLARE_RIVET_PLUGIN(ttw_ttH);
}
