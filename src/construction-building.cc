/**
 * @file   construction-building.cc
 * @author  <mankalas@localhost,>
 * @date   Wed Jan  7 14:27:09 2009
 *
 * @brief  Implementation of ConstructionBuilding.
 *
 */

#include <map>
#include "construction-building.hh"
#include "view.hh"
#include "game-engine.hh"

using namespace controller;

ConstructionBuilding::~ConstructionBuilding()
{
}


ConstructionBuilding::ConstructionBuilding(GameEngine *ge, const BuildingType &construc_type)
	: Building("void", BuildingType::fixed, ResourceMap(0), ResourceMap(0)),
	  OmniscientBuilding(ge),
	  construc_type(construc_type)
{
}

void ConstructionBuilding::on_activate()
{
	//  unsigned i = 1;
	unsigned choice = 0;

	std::map<unsigned, BuildingSmartPtr> building_choice;

	/*std::cout << "0. Pass" << std::endl;
	foreach (const BuildingSmartPtr& building, game_->buildings())
	{
	  if (building->type() == construc_type)
	  {
	    std::cout << i << ". " << building->name() << std::endl;
	    building_choice[i++] = building;
	  }
	}
	choice = ConsoleUI::inst()->askChoice(0, building_choice.size() + 1);*/
	choice = ask_building_signal_();
	if (choice == 0)
	{
		return;
	}
	else
		game_->build(*(std::find(game_->buildings().begin(),
		                         game_->buildings().end(),
		                         building_choice[choice])), worker_);
}

void ConstructionBuilding::on_build()
{
	ask_building_signal_.connect(owner_->view()->getAskBuildingSlot());
}
