#
# Basic setup for dumping Tagging information
#

# Set the minimum required CMake version:
cmake_minimum_required( VERSION 3.2 FATAL_ERROR )
find_package( AnalysisBase 21.2 REQUIRED EXACT )

# Set up CTest:
atlas_ctest_setup()

# Set up a work directory project:
atlas_project( WorkDir 21.2.0 USE AnalysisBase 21.2.0 )

# Set up the runtime environment setup script(s):
lcg_generate_env( SH_FILE ${CMAKE_BINARY_DIR}/${ATLAS_PLATFORM}/env_setup.sh )
install( FILES ${CMAKE_BINARY_DIR}/${ATLAS_PLATFORM}/env_setup.sh
   DESTINATION . )

# Set up CPack:
atlas_cpack_setup()
