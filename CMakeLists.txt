cmake_minimum_required (VERSION 2.8)
set(CMAKE_CXX_FLAGS "-g -Wall")

project (Caylus CXX)

# The version number.
set (Caylus_VERSION_MAJOR 1)
set (Caylus_VERSION_MINOR 0)

# Directories
set (CAYLUS_SOURCE_DIR "src")
set (CAYLUS_BINARY_DIR "bin")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${CAYLUS_SOURCE_DIR}/CaylusConfig.h.in"
  "${CAYLUS_SOURCE_DIR}/CaylusConfig.h"
  )

# add the binary tree to the search path for include files
# so that we will find CaylusConfig.h
include_directories("${CAYLUS_SOURCE_DIR}")

# Subdirectories
add_subdirectory ("${CAYLUS_SOURCE_DIR}/view")
add_subdirectory ("${CAYLUS_SOURCE_DIR}/controller")
add_subdirectory ("${CAYLUS_SOURCE_DIR}/gfx")

# Define sources and executable
set (EXECUTABLE_NAME "Caylus")
add_executable (${EXECUTABLE_NAME} "${CAYLUS_SOURCE_DIR}/main.cc")
target_link_libraries (${EXECUTABLE_NAME} Caylus_Controller)
target_link_libraries (${EXECUTABLE_NAME} Caylus_View)
target_link_libraries (${EXECUTABLE_NAME} Caylus_GFX)

# External libs
find_package (Boost REQUIRED)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package (SFML 1.6 REQUIRED system window graphics network audio)

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION ${CAYLUS_BINARY_DIR})
