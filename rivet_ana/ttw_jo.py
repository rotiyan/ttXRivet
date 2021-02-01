from glob import glob
import sys,os


theApp.EvtMax = -1
#theApp.EvtMax=500

import AthenaPoolCnvSvc.ReadAthenaPool
#svcMgr.EventSelector.InputCollections = glob("~/samples/user.mcfayden.evnt.2015-05-07_025309.200001.8TeV_ttZlloff_EXT1/*.root*")
#svcMgr.EventSelector.InputCollections=['/code/rohin/mcvalid/josh_jo/WorkArea/run/MadgraphControl_ttV_LO_Pythia8_A14_CKKWLkTMerge.pool.root']
if os.path.exists("input.txt"):
    with open('input.txt') as f:
        svcMgr.EventSelector.InputCollections = [x.strip("\n") for x in f.read().split(",")]

else:
    svcMgr.EventSelector.InputCollections=['/scratch/users/rnarayan/mcProd/ttV/ttW_2210/inclusive/nominal/530/EVNT_530.pool.root']

#svcMgr.EventSelector.InputCollections= glob("/afs/cern.ch/user/n/narayan/work/mcProd/sherpa/pmg-rivet/rivet_plugins/user.narayan.ttZ_Sherpa225_NLO_180627_EXT1/*")

#print sys.argv[1]
#svcMgr.EventSelector.InputCollections= sys.argv[1]


from AthenaCommon.AlgSequence import AlgSequence
job = AlgSequence()

from Rivet_i.Rivet_iConf import Rivet_i

import os
rivet = Rivet_i()
rivet.AnalysisPath = os.environ['PWD']

#rivet.Analyses +=["ttW_revised"]
rivet.Analyses +=['ttw_analysis']
rivet.RunName = ""
rivet.HistoFile = "ttw_analysis"
rivet.CrossSection = xs # xs to be read from athena or pathena commandline
print "CrossSection",xs
job += rivet
