from glob import glob


theApp.EvtMax = -1
#theApp.EvtMax=500

import AthenaPoolCnvSvc.ReadAthenaPool
#svcMgr.EventSelector.InputCollections = glob("~/samples/user.mcfayden.evnt.2015-05-07_025309.200001.8TeV_ttZlloff_EXT1/*.root*")
#svcMgr.EventSelector.InputCollections=['/code/rohin/mcvalid/josh_jo/WorkArea/run/MadgraphControl_ttV_LO_Pythia8_A14_CKKWLkTMerge.pool.root']
#svcMgr.EventSelector.InputCollections=['/home/narayan/samples/user.mcfayden.evnt.2015-05-07_025309.200001.8TeV_ttZlloff_EXT1/user.mcfayden.5405795.EXT1._000186.mc12_7TeV.200001.EVNT.root']
svcMgr.EventSelector.InputCollections = glob("/data/onyisi/sherpa/ttll_hi_13TeV/*")
#svcMgr.EventSelector.InputCollections = glob('/data/narayan/josh_samples_massive/user.mcfayden.evnt.2015-10-25_182608.410111.13TeV_ttee/*')
#svcMgr.EventSelector.InputCollections = glob('/data/narayan/josh_samples_massive/user.mcfayden.evnt.2015-10-25_182708.410112.13TeV_ttee/*')
#svcMgr.EventSelector.InputCollections = glob('/data/narayan/josh_samples_massive/user.mcfayden.evnt.2015-10-25_182804.410113.13TeV_ttmumu/*')
#svcMgr.EventSelector.InputCollections = glob('/data/narayan/josh_samples_massive/user.mcfayden.evnt.2015-10-25_182859.410114.13TeV_ttmumu/*')
from AthenaCommon.AlgSequence import AlgSequence
job = AlgSequence()

from Rivet_i.Rivet_iConf import Rivet_i

import os
rivet = Rivet_i()
rivet.AnalysisPath = os.environ['PWD']

rivet.Analyses +=["TTBAR_ANA"]#,"hepmc_analysis"]
#rivet.Analyses +=["hepmc_analysis"]
#rivet.Analyses += ['TTZ_analysis','hepmc_analysis','TTBAR_ANA']
#rivet.Analyses += [ 'MC_JET','PDFS','GENERIC','PHOTONS','PHOTONINC','WINC','TTBAR_ANA','HFJET_ANA','ZINC','JETTAGS']
#rivet.Analyses+=["TTBAR_ANA"]
rivet.RunName = ""
rivet.HistoFile = "ttz_analysis"
rivet.CrossSection = xs # xs to be read from athena or pathena commandline
print "CrossSection",xs
job += rivet
