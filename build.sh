#!/usr/bin/env bash

if [[ $- == *i* ]] ; then
    echo "Don't source me!" >&2
    return 1
else
    set -eu
fi

# use a provided HDF path and don't build the more complicated parts
# of the ntuple maker.
cmake -DH5_LOC=${HDF5_ROOT}
make -j 4

ln -s ${AnalysisBase_PLATFORM}/bin/dump-test
