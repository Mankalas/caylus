/*!
  \file   building-type.cc
  \brief  Implementation of BuildingType

  \author nicuveo
  \date   2009-01-06
*/

#include "building-type.hh"

using namespace controller;

const BuildingType BuildingType::fixed       = BuildingType ("fixed");
const BuildingType BuildingType::neutral     = BuildingType ("neutral");
const BuildingType BuildingType::wood        = BuildingType ("wood");
const BuildingType BuildingType::stone       = BuildingType ("stone");
const BuildingType BuildingType::residential = BuildingType ("residential");
const BuildingType BuildingType::prestige    = BuildingType ("prestige");

BuildingType::BuildingType (const BuildingType &r)
	: EnumObject<BuildingType> (r)
{
	this->operator = (r);
}

BuildingType::BuildingType (const std::string &name)
	: EnumObject<BuildingType> (name)
{
}
