#!/bin/bash

export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/
export ALRB_localConfigDir=/code/localConfig
. /cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/user/atlasLocalSetup.sh

lsetup "asetup 21.6.33,AthGeneration"
#source ${LCG_RELEASE_BASE}/LCG_88/MCGenerators/rivet/${RIVETVER}/${LCG_PLATFORM}/rivetenv.sh

#athena -c "xs=1.0" ttw_tth_jo.py
athena -c "xs=1.0" ttll_jo.py
#athena -c "xs=1.0" ttx_jo.py


lsetup "lcgenv -p LCG_88 $LCG_PLATFORM yoda  1.8.3"
python yoda2root.py ttll_study.yoda ;
cp ttll_study.root Rivet.root
