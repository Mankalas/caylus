cmake_minimum_required (VERSION 2.8)
set(CMAKE_CXX_FLAGS "-g -Wall")

project (Caylus CXX)

# The version number.
set (Caylus_VERSION_MAJOR 1)
set (Caylus_VERSION_MINOR 0)

# Directories
set (CAYLUS_SOURCE_DIR "src")
set (CAYLUS_BINARY_DIR "bin")
set (Caylus_IMAGE_DIR "share/img")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${CAYLUS_SOURCE_DIR}/CaylusConfig.h.in"
  "${CAYLUS_SOURCE_DIR}/CaylusConfig.h"
  )

# add the binary tree to the search path for include files
# so that we will find CaylusConfig.h
include_directories ("${CAYLUS_SOURCE_DIR}")

# Define sources and executable
set (EXECUTABLE_NAME "Caylus")
add_executable (${EXECUTABLE_NAME} "${CAYLUS_SOURCE_DIR}/main.cc")

# Subdirectories
add_subdirectory ("${CAYLUS_SOURCE_DIR}/controller")
target_link_libraries (${EXECUTABLE_NAME} Caylus_Controller)

add_subdirectory ("${CAYLUS_SOURCE_DIR}/gfx")
target_link_libraries (${EXECUTABLE_NAME} Caylus_GFX)

add_subdirectory ("${CAYLUS_SOURCE_DIR}/view")
target_link_libraries (${EXECUTABLE_NAME} Caylus_View)


# External libs
find_package (Boost REQUIRED thread signals)
target_link_libraries (${EXECUTABLE_NAME} ${Boost_LIBRARIES})

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package (SFML 1.6 REQUIRED system window graphics network audio)
target_link_libraries (${EXECUTABLE_NAME} ${SFML_LIBRARIES})

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION ${CAYLUS_BINARY_DIR})
