#
# Build configuration for the IOTests package
#

# Set the name of the package:
atlas_subdir( BTagTrainingPreprocessing )

# Packages that this package depends on:
atlas_depends_on_subdirs(
   PRIVATE
   Control/xAODRootAccess
   Event/xAOD/xAODEventInfo
   Event/xAOD/xAODCaloCluster )

# External(s) used by the package:
find_package( ROOT COMPONENTS Core RIO REQUIRED )

include_directories(BEFORE $ENV{ALRB_HDF5_PATH}/include)

# Build the test executable:
atlas_add_executable( dump-test
   utils/dump-test.cxx src/*.cxx
   INCLUDE_DIRS ${ROOT_INCLUDE_DIRS} src
   LINK_LIBRARIES ${ROOT_LIBRARIES}
   xAODRootAccess xAODCaloEvent xAODTracking xAODJet)

# Add HDF5 libraries
set(HDF5_LIBS
  $ENV{ALRB_HDF5_PATH}/lib/libhdf5.so
  $ENV{ALRB_HDF5_PATH}/lib/libhdf5_cpp.so
  $ENV{ALRB_HDF5_PATH}/lib/libhdf5_hl_cpp.so
  $ENV{ALRB_HDF5_PATH}/lib/libhdf5_hl.so)

target_link_libraries(dump-test ${HDF5_LIBS})
