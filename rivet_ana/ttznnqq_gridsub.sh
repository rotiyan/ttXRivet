export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/
export ALRB_localConfigDir=/code/localConfig
. /cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/user/atlasLocalSetup.sh
lsetup asetup
lsetup panda
asetup 19.3.0.1,here

timeStamp=`date +%H%M%S_%m%Y`

pathena -c 'xs=173.350' --noBuild --extFile=Rivetttznnq_analysis.so --nFilesPerJob=1 --long --extOutFile=rivetTree.root --inDS=mc15_valid.410073.MadGraphPythia8EvtGen_A14NNPDF23LO_ttZnnqq_Np0.evgen.EVNT.e4493/ --outDS=user.narayan.${timeStamp}.rivet-Madgraph_ttZnnqq_e4493/ rivet_ttznnqq_jo.py
#
pathena -c 'xs=122.280' --noBuild --extFile=Rivetttznnq_analysis.so --nFilesPerJob=1 --long --extOutFile=rivetTree.root --inDS=mc15_valid.410073.MadGraphPythia8EvtGen_A14NNPDF23LO_ttZnnqq_Np0.evgen.EVNT.e4462/ --outDS=user.narayan.${timeStamp}.rivet-Madgraph_ttZnnqq_e4462/ rivet_ttznnqq_jo.py

pathena -c 'xs=611' --noBuild --extFile=Rivetttznnq_analysis.so --nFilesPerJob=1 --long --extOutFile=rivetTree.root --inDS=user.narayan.sherpa2.2_ttZnnqq_13TeV --outDS=user.narayan.${timeStamp}.rivet-Sherpa2.2_ttZnnqq/ rivet_ttznnqq_jo.py
