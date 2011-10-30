/*!
  \file   building.cc
  \brief  Implementation of Building

  \author nicuveo
  \date   2009-01-06
*/

#include <cassert>
#include "building.hh"
#include <cassert>
#include "exceptions.hh"
#include "player.hh"

Building::Building (const std::string &name,
                    const BuildingType &type,
                    const std::vector<ResourceMap>& cost,
                    const ResourceMap  &gain)
	: name_(name), type_(type), gain_(gain), cost_(cost), owner_(0), worker_(0)
{
}

Building::~Building ()
{
}

void
Building::build (Player *current)
{
	assert(!owner_);
	assert(type_ != BuildingType::fixed);
	assert(type_ != BuildingType::neutral);
	assert(current);

	owner_ = current;
	foreach (const ResourceMap cost, cost_)
	{
		if (current->resources() >= cost)
		{
			current->resources() += gain_;
			current->resources() -= cost;
			on_build ();
		}
		else
		{
			assert(false);  // throw exception -> the player does not have enough resources.
		}
	}
}

void
Building::worker_set (Player &current)
{
	if (worker_)
	{
		throw new OccupiedBuildingEx();
	}
	if (type_ == BuildingType::prestige || type_ == BuildingType::residential)
	{
		throw new UnactivableBuildingEx();
	}

	if (owner_ && owner_ != &current)
	{
		owner_->resources()[Resource::prestige] += 1;
	}
	worker_ = &current;
	current.workers() -= 1;
}

void
Building::activate ()
{
	if (!worker_)
	{
		return;
	}

	std::cout << "Activation of " << name_ << " for player " << *worker_ << std::endl;

	on_activate ();

	worker_unset ();
}

void
Building::worker_unset ()
{
	worker_ = NULL;
}

void
Building::demolish ()
{
	assert (!worker_);

	on_demolish ();

	owner_ = 0;
}

void
Building::on_build ()
{
}

void
Building::on_activate ()
{
}

void
Building::on_demolish ()
{
}

bool Building::isBuilding() const
{
	return true;
}

std::ostream&
operator<<(std::ostream &o, const Building &b)
{
	o << b.name();
	if (b.owner())
	{
		o << " (" << b.owner()->name() << ") ";
	}
	if (b.worker())
	{
		o << " : " << b.worker()->name();
	}
	return o;
}
