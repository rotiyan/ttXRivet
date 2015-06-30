export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/
export ALRB_localConfigDir=/code/localConfig
. /cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/user/atlasLocalSetup.sh
localSetupPandaClient
asetup 19.2.3.9,here 
voms-proxy-init -voms atlas
#pathena  --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so,Rivetttz_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=user.narayan.Sherpa_CT10_ttll.1M_EXT0/ --outDS=user.narayan.19-15-2015.rivet-Sherpa_CT10_ttll_8TeV_v1/  ttz_rivet_jo.py 

#pathena -c 'xs=1' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so,Rivetttz_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-05-07_025202.100000.8TeV_ttZllon_EXT1/ --outDS=user.narayan.19-15-2015.rivet-MadGraph.100000_8TeV_ttZllon/  ttz_rivet.100000_8TeV_ttZllOn.py
#
#pathena  --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so,Rivetttz_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-05-07_025225.100001.8TeV_ttZllon_EXT1/ --outDS=user.narayan.19-15-2015.rivet-MadGraph.100001_8TeV_ttZllon/  ttz_rivet.100001_8TeV_ttZllOn.py
#
#pathena  --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so,Rivetttz_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-05-07_025247.200000.8TeV_ttZlloff_EXT1/ --outDS=user.narayan.19-15-2015.rivet-MadGraph.200000_8TeV_ttZllof_v1/  ttz_rivet.200000_8TeV_ttZllOff.py
#
#pathena -c 'xs=1' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so,Rivetttz_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-05-07_025309.200001.8TeV_ttZlloff_EXT1/ --outDS=user.narayan.19-15-2015.rivet-MadGraph.200001_8TeV_ttZllof_v1/  ttz_rivet.200001_8TeV_ttZllOff.py
#
#pathena -c 'xs=1' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so,Rivetttz_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=mc12_8TeV.119355.MadGraphPythia_AUET2BCTEQ6L1_ttbarZ.evgen.EVNT.e1352/ --outDS=user.narayan.19-15-2015.rivet-MadGraph.119355_8TeV_ttbarZ/  ttz_rivet.119355_8TeV_ttbarZ.py 
#
#pathena -c 'xs=1' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so,Rivetttz_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=mc12_8TeV.174832.MadGraphPythia_AUET2BCTEQ6L1_ttbarZjExcl.evgen.EVNT.e1672/ --outDS=user.narayan.19-15-2015.rivet-MadGraph.174832_8TeV_ttbarZ/  ttz_rivet.174832_8TeV_ttbarZ.py
#



#mc12_8TeV.117489.MadGraphPythia_AUET2B_CTEQ6L1_ttbarZ_Np0_MGDec_1lep.evgen.EVNT.e2649
#mc12_8TeV.117490.MadGraphPythia_AUET2B_CTEQ6L1_ttbarZ_Zll_Np1in_MGDec_1lep.evgen.EVNT.e2649

timeStamp=`date +%H%M%S_%m%Y`

pathena -c 'xs=0.067690' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=mc12_8TeV.119355.MadGraphPythia_AUET2BCTEQ6L1_ttbarZ.evgen.EVNT.e1352/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.119355_8TeV_ttbarZ/ rivet_MC_jo.py

pathena -c 'xs=0.045357' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=mc12_8TeV.174832.MadGraphPythia_AUET2BCTEQ6L1_ttbarZjExcl.evgen.EVNT.e1672/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.174832_8TeV_ttbarZ/ rivet_MC_jo.py

pathena -c 'xs=0.039772' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=mc12_8TeV.174833.MadGraphPythia_AUET2BCTEQ6L1_ttbarZjjIncl.evgen.EVNT.e1672/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.174833_8TeV_ttbarZ/ rivet_MC_jo.py

pathena -c 'xs=0.093229' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=mc12_8TeV.117489.MadGraphPythia_AUET2B_CTEQ6L1_ttbarZ_Np0_MGDec_1lep.evgen.EVNT.e2649/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.117489_8TeV_ttbarZ/ rivet_MC_jo.py

pathena -c 'xs=0.18655' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=mc12_8TeV.117490.MadGraphPythia_AUET2B_CTEQ6L1_ttbarZ_Zll_Np1in_MGDec_1lep.evgen.EVNT.e2649/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.117490_8TeV_ttbarZ/  rivet_MC_jo.py

pathena -c 'xs=0.00593384' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-05-07_025202.100000.8TeV_ttZllon_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.100000_8TeV_ttZllon/  rivet_MC_jo.py

pathena -c 'xs=0.00723162' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-05-07_025225.100001.8TeV_ttZllon_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.100001_8TeV_ttZllon/ rivet_MC_jo.py

pathena -c 'xs=0.00861146' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-05-07_025247.200000.8TeV_ttZlloff_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.200000_8TeV_ttZllof/  rivet_MC_jo.py

pathena -c 'xs=0.00244216' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-05-07_025309.200001.8TeV_ttZlloff_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.200001_8TeV_ttZlloff/  rivet_MC_jo.py

pathena -c 'xs=0.00121535' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-05-25_193729.911000.8TeV_ttee_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.911000_8TeV_ttee/  rivet_MC_jo.py

pathena -c 'xs=0.00136184' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-05-25_193759.911001.8TeV_ttee_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.911001_8TeV_ttee/  rivet_MC_jo.py

pathena -c 'xs=0.00122395' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-05-25_193830.913000.8TeV_ttmumu_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.913000_8TeV_ttmumu/ rivet_MC_jo.py

pathena -c 'xs=0.00135781' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-05-25_193856.913001.8TeV_ttmumu_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.913001_8TeV_ttmumu/ rivet_MC_jo.py

pathena -c 'xs=0.00227596' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-05-20_103645.500000.8TeV_ttZllon_cteq6l1_EXT1 --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.500000_8TeV_ttZllon_cteq6l1/  rivet_MC_jo.py

pathena -c 'xs=0.00691532' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-05-20_103709.500001.8TeV_ttZllon_cteq6l1_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.500001_8TeV_ttZllon_cteq6l1/  rivet_MC_jo.py

pathena -c 'xs=0.00120981' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-05-25_195805.911100.8TeV_ttee_cteq6l1_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.911100_8TeV_ttee_cteq6l1/  rivet_MC_jo.py

pathena -c 'xs=0.00117124' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-05-25_195834.911101.8TeV_ttee_cteq6l1_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.911101_8TeV_ttZllof/  rivet_MC_jo.py

pathena -c 'xs=0.00120949' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-05-25_195901.913100.8TeV_ttmumu_cteq6l1_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.913100_8TeV_ttmumu_cteq6l1/ rivet_MC_jo.py

pathena -c 'xs=0.00116136' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-05-25_195929.913101.8TeV_ttmumu_cteq6l1_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.913101_8TeV_ttmumu_cteq6l1/ rivet_MC_jo.py

pathena -c 'xs=0.0609748' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-05-27_095528.119355.8TeV_ttZ_MC12_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.119355_8TeV_ttZ_MC12/  rivet_MC_jo.py

pathena -c 'xs=0.086905' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-05-27_095542.119356.8TeV_ttZ_MC12_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.119356_8TeV_ttZ_MC12/  rivet_MC_jo.py

pathena -c 'xs=0.006022588' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-05-27_095500.219355.8TeV_ttll_MC12_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.219355_8TeV_ttZ_MC12/  rivet_MC_jo.py

pathena -c 'xs=0.00768966' --noBuild --extFile=RivetTTBAR_ANA.soRivetTTBAR_ANA.so,,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-05-27_095515.219356.8TeV_ttll_MC12_EXT1/ --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.219356_8TeV_ttz_MC12/ rivet_MC_jo.py
