# Caylus GFX
source_group (Caylus_GFX_SRC .*.cc)
add_library (Caylus_GFX SHARED "${Caylus_GFX_SRC}")
set_target_properties (Caylus_GFX PROPERTIES LINKER_LANGUAGE CXX)
