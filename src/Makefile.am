bin_PROGRAMS = caylus_ia

caylus_ia_CXXFLAGS = -W -Wall -Wextra -Werror -ansi -pedantic -O5

caylus_ia_LDADD = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_signals -lboost_thread

caylus_ia_LDFLAGS =

caylus_ia_SOURCES = $(controler_SOURCES) $(view_SOURCES)	\
$(gfx_SOURCES)

controler_SOURCES := board-element.hh board-element.cc player.cc	\
player.hh player.hxx all-buildings.cc all-buildings.hh			\
building-type.cc building-type.hh building.cc building.hh building.hxx	\
construction-building.cc construction-building.hh enum-object.hh	\
enum-object.hxx exceptions.hh favor-building.cc favor-building.hh	\
game-engine.cc game-engine.hh game-engine.hxx gate.cc gate.hh inn.cc	\
inn.hh inn.hxx main.cc merchant-guild.cc merchant-guild.hh		\
omniscient-building.cc omniscient-building.hh omniscient-building.hxx	\
production-building.cc production-building.hh residential-building.cc	\
residential-building.hh resource-map.cc resource-map.hh			\
resource-map.hxx resource.cc resource.hh resource.hxx road.cc road.hh	\
road.hxx stables.cc stables.hh trade-building.cc trade-building.hh	\
joust-field.hh joust-field.cc castle.hh castle.cc castle.hxx bridge.hh	\
bridge.hxx bridge.cc const.hh game-signals.hh board.hh board.hxx	\
board.cc debug-logger.hh player-signals.hh playback.hh playback.cc

view_SOURCES := view.hh view.cc active-view.hh active-view.cc		\
passive-view.hh passive-view.cc display-view.hh console-view.hh		\
console-view.cc human.hh human.cc logger.hh logger.hxx logger.cc

gfx_SOURCES := graphic-view.cc graphic-view.hh gfx-window.cc	\
gfx-window.hxx gfx-window.hh gfx-sprite.hh gfx-sprite.cc	\
gfx-sprite.hxx gfx-sprite-library.cc gfx-sprite-library.hxx	\
gfx-sprite-library.hh gfx-board.hh gfx-board.cc


# ai.hh ai.cc
