/**
 * @file   residential-building.cc
 * @author Nicuvëo <crucuny@gmail.com
 * @date   Jun 01 19:44:49 2009
 *
 * @brief  Declaration of the residential-building class.
 */

#include <cassert>
#include "residential-building.hh"

ResidentialBuilding::~ResidentialBuilding()
{
}

ResidentialBuilding::ResidentialBuilding(unsigned deniers)
	: Building("void", BuildingType::fixed, ResourceMap(0), ResourceMap(0))
	, deniers(deniers)
{
	assert(deniers > 0);
}

void
ResidentialBuilding::onBuild()
{
	assert(owner_);
	owner_->increaseIncome(deniers);
}

void
ResidentialBuilding::onDemolish()
{
	assert(owner_);
	owner_->decreaseIncome(deniers);
}
