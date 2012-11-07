# Caylus GFX
add_library (Caylus_GFX SHARED gfx-board.cc gfx-display-visitor.cc gfx-sprite.cc gfx-sprite-library.cc gfx-window.cc)
set_target_properties (Caylus_GFX PROPERTIES LINKER_LANGUAGE CXX)
