from glob import glob
print "HELLO",myCs

theApp.EvtMax = 1

import AthenaPoolCnvSvc.ReadAthenaPool
#svcMgr.EventSelector.InputCollections = glob("/data/narayan/user.narayan.Sherpa_CT10_ttll.1M_EXT0.284*/*.root*")
svcMgr.EventSelector.InputCollections=['/code/rohin/mcvalid/josh_jo/WorkArea/run/MadgraphControl_ttV_LO_Pythia8_A14_CKKWLkTMerge.pool.root']
from AthenaCommon.AlgSequence import AlgSequence
job = AlgSequence()

print "HELLO",myCs
