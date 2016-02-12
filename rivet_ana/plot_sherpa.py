import ROOT

f = ROOT.TFile("analysis.root")
t = f.Get("sherpa_valid")


outFile = ROOT.TFile("outFile.root","RECREATE")

h_el_mass = ROOT.TH1F("el_mass","el_mass",100,5,115)
h_mu_mass = ROOT.TH1F("mu_mass","mu_mass",100,5,115)

for ev in t:
    el_ptVec    = ev.el_pt
    el_etaVec   = ev.el_eta
    el_phiVec   = ev.el_phi
    el_eVec     = ev.el_e
    el_chVec    = ev.el_charge
    weight      = ev.evnt_weight

    mu_ptVec    = ev.mu_pt
    mu_etaVec   = ev.mu_eta
    mu_phiVec   = ev.mu_phi
    mu_eVec     = ev.mu_e
    mu_chVec    = ev.mu_charge
    
    if(el_chVec.size() ==2):
        if(el_chVec.at(0) == -el_chVec.at(1)):
            el_lv0 = ROOT.TLorentzVector()
            el_lv1 = ROOT.TLorentzVector()
            el_lv0.SetPtEtaPhiE(el_ptVec.at(0),el_etaVec.at(0),el_phiVec.at(0),el_eVec.at(0))
            el_lv1.SetPtEtaPhiE(el_ptVec.at(1),el_etaVec.at(1),el_phiVec.at(1),el_eVec.at(1))

            h_el_mass.Fill( (el_lv0 + el_lv1).M(), weight)

    if(mu_chVec.size() ==2):
        if(mu_chVec.at(0) == -mu_chVec.at(1)):
            mu_lv0 = ROOT.TLorentzVector()
            mu_lv1 = ROOT.TLorentzVector()
            mu_lv0.SetPtEtaPhiE(mu_ptVec.at(0),mu_etaVec.at(0),mu_phiVec.at(0),mu_eVec.at(0))
            mu_lv1.SetPtEtaPhiE(mu_ptVec.at(1),mu_etaVec.at(1),mu_phiVec.at(1),mu_eVec.at(1))

            h_mu_mass.Fill( (mu_lv0 + mu_lv1).M(), weight)
    
c = ROOT.TCanvas()
c.Divide(1,2)
c.cd(1)
h_el_mass.Draw()
c.cd(2)
h_mu_mass.Draw()

h_el_mass.Write()
h_mu_mass.Write()
outFile.Close()
