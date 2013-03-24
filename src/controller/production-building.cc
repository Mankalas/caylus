/**
 * @file   production-building.cc
 * @author Nicuvëo (crucuny@gmail.com)
 * @date   Jun 6 22:22:22 2011
 *
 * @brief  Declaration of the production-building class.
 */

#include "production-building.hh"
#include "debug-logger.hh"
#include "../player-signals.hh"

ProductionBuilding::~ProductionBuilding()
{
}


ProductionBuilding::ProductionBuilding(const std::vector<ResourceMap>& wchc,
                                       const std::vector<ResourceMap>& ochc)
	: Building("void", BuildingType::fixed, ResourceMap(0), ResourceMap(0)),
	  owner_choices_(ochc), worker_choices_(wchc)
{
}

void
ProductionBuilding::on_activate()
{
	Building::on_activate();
	if (worker_choices_.size() == 1)
	{
		worker_->addResources(worker_choices_[0]);
		return;
	}

	DebugLogger::log( "Here ");
	const ResourceMap & choice = worker_->signals().ask_resource(worker_choices_);
	worker_->addResources(choice);
}
