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
   Event/xAOD/xAODCaloCluster
   Control/AthToolSupport/AsgTools
   Reconstruction/Jet/JetCalibTools )

# External(s) used by the package:
find_package( ROOT COMPONENTS Core RIO REQUIRED )

ExternalProject_Add( ttree2hdf5
  PREFIX ${CMAKE_BINARY_DIR}/externals
  INSTALL_DIR ${CMAKE_BINARY_DIR}/externals/ttree2hdf5
  GIT_REPOSITORY "https://github.com/dguest/ttree2hdf5.git"
  CMAKE_CACHE_ARGS
  -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}
  -DH5_LOC:STRING=BUILTIN
  )


include_directories(BEFORE $ENV{ALRB_HDF5_PATH}/include)

# Build the test executable:
atlas_add_executable( dump-test
   utils/dump-test.cxx src/*.cxx
   INCLUDE_DIRS ${ROOT_INCLUDE_DIRS} src
   LINK_LIBRARIES ${ROOT_LIBRARIES}
   xAODRootAccess xAODCaloEvent xAODTracking xAODJet AsgTools JetCalibToolsLib)

# Add HDF5 libraries
set(HDF5_LIBS
  $ENV{ALRB_HDF5_PATH}/lib/libhdf5.so
  $ENV{ALRB_HDF5_PATH}/lib/libhdf5_cpp.so
  $ENV{ALRB_HDF5_PATH}/lib/libhdf5_hl_cpp.so
  $ENV{ALRB_HDF5_PATH}/lib/libhdf5_hl.so)

target_link_libraries(dump-test ${HDF5_LIBS})
