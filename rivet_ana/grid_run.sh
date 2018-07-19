#!/bin/bash

export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/
export ALRB_localConfigDir=/code/localConfig
. /cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/user/atlasLocalSetup.sh

lsetup "asetup 19.2.5.33.1,MCProd,here"
athena -c "xs=1.0" ttll_jo.py
