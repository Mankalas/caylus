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
#include "game-engine.hh"

using namespace controller;

ConstructionBuilding::~ConstructionBuilding()
{
}


ConstructionBuilding::ConstructionBuilding(GameEngine * ge, const BuildingType & construc_type)
	: Building("void", BuildingType::fixed, ResourceMap(0), ResourceMap(0)),
	  OmniscientBuilding(ge),
	  construc_type(construc_type)
{
}

void ConstructionBuilding::onActivate()
{
	Building::onActivate();
	unsigned choice = 0;

	std::map<unsigned, BuildingSmartPtr> building_choice;
	choice = ask_building_signal_();
	if (choice == 0)
	{
		return;
	}
	else
		game_engine_->build(*(std::find(game_engine_->buildings().begin(),
		                                game_engine_->buildings().end(),
		                                building_choice[choice])), worker_);
}

void ConstructionBuilding::onBuild()
{
	//ask_building_signal_.connect(owner_->view()->askBuildingSlot());
}
