# Caylus GFX
project (Caylus_GFX)

set (Caylus_GFX_SRC gfx-window.cc gfx-sprite.cc gfx-sprite-library.cc gfx-board.cc)

add_library (Caylus_GFX SHARED "${Caylus_GFX_SRC}")
