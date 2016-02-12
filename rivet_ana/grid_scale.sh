export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/
export ALRB_localConfigDir=/code/localConfig
. /cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/user/atlasLocalSetup.sh
lsetup panda
lsetup asetup
asetup 19.3.0.1,here

timeStamp=`date +%H%M%S_%m%Y`


pathena -c 'xs=15.7' --noBuild --extFile=RivetTTll.so   --extOutFile=ttll_study.yoda --inDS=mc15_13TeV.410202.MadGraphPythia8EvtGen_A14NNPDF23LO_ttee_Np0_scaleUp.evgen.EVNT.e4796/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.41011_scaleUp/  ttll_jo.py

pathena -c 'xs=15.9' --noBuild --extFile=RivetTTll.so   --extOutFile=ttll_study.yoda --inDS=mc15_13TeV.410203.MadGraphPythia8EvtGen_A14NNPDF23LO_ttee_Np0_scaleDn.evgen.EVNT.e4796/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410111_scaleDwn/ ttll_jo.py

pathena -c 'xs=11.82' --noBuild --extFile=RivetTTll.so   --extOutFile=ttll_study.yoda --inDS=mc15_13TeV.410204.MadGraphPythia8EvtGen_A14NNPDF23LO_ttee_Np1_scaleUp.evgen.EVNT.e4796/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410112_scaleUp/ ttll_jo.py

pathena -c 'xs=27.1' --noBuild --extFile=RivetTTll.so   --extOutFile=ttll_study.yoda --inDS=mc15_13TeV.410205.MadGraphPythia8EvtGen_A14NNPDF23LO_ttee_Np1_scaleDn.evgen.EVNT.e4796/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410112_scaleDwn/ ttll_jo.py

pathena -c 'xs=6.673' --noBuild --extFile=RivetTTll.so   --extOutFile=ttll_study.yoda --inDS=mc15_13TeV.410206.MadGraphPythia8EvtGen_A14NNPDF23LO_ttmumu_Np0_scaleUp.evgen.EVNT.e4796/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410113_scaleUp/ ttll_jo.py

pathena -c 'xs=15.6' --noBuild --extFile=RivetTTll.so   --extOutFile=ttll_study.yoda --inDS=mc15_13TeV.410207.MadGraphPythia8EvtGen_A14NNPDF23LO_ttmumu_Np0_scaleDn.evgen.EVNT.e4796/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410113_scaleDwn/ ttll_jo.py

pathena -c 'xs=11.59' --noBuild --extFile=RivetTTll.so   --extOutFile=ttll_study.yoda --inDS=mc15_13TeV.410208.MadGraphPythia8EvtGen_A14NNPDF23LO_ttmumu_Np1_scaleUp.evgen.EVNT.e4796/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410114_scaleUp/ ttll_jo.py

pathena -c 'xs=26.8' --noBuild --extFile=RivetTTll.so   --extOutFile=ttll_study.yoda --inDS=mc15_13TeV.410209.MadGraphPythia8EvtGen_A14NNPDF23LO_ttmumu_Np1_scaleDn.evgen.EVNT.e4796/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410114_scaleDwn/ ttll_jo.py

pathena -c 'xs=6.803' --noBuild --extFile=RivetTTll.so   --extOutFile=ttll_study.yoda --inDS=mc15_13TeV.410210.MadGraphPythia8EvtGen_A14NNPDF23LO_tttautau_Np0_scaleUp.evgen.EVNT.e4796/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410115_scaleUp/ ttll_jo.py

pathena -c 'xs=16.18' --noBuild --extFile=RivetTTll.so   --extOutFile=ttll_study.yoda --inDS=mc15_13TeV.410211.MadGraphPythia8EvtGen_A14NNPDF23LO_tttautau_Np0_scaleDn.evgen.EVNT.e4796/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410115_scaleDwn/ ttll_jo.py

pathena -c 'xs=12.23' --noBuild --extFile=RivetTTll.so   --extOutFile=ttll_study.yoda --inDS=mc15_13TeV.410212.MadGraphPythia8EvtGen_A14NNPDF23LO_tttautau_Np1_scaleUp.evgen.EVNT.e4796/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410116_scaleUp/ ttll_jo.py

pathena -c 'xs=27.78' --noBuild --extFile=RivetTTll.so   --extOutFile=ttll_study.yoda --inDS=mc15_13TeV.410213.MadGraphPythia8EvtGen_A14NNPDF23LO_tttautau_Np1_scaleDn.evgen.EVNT.e4796/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410116_scaleDwn/ ttll_jo.py

#Generate on UT Tier3/ No need to rerun
pathena -c 'xs=176.50' --noBuild --extFile=RivetTTll.so   --extOutFile=ttll_study.yoda --inDS=mc15_13TeV.410196.MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np0_scaleUp.evgen.EVNT.e4799 --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410066_scaleUp/ ttll_jo.py
#
pathena -c 'xs=176.50' --noBuild --extFile=RivetTTll.so   --extOutFile=ttll_study.yoda --inDS=mc15_13TeV.410197.MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np0_scaleDn.evgen.EVNT.e4799 --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410066_scaleDwn/ ttll_jo.py
#
pathena -c 'xs=176.50' --noBuild --extFile=RivetTTll.so   --extOutFile=ttll_study.yoda --inDS=mc15_13TeV.410198.MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np1_scaleUp.evgen.EVNT.e4799 --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410067_scaleUp/ ttll_jo.py
#
pathena -c 'xs=176.50' --noBuild --extFile=RivetTTll.so   --extOutFile=ttll_study.yoda --inDS=mc15_13TeV.410199.MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np1_scaleDn.evgen.EVNT.e4799 --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410067_scaleDwn/ ttll_jo.py
#
pathena -c 'xs=176.50' --noBuild --extFile=RivetTTll.so   --extOutFile=ttll_study.yoda --inDS=mc15_13TeV.410200.MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np2_scaleUp.evgen.EVNT.e4799 --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410068_scaleUp/ ttll_jo.py
#
pathena -c 'xs=176.50' --noBuild --extFile=RivetTTll.so   --extOutFile=ttll_study.yoda --inDS=mc15_13TeV.410201.MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np2_scaleDn.evgen.EVNT.e4799 --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410068_scaleDwn/ ttll_jo.py

pathena -c 'xs=9.739' --noBuild --extFile=RivetTTll.so   --extOutFile=ttll_study.yoda  --inDS=mc15_13TeV.410111.MadGraphPythia8EvtGen_A14NNPDF23LO_ttee_Np0.evgen.EVNT.e4632/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410111_13TeV_ttee_np1/  ttll_jo.py

pathena -c 'xs=17.25' --noBuild --extFile=RivetTTll.so   --extOutFile=ttll_study.yoda  --inDS=mc15_13TeV.410112.MadGraphPythia8EvtGen_A14NNPDF23LO_ttee_Np1.evgen.EVNT.e4632/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410112_13TeV_ttee_np1/ ttll_jo.py

pathena -c 'xs=9.577' --noBuild --extFile=RivetTTll.so   --extOutFile=ttll_study.yoda  --inDS=mc15_13TeV.410113.MadGraphPythia8EvtGen_A14NNPDF23LO_ttmumu_Np0.evgen.EVNT.e4632/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410113_13TeV_ttmumu_np0/  ttll_jo.py

pathena -c 'xs=17.34' --noBuild --extFile=RivetTTll.so   --extOutFile=ttll_study.yoda  --inDS=mc15_13TeV.410114.MadGraphPythia8EvtGen_A14NNPDF23LO_ttmumu_Np1.evgen.EVNT.e4632/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410114_13TeV_ttmumu_np1/  ttll_jo.py

pathena -c 'xs=9.848' --noBuild --extFile=RivetTTll.so   --extOutFile=ttll_study.yoda  --inDS=mc15_13TeV.410115.MadGraphPythia8EvtGen_A14NNPDF23LO_tttautau_Np0.evgen.EVNT.e4632/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410115_13TeV_tttautau_np0/ ttll_jo.py

pathena -c 'xs=17.700' --noBuild --extFile=RivetTTll.so   --extOutFile=ttll_study.yoda  --inDS=mc15_13TeV.410116.MadGraphPythia8EvtGen_A14NNPDF23LO_tttautau_Np1.evgen.EVNT.e4632/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.410116_13TeV_tttautau_np1/ ttll_jo.py 

pathena -c 'xs=176.50' --noBuild --extFile=RivetTTll.so   --extOutFile=ttll_study.yoda  --inDS=mc15_13TeV.410066.MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np0.evgen.EVNT.e4111/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410066_ttW/ ttll_jo.py

pathena -c 'xs=140.620' --noBuild --extFile=RivetTTll.so   --extOutFile=ttll_study.yoda  --inDS=mc15_13TeV.410067.MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np1.evgen.EVNT.e4111/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410067_ttW/ ttll_jo.py

pathena -c 'xs=136.800' --noBuild --extFile=RivetTTll.so   --extOutFile=ttll_study.yoda  --inDS=mc15_13TeV.410068.MadGraphPythia8EvtGen_A14NNPDF23LO_ttW_Np2.evgen.EVNT.e4111/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph.410068_ttW/ ttll_jo.py

