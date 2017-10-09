#!/usr/bin/env bash

# Input derivation I got from rachael
INPUT_FILE=/afs/cern.ch/work/d/dguest/public/rachael/DAOD_FTAG2.ttbar_mc16.pool.root

if [[ ! -f $INPUT_FILE ]] ; then
    echo "ERROR: input file $INPUT_FILE not found" >&2
    exit 1
fi

# run the script
./dump-test $INPUT_FILE
