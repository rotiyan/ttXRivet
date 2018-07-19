#!/bin/sh

timeStamp=`date +%H%M%S_%m%Y`
#prun --exec "grid_run.sh " --writeInputToTxt %IN:input.txt  --nFilesPerJob=2 --inDS=mc15_13TeV.410218.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttee.evgen.EVNT.e5070 --extFile=Rivet_TTZ_analysis.so --outputs ttll_study.yoda --outDS=user.narayan.${timeStamp}.MG5_ttZ_ee_410218/

#prun --exec "grid_run.sh " --writeInputToTxt %IN:input.txt --nFilesPerJob=2 --inDS=mc15_13TeV.410219.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttmumu.evgen.EVNT.e5070 --extFile=Rivet_TTZ_analysis.so --outputs ttll_study.yoda --outDS=user.narayan.${timeStamp}.MG5_ttZ_mumu_410219/

#prun --exec "grid_run.sh " --writeInputToTxt %IN:input.txt --nFilesPerJob=10 --inDS=user.narayan.ttZ_Sherpa225_NLO_180627_EXT1/ --extFile=Rivet_TTZ_analysis.so --outputs ttll_study.yoda --outDS=user.narayan.${timeStamp}.Sherpa225_ttZ 


#prun --exec "grid_run.sh " --writeInputToTxt %IN:input.txt --nFilesPerJob=10 --inDS=user.narayan.ttZ_Sherpa225_NLO_180627_EXT1/ --extFile=Rivet_TTZ_analysis.so --outputs ttll_study.yoda --outDS=user.narayan.${timeStamp}.Sherpa225_ttZ 

prun --exec "grid_run.sh " --writeInputToTxt %IN:input.txt --nFilesPerJob=10 --inDS=mc15_13TeV.410220.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_tttautau.evgen.EVNT.e5070 --extFile=Rivet_TTZ_analysis.so --outputs ttll_study.yoda --outDS=user.narayan.${timeStamp}.MG5_ttZ_tautau_410220
