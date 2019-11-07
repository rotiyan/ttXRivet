#include "Rivet/Analysis.hh"
#include "Rivet/Projections/PartonicTops.hh"
#include "Rivet/Projections/VetoedFinalState.hh"
#include "Rivet/Projections/FastJets.hh"
#include <iostream>
/** Adapted from CMS_2015_I1397174*/

namespace Rivet {

/// Fully hadronic partonic ttW analysis
class ttW_partonTop: public Analysis {
   public:
        /// Minimal constructor
        ttW_partonTop()
          : Analysis("ttW_partonTop") { }
 
 
   /// @name Analysis methods
   //@{
   
   /// Set up projections and book histograms
   void init() {
    
           // Parton level top quarks
           addProjection(PartonicTops(PartonicTops::ANY),"TopFS");
      
           // Find jets not related to the top/W decays
           VetoedFinalState vfs;
           vfs.addDecayProductsVeto(PID::WPLUSBOSON);
           vfs.addDecayProductsVeto(PID::WMINUSBOSON);
           FastJets fj(vfs, FastJets::ANTIKT, 0.4, JetAlg::ALL_MUONS, JetAlg::ALL_INVISIBLES);
           addProjection(fj, "Jets");

	   //Create a second jet projection just to get the total number of jets
	   FastJets all_jets(FinalState(-5,5,25*GeV), FastJets::ANTIKT, 0.4, JetAlg::ALL_MUONS, JetAlg::ALL_INVISIBLES);
	   addProjection(all_jets,"AllJets");



           // Book histograms
           _h_sumWeights		= bookHisto1D("sumWeights",5,1,6);

	   _h_nJets			= bookHisto1D("nJets",20,-0.5,19.5);
	   _h_nJets30		        = bookHisto1D("nJets30",20,-0.5,19.5);
	   _h_nJets60			= bookHisto1D("nJets60",20,-0.5,19.5);
	   _h_nJets100			= bookHisto1D("nJets100",20,-0.5,19.5);

	   _h_wP_nJets			= bookHisto1D("wP_nJets",20,-0.5,19.5);
	   _h_wP_nJets30		= bookHisto1D("wP_nJets30",20,-0.5,19.5);
	   _h_wP_nJets60		= bookHisto1D("wP_nJets60",20,-0.5,19.5);
	   _h_wP_nJets100		= bookHisto1D("wP_nJets100",20,-0.5,19.5);



	   _h_wP_add_nJets		= bookHisto1D("wP_add_nJets",20,-0.5,19.5);
	   _h_wP_add_nBjets		= bookHisto1D("wP_add_nBjets",5,-0.5,4.5);

	   _h_wP_add_nJets_region1	= bookHisto1D("wP_add_nJets_region1",20,-0.5,19.5);
	   _h_wP_add_nJets_region2	= bookHisto1D("wP_add_nJets_region2",20,-0.5,19.5);

	   _h_wP_add_diL_region1_pT	= bookHisto1D("wP_add_diL_region1_jetPt",100,0,1000);
	   _h_wP_add_semiL_region1_pT	= bookHisto1D("wP_add_semiL_region1_jetPt",100,0,1000);
	   _h_wP_add_had_region1_pT	= bookHisto1D("wP_add_had_region1_jetPt",100,0,1000);

	   _h_wP_add_diL_region2_pT	= bookHisto1D("wP_add_diL_region2_jetPt",100,0,1000);
	   _h_wP_add_semiL_region2_pT	= bookHisto1D("wP_add_semiL_region2_jetPt",100,0,1000);
	   _h_wP_add_had_region2_pT	= bookHisto1D("wP_add_had_region2_jetPt",100,0,1000);

	   _h_wP_ttbar_pt		= bookHisto1D("wP_ttbar_pt",100,0,1000);
	   _h_wP_top_pt			= bookHisto1D("wP_top_pt",100,0,1000);
	   _h_wP_top_mass		= bookHisto1D("wP_top_mass",100,0,300);
	   _h_wP_W_mass			= bookHisto1D("wP_W_mass",80,40,120);
	   _h_wP_top_dR			= bookHisto1D("wP_top_dR",50,0,10);
	   _h_wP_top_b_pt		= bookHisto1D("wP_top_bPt",100,0,1000);
	   _h_wP_top_W_pt		= bookHisto1D("wP_top_wPt",100,0,1000);
	   _h_wP_WME_mass		= bookHisto1D("wP_WME_mass",80,40,120);
	   _h_wP_ME_W_pt		= bookHisto1D("wP_ME_wPt",100,0,1000);
	   _h_wP_ME_W_eta		= bookHisto1D("wP_ME_wEta",100,-6,6);

	   _h_wM_nJets			= bookHisto1D("wM_nJets",20,-0.5,19.5);
	   _h_wM_nJets30		= bookHisto1D("wM_nJets30",20,-0.5,19.5);
	   _h_wM_nJets60		= bookHisto1D("wM_nJets60",20,-0.5,19.5);
	   _h_wM_nJets100		= bookHisto1D("wM_nJets100",20,-0.5,19.5);


	   _h_wM_add_nJets		= bookHisto1D("wM_add_nJets",20,-0.5,19.5);
	   _h_wM_add_nBjets		= bookHisto1D("wM_add_nBjets",5,-0.5,4.5);

	   _h_wM_add_nJets_region1	= bookHisto1D("wM_add_nJets_region1",20,-0.5,19.5);
	   _h_wM_add_nJets_region2	= bookHisto1D("wM_add_nJets_region2",20,-0.5,19.5);

	   _h_wM_add_diL_region1_pT	= bookHisto1D("wM_add_diL_region1_jetPt",100,0,1000);
	   _h_wM_add_semiL_region1_pT	= bookHisto1D("wM_add_semiL_region1_jetPt",100,0,1000);
	   _h_wM_add_had_region1_pT	= bookHisto1D("wM_add_had_region1_jetPt",100,0,1000);

	   _h_wM_add_diL_region2_pT	= bookHisto1D("wM_add_diL_region2_jetPt",100,0,1000);
	   _h_wM_add_semiL_region2_pT	= bookHisto1D("wM_add_semiL_region2_jetPt",100,0,1000);
	   _h_wM_add_had_region2_pT	= bookHisto1D("wM_add_had_region2_jetPt",100,0,1000);

	   _h_wM_ttbar_pt		= bookHisto1D("wM_ttbar_pt",100,0,1000);
	   _h_wM_top_pt			= bookHisto1D("wM_top_pt",100,0,1000);
	   _h_wM_top_mass		= bookHisto1D("wM_top_mass",100,0,300);
	   _h_wM_W_mass			= bookHisto1D("wM_W_mass",80,40,120);
	   _h_wM_top_dR			= bookHisto1D("wM_top_dR",50,0,10);
	   _h_wM_top_b_pt		= bookHisto1D("wM_top_bPt",100,0,1000);
	   _h_wM_top_W_pt		= bookHisto1D("wM_top_wMt",100,0,1000);
	   _h_wM_WME_mass		= bookHisto1D("wM_WME_mass",80,40,120);
	   _h_wM_ME_W_pt		= bookHisto1D("wM_ME_wMt",100,0,1000);
	   _h_wM_ME_W_eta		= bookHisto1D("wM_ME_wEta",100,-6,6);


         }

 
        void analyze(const Event& event) {

            // The objects used in the PAPER 12-041 are defined as follows (see p.16 for details):
            //
            //   * Leptons    : from the W boson decays after FSR
            //   * Jets       : anti-kT R=0.5 to all stable particles
            //                               exclude W->enu, munu, taunu
            //   * B jet      : B-Ghost matched
            //   * B from top : B hadron from top->b decay
            //
            // Visible phase space definition:
            //
            //   * Leptons         : pT > 20, |eta| < 2.4
            //   * B jets from top : pT > 30, |eta| < 2.4
            //     Additional jets : pT > 20, |eta| < 2.4
            //   *
            // Full phase space definition:
            //
            //   * Correction to dilepton BR from W boson BR
            //   * No cut on top decay products
            //   * Additional jets : pT > 20, |eta| < 2.4
           
           const double weight = event.weight();
	   _h_sumWeights->fill(1,weight);

            // Do the analysis  if there is two tops
            const Particles partontops = apply<ParticleFinder>(event, "TopFS").particlesByPt();
      	    if (partontops.size() != 2) vetoEvent;
            const Particle& t1 = partontops[0];
            const Particle& t2 = partontops[1];
	    
	    Particles t1_b	= t1.allDescendants(lastParticleWith([](const Particle &p){return p.hasBottom();}));
	    Particles t2_b	= t2.allDescendants(lastParticleWith([](const Particle &p){return p.hasBottom();}));
	    Particle t1_W 	= t1.allDescendants(lastParticleWith([](const Particle &p){return p.pdgId()==24|| p.pdgId() ==-24;;})).front();
	    Particle t2_W 	= t2.allDescendants(lastParticleWith([](const Particle &p){return p.pdgId()==24|| p.pdgId() ==-24;;})).front();

	    Particle ME_W;
	    for (auto gp: particles(event.genEvent()))
	    {
		bool isME_W =false;
		if( abs(gp->pdg_id()) == 24)
		{
	            GenVertex *wVert      = gp->production_vertex();
              	    for(GenVertex::particles_in_const_iterator wIter = wVert->particles_in_const_begin(); wIter!= wVert->particles_in_const_end(); ++wIter)
		    {
		       if(abs((*wIter)->pdg_id())!=24 && abs((*wIter)->pdg_id())!=6) {isME_W=true;}
		    }
		}
		if (isME_W) {ME_W = Particle(gp);}
	    }
	    MSG_DEBUG("ME_W: "<<ME_W.pdgId());

	    Particles top_bQuarks(t1_b);
	    top_bQuarks.insert(top_bQuarks.end(),t2_b.begin(),t2_b.end());
	 
           // Apply acceptance cuts on top-decay leptons (existence should be guaranteed)
           const auto isPromptChLepton = [](const Particle& p){return isChargedLepton(p) && !fromDecay(p);};
           const Particles leps_t1 = t1.allDescendants(lastParticleWith(isPromptChLepton));
           const Particles leps_t2 = t2.allDescendants(lastParticleWith(isPromptChLepton));

	   Particles w1_children = t1_W.allDescendants(lastParticleWith([] (const Particle &p){ return isQuark(p);}));
	   Particles w2_children = t2_W.allDescendants(lastParticleWith([] (const Particle &p){ return isQuark(p);}));

	   Particles w_Qchildren(w1_children);
	   w_Qchildren.insert(w_Qchildren.end(),w2_children.begin(),w2_children.end());

	  
	   bool allHadronic =false;
	   bool semiLeptonic =false;
	   bool diLeptonic = false;
	   if ( w1_children.size()==2 && w2_children.size()==2 ){ allHadronic=true;}
	   if ( (w1_children.size()==2 && w2_children.size()==0) || ( w1_children.size()==0 && w2_children.size()==2) ) {semiLeptonic=true;}
	   if ( (w1_children.size()==0 && w2_children.size()==0)) {diLeptonic=true;}
	   //if ((leps_t1.size() == 2 && leps_t2.size()==0) || (leps_t1.size()==0 && leps_t2.size()==2)) semiLeptonic=true;
	   //if ((leps_t1.size() == 2 && leps_t2.size()==2)) diLeptonic=true;

	   MSG_DEBUG("allHadronic: "<<allHadronic);
 	   MSG_DEBUG("semileptonic: "<<semiLeptonic);
	   MSG_DEBUG("dileptonic: "<<diLeptonic);

           const Jets jets = apply<JetAlg>(event, "Jets").jetsByPt(Cuts::pT > 25*GeV && Cuts::abseta < 5);
	   const Jets all_jets = apply<JetAlg>(event,"AllJets").jetsByPt(Cuts::pT >25*GeV && Cuts::abseta <5);
           
	   int nJet = 0,nJet30 = 0, nJet60 = 0, nJet100 = 0;
	   for(const auto&jet: all_jets)
	   {
	       nJet += 1;
               if(jet.pT()>30*GeV) nJet30 +=1;
	       if(jet.pT()>60*GeV) nJet60 +=1;
	       if(jet.pT()>100*GeV) nJet100 +=1;
	   }

	   Jets topBJets, addJets, addBJets;

           for (const Jet& jet : jets) {
              const bool isBtagged = jet.bTagged();
	      bool isBFromTop =false;
	      //do a deletaR match to find highest pT top quarks
	      for(const Particle bQuark: top_bQuarks)
	      {
		 if (deltaR(jet.momentum(),bQuark.momentum()) < 0.4 && isBtagged ) isBFromTop = true;
	      }

              if(isBFromTop && isBtagged) {
                   if (jet.pT() > 25*GeV) topBJets.push_back(jet);
              } else if (isBtagged)
	      {
   	          addBJets.push_back(jet);
	      }
	      else {addJets.push_back(jet);}
	   }
	   
 	   if (topBJets.size()<2) vetoEvent;
	
	   int nJets_region1(0),nJets_region2(0);
	   for(const auto jet : addJets)
	   {
	       if(abs(jet.eta()) < 2.5)
	       { 
		   nJets_region1++;
	           if(diLeptonic) 
 		   {
		      if(ME_W.pdgId() >0){ _h_wP_add_diL_region1_pT    ->fill(jet.pT()/GeV,weight);}
		      else {_h_wM_add_diL_region1_pT ->fill(jet.pT()/GeV,weight);}
  		   }
		   if(semiLeptonic)
		   {
		      if(ME_W.pdgId() >0){ _h_wP_add_semiL_region1_pT  ->fill(jet.pT()/GeV,weight);}
		      else { _h_wM_add_semiL_region1_pT->fill(jet.pT()/GeV,weight);}
		   }
		   if(allHadronic)
		   {
		      if(ME_W.pdgId()>0){ _h_wP_add_had_region1_pT    ->fill(jet.pT()/GeV,weight);}
		      else {_h_wM_add_had_region1_pT ->fill(jet.pT()/GeV,weight);}
		   }
	       }
	       else{
		   nJets_region2++;
		   if(diLeptonic)
	           {
		      if(ME_W.pdgId()>0) { _h_wM_add_diL_region2_pT    ->fill(jet.pT()/GeV,weight);}
		      else { _h_wM_add_diL_region2_pT ->fill(jet.pT()/GeV,weight);}
		   }
		   if(semiLeptonic)
		   {
		      if(ME_W.pdgId()>0) {_h_wM_add_semiL_region2_pT  ->fill(jet.pT()/GeV,weight);}
		      else {_h_wM_add_diL_region2_pT ->fill(jet.pT()/GeV,weight);}
		   }
		   if(allHadronic)
		   {
		      if(ME_W.pdgId()>0){_h_wM_add_had_region2_pT	->fill(jet.pT()/GeV,weight);}
		      else{_h_wM_add_had_region2_pT->fill(jet.pT()/GeV,weight);}
		   }
	       }
	   }

	   _h_nJets 	->fill(nJet, weight);
	   _h_nJets30	->fill(nJet30,weight);
	   _h_nJets60	->fill(nJet60,weight);
	   _h_nJets100	->fill(nJet100,weight);
           
           if(ME_W.pdgId()>0){

	       _h_wP_nJets	->fill( nJet, weight);
	       _h_wP_nJets30	->fill( nJet30, weight);
	       _h_wP_nJets60	->fill( nJet60, weight);
	       _h_wP_nJets100	->fill( nJet100, weight);

	       _h_wP_add_nJets	->fill( addJets.size(),weight);
	       _h_wP_add_nBjets	->fill( addBJets.size(),weight);

	       _h_wP_add_nJets_region1->fill(nJets_region1,weight);
	       _h_wP_add_nJets_region2->fill(nJets_region2,weight);

	       _h_wP_ttbar_pt	->fill( (t1.momentum() + t2.momentum()).pT()/GeV,weight);
	       _h_wP_top_dR		->fill( deltaR(t1.momentum(),t2.momentum()),weight);
               _h_wP_top_mass	->fill( t1.momentum().mass()/GeV,weight);
	       _h_wP_top_mass  	->fill( t2.momentum().mass()/GeV,weight);
	       _h_wP_top_b_pt	->fill( t1_b[0].momentum().pT()/GeV,weight);
	       _h_wP_top_pt    	->fill( t1.momentum().pT()/GeV,weight);
               _h_wP_top_pt		->fill( t2.momentum().pT()/GeV,weight);
	       _h_wP_top_b_pt	->fill( t2_b[0].momentum().pT()/GeV,weight);
	       _h_wP_top_W_pt	->fill( t1_W.momentum().pT()/GeV,weight);
	       _h_wP_top_W_pt	->fill( t2_W.momentum().pT()/GeV,weight);
	       _h_wP_WME_mass   ->fill( ME_W.momentum().mass()/GeV,weight);
	       _h_wP_ME_W_pt	->fill( ME_W.momentum().pT()/GeV,weight);
	       _h_wP_ME_W_eta	->fill( ME_W.momentum().eta(),weight);
	   }

           if(ME_W.pdgId() <0){
	       _h_wM_nJets	->fill( nJet, weight);
	       _h_wM_nJets30	->fill( nJet30, weight);
	       _h_wM_nJets60	->fill( nJet60, weight);
	       _h_wM_nJets100	->fill( nJet100, weight);


	       _h_wM_add_nJets	->fill( addJets.size(),weight);
	       _h_wM_add_nBjets	->fill( addBJets.size(),weight);

	       _h_wM_add_nJets_region1->fill(nJets_region1,weight);
	       _h_wM_add_nJets_region2->fill(nJets_region2,weight);

	       _h_wM_ttbar_pt	->fill( (t1.momentum() + t2.momentum()).pT()/GeV,weight);
	       _h_wM_top_dR		->fill( deltaR(t1.momentum(),t2.momentum()),weight);
               _h_wM_top_mass	->fill( t1.momentum().mass()/GeV,weight);
	       _h_wM_top_mass  	->fill( t2.momentum().mass()/GeV,weight);
	       _h_wM_top_b_pt	->fill( t1_b[0].momentum().pT()/GeV,weight);
	       _h_wM_top_pt    	->fill( t1.momentum().pT()/GeV,weight);
               _h_wM_top_pt		->fill( t2.momentum().pT()/GeV,weight);
	       _h_wM_top_b_pt	->fill( t2_b[0].momentum().pT()/GeV,weight);
	       _h_wM_top_W_pt	->fill( t1_W.momentum().pT()/GeV,weight);
	       _h_wM_top_W_pt	->fill( t2_W.momentum().pT()/GeV,weight);
	       _h_wM_WME_mass	->fill( t2_W.momentum().mass()/GeV,weight);
	       _h_wM_ME_W_pt	->fill( ME_W.momentum().pT()/GeV,weight);
	       _h_wM_ME_W_eta	->fill( ME_W.momentum().eta(),weight);
	   }

     }

   
    void finalize() {
       const double ttbarXS = !std::isnan(crossSectionPerEvent()) ? crossSection() : 252.89*picobarn;
       if (std::isnan(crossSectionPerEvent()))
           MSG_DEBUG("No valid cross-section given, using NNLO (arXiv:1303.6254; sqrt(s)=8 TeV, m_t=172.5 GeV): " << ttbarXS/picobarn << " pb");
       
           //normalize({_hVis_nJet30,_hVis_nJet60, _hVis_nJet100});
       
           const double xsPerWeight = ttbarXS/picobarn / sumOfWeights();
	   const double sfull = xsPerWeight / 0.0454; //< correct for dilepton branching fraction
       }
   //@}
 

 


// @name Histogram data members
//@{

Histo1DPtr _h_sumWeights;
Histo1DPtr _h_nJets,_h_nJets30,_h_nJets60,_h_nJets100;

Histo1DPtr _h_wP_nJets,_h_wP_nJets30,_h_wP_nJets60,_h_wP_nJets100;
Histo1DPtr _h_wP_add_nJets,_h_wP_add_nBjets;
Histo1DPtr _h_wP_add_nJets_region1, _h_wP_add_nJets_region2;
Histo1DPtr _h_wP_add_diL_region1_pT,_h_wP_add_semiL_region1_pT,_h_wP_add_had_region1_pT;     
Histo1DPtr _h_wP_add_diL_region2_pT,_h_wP_add_semiL_region2_pT,_h_wP_add_had_region2_pT; 
Histo1DPtr _h_wP_ttbar_pt,_h_wP_top_pt,_h_wP_top_mass, _h_wP_W_mass,_h_wP_top_dR,_h_wP_top_b_pt,_h_wP_top_W_pt,_h_wP_WME_mass, _h_wP_ME_W_pt,_h_wP_ME_W_eta;

Histo1DPtr _h_wM_nJets,_h_wM_nJets30,_h_wM_nJets60,_h_wM_nJets100;
Histo1DPtr _h_wM_add_nJets,_h_wM_add_nBjets;
Histo1DPtr _h_wM_add_nJets_region1, _h_wM_add_nJets_region2;
Histo1DPtr _h_wM_add_diL_region1_pT,_h_wM_add_semiL_region1_pT,_h_wM_add_had_region1_pT;     
Histo1DPtr _h_wM_add_diL_region2_pT,_h_wM_add_semiL_region2_pT,_h_wM_add_had_region2_pT; 
Histo1DPtr _h_wM_ttbar_pt,_h_wM_top_pt,_h_wM_top_mass,_h_wM_W_mass,_h_wM_top_dR,_h_wM_top_b_pt,_h_wM_top_W_pt,_h_wM_WME_mass,_h_wM_ME_W_pt,_h_wM_ME_W_eta;


//Profile1DPtr _hGap_addJet1Pt, _hGap_addJet1Pt_eta0, _hGap_addJet1Pt_eta1, _hGap_addJet1Pt_eta2;
 
//@}
 
};

 
   // The hook for the plugin system
   DECLARE_RIVET_PLUGIN(ttW_partonTop);

 
 }
