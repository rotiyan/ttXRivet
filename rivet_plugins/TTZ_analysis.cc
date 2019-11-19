#include "Rivet/Analysis.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/InvMassFinalState.hh"
#include "Rivet/Projections/PromptFinalState.hh"
#include "Rivet/Projections/HeavyHadrons.hh"
#include "Rivet/Projections/VetoedFinalState.hh"
#include "Rivet/Projections/ChargedLeptons.hh"
#include "Rivet/Projections/ChargedFinalState.hh"
#include "Rivet/Projections/MissingMomentum.hh"
#include "Rivet/Projections/IdentifiedFinalState.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/AnalysisLoader.hh"

namespace Rivet
{
    class TTZ_analysis : public Analysis
    {
        public:
            TTZ_analysis(): Analysis("TTZ_analysis"){}

            void init()
            {
                IdentifiedFinalState electrons(FinalState(-4,4,10*GeV));
                electrons.acceptId(PID::ELECTRON);
                electrons.acceptId(PID::POSITRON);
                addProjection(electrons,"EFS");

                IdentifiedFinalState muons(FinalState(-4,4,10*GeV));
                muons.acceptId(PID::MUON);
                muons.acceptId(PID::ANTIMUON);
                addProjection(muons,"MUFS");

                ChargedLeptons lfs(FinalState(-4,4,10*GeV));
                addProjection(lfs,"LFS");

                ChargedFinalState cfs(FinalState(-4,4,0*GeV));
                addProjection(cfs,"CFS");

                addProjection(HeavyHadrons(Cuts::abseta <5 && Cuts::pT >5*GeV),"BCHadrons");

                //FinalState to reconstruct jets
                VetoedFinalState fs (FinalState(-4,4,0*GeV));
                fs.addVetoOnThisFinalState(lfs);
                addProjection(FastJets(fs, FastJets::ANTIKT,0.4),"Jets");
                addProjection(MissingMomentum(fs),"MissingET");

                IdentifiedFinalState nu_id(FinalState(-4,4,0*GeV));
                nu_id.acceptNeutrinos();
                PromptFinalState neutrinos(nu_id);
                addProjection(neutrinos,"Neutrinos");

                VetoedFinalState vfs(FinalState(-4,4,0*GeV));
                vfs.addVetoOnThisFinalState(lfs);
                addProjection(vfs,"VFS");

                //Initialize Histograms
                //
                _h_sumWeights   = bookHisto1D("sumWeights",5,1,5);
                _h_event_MET    = bookHisto1D("event_MET",200,10,100);
                _h_event_nJets  = bookHisto1D("event_nJets",20,-0.5,19.5);
                _h_event_HT     = bookHisto1D("event_HT",200,20,100);
                _h_event_nEl    = bookHisto1D("event_nEl",20,-0.5,19.5);
                _h_event_nMu    = bookHisto1D("event_nMu",20,-0.5,19.5);

                _h_diEl_mass    = bookHisto1D("diEl_mass",240,0,120);
                _h_diEl_pt      = bookHisto1D("diEl_pt",200,10,210);
                _h_diEl_eta     = bookHisto1D("diEl_eta",100,-4,4);
                _h_diEl_phi     = bookHisto1D("diEl_phi",100,0,6);

                _h_diMu_mass    = bookHisto1D("diMu_mass",240,0,120);
                _h_diMu_pt      = bookHisto1D("diMu_pt",200,10,210);
                _h_diMu_eta     = bookHisto1D("diMu_eta",100,-4,4);
                _h_diMu_phi     = bookHisto1D("diMu_phi",100,0,6);

                _h_WLep_mass    = bookHisto1D("WLep_mass",240,0,120);
                _h_WLep_pt      = bookHisto1D("WLep_pt",200,10,210);
                _h_WLep_eta     = bookHisto1D("WLep_eta",100,-4,4);
                _h_WLep_phi     = bookHisto1D("Wlept_phi",100,0,6);

                _h_WHad_mass    = bookHisto1D("WHad_mass",240,0,120);
                _h_WHad_pt      = bookHisto1D("WHad_pt",200,10,210);
                _h_WHad_eta     = bookHisto1D("WHad_eta",100,-4,4);
                _h_WHad_phi     = bookHisto1D("WHad_phi",100,0,6);

                _h_top_mass     = bookHisto1D("top_mass",200,120,380);
                _h_top_pt       = bookHisto1D("top_pt",100,150,250);
                _h_top_eta      = bookHisto1D("top_eta",100,-4,4);
                _h_top_phi      = bookHisto1D("top_phi",100,0,6);


                _h_top_dR       = bookHisto1D("top_dR",50,0,2);
                _h_top_dEta     = bookHisto1D("top_dEta",50,0,3);
                _h_top_dPhi     = bookHisto1D("top_dPhi",100,0,3);


            }

            void analyze(const Event & event)
            {
                const double weight       = event.weight();

                const ChargedLeptons& lfs = applyProjection<ChargedLeptons>(event, "LFS");
                const Particles electrons = applyProjection<IdentifiedFinalState>(event,"EFS").particles();

                const MissingMomentum &met = applyProjection<MissingMomentum>(event,"MissingET");
                _MET = met.vectorEt().mod();

                _h_event_MET->fill(_MET/GeV,weight);
                _h_sumWeights->fill(1,weight);

                if(met.vectorEt().mod()<10*GeV)
                {
                    vetoEvent;
                }



                Particles muons = applyProjection<IdentifiedFinalState>(event,"MUFS").particles();

                const FastJets & jetpro = applyProjection<FastJets>(event, "Jets");
                const Jets alljets      = jetpro.jetsByPt(20*GeV);

                Particles cand_e;
                //Discard two electrons within R=0.1
                std::vector<bool> vetoed(electrons.size(),false);
                for(size_t i =0;i<electrons.size(); ++i)
                {
                    if(vetoed[i]) continue;

                    for(size_t j=i+1; j <electrons.size(); ++j)
                    {
                        if(deltaR(electrons[i],electrons[j]) <0.1)
                        {
                            vetoed[j]=true;
                        }
                    }

                    if(vetoed[i]==false)
                    {
                        cand_e.push_back(electrons[i]);
                    }
                }

                //Keep electrons away from jets.
                Particles cand2_e;

                foreach(const Particle &e, cand_e)
                {
                    bool away = true;
                    foreach(const Jet& jet, jetpro.jetsByPt())
                    {
                        if(deltaR(e,jet) <0.4)
                        {
                            away = false;
                            break;
                        }
                    }
                    if(away)
                    {
                        cand2_e.push_back(e);
                    }
                }

                //Keep muons away from jets
                Particles cand2_mu;
                foreach(const Particle &mu, muons)
                {
                    bool away = true;
                    foreach(const Jet& jet, jetpro.jetsByPt())
                    {
                        if(deltaR(mu,jet)<0.4)
                        {
                            away = false;
                            break;
                        }
                    }
                    if(away) cand2_mu.push_back(mu);
                }

                //Electron isolation
                Particles charg_particles = applyProjection<ChargedFinalState>(event,"CFS").particles();
                Particles cand3_e;
                foreach(const Particle&e, cand2_e)
                {
                    double ptInCone = -e.pT(); //Substract the electron pt
                    foreach(const Particle&p, charg_particles)
                    {
                        if(p.pT() >0.4*GeV && deltaR(e,p) <=0.3)
                        {
                            ptInCone += p.pT();
                        }
                    }
                    if(ptInCone/e.pT() <0.18) cand3_e.push_back(e);
                }

                //Muon isolation
                Particles cand3_mu;
                foreach(const Particle &mu,cand2_mu)
                {
                    double ptInCone = -mu.pT();
                    foreach( const Particle &track, charg_particles)
                    {
                        if(track.pT()>1*GeV && deltaR(mu,track) <=0.3)
                        {
                            ptInCone += track.pT();
                        }
                    }
                    if(ptInCone/mu.pT() <0.12) cand3_mu.push_back(mu);
                }

                //Select same flavour opposite sign pairs
                Particles recon_e,recon_mu;
                std::vector<FourMomentum> diEl_FourMom,diMu_FourMom;

                if (cand3_e.size() > 2 ) vetoEvent;
                if (cand3_mu.size()> 2 ) vetoEvent;

                for(size_t i =0;i<cand3_e.size(); ++i)
                {
                    for(size_t j=i+1; j< cand3_e.size();++j)
                    {
                        if(cand3_e[i].pid()*cand3_e[j].pid()<0 &&deltaR(cand3_e[i],cand3_e[j])>0.2)
                            diEl_FourMom.push_back(cand3_e[i].momentum() + cand3_e[j].momentum());
                    }
                }

                for(size_t i=0; i <cand3_mu.size(); ++i)
                {
                    for(size_t j=i+1; j<cand3_mu.size(); ++j)
                    {
                        if(cand3_mu[i].pid()*cand3_mu[j].pid()<0 && deltaR(cand3_mu[i],cand3_mu[j])>0.2)
                            diMu_FourMom.push_back(cand3_mu[i].momentum() + cand3_mu[j].momentum());
                    }
                }

                bool diElEvent=false;
                bool diMuEvent=false;

                FourMomentum zeeCand(10*sqrtS(),0.,0.,0.);
                float targetMass = 91.2*GeV;
                foreach(const FourMomentum &vec, diEl_FourMom)
                {
                    if(1<vec.mass()/GeV && 120>vec.mass()/GeV)
                    {
                        MSG_INFO("diEl Mass diff:"<< fabs(vec.mass()-targetMass));
                        if(fabs(vec.mass()-targetMass) < zeeCand.mass()-targetMass)
                        {
                            const FourMomentum myVec = vec;
                            zeeCand = myVec;
                            diElEvent =true;
                        }
                    }
                }
                if(diElEvent)
                {
                    _h_diEl_mass->fill(zeeCand.mass()/GeV,weight);
                    _h_diEl_pt->fill(zeeCand.pT()/GeV,weight);
                    _h_diEl_eta->fill(zeeCand.eta(),weight);
                    _h_diEl_phi->fill(zeeCand.phi()/weight);
                }

                FourMomentum zmumuCand(0.,0.,0.,0.);
                foreach(const FourMomentum &vec, diMu_FourMom)
                {
                    if(1<vec.mass()/GeV && 120 >vec.mass()/GeV)
                    {
                        if(fabs(vec.mass()-targetMass) < zeeCand.mass()-targetMass)
                        {
                            const FourMomentum myVec = vec;
                            zmumuCand = myVec;
                            diMuEvent =true;
                        }
                    }
                }
                if(diMuEvent)
                {
                    _h_diMu_mass->fill(zmumuCand.mass()/GeV,weight);
                    _h_diMu_pt->fill(zmumuCand.pT()/GeV,weight);
                    _h_diMu_eta->fill(zmumuCand.eta(),weight);
                    _h_diMu_phi->fill(zmumuCand.phi(),weight);
                }

                if(!(diElEvent||diMuEvent))
                {
                    vetoEvent;
                    MSG_INFO("Failed diLepton inv Mass cut");
                }

                //Find Leptonic W's 
                const Particles neutrinos = applyProjection<PromptFinalState>(event,"Neutrinos").particles();
                //LoopOver electrons and muons to find the Wlep candidate
                FourMomentum Wel(10*sqrtS(),0.,0.,0.);
                FourMomentum Wmu(10*sqrtS(),0.,0.,0.);

                foreach(const Particle &nu,neutrinos)
                {
                    foreach(Particle &el,cand3_e)
                    {
                        const FourMomentum WCand = el.momentum() + nu.momentum();
                        if(fabs(WCand.mass()-80.4*GeV) < Wel.mass()-80.04*GeV) Wel = WCand;
                    }
                    foreach(Particle &mu,cand3_mu)
                    {
                        const FourMomentum WCand = mu.momentum() + nu.momentum();
                        if(fabs(WCand.mass()-80.4*GeV) < Wmu.mass()-80.04*GeV) Wmu = WCand;
                    }
                }
                MSG_INFO("Wel mass:"<<Wel.mass()/GeV);

                _h_WLep_mass->fill(Wel.mass()/GeV,weight);
                _h_WLep_mass->fill(Wmu.mass()/GeV,weight);
                _h_WLep_pt->fill(Wel.pT()/GeV,weight);
                _h_WLep_pt->fill(Wmu.pT()/GeV,weight);
                _h_WLep_eta->fill(Wel.eta(),weight);
                _h_WLep_eta->fill(Wmu.eta(),weight);

                //Do B-jets..

                //Get b-hadrons
                const Particles bhadrons = sortByPt(applyProjection<HeavyHadrons>(event,"BCHadrons").bHadrons());

                const Jets jets = jetpro.jetsByPt(20*GeV);
                Jets bjets,ljets;
                foreach(const Jet &jet,jets)
                {
                    bool isolated =true;
                    foreach (const Particle &lepton, lfs.chargedLeptons())
                    {
                        if(deltaR(jet.momentum(),lepton.momentum())<0.3)
                        {
                            isolated = false;
                            break;
                        }
                    }
                    if(!isolated)
                    {
                        MSG_INFO("Jet failed lepton isolation cut");
                        break;
                    }
                    foreach( const Particle & b, bhadrons)
                    {
                        if(deltaR(jet,b) < 0.3)
                        {
                            bjets.push_back(jet);
                        }
                        else
                        {
                            ljets.push_back(jet);
                        }
                    }
                }
                MSG_INFO("Number of b-jets = "<<bjets.size());
                MSG_INFO("Number of l-jets = "<< ljets.size());
                if(bjets.size() < 2)
                {
                    MSG_INFO("#bjets < 2");
                    vetoEvent;

                }
                if(ljets.size()<2)
                {
                    MSG_INFO("l-jets<2");
                    vetoEvent;
                }

                double ht=0;
                foreach (const Jet &jet,jets)
                {
                    ht += jet.pT();
                }
                _h_event_HT->fill(ht/GeV,weight);
                _h_event_nJets->fill(jets.size(),weight);
                _h_event_nEl->fill(cand3_e.size(),weight);
                _h_event_nMu->fill(cand3_mu.size(),weight);

                //Find W candidate
                FourMomentum W(10*sqrtS(),0,0,0);
                for(size_t i =0;i<ljets.size()-1;++i)
                {
                    for(size_t j =i+1; j<ljets.size();++j)
                    {
                        const FourMomentum Wcand = ljets[i].momentum() + ljets[j].momentum();
                        if(fabs(Wcand.mass() - 80.4*GeV) < fabs(W.mass() -80.4*GeV))
                        {
                            W = Wcand;
                        }
                    }
                }
                _h_WHad_mass->fill(W.mass());
                _h_WHad_pt->fill(W.pt());
                _h_WHad_eta->fill(W.eta());
                _h_WHad_phi->fill(W.phi());

                //Construct top candidates
                const FourMomentum t1 = W + bjets[0].momentum();
                const FourMomentum t2 = W + bjets[1].momentum();

                _h_top_mass->fill(t1.mass()/GeV,weight);
                _h_top_mass->fill(t2.mass()/GeV,weight);
                MSG_INFO("What is picobarn"<<picobarn);

            }

            void finalize()
            {
                float norm = crossSection()/picobarn/sumOfWeights();
                norm = 1.0;

                scale(_h_event_MET,norm);
                scale(_h_event_nJets,norm);
                scale(_h_event_HT,norm);
                scale(_h_event_nEl,norm);
                scale(_h_event_nMu,norm);

                scale(_h_diEl_mass,norm);
                scale(_h_diEl_pt,norm);
                scale(_h_diEl_eta,norm);
                scale(_h_diEl_phi,norm);

                scale(_h_diMu_mass,norm);
                scale(_h_diMu_pt,norm);
                scale(_h_diMu_eta,norm);
                scale(_h_diMu_phi,norm);

                scale(_h_WLep_mass,norm);
                scale(_h_WLep_pt,norm);
                scale(_h_WLep_eta,norm);
                scale(_h_WLep_phi,norm);

                scale(_h_WHad_mass,norm);
                scale(_h_WHad_pt,norm);
                scale(_h_WHad_eta,norm);
                scale(_h_WHad_phi,norm);

                scale(_h_top_mass,norm);
                scale(_h_top_pt,norm);
                scale(_h_top_eta,norm);
                scale(_h_top_phi,norm);


                scale(_h_top_dR,norm);
                scale(_h_top_dEta,norm);
                scale(_h_top_dPhi,norm);

            }

        private:
            Histo1DPtr _h_sumWeights;
            Histo1DPtr _h_event_MET;
            Histo1DPtr _h_event_nJets;
            Histo1DPtr _h_event_HT;
            Histo1DPtr _h_event_nEl;
            Histo1DPtr _h_event_nMu;

            Histo1DPtr _h_diEl_mass;
            Histo1DPtr _h_diEl_pt;
            Histo1DPtr _h_diEl_eta;
            Histo1DPtr _h_diEl_phi;

            Histo1DPtr _h_diMu_mass;
            Histo1DPtr _h_diMu_pt;
            Histo1DPtr _h_diMu_eta;
            Histo1DPtr _h_diMu_phi;

            Histo1DPtr _h_WLep_mass;
            Histo1DPtr _h_WLep_pt;
            Histo1DPtr _h_WLep_eta;
            Histo1DPtr _h_WLep_phi;

            Histo1DPtr _h_WHad_mass;
            Histo1DPtr _h_WHad_pt;
            Histo1DPtr _h_WHad_eta;
            Histo1DPtr _h_WHad_phi;

            Histo1DPtr _h_top_mass;
            Histo1DPtr _h_top_pt;
            Histo1DPtr _h_top_eta;
            Histo1DPtr _h_top_phi;


            Histo1DPtr _h_top_dR;
            Histo1DPtr _h_top_dEta;
            Histo1DPtr _h_top_dPhi;

            float _MET;

    };

    DECLARE_RIVET_PLUGIN(TTZ_analysis);
}
