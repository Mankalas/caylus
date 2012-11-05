cmake_minimum_required (VERSION 2.8)

project (Caylus)

# The version number.
set (Caylus_VERSION_MAJOR 1)
set (Caylus_VERSION_MINOR 0)

# Directories
set (CAYLUS_SOURCE_DIR "src")
set (CAYLUS_BINARY_DIR "bin")

# Subdirectories
add_subdirectory ("${CAYLUS_SOURCE_DIR}/view")
add_subdirectory ("${CAYLUS_SOURCE_DIR}/controller")
add_subdirectory ("${CAYLUS_SOURCE_DIR}/gfx")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${CAYLUS_SOURCE_DIR}/CaylusConfig.h.in"
  "${CAYLUS_BINARY_DIR}/CaylusConfig.h"
  )

# add the binary tree to the search path for include files
# so that we will find CaylusConfig.h
include_directories("${CAYLUS_BINARY_DIR}")

add_executable (Caylus "${CAYLUS_SOURCE_DIR}/main.cc")

