#!/usr/bin/env bash

if [[ $- == *i* ]] ; then
    echo "Don't source me!" >&2
    return 1
else
    set -eu
fi

if ! mkdir build >& /dev/null; then
    echo "build directory already exists, remove it to rebuild"
    exit 1
fi
cd build/
cmake ..
make -j 4
