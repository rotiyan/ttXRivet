export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/
export ALRB_localConfigDir=/code/localConfig
. /cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/user/atlasLocalSetup.sh
lsetup panda
lsetup asetup
asetup 19.3.0.1,here

timeStamp=`date +%H%M%S_%m%Y`


pathena -c 'xs=9.739' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=mc15_13TeV.410111.MadGraphPythia8EvtGen_A14NNPDF23LO_ttee_Np0.evgen.EVNT.e4632/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410111_13TeV_ttee_np1  multilep_jo.py

pathena -c 'xs=9.681' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_082424.410111.var1Up_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410111_var1Up/  multilep_jo.py

pathena -c 'xs=9.552' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_082912.410111.var1Dwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410111_var1Dwn/  multilep_jo.py

pathena -c 'xs=9.523' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_083445.410111.var2Up_EXT1/   --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410111_var2Up/  multilep_jo.py

pathena -c 'xs=9.665' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_085115.410111.var2Dwn_EXT1/  --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410111_var2Dwn/  multilep_jo.py

pathena -c 'xs=9.204' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_085703.410111.var3aUp_EXT1/  --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410111_var3aUp/  multilep_jo.py

pathena -c 'xs=9.807' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_091424.410111.var3aDwn_EXT1/   --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410111_var3aDwn/  multilep_jo.py

pathena -c 'xs=9.535' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_094300.410111.var3bUp_EXT1/  --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410111_var3bUp/  multilep_jo.py

pathena -c 'xs=9.674' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_094709.410111.var3bDwn_EXT1/   --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410111_var3bDwn/  multilep_jo.py

pathena -c 'xs=8.77' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_095046.410111.var3cUp_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410111_var3cUp/  multilep_jo.py

pathena -c 'xs=10.4' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_095431.410111.var3cDwn_EXT1/  --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410111_var3cDwn/  multilep_jo.py

##
pathena -c 'xs=17.25' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=mc15_13TeV.410112.MadGraphPythia8EvtGen_A14NNPDF23LO_ttee_Np1.evgen.EVNT.e4632/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410112_13TeV_ttee_np1/ multilep_jo.py

pathena -c 'xs=17.69' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_082424.410112.var1Up_EXT1/  --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410112_var1Up/ multilep_jo.py

pathena -c 'xs=17.26' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_082912.410112.var1Dwn_EXT1/  --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410112_var1Dwn/ multilep_jo.py

pathena -c 'xs=17.50' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_083445.410112.var2Up_EXT1/  --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410112_var2Up/ multilep_jo.py

pathena -c 'xs=17.10' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_085115.410112.var2Dwn_EXT1/  --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410112_var2Dwn/ multilep_jo.py

pathena -c 'xs=17.03' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_085703.410112.var3aUp_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410112_var3aUp/ multilep_jo.py

pathena -c 'xs=17.90' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_091424.410112.var3aDwn_EXT1/  --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410112_var3aDwn/ multilep_jo.py

pathena -c 'xs=17.28' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_094300.410112.var3bUp_EXT1/  --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410112_var3bUp/ multilep_jo.py

pathena -c 'xs=17.48' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_094709.410112.var3bDwn_EXT1/  --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410112_var3bDwn/ multilep_jo.py

pathena -c 'xs=18.25' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_095046.410112.var3cUp_EXT1/   --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410112_var3cUp/ multilep_jo.py

pathena -c 'xs=16.45' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_095431.410112.var3cDwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410112_var3cDwn/ multilep_jo.py

##

pathena -c 'xs=9.577' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=mc15_13TeV.410113.MadGraphPythia8EvtGen_A14NNPDF23LO_ttmumu_Np0.evgen.EVNT.e4632/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410113_13TeV_ttmumu_np0/  multilep_jo.py

pathena -c 'xs=9.49' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_082424.410113.var1Up_EXT1/  --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410113_var1Up/  multilep_jo.py

pathena -c 'xs=9.544' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_082912.410113.var1Dwn_EXT1/  --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410113_var1Dwn/  multilep_jo.py

pathena -c 'xs=9.764' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_083445.410113.var2Up_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410113_var2Up/  multilep_jo.py

pathena -c 'xs=9.688' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_085115.410113.var2Dwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410113_var2Dwn/  multilep_jo.py

pathena -c 'xs=9.377' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_085703.410113.var3aUp_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410113_var3aUp/  multilep_jo.py

pathena -c 'xs=9.714' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_091424.410113.var3aDwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410113_var3aDwn/  multilep_jo.py

pathena -c 'xs=9.590' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_094300.410113.var3bUp_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410113_var3bUp/  multilep_jo.py

pathena -c 'xs=9.804' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_094709.410113.var3bDwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410113_var3bDwn/  multilep_jo.py

pathena -c 'xs=8.716' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_095046.410113.var3cUp_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410113_var3cUp/  multilep_jo.py

pathena -c 'xs=10.036' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_095431.410113.var3cDwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410113_var3cDwn/  multilep_jo.py

##
pathena -c 'xs=17.34' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=mc15_13TeV.410114.MadGraphPythia8EvtGen_A14NNPDF23LO_ttmumu_Np1.evgen.EVNT.e4632/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410114_13TeV_ttmumu_np1/  multilep_jo.py

pathena -c 'xs=17.4' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_082424.410114.var1Up_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410114_var1Up/  multilep_jo.py

pathena -c 'xs=17.46' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_082912.410114.var1Dwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410114_var1Dwn/  multilep_jo.py

pathena -c 'xs=17.55' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_083445.410114.var2Up_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410114_var2Up/  multilep_jo.py

pathena -c 'xs=17.17' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_085115.410114.var2Dwn_EXT1/  --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410114_var2Dwn/  multilep_jo.py

pathena -c 'xs=16.74' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_085703.410114.var3aUp_EXT1/  --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410114_var3aUp/  multilep_jo.py

pathena -c 'xs=17.78' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_091424.410114.var3aDwn_EXT1/  --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410114_var3aDwn/  multilep_jo.py

pathena -c 'xs=17.24' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_094300.410114.var3bUp_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410114_var3bUp/  multilep_jo.py

pathena -c 'xs=17.58' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_094709.410114.var3bDwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410114_var3bDwn/  multilep_jo.py

pathena -c 'xs=18.05' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_095046.410114.var3cUp_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410114_var3cUp/  multilep_jo.py

pathena -c 'xs=16.75' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_095431.410114.var3cDwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410114_var3cDwn/  multilep_jo.py


##
pathena -c 'xs=9.848' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=mc15_13TeV.410115.MadGraphPythia8EvtGen_A14NNPDF23LO_tttautau_Np0.evgen.EVNT.e4632/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410115_13TeV_tttautau_np0/ multilep_jo.py

pathena -c 'xs=9.75' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_082424.410115.var1Up_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410115_var1Up/ multilep_jo.py

pathena -c 'xs=9.748' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_082912.410115.var1Dwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410115_var1Dwn/ multilep_jo.py

pathena -c 'xs=9.954' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_083445.410115.var2Up_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410115_var2Up/ multilep_jo.py

pathena -c 'xs=9.837' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_085115.410115.var2Dwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410115_var2Dwn/ multilep_jo.py

pathena -c 'xs=9.470' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_085703.410115.var3aUp_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410115_var3aUp/ multilep_jo.py

pathena -c 'xs=10.08' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_091424.410115.var3aDwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410115_var3aDwn/ multilep_jo.py

pathena -c 'xs=9.834' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_094300.410115.var3bUp_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410115_var3bUp/ multilep_jo.py

pathena -c 'xs=9.984' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_094709.410115.var3bDwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410115_var3bDwn/ multilep_jo.py

pathena -c 'xs=9.182' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_095046.410115.var3cUp_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410115_var3cUp/ multilep_jo.py

pathena -c 'xs=10.88' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_095431.410115.var3cDwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410115_var3cDwn/ multilep_jo.py

##
pathena -c 'xs=17.700' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=mc15_13TeV.410116.MadGraphPythia8EvtGen_A14NNPDF23LO_tttautau_Np1.evgen.EVNT.e4632/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410116_13TeV_tttautau_np1/ multilep_jo.py 

pathena -c 'xs=17.79' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_082424.410116.var1Up_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410116_var1Up/ multilep_jo.py 

pathena -c 'xs=17.84' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_082912.410116.var1Dwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410116_var1Dwn/ multilep_jo.py 

pathena -c 'xs=17.86' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_083445.410116.var2Up_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410116_var2Up/ multilep_jo.py 

pathena -c 'xs=17.58' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_085115.410116.var2Dwn_EXT1/  --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410116_var2Dwn/ multilep_jo.py

pathena -c 'xs=17.13' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_085703.410116.var3aUp_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410116_var3aUp/ multilep_jo.py 

pathena -c 'xs=18.21' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_091424.410116.var3aDwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410116_var3aDwn/ multilep_jo.py

pathena -c 'xs=17.75' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_094300.410116.var3bUp_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410116_var3bUp/ multilep_jo.py 

pathena -c 'xs=18.06' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_094709.410116.var3bDwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410116_var3bDwn/ multilep_jo.py

pathena -c 'xs=18.52' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_095046.410116.var3cUp_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410116_var3cUp/ multilep_jo.py 

pathena -c 'xs=16.90' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_095431.410116.var3cDwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410116_var3cDwn/ multilep_jo.py

##
#
pathena -c 'xs=176.50' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=mc15_13TeV.410066.MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np0.evgen.EVNT.e4111/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410066_ttW/ multilep_jo.py

pathena -c 'xs=182.0' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_082424.410066.var1Up_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410066_var1Up/ multilep_jo.py


pathena -c 'xs=182.1' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_082912.410066.var1Dwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410066_var1Dwn/ multilep_jo.py


pathena -c 'xs=177.8' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_083445.410066.var2Up_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410066_var2Up/ multilep_jo.py


pathena -c 'xs=186.5' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_085115.410066.var2Dwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410066_var2Dwn/ multilep_jo.py


pathena -c 'xs=180.6' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_085703.410066.var3aUp_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410066_var3aUp/ multilep_jo.py


pathena -c 'xs=187.1' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_091424.410066.var3aDwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410066_var3aDwn/ multilep_jo.py


pathena -c 'xs=178.7' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_094300.410066.var3bUp_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410066_var3bUp/ multilep_jo.py


pathena -c 'xs=180.3' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_094709.410066.var3bDwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410066_var3bDwn/ multilep_jo.py


pathena -c 'xs=171.4' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_095046.410066.var3cUp_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410066_var3cUp/ multilep_jo.py


pathena -c 'xs=191.8' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_095431.410066.var3cDwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410066_var3cDwn/ multilep_jo.py

###########
pathena -c 'xs=140.620' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=mc15_13TeV.410067.MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np1.evgen.EVNT.e4111/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410067_ttW/ multilep_jo.py

pathena -c 'xs=141.7' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_082424.410067.var1Up_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410067_var1Up/ multilep_jo.py


pathena -c 'xs=144.8' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_082912.410067.var1Dwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410067_var1Dwn/ multilep_jo.py


pathena -c 'xs=140.4' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_083445.410067.var2Up_EXT1/  --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410067_var2Up/ multilep_jo.py


pathena -c 'xs=144.6' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_085115.410067.var2Dwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410067_var2Dwn/ multilep_jo.py


pathena -c 'xs=143.2' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_085703.410067.var3aUp_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410067_var3aUp/ multilep_jo.py


pathena -c 'xs=145.5' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_091424.410067.var3aDwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410067_var3aDwn/ multilep_jo.py


pathena -c 'xs=143.0' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_094300.410067.var3bUp_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410067_var3bUp/ multilep_jo.py


pathena -c 'xs=145.8' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_094709.410067.var3bDwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410067_var3bDwn/ multilep_jo.py


pathena -c 'xs=146.1' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_095046.410067.var3cUp_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410067_var3cUp/ multilep_jo.py


pathena -c 'xs=142.1' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_095431.410067.var3cDwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410067_var3cDwn/ multilep_jo.py


###################

pathena -c 'xs=136.800' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=mc15_13TeV.410068.MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np2.evgen.EVNT.e4111/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410068_ttW/ multilep_jo.py

pathena -c 'xs=138.9' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_082424.410068.var1Up_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410068_var1Up/ multilep_jo.py

pathena -c 'xs=139.1' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_082912.410068.var1Dwn_EXT1/  --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410068_var1Dwn/ multilep_jo.py

pathena -c 'xs=141.9' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_083445.410068.var2Up_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410068_var2Up/ multilep_jo.py

pathena -c 'xs=134.3' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_085115.410068.var2Dwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410068_var2Dwn/ multilep_jo.py

pathena -c 'xs=140.9' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_085703.410068.var3aUp_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410068_var3aUp/ multilep_jo.py

pathena -c 'xs=139.3' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_091424.410068.var3aDwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410068_var3aDwn/ multilep_jo.py

pathena -c 'xs=134.7' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_094300.410068.var3bUp_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410068_var3bUp/ multilep_jo.py

pathena -c 'xs=142.2' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_094709.410068.var3bDwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410068_var3bDwn/ multilep_jo.py

pathena -c 'xs=151.5' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_095046.410068.var3cUp_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410068_var3cUp/ multilep_jo.py

pathena -c 'xs=126.7' --noBuild --extFile=RivetMultilepNtup.so   --extOutFile=analysis.root  --inDS=user.narayan.evnt.2016-01-15_095431.410068.var3cDwn_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410068_var3cDwn/ multilep_jo.py



pathena -c 'xs=15.7' --noBuild --extFile=RivetMultilepNtup.so    --extOutFile=analysis.root --inDS=mc15_13TeV.410202.MadGraphPythia8EvtGen_A14NNPDF23LO_ttee_Np0_scaleUp.evgen.EVNT.e4796/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.41011_scaleUp/  multilep_jo.py

pathena -c 'xs=15.9' --noBuild --extFile=RivetMultilepNtup.so    --extOutFile=analysis.root --inDS=mc15_13TeV.410203.MadGraphPythia8EvtGen_A14NNPDF23LO_ttee_Np0_scaleDn.evgen.EVNT.e4796/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410111_scaleDwn/ multilep_jo.py

pathena -c 'xs=11.82' --noBuild --extFile=RivetMultilepNtup.so    --extOutFile=analysis.root --inDS=mc15_13TeV.410204.MadGraphPythia8EvtGen_A14NNPDF23LO_ttee_Np1_scaleUp.evgen.EVNT.e4796/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410112_scaleUp/ multilep_jo.py

pathena -c 'xs=27.1' --noBuild --extFile=RivetMultilepNtup.so    --extOutFile=analysis.root --inDS=mc15_13TeV.410205.MadGraphPythia8EvtGen_A14NNPDF23LO_ttee_Np1_scaleDn.evgen.EVNT.e4796/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410112_scaleDwn/ multilep_jo.py

pathena -c 'xs=6.673' --noBuild --extFile=RivetMultilepNtup.so    --extOutFile=analysis.root --inDS=mc15_13TeV.410206.MadGraphPythia8EvtGen_A14NNPDF23LO_ttmumu_Np0_scaleUp.evgen.EVNT.e4796/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410113_scaleUp/ multilep_jo.py

pathena -c 'xs=15.6' --noBuild --extFile=RivetMultilepNtup.so    --extOutFile=analysis.root --inDS=mc15_13TeV.410207.MadGraphPythia8EvtGen_A14NNPDF23LO_ttmumu_Np0_scaleDn.evgen.EVNT.e4796/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410113_scaleDwn/ multilep_jo.py

pathena -c 'xs=11.59' --noBuild --extFile=RivetMultilepNtup.so    --extOutFile=analysis.root --inDS=mc15_13TeV.410208.MadGraphPythia8EvtGen_A14NNPDF23LO_ttmumu_Np1_scaleUp.evgen.EVNT.e4796/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410114_scaleUp/ multilep_jo.py

pathena -c 'xs=26.8' --noBuild --extFile=RivetMultilepNtup.so    --extOutFile=analysis.root --inDS=mc15_13TeV.410209.MadGraphPythia8EvtGen_A14NNPDF23LO_ttmumu_Np1_scaleDn.evgen.EVNT.e4796/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410114_scaleDwn/ multilep_jo.py

pathena -c 'xs=6.803' --noBuild --extFile=RivetMultilepNtup.so    --extOutFile=analysis.root --inDS=mc15_13TeV.410210.MadGraphPythia8EvtGen_A14NNPDF23LO_tttautau_Np0_scaleUp.evgen.EVNT.e4796/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410115_scaleUp/ multilep_jo.py

pathena -c 'xs=16.18' --noBuild --extFile=RivetMultilepNtup.so    --extOutFile=analysis.root --inDS=mc15_13TeV.410211.MadGraphPythia8EvtGen_A14NNPDF23LO_tttautau_Np0_scaleDn.evgen.EVNT.e4796/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410115_scaleDwn/ multilep_jo.py

pathena -c 'xs=12.23' --noBuild --extFile=RivetMultilepNtup.so    --extOutFile=analysis.root --inDS=mc15_13TeV.410212.MadGraphPythia8EvtGen_A14NNPDF23LO_tttautau_Np1_scaleUp.evgen.EVNT.e4796/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410116_scaleUp/ multilep_jo.py

pathena -c 'xs=27.78' --noBuild --extFile=RivetMultilepNtup.so    --extOutFile=analysis.root --inDS=mc15_13TeV.410213.MadGraphPythia8EvtGen_A14NNPDF23LO_tttautau_Np1_scaleDn.evgen.EVNT.e4796/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410116_scaleDwn/ multilep_jo.py

pathena -c 'xs=176.50' --noBuild --extFile=RivetMultilepNtup.so    --extOutFile=analysis.root --inDS=mc15_13TeV.410196.MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np0_scaleUp.evgen.EVNT.e4799 --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410066_scaleUp/ multilep_jo.py
#
pathena -c 'xs=176.50' --noBuild --extFile=RivetMultilepNtup.so    --extOutFile=analysis.root --inDS=mc15_13TeV.410197.MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np0_scaleDn.evgen.EVNT.e4799 --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410066_scaleDwn/ multilep_jo.py
#
pathena -c 'xs=176.50' --noBuild --extFile=RivetMultilepNtup.so    --extOutFile=analysis.root --inDS=mc15_13TeV.410198.MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np1_scaleUp.evgen.EVNT.e4799 --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410067_scaleUp/ multilep_jo.py
#
pathena -c 'xs=176.50' --noBuild --extFile=RivetMultilepNtup.so    --extOutFile=analysis.root --inDS=mc15_13TeV.410199.MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np1_scaleDn.evgen.EVNT.e4799 --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410067_scaleDwn/ multilep_jo.py
#
pathena -c 'xs=176.50' --noBuild --extFile=RivetMultilepNtup.so    --extOutFile=analysis.root --inDS=mc15_13TeV.410200.MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np2_scaleUp.evgen.EVNT.e4799 --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410068_scaleUp/ multilep_jo.py
#
pathena -c 'xs=176.50' --noBuild --extFile=RivetMultilepNtup.so    --extOutFile=analysis.root --inDS=mc15_13TeV.410201.MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np2_scaleDn.evgen.EVNT.e4799 --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410068_scaleDwn/ multilep_jo.py

