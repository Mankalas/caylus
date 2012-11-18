/**
 * @file   gate.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Thu Jan 15 14:18:10 2009
 *
 * @brief Implementation of the Gate class.
 */

#include "gate.hh"
#include "exceptions.hh"
#include "game-engine.hh"
#include "board-element.hh"
#include "debug-logger.hh"
#include "castle.hh"
#include "const.hh"
#include "player.hh"

Gate::Gate(GameEngine * game_engine)
	: Building(GATE,
	           BuildingType::fixed,
	           ResourceMap(0),
	           ResourceMap(0)),
	OmniscientBuilding(game_engine)
{
}

void Gate::on_activate()
{
	Building::on_activate();

	bool is_selection_valid = false;
	unsigned int selected_case;
	while (!is_selection_valid)
	{
		selected_case = worker_->askWorkerPlacement();
		if (selected_case == Castle::CASE_NUMBER)
		{
			game_engine_->board().castle().add(worker_);
			is_selection_valid = true;
		}
		else if (selected_case != Bridge::CASE_NUMBER)
		{
			BuildingSmartPtr selected_building = game_engine_->board().road().get()[selected_case];
			selected_building->worker(worker_);
			is_selection_valid = true;
		}
	}
}
