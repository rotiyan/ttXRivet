export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/
export ALRB_localConfigDir=/code/localConfig
. /cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/user/atlasLocalSetup.sh
localSetupPandaClient
asetup 19.2.3.9,here 

timeStamp=`date +%H%M%S_%m%Y`

pathena -c 'xs=0.054658' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile=ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-08-14_111245.410000.13TeV_ttll_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410000_13TeV_ttll/ rivet_MC_jo.py

pathena -c 'xs=0.54136' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile=ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-08-14_111624.410003.13TeV_ttW_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410003_13TeV_ttW/ rivet_MC_jo.py

pathena -c 'xs=0.01471' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile=ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-08-15_120748.410000.8TeV_ttll_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410000_8TeV_ttll/ rivet_MC_jo.py

pathena -c 'xs=0.20102' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile=ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-08-15_120924.410003.8TeV_ttW_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410003_8TeV_ttW/ rivet_MC_jo.py
