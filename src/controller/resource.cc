/*!
  \file   resource.cc
  \brief  Implementation of Resource.

  \author nicuveo
  \date   2009-01-06
*/

#include "resource.hh"

using namespace controller;

std::list<Resource> Resource::list_;

const Resource Resource::food     = Resource ("food cube");
const Resource Resource::wood     = Resource ("wood cube");
const Resource Resource::cloth    = Resource ("cloth cube");
const Resource Resource::stone    = Resource ("stone cube");
const Resource Resource::gold     = Resource ("gold cube");
const Resource Resource::denier   = Resource ("denier");
const Resource Resource::prestige = Resource ("prestige point");
const Resource Resource::favor    = Resource ("royal favor");

Resource::Resource (const std::string &name)
	: EnumObject<Resource> (name)
{
	list_.push_back (*this);
}

Resource::Resource (const Resource &r)
	: EnumObject<Resource> (r)
{
	this->operator = (r);
}
