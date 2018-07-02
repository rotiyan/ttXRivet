RIVET (Robust Independant Verification of Experiment and Theory) is a tool to validate montecarlo samples. 
RIVET encapsulates the generator dependancies in the HepMC records behind a robust object oriented interface. 

The current package does validation studies for ttbar + vector bosons. it produces output files wchich are in .yoda format which can be 
converted to root format with `yoda2root`. 

# Checking out package and setting up 

```
git clone https://:@gitlab.cern.ch:8443/narayan/pmg-rivet.git
``` 

Navigate to the folder ``pmg-rivet`` and setup a latest MCProd cache


```
lsetup "asetup 19.2.5.33.1,MCProd,here" 
```
#  Building the rivet-plugins

The plugins are located in the rivet_plugins folder. ``cd rivet_plugins``

To build the plugin do the following 
```
rivet-buildplugin RivetTTZ_analysis.so TTZ_analysis.cc
```

(rivet-buildplugin is a script that links rivet libraries from afs. If you don't have afs, you should compile the .so with rivet libraries in appropriate cvmfs locations)

# Running the analysis using the plugin 
Copy the plugin to the ``rivet-ana`` folder. The plugin can be run standalone or as an option to the ``Generate_tf.py`` script. 

The following procedure explains how to do a standalone analysis. 

Modify the ``ttll_jo.py`` script accordingly  and can be ran locally by running athena 

```
athena -c 'xs=' rivet_MC_jo.py
```
Here ``xs`` is the cross section of the sample under consideration (Used in the plugin internally for normalization)

# Running the jobs on grid

If you want to run the jobs on grid (most likely the case), you may use pathena to do so.

```
pathena -c 'xs=0.00227596' --noBuild --extFile=RivetTTZ_analysis.so --extOutFile ttz_analysis.yoda --inDS=<inputds> --outDS=<output_ds>  ttll_jo.py
```