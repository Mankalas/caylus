# Caylus view
source_group (Caylus_View_SRC .*.cc)
add_library (Caylus_View SHARED "${Caylus_View_SRC}")
set_target_properties (Caylus_View PROPERTIES LINKER_LANGUAGE CXX)
