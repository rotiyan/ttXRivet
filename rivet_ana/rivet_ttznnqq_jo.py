from glob import glob

theApp.EvtMax = -1
#theApp.EvtMax=500

import AthenaPoolCnvSvc.ReadAthenaPool
#svcMgr.EventSelector.InputCollections = glob("~/samples/user.mcfayden.evnt.2015-05-07_025309.200001.8TeV_ttZlloff_EXT1/*.root*")
#svcMgr.EventSelector.InputCollections=['/code/rohin/mcvalid/josh_jo/WorkArea/run/MadgraphControl_ttV_LO_Pythia8_A14_CKKWLkTMerge.pool.root']
#svcMgr.EventSelector.InputCollections=['/home/narayan/samples/user.mcfayden.evnt.2015-05-07_025309.200001.8TeV_ttZlloff_EXT1/user.mcfayden.5405795.EXT1._000186.mc12_7TeV.200001.EVNT.root']
svcMgr.EventSelector.InputCollections=['/home/narayan/samples/mc15_valid.410073.MadGraphPythia8EvtGen_A14NNPDF23LO_ttZnnqq_Np0.evgen.EVNT.e4493_tid06645850_00/EVNT.06645850._000197.pool.root.1']
from AthenaCommon.AlgSequence import AlgSequence
job = AlgSequence()

from Rivet_i.Rivet_iConf import Rivet_i

import os
rivet = Rivet_i()
rivet.AnalysisPath = os.environ['PWD']

rivet.Analyses +=["ttznnqq_analysis"]
rivet.RunName = ""
rivet.HistoFile = "ttznnqq_analysis"
rivet.CrossSection = xs # xs to be read from athena or pathena commandline
print "CrossSection",xs
job += rivet
