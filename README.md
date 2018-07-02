RIVET (Robust Independant Verification of Experiment and Theory) is a tool to validate montecarlo samples. 
RIVET encapsulates the generator dependancies in the HepMC records behind a robust object oriented interface
wchich is as close to what one might end up seeing in the detector. 

The current package does validation studies for ttbar + vector bosons. it produces output files wchich are in .yoda format which can be 
converted to root format with `yoda2root`. 

Follow the following chain to compile and run rivet

Setup the latest MCProd Cache: 

```
lsetup "asetup 19.2.5.33.1,MCProd,here" 
```

rivet-buildplugin RivetTTBAR_ANA.so TTBAR_ANA.cc
(rivet-buildplugin is a script that links rivet libraries from afs. If you don't have afs, you should compile the .so with rivet libraries in appropriate cvmfs locations)
Use and modify rivet_MC_jo.py accordingly and run the analysis.
athena -c 'xs=' rivet_MC_jo.py

If you want to run the jobs on grid (most likely the case), you may use pathena to do so.
pathena -c 'xs=0.00227596' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-05-20_103645.500000.8TeV_ttZllon_cteq6l1_EXT1 --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.500000_8TeV_ttZllon_cteq6l1/  rivet_MC_jo.py
