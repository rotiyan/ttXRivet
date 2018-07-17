#!/bin/bash

#export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/
#export ALRB_localConfigDir=/code/localConfig
#. /cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/user/atlasLocalSetup.sh
#lsetup panda
#lsetup asetup
#asetup 19.3.0.1,here
lsetup "asetup 19.2.5.33.1,MCProd,here"
lsetup panda

timeStamp=`date +%H%M%S_%m%Y`

pathena -c 'xs=1.0' --noBuild --extFile=Rivet_TTZ_analysis.so --extOutFile=ttll_study.yoda  --inDS=mc15_13TeV.410218.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttee.evgen.EVNT.e5070 --outDS=user.narayan.${timeStamp}.MG5_ttZ_ee_410218_180702/ ttll_jo.py
pathena -c 'xs=1.0' --noBuild --extFile=Rivet_TTZ_analysis.so --extOutFile=ttll_study.yoda  --inDS=mc15_13TeV.410219.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttmumu.evgen.EVNT.e5070 --outDS=user.narayan.${timeStamp}.MG5_ttZ_mumu_410219_180702/ ttll_jo.py
pathena -c 'xs=1.0' --noBuild --extFile=Rivet_TTZ_analysis.so --extOutFile=ttll_study.yoda  --inDS=mc15_13TeV.410220.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_tttautau.evgen.EVNT.e5070 --outDS=user.narayan.${timeStamp}.MG5_ttZ_tautau_410220_180702/ ttll_jo.py
pathena -c 'xs=1.0' --noBuild --extFile=Rivet_TTZ_analysis.so --extOutFile=ttll_study.yoda  --inDS=user.narayan.ttZ_Sherpa225_NLO_180627_EXT1/ --outDS=user.narayan.${timeStamp}.Sherpa225_ttZ_180702/ ttll_jo.py
