# Caylus controller
project (Caylus_Controller)

set (Caylus_Controller_SRC board-element.cc player.cc all-buildings.cc building-type.cc building.cc construction-building.cc favor-building.cc game-engine.cc gate.cc inn.cc merchant-guild omniscient-building.cc production-building.cc residential-building.cc resource-map.cc resource.cc road.cc stables.cc trade-building.cc joust-field.cc castle.cc bridge.cc board.cc playback.cc)

add_library (Caylus_Controller SHARED "${Caylus_Controller_SRC}")
