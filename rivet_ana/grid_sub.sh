#!/bin/sh

timeStamp=`date +%H%M%S_%m%Y`
#prun --exec "grid_run.sh " --writeInputToTxt %IN:input.txt  --nFilesPerJob=2 --inDS=mc15_13TeV.410218.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttee.evgen.EVNT.e5070 --extFile=Rivet_TTZ_analysis.so --outputs ttll_study.yoda --outDS=user.narayan.${timeStamp}.MG5_ttZ_ee_410218/

#prun --exec "grid_run.sh " --writeInputToTxt %IN:input.txt --nFilesPerJob=2 --inDS=mc15_13TeV.410219.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttmumu.evgen.EVNT.e5070 --extFile=Rivet_TTZ_analysis.so --outputs ttll_study.yoda --outDS=user.narayan.${timeStamp}.MG5_ttZ_mumu_410219/

#prun --exec "grid_run.sh " --writeInputToTxt %IN:input.txt --nFilesPerJob=10 --inDS=user.narayan.ttZ_Sherpa225_NLO_180627_EXT1/ --extFile=Rivet_TTZ_analysis.so --outputs ttll_study.yoda --outDS=user.narayan.${timeStamp}.Sherpa225_ttZ 


#prun --exec "grid_run.sh " --writeInputToTxt %IN:input.txt --nFilesPerJob=10 --inDS=user.narayan.ttZ_Sherpa225_NLO_180627_EXT1/ --extFile=Rivet_TTZ_analysis.so --outputs ttll_study.yoda --outDS=user.narayan.${timeStamp}.Sherpa225_ttZ 

#prun --exec "grid_run.sh " --writeInputToTxt %IN:input.txt --nFilesPerJob=10 --inDS=mc15_13TeV.410220.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_tttautau.evgen.EVNT.e5070 --extFile=Rivet_TTZ_analysis.so --outputs ttll_study.yoda --outDS=user.narayan.${timeStamp}.MG5_ttZ_tautau_410220

#prun --exec "grid_run.sh " --writeInputToTxt %IN:input.txt --nFilesPerJob=10 --inDS=user.narayan.ttZ_Sherpa225_NLO_180811_EXT1 --extFile=Rivet_TTZ_analysis.so --outputs ttll_study.yoda --outDS=user.narayan.${timeStamp}.Sherpa225_Rivet
#prun --exec "grid_run.sh " --writeInputToTxt %IN:input.txt --nFilesPerJob=10 --inDS=mc15_13TeV.410155.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttW.evgen.EVNT.e5070 --extFile=RivetAnalysis.so --outputs ttw_analysis.yoda --outDS=user.narayan.${timeStamp}.410155.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttW.evgen 
#
#prun --exec "grid_run.sh " --writeInputToTxt %IN:input.txt --nFilesPerJob=10 --inDS=mc15_13TeV.413008.Sherpa_221_NN30NNLO_ttW_multilegNLO.evgen.EVNT.e7286 --extFile=RivetAnalysis.so --outputs ttw_analysis.yoda --outDS=user.narayan.${timeStamp}.413008.Sherpa_221_NN30NNLO_ttW_multilegNLO.evgen.EVNT.e7286 

prun --exec "grid_run.sh " --writeInputToTxt %IN:input.txt --nFilesPerJob=100 --inDS=mc16_13TeV.700000.Sh_228_ttW.merge.EVNT.e7793_e7400 --extFile=Rivet_ttW_ttH_analysis.so --outputs Rivet.root --outDS=user.narayan.${timeStamp}.700000.Sherpa_228_ttWEWK_20200821

#prun --exec "grid_run.sh " --writeInputToTxt %IN:input.txt --nFilesPerJob=100 --inDS=mc16_13TeV.413023.Sherpa_221_ttll_multileg_NLO.merge.EVNT.e7504_e5984 --extFile=RivetTTZ_analysis.so --outputs Rivet.root --outDS=user.narayan.${timeStamp}.413023.Sherpa_221_ttll_20200821/
