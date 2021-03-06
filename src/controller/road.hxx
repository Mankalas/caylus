/*!
  \file   road.hxx
  \brief  Inline implementations for Road.

  \author nicuveo
  \date   2009-01-06
*/

#ifndef ROAD_HXX_
# define ROAD_HXX_

# include "road.hh"
# include "player.hh"
# include "exceptions.hh"

# include "../const.hh"
# include "../visitor.hh"

inline const std::vector<BuildingSmartPtr>&
Road::get() const
{
	return buildings_;
}

inline BuildingSmartPtr &
Road::operator [](unsigned i)
{
	assert(i < buildings_.size());
	return buildings_[i];
}

inline const BuildingSmartPtr &
Road::operator [](unsigned i) const
{
	assert(i < buildings_.size());
	return buildings_[i];
}

inline BuildingSmartPtr &
Road::operator [](const std::string & name)
{
	foreach(BuildingSmartPtr & ptr, buildings_)
	{
		if (ptr->name().compare(name) == 0)
		{
			return ptr;
		}
	}
	throw new NoBuildingEx();
}

inline const BuildingSmartPtr &
Road::operator [](const std::string & name) const
{
	foreach(const BuildingSmartPtr & ptr, buildings_)
	{
		if (ptr->name().compare(name) == 0)
		{
			return ptr;
		}
	}
	throw new NoBuildingEx();
}

inline
void controller::Road::accept(ConstVisitor & v) const
{
	v.operator()(*this);
}

inline
void controller::Road::accept(Visitor & v)
{
	v.operator()(*this);
}

#endif /* !ROAD_HXX_ */
