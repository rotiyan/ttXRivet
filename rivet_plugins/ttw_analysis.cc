// -*- C++ -*-
#include "Rivet/Analysis.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/ChargedLeptons.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Projections/VetoedFinalState.hh"
#include "Rivet/Projections/UnstableFinalState.hh"
#include "Rivet/Projections/WFinder.hh"

#include <vector>
/// @todo Include more projections as required, e.g. ChargedFinalState, FastJets, ZFinder...

namespace Rivet {

  using namespace Cuts;

  class ttw_analysis : public Analysis {
  public:

    /// Constructor
    ttw_analysis()
      : Analysis("ttw_analysis")
    {    }


    /// @name Analysis methods
    //@{

    /// Book histograms and initialise projections before the run
    void init() {

      // A FinalState is used to select particles within |eta| < 4.2 and with pT
      // > 20 GeV, out of which the ChargedLeptons projection picks only the
      // electrons and muons, to be accessed later as "LFS".
      ChargedLeptons lfs(FinalState(-4.2, 4.2, 20*GeV));
      addProjection(lfs, "LFS");
      VetoedFinalState fs(FinalState(-4.2, 4.2, 0*GeV));
      fs.addVetoOnThisFinalState(lfs); //Remove leptons ?

      addProjection(FastJets(fs, FastJets::ANTIKT, 0.4), "Jets");


      UnstableFinalState ufs;
      addProjection(ufs, "UFS");
      
      FinalState myfs;
      WFinder wfinder(myfs, Cuts::abseta < 3.5,PID::ELECTRON , 60.0*GeV, 100.0*GeV, 25.0*GeV, 0.2);
      addProjection(wfinder, "WFinder");
     

      /// @todo Book histograms here, e.g.:
      // _h_XXXX = bookProfile1D(1, 1, 1);
      // _h_YYYY = bookHisto1D(2, 1, 1);
      h_njets	 = bookHisto1D("jet_mult", 11, -0.5, 10.5);
      h_nljets   = bookHisto1D("ljet_mult",11, -0.5, 10.5);
      h_nbjets   = bookHisto1D("bjet_mult",11, -0.5, 10.5);
      h_nChrgLeps= bookHisto1D("chrgLep_mult",11,-05,10.5);

      h_b1_b2_dEta= bookHisto1D("b1_b2-dEta",100,-3.14,3.14);
      h_b1_b2_dPhi= bookHisto1D("b1_b2-dPhi",100,-3.14,3.14);
      h_b1_b2_dR  = bookHisto1D("b1_b2_dR",100,-4,4);

      h_top_mass  = bookHisto1D("top_mass",400,100,500);
      h_top_pt	  = bookHisto1D("top_pt",450,50,500);
      h_top_eta   = bookHisto1D("top_eta",100,-4,4);
      h_top_phi   = bookHisto1D("top_phi",100,-3.14,3.15);

      h_wlep_mass    = bookHisto1D("wlep_mass",200,40,140);
      h_wlep_pt	     = bookHisto1D("wlep_pt",200,10,200);
      h_wlep_eta     = bookHisto1D("wlep_eta",100,-4,4);
      h_wlep_phi     = bookHisto1D("wlep_phi",100,0,3.14);

      h_wHad1_mass    = bookHisto1D("wHad1_mass",200,40,140);
      h_wHad1_pt      = bookHisto1D("wHad1_pt",200,10,200);
      h_wHad1_eta     = bookHisto1D("wHad1_eta",100,-4,4);
      h_wHad1_phi     = bookHisto1D("wHad1_phi",100,0,3.14);

      h_wHad2_mass    = bookHisto1D("wHad2_mass",200,40,140);
      h_wHad2_pt      = bookHisto1D("wHad2_pt",200,10,200);
      h_wHad2_eta     = bookHisto1D("wHad2_eta",100,-4,4);
      h_wHad2_phi     = bookHisto1D("wHad2_phi",100,0,3.14);




    }


    /// Perform the per-event analysis
    void analyze(const Event& event) {
      const double weight = event.weight();

      /// @todo Do the event by event analysis here
      const ChargedLeptons& lfs = applyProjection<ChargedLeptons>(event, "LFS");
      const UnstableFinalState& ufs = applyProjection<UnstableFinalState>(event, "UFS");

      if (lfs.chargedLeptons().empty())
      {
          MSG_DEBUG("Event failed lepton multiplicity cut");
	  vetoEvent;
      }
      h_nChrgLeps->fill(lfs.chargedLeptons().size(),weight);

      const FastJets& jetpro = applyProjection<FastJets>(event, "Jets");
      
      const Jets jets = jetpro.jetsByPt(20.0*GeV);
      h_njets->fill(jets.size(), weight);
     // Sort the jets into b-jets and light jets. We expect one hard b-jet from
     // each top decay, so our 4 hardest jets should include two b-jets. The
     // Jet::containsBottom() method is equivalent to perfect experimental
     // b-tagging, in a generator-independent way.
     
     Jets bjets, ljets;
     foreach (const Jet& jet, jets)
     {
     	// Don't count jets that overlap with the hard leptons
     	bool isolated = true;
        foreach (const Particle& lepton, lfs.chargedLeptons()) 
	{
              if (deltaR(jet.momentum(), lepton.momentum()) < 0.3) 
              {
     	      	   isolated = false;
                   break;
              }
        }
        if (!isolated)
        {
             MSG_DEBUG("Jet failed lepton isolation cut");
             break;
        }
        if( jet.momentum().pt()/GeV > 20)
        {
		if (jet.containsBottom()) 
		{
		     bjets.push_back(jet);
		} 
		else 
		{
		   ljets.push_back(jet);
		}
	}
   }
   h_nbjets->fill(bjets.size(),weight);
   h_nljets->fill(ljets.size(),weight);

   //Do b-jet analysis
   for(int i =0; i <bjets.size(); ++i)
   {
	for(int j=i; j<bjets.size(); ++j)
	{
	    Jet b1 = bjets[i];
	    Jet b2 = bjets[j]; 
            
            h_b1_b2_dEta->fill( deltaEta(b1,b2),weight );
	    h_b1_b2_dPhi->fill( deltaPhi(b1,b2),weight );
	    h_b1_b2_dR  ->fill( deltaR(b1,b2),weight );
         }
   }

   const WFinder& wfinder = applyProjection<WFinder>(event, "WFinder");
   if (wfinder.bosons().size() != 1) {
       vetoEvent;
    }
    else {
         h_wlep_mass->fill(wfinder.bosons().front().momentum().mass(),weight);
         h_wlep_pt->fill(wfinder.bosons().front().momentum().pt(),weight);
	 h_wlep_eta->fill(wfinder.bosons().front().momentum().eta(),weight);
         h_wlep_phi->fill(wfinder.bosons().front().momentum().phi(),weight);
    }

    //Find Hadronically decaying W 
    std::vector<FourMomentum> WCandCont;
    FourMomentum W(10*sqrtS(), 0, 0, 0);
    for (size_t i = 0; i < ljets.size(); i++) {
        for (size_t j = i + 1; j < ljets.size(); j++) {
            const FourMomentum Wcand = ljets[i].momentum() + ljets[j].momentum();
            MSG_TRACE(i << "," << j << ": candidate W mass = " << Wcand.mass()/GeV
                     << " GeV, vs. incumbent candidate with " << W.mass()/GeV << " GeV");
            if (deltaR(ljets[i].momentum(),ljets[j].momentum()) < 1.2) {
            WCandCont.push_back(Wcand);
            }
        }
     }
     if(WCandCont.size() <2) vetoEvent;

     h_wHad1_mass->fill(WCandCont[0].mass(),weight);
     h_wHad1_pt->fill(WCandCont[0].pt(),weight);
     h_wHad1_eta->fill(WCandCont[0].eta(),weight);
     h_wHad1_phi->fill(WCandCont[0].phi(),weight);
 
     h_wHad2_mass->fill(WCandCont[1].mass(),weight);
     h_wHad2_pt->fill(WCandCont[1].pt(),weight);
     h_wHad2_eta->fill(WCandCont[1].eta(),weight);
     h_wHad2_phi->fill(WCandCont[1].phi(),weight);


    for(size_t i =0; i < bjets.size(); ++i)
    {
        Jet b1 = bjets[i];
        for (size_t j=0; j<WCandCont.size(); ++j)
	{
     	    FourMomentum W = WCandCont[j];
	    if(deltaR(W,b1.momentum())>1.2 && deltaR(W,b1.momentum())<2)
	    {
		 FourMomentum topCand = W+b1.momentum();
            	 h_top_mass->fill(topCand.mass(),weight);
    	   	 h_top_pt->fill(topCand.pt(),weight);
	    	 h_top_eta->fill(topCand.eta(),weight);
	    	 h_top_phi->fill(topCand.phi(),weight);
	    }
	}

     }
   
   }


    /// Normalise histograms etc., after the run
    void finalize() {

      /// @todo Normalise, scale and otherwise manipulate histograms here

      // scale(_h_YYYY, crossSection()/sumOfWeights()); // norm to cross section
      // normalize(_h_YYYY); // normalize to unity
      normalize(h_nChrgLeps);
      normalize(h_njets);
      normalize(h_nljets);
      normalize(h_nljets);

    }

    //@}


  private:

    // Data members like post-cuts event weight counters go here


    /// @name Histograms
    //@{
    Profile1DPtr _h_XXXX;
    Histo1DPtr _h_YYYY;
    
    //Counters
    Histo1DPtr h_njets;
    Histo1DPtr h_nChrgLeps;
    Histo1DPtr h_nbjets;
    Histo1DPtr h_nljets;

   //kinematic variables
   Histo1DPtr h_b1_pt;
   Histo1DPtr h_b2_pt;
   Histo1DPtr h_l1_pt;
   Histo1DPtr h_l2_pt;
   
   Histo1DPtr h_b1_b2_dEta;
   Histo1DPtr h_b1_b2_dPhi;
   Histo1DPtr h_b1_b2_dR;

   Histo1DPtr h_top_mass;
   Histo1DPtr h_top_pt;
   Histo1DPtr h_top_eta;
   Histo1DPtr h_top_phi;

   Histo1DPtr h_wlep_mass;
   Histo1DPtr h_wlep_pt;
   Histo1DPtr h_wlep_eta;
   Histo1DPtr h_wlep_phi;
 
   Histo1DPtr h_wHad1_mass;
   Histo1DPtr h_wHad1_pt;
   Histo1DPtr h_wHad1_eta;
   Histo1DPtr h_wHad1_phi;

   Histo1DPtr h_wHad2_mass;
   Histo1DPtr h_wHad2_pt;
   Histo1DPtr h_wHad2_eta;
   Histo1DPtr h_wHad2_phi;

    //@}


  };



  // The hook for the plugin system
  DECLARE_RIVET_PLUGIN(ttw_analysis);

}
