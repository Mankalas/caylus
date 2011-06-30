/*!
  \file   residential-building.cc
  \brief  Implementation of ResidentialBuilding.

  \author nicuveo
  \date   2009-01-06
*/

#include <cassert>
#include "residential-building.hh"


ResidentialBuilding::~ResidentialBuilding()
{
}


ResidentialBuilding::ResidentialBuilding (unsigned deniers)
  : Building("void", BuildingType::fixed, ResourceMap(0), ResourceMap(0)),
    deniers(deniers)
{
  assert (deniers > 0);
}


void
ResidentialBuilding::on_build ()
{
  assert (owner_);
  owner_->residences() += deniers;
}

void
ResidentialBuilding::on_demolish ()
{
  assert (owner_);
  owner_->residences() -= deniers;
}
