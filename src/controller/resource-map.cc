/*!
  \file   resource-map.cc
  \brief  Implementation of ResourceMap.

  \author nicuveo
  \date   2009-01-06
*/

#include <cassert>
#include "resource-map.hh"
#include "../const.hh"

ResourceMap::ResourceMap(const unsigned & value)
{
	foreach(const Resource & r, Resource::list())
	map_[r] = value;
}

ResourceMap::ResourceMap(const Resource & k)
{
	foreach(const Resource & r, Resource::list())
	map_[r] = r == k ? 1 : 0;
}


unsigned &
ResourceMap::operator [](const Resource & r)
{
	std::map<Resource, unsigned>::iterator it;

	it = map_.find(r);
	assert(it != map_.end());

	return it->second;
}

unsigned
ResourceMap::operator [](const Resource & r) const
{
	std::map<Resource, unsigned>::const_iterator it;

	it = map_.find(r);
	assert(it != map_.end());

	return it->second;
}


ResourceMap &
ResourceMap::operator += (const ResourceMap & rmap)
{
	assert(map_.size()      == Resource::list().size());
	assert(rmap.map_.size() == Resource::list().size());

	foreach(const Resource & r, Resource::list())
	map_[r] += rmap[r];

	return *this;
}

ResourceMap &
ResourceMap::operator -= (const ResourceMap & rmap)
{
	assert(map_.size()      == Resource::list().size());
	assert(rmap.map_.size() == Resource::list().size());

	//assert (*this >= rmap); //TODO: add exception throw otherwise

	foreach(const Resource & r, Resource::list())
	map_[r] = rmap[r] > map_[r] ? 0 : map_[r] - rmap[r];

	return *this;
}


bool
ResourceMap::operator > (const ResourceMap & rmap) const
{
	assert(map_.size()      == Resource::list().size());
	assert(rmap.map_.size() == Resource::list().size());

	foreach(const Resource & r, Resource::list())
	if ((*this)[r] <= rmap[r])
	{
		return false;
	}
	return true;
}

bool
ResourceMap::operator < (const ResourceMap & rmap) const
{
	assert(map_.size()      == Resource::list().size());
	assert(rmap.map_.size() == Resource::list().size());

	foreach(const Resource & r, Resource::list())
	{
		if ((*this)[r] >= rmap[r])
		{
			return false;
		}
	}
	return true;
}

bool
ResourceMap::operator >= (const ResourceMap & rmap) const
{
	assert(map_.size()      == Resource::list().size());
	assert(rmap.map_.size() == Resource::list().size());

	foreach(const Resource & r, Resource::list())
	if ((*this)[r] < rmap[r])
	{
		return false;
	}
	return true;
}

bool
ResourceMap::operator <= (const ResourceMap & rmap) const
{
	assert(map_.size()      == Resource::list().size());
	assert(rmap.map_.size() == Resource::list().size());

	foreach(const Resource & r, Resource::list())
	if ((*this)[r] > rmap[r])
	{
		return false;
	}
	return true;
}

bool
ResourceMap::operator == (const ResourceMap & rmap) const
{
	assert(map_.size()      == Resource::list().size());
	assert(rmap.map_.size() == Resource::list().size());

	return map_ == rmap.map_;
}

bool
ResourceMap::operator != (const ResourceMap & rmap) const
{
	return !(*this == rmap);
}


ResourceMap
ResourceMap::operator + (const ResourceMap & rmap) const
{
	ResourceMap res;

	assert(map_.size()      == Resource::list().size());
	assert(rmap.map_.size() == Resource::list().size());

	foreach(const Resource & r, Resource::list())
	res[r] = (*this)[r] + rmap[r];

	return res;
}

ResourceMap
ResourceMap::operator - (const ResourceMap & rmap) const
{
	ResourceMap res;

	assert(map_.size()      == Resource::list().size());
	assert(rmap.map_.size() == Resource::list().size());

	assert(*this >= rmap);  //TODO: add exception throw otherwise

	foreach(const Resource & r, Resource::list())
	res[r] = (*this)[r] - rmap[r];

	return res;
}


ResourceMap
ResourceMap::operator * (const unsigned & mul) const
{
	ResourceMap res;

	assert(map_.size() == Resource::list().size());

	foreach(const Resource & r, Resource::list())
	res[r] = (*this)[r] * mul;

	return res;
}

ResourceMap &
ResourceMap::operator *= (const unsigned & mul)
{
	assert(map_.size() == Resource::list().size());

	foreach(const Resource & r, Resource::list())
	(*this)[r] *= mul;

	return *this;
}

std::ostream &
operator << (std::ostream & ostr, const ResourceMap & rm)
{
	bool first = true;

	foreach(const Resource & r, Resource::list())
	{
		if (rm[r] == 0)
		{
			continue;
		}
		if (r == Resource::food)
		{
			ostr << MAGENTA;
		}
		else if (r == Resource::wood)
		{
			ostr << RED;
		}
		else if (r == Resource::stone)
		{
			ostr << GRAY;
		}
		else if (r == Resource::gold)
		{
			ostr << YELLOW;
		}
		else if (r == Resource::denier)
		{
			ostr << GREEN;
		}
		else if (r == Resource::cloth)
		{
			ostr << BLUE;
		}
		else if (r == Resource::prestige)
		{
			ostr << MAGENTA;
		}
		else if (r == Resource::favor)
		{
			ostr << CYAN;
		}
		ostr << (first ? "" : ", ") << rm[r] << " " << r << (rm[r] > 1 ? "s" : "")
		     << RESET;
		first = false;
	}

	return ostr;
}
