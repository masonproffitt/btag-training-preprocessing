#
# Project configuration for AnalysisBaseIOTests
#

# Set the minimum required CMake version:
cmake_minimum_required( VERSION 3.4 FATAL_ERROR )

# Find the AnalysisBase project:
find_package( AnalysisBase 21.2 REQUIRED )

# Set up CTest:
atlas_ctest_setup()

# Set up the HSSIPAnalysis project:
atlas_project( AnalysisBaseIOTests 1.0.0
   USE AnalysisBase ${AnalysisBase_VERSION} )

# Set up the runtime environment setup script(s):
lcg_generate_env( SH_FILE ${CMAKE_BINARY_DIR}/${ATLAS_PLATFORM}/env_setup.sh )
install( FILES ${CMAKE_BINARY_DIR}/${ATLAS_PLATFORM}/env_setup.sh
   DESTINATION . )

# Set up CPack:
atlas_cpack_setup()
