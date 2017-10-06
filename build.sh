#!/usr/bin/env bash

if [[ $- == *i* ]] ; then
    echo "Don't source me!" >&2
    return 1
else
    set -eu
fi

mkdir -p build
cd build/
cmake -DH5_LOC=${HDF_ROOT} ..
make -j 4
