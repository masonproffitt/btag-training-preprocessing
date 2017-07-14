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

# Build the test executable:
atlas_add_executable( dump-test
   utils/dump-test.cxx
   INCLUDE_DIRS ${ROOT_INCLUDE_DIRS}
   LINK_LIBRARIES ${ROOT_LIBRARIES} xAODRootAccess xAODCaloEvent xAODTracking )
