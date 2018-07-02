RIVET (Robust Independant Verification of Experiment and Theory) is a tool to validate montecarlo samples. 
RIVET encapsulates the generator dependancies in the HepMC records behind a robust object oriented interface
wchich is as close to what one might end up seeing in the detector. 

The current package does validation studies for ttbar + vector bosons. it produces output files wchich are in .yoda format which can be 
converted to root format with `yoda2root`. 

# 1. Checking out package and setting up 
Setup the latest MCProd Cache: 

```
git clone https://:@gitlab.cern.ch:8443/narayan/pmg-rivet.git
``` 

Navigate to the folder ``pmg-rivet`` and setup a latest MCProd cache


```
lsetup "asetup 19.2.5.33.1,MCProd,here" 
```
#2. Building the rivet-plugins

The plugins are located in the rivet_plugins folder. ``cd rivet_plugins``

To build the plugin do the following 
```
rivet-buildplugin RivetTTZ_analysis.so TTZ_analysis.cc
```

(rivet-buildplugin is a script that links rivet libraries from afs. If you don't have afs, you should compile the .so with rivet libraries in appropriate cvmfs locations)

#3. Running the analysis using the plugin 
Copy the plugin to the ``rivet-ana`` folder. The plugin can be ran standalone as well as an option to the ``Generate_tf.py`` script. 

The following procedure explains how to do a standalone analysis. 

Use and modify rivet_MC_jo.py accordingly and run the analysis.
athena -c 'xs=' rivet_MC_jo.py

If you want to run the jobs on grid (most likely the case), you may use pathena to do so.
pathena -c 'xs=0.00227596' --noBuild --extFile=RivetTTBAR_ANA.so,RivetTTZ_analysis.so --nFilesPerJob=2 --long --extOutFile ttz_analysis.yoda --inDS=user.mcfayden.evnt.2015-05-20_103645.500000.8TeV_ttZllon_cteq6l1_EXT1 --outDS=user.narayan.${timeStamp}.rivet-MadGraph_MC_ANA.500000_8TeV_ttZllon_cteq6l1/  rivet_MC_jo.py
