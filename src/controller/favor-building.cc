/*!
  \file   favor-building.cc
  \brief  Implementation of FavorBuilding.

  \author nicuveo
  \date   2009-01-06
*/

#include <cassert>
#include "favor-building.hh"

FavorBuilding::~FavorBuilding()
{
}


FavorBuilding::FavorBuilding()
	: Building("void", BuildingType::fixed, ResourceMap(0), ResourceMap(0))
{
}


void
FavorBuilding::onBuild_()
{
	assert(owner_);

	// owner_->favor_proceed (); TODO:
}

bool FavorBuilding::canBePlacedOn_() const
{
	return false;
}
