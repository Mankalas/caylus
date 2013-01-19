# Caylus view

add_library (Caylus_View SHARED active-view.cc ai.cc board.cc
gfx-visitor.cc image-library.cc console-view.cc graphic-view.cc
human.cc logger.cc passive-view.cc playback.cc player-view.cc view.cc)

set_target_properties (Caylus_View PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries (Caylus_View Caylus_Controller)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules"
${CMAKE_MODULE_PATH})

find_package (SFML 1.6 REQUIRED system window graphics)
target_link_libraries (Caylus_View ${SFML_LIBRARIES})
