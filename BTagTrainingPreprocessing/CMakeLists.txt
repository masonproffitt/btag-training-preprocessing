#
# Build configuration for the IOTests package
#

# Set the name of the package:
atlas_subdir( BTagTrainingPreprocessing )

# turn off an annoying set of warnings I get from HDF5
string(REPLACE "-Woverloaded-virtual" "" NEW_FLAGS ${CMAKE_CXX_FLAGS_DEBUG})
set(CMAKE_CXX_FLAGS_DEBUG ${NEW_FLAGS})

# Packages that this package depends on:
atlas_depends_on_subdirs(
   PRIVATE
   Control/xAODRootAccess
   Event/xAOD/xAODEventInfo
   Event/xAOD/xAODCaloCluster
   Control/AthToolSupport/AsgTools
   Reconstruction/Jet/JetCalibTools )

# External(s) used by the package:
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED COMPONENTS RIO Hist Tree Net Core)

# find zlib
find_package( ZLIB REQUIRED )
get_filename_component(ZLIB_LIB_DIR ZLIB_LIBRARIES DIRECTORY)

# Find or build HDF5
set(H5_LOC "FIND" CACHE STRING "Directory where HDF5 lives (or BUILTIN)")
if(H5_LOC STREQUAL "FIND")
  find_package( HDF5 1.8.12 REQUIRED COMPONENTS CXX HL)
else()
  if(H5_LOC STREQUAL "BUILTIN")
    # if we use builtin HDF5, tell ttree2hdf5 to build it
    set(H5_LOC ${CMAKE_BINARY_DIR}/externals/hdf5)
    set(BUILTIN_HDF5 TRUE)
    # Tell ttree2hdf5 not to build the root parts
    set(ROOT_DEPENDANTS NO)
  elseif(NOT IS_DIRECTORY ${H5_LOC})
    message(FATAL_ERROR "HDF5 path ${H5_LOC} does not point to a directory")
  endif()
  set( HDF5_INCLUDE_DIRS "${H5_LOC}/include/")
  set( HDF5_LIB "${H5_LOC}/lib/")
  set( SUFFFIX ${CMAKE_STATIC_LIBRARY_SUFFIX})
  set( HDF5_LIBRARIES
    ${HDF5_LIB}/libhdf5_cpp${SUFFFIX}
    ${HDF5_LIB}/libhdf5_hl_cpp${SUFFFIX}
    ${HDF5_LIB}/libhdf5${SUFFFIX} )
endif()

# not sure how to add a subdirectory within atlas properly, so we have
# this hack
set(HDFTUPLE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ttree2hdf5/include)
set(HDFTUPLE_LIBRARIES ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libHdfTuple-static.a)

# Build the test executable:
atlas_add_executable( dump-test
  utils/dump-test.cxx src/BTagJetWriter.cxx src/HDF5Defs.cxx
  src/HDF5Writer.cxx src/HDF5WriterAbstraction.cxx
  src/Jet.cxx src/Track.hh
  INCLUDE_DIRS ${ROOT_INCLUDE_DIRS} src ${HDF5_INCLUDE_DIRS}
  LINK_LIBRARIES ${ROOT_LIBRARIES}
  xAODRootAccess xAODCaloEvent xAODTracking xAODJet AsgTools JetCalibToolsLib)

# if( BUILTIN_HDF5 )
#   add_dependencies(dump-test ${HDFTUPLE_LIBRARIES})
# endif()


# Add HDF5 libraries
target_link_libraries(dump-test ${HDF5_LIBRARIES} ${HDFTUPLE_LIBRARIES})

# Add HDF5 ntuple writer
target_include_directories(dump-test
  PRIVATE ${HDFTUPLE_INCLUDE_DIR}
  ${HDF5_INCLUDE_DIRS})
