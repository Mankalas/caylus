# Caylus GFX
add_library (Caylus_GFX SHARED gfx-board.cc gfx-display-visitor.cc gfx-sprite.cc gfx-sprite-library.cc gfx-window.cc)
set_target_properties (Caylus_GFX PROPERTIES LINKER_LANGUAGE CXX)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package (SFML 1.6 REQUIRED system window graphics network audio)
target_link_libraries (Caylus_GFX ${SFML_LIBRARIES})
