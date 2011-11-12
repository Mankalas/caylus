/**
 * @file   production-building.cc
 * @author Nicuvëo (crucuny@gmail.com)
 * @date   Jun 6 22:22:22 2011
 *
 * @brief  Declaration of the production-building class.
 */

#include "production-building.hh"
#include "console-ui.hh"
#include "debug-logger.hh"

ProductionBuilding::~ProductionBuilding()
{
}


ProductionBuilding::ProductionBuilding (const std::vector<ResourceMap>& wchc,
                                        const std::vector<ResourceMap>& ochc)
	: Building("void", BuildingType::fixed, ResourceMap(0), ResourceMap(0)),
	  owner_choices_ (ochc), worker_choices_ (wchc)
{
}

void
ProductionBuilding::on_activate ()
{
	DebugLogger::log("Activating Trading post.");
	if (worker_choices_.size() == 1)
	{
		worker_->resources() += worker_choices_[0];
		return;
	}

	//unsigned i = 0;
	/*std::cout << i++ << ". Nothing" << std::endl;
	foreach (ResourceMap r, worker_choices_)
	  std::cout << i++ << ". " << r << std::endl;

	  int choice = ConsoleUI::inst()->askChoice(0, worker_choices_.size());*/

	unsigned choice = ask_resource_choice_();
	if (choice == 0)
	{
		return;
	}
	--choice;

	worker_->resources() += worker_choices_[choice];
}
