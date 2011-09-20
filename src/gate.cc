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

Gate::Gate(GameEngine* ge)
  : Building("Gate",
             BuildingType::fixed,
             ResourceMap(0),
             ResourceMap(0)),
    OmniscientBuilding(ge)
{
}

void Gate::on_activate()
{
  BuildingSmartPtr building;
  //int choice = 0;

  std::cout << *game_ << std::endl;
  try
  {
	  /*while (worker_)
    {
	    choice = ConsoleUI::inst()->getBuilding(game_->road(), false);
      if (choice == -1)
      {
        if (game_->addToCastle(worker_))
          worker_ = NULL;
      }
      else
      {
        building = game_->road()[choice];
        assert(building);
        worker_->workers() += 1;
        building->worker_set(*worker_);
        worker_ = NULL;
      }
      }*/
	  worker_->askWorkerPlacement();
  }
  catch(OccupiedBuildingEx*)
  {
    //worker_->showMessage(building->name() + " already occupied.");
    on_activate();
  }
  catch(UnactivableBuildingEx*)
  {
    //worker_->showMessage(building->name() +
    //" does not accept workers.");
    on_activate();
  }
}
