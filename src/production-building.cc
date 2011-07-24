/*!
  \file   production-building.cc
  \brief  Implementation of ProductionBuilding

  \author nicuveo
  \date   2009-01-06
*/

#include "production-building.hh"
#include "console-ui.hh"

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
  if (worker_choices_.size() == 1)
  {
    worker_->resources() += worker_choices_[0];
    return;
  }

  unsigned i = 0;
  std::cout << i++ << ". Nothing" << std::endl;
  foreach (ResourceMap r, worker_choices_)
    std::cout << i++ << ". " << r << std::endl;

  int choice = ConsoleUI::inst()->askChoice(0, worker_choices_.size());
  if (choice == 0)
    return;
  --choice;

  worker_->resources() += worker_choices_[choice];
}
