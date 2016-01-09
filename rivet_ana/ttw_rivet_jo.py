from glob import glob


theApp.EvtMax = -1

import AthenaPoolCnvSvc.ReadAthenaPool
svcMgr.EventSelector.InputCollections = glob('/scratch/rohin/user.mcfayden.evnt.test.2015-04-29_153313.300001.test_EXT1.26329904/*')

from AthenaCommon.AlgSequence import AlgSequence
job = AlgSequence()

from Rivet_i.Rivet_iConf import Rivet_i

import os
rivet = Rivet_i()
rivet.AnalysisPath = os.environ['PWD']

rivet.Analyses += [ 'ttw_analysis']
rivet.RunName = ""
rivet.HistoFile = "myanalysis"
rivet.CrossSection = xs
job += rivet
