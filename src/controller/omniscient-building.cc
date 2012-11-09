/**
 * @file   omniscient-building.cc
 * @author  <mankalas@localhost,>
 * @date   Mon Jan 12 00:14:20 2009
 *
 * @brief
 *
 *
 */

#include "omniscient-building.hh"

OmniscientBuilding::OmniscientBuilding(GameEngine * ge)
	: Building("void", BuildingType::fixed, ResourceMap(0), ResourceMap(0)),
	  game_(ge)
{
}


OmniscientBuilding::~OmniscientBuilding()
{
}
