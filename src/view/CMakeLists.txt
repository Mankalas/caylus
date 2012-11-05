# Caylus view
set (Caylus_View_SRC view.cc active-view.cc passive-view.cc console-view.cc human.cc logger.cc graphic-view.cc)

add_library (Caylus_View SHARED "${Caylus_View_SRC}")
