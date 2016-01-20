from glob import glob


theApp.EvtMax = -1

import AthenaPoolCnvSvc.ReadAthenaPool
svcMgr.EventSelector.InputCollections = glob('/home/narayan/samples/user.mcfayden.evnt.2015-05-07_144035.400002.8TeV_ttW_EXT1/*.')

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
