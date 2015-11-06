export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/
export ALRB_localConfigDir=/code/localConfig
. /cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/user/atlasLocalSetup.sh
lsetup panda
lsetup asetup
asetup 19.3.0.1,here 

timeStamp=`date +%H%M%S_%m%Y`

pathena -c 'xs=0.054658' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile=ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-08-14_111245.410000.13TeV_ttll_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410000_13TeV_ttll_phase2_dressed/ rivet_MC_jo.py
