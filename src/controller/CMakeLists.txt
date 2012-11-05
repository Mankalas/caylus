# Caylus controller
source_group (Caylus_Controller_SRC .*.cc)
add_library (Caylus_Controller SHARED "${Caylus_Controller_SRC}")
set_target_properties (Caylus_Controller PROPERTIES LINKER_LANGUAGE CXX)
