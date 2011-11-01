/**
 * @file   gate.cc
 * @author  <mankalas@localhost,>
 * @date   Thu Jan 15 14:18:10 2009
 *
 * @brief Implementation of the Gate
 */

#include "exceptions.hh"
#include "gate.hh"
#include "console-ui.hh"
#include "game-engine.hh"
#include "board-element.hh"
#include "logger.hh"
#include "castle.hh"

Gate::Gate(GameEngine *ge)
	: Building("Gate",
	           BuildingType::fixed,
	           ResourceMap(0),
	           ResourceMap(0)),
		OmniscientBuilding(ge)
{
}

void Gate::on_activate()
{
	try
	{
<<<<<<< HEAD
		Logger::instance().log("Activating Gate.");
=======
		Logger::log("Activating Gate.");
>>>>>>> 3d05f8338c3fe83888f78ecfad0dedc615162b67
		BoardElement * player_choice = NULL;
		std::vector<BoardElement *> choices = game_->road().getAvailableBuildingsForPlayer();
		choices.push_back(&game_->castle());
		do
		{
			player_choice = worker_->askWorkerPlacement(choices);
		}
		while (!player_choice->isBuilding() || !player_choice->isCastle());
		if (player_choice->isBuilding())
		{
<<<<<<< HEAD
			Logger::instance().log("Gate activated for Building.\n");
			Building * building = dynamic_cast<Building*>(player_choice);
			Logger::instance().log(building->name());
		}
		else
		{
			Logger::instance().log("Gate activated for Castle.\n");
=======
			Logger::log("Gate activated for Building.\n");
			Building * building = dynamic_cast<Building*>(player_choice);
			Logger::log(building->name());
		}
		else
		{
			Logger::log("Gate activated for Castle.\n");
>>>>>>> 3d05f8338c3fe83888f78ecfad0dedc615162b67
			Castle * castle = dynamic_cast<Castle*>(player_choice);
			castle->add(worker_);
		}

	}
	catch (OccupiedBuildingEx *)
	{
		on_activate();
	}
	catch (UnactivableBuildingEx *)
	{
		on_activate();
	}
}
