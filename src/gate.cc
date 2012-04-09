/**
 * @file   gate.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Thu Jan 15 14:18:10 2009
 *
 * @brief Implementation of the Gate class.
 */

#include "exceptions.hh"
#include "gate.hh"
#include "console-ui.hh"
#include "game-engine.hh"
#include "board-element.hh"
#include "debug-logger.hh"
#include "castle.hh"
#include "const.hh"

Gate::Gate(GameEngine *ge)
	: Building(GATE,
	           BuildingType::fixed,
	           ResourceMap(0),
	           ResourceMap(0)),
		OmniscientBuilding(ge)
{
}

void Gate::on_activate()
{
	DebugLogger::log("Activating Gate.");
	BoardElement * player_choice = NULL;
	std::vector<BoardElement *> choices = game_->board().road().getAvailableBuildings(worker_);
	choices.insert(choices.begin(), (BoardElement*)&game_->board().castle());
	player_choice = worker_->askWorkerPlacement(choices);
	if (player_choice->isBuilding())
	{
		DebugLogger::log("Gate activated for Building.\n");
		Building * building = dynamic_cast<Building*>(player_choice);
		DebugLogger::log(building->name());
	}
	else
	{
		DebugLogger::log("Gate activated for Castle.\n");
		Castle * castle = dynamic_cast<Castle*>(player_choice);
		castle->add(worker_);
	}
}
