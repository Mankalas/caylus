# Caylus view
add_library (Caylus_View SHARED active-view.cc ai.cc console-view.cc graphic-view.cc human.cc logger.cc passive-view.cc playback.cc player-view.cc view.cc)
set_target_properties (Caylus_View PROPERTIES LINKER_LANGUAGE CXX)
