
# setup ATLAS
export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
alias setupATLAS='source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh'

echo "=== running setupATLAS ==="
setupATLAS -q
echo "=== running lsetup ==="
lsetup asetup
echo "=== running asetup ==="
asetup AnalysisBase,21.2.0


# setup HDF5
export HDF_ROOT=/afs/cern.ch/user/d/dguest/afswork/public/hdf5/hdf5-1.8.19/install/
export LD_LIBRARY_PATH=${HDF_ROOT}/lib:${LD_LIBRARY_PATH}
# echo "=== setting up HDF5 ==="
# This next line is commented out until we figure out
#
# https://sft.its.cern.ch/jira/browse/SPI-984
#
# Until then we need to use some weird flags building the hdf5
# wrappers
#
# ------ uncomment when fixed -----
# lsetup "hdf5 1.10.0-x86_64-slc6-gcc62-opt"
# ---------------------------------


