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

void ConstructionBuilding::onActivate_()
{
	unsigned choice = 0;
	bool has_built = false;

	while (!has_built)
	{
		choice = worker_->signals().ask_building_to_construct();
		if (choice == 0)
		{
			break;
		}
		try
		{
			game_engine_->build(choice, worker_);
			has_built = true;
		}
		catch (NotEnoughResourceEx * ex)
		{
			std::cerr << ex->msg() << std::endl;
			// Nothing to do, keep looping...
		}
	}
}

void ConstructionBuilding::onBuild_()
{
	//ask_building_signal_.connect(owner_->view()->askBuildingSlot());
}
