#!/usr/bin/env bash

if [[ $- == *i* ]] ; then
    echo "Don't source me!" >&2
    return 1
else
    set -eu
fi

mkdir -p build
cd build/
# use a provided HDF path and don't build the more complicated parts
# of the ntuple maker.
cmake -DH5_LOC=${HDF_ROOT} -DROOT_DEPENDANTS=NO ..
make -j 4
