# Caylus controller

add_library (Caylus_Controller STATIC all-buildings.cc
board-element.cc building.cc castle.cc favor-building.cc
game-signals.cc inn.cc merchant-guild.cc player.cc
residential-building.cc resource-map.cc stables.cc board.cc bridge.cc
building-type.cc construction-building.cc game-engine.cc gate.cc
joust-field.cc omniscient-building.cc production-building.cc
resource.cc road.cc trade-building.cc)

set_target_properties (Caylus_Controller PROPERTIES LINKER_LANGUAGE CXX)
