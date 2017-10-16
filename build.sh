#!/usr/bin/env bash

if [[ $- == *i* ]] ; then
    echo "Don't source me!" >&2
    return 1
else
    set -eu
fi

# use a provided HDF path and don't build the more complicated parts
# of the ntuple maker.
HDF5_ROOT=${HDF5_ROOT} cmake ../proj
make -j 4

ln -s ${AnalysisBase_PLATFORM}/bin/dump-test
