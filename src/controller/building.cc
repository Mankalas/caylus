/**
 * @file   building.cc
 * @author Nicuvëo (crucuny@gmail.com)
 * @date   Jun  6 21:22:56 2009
 *
 * @brief  Declaration of the building class.
 */

#include <cassert>
#include "building.hh"
#include "exceptions.hh"
#include "player.hh"
#include "../const.hh"

Building::Building(const std::string & name,
                   const BuildingType & type,
                   const std::vector<ResourceMap>& cost,
                   const ResourceMap & gain) :
	BoardElement(name),
	type_(type), gain_(gain), cost_(cost), owner_(0), worker_(0)
{
}

Building::~Building()
{
}

void
Building::build(Player * current)
{
	assert(!owner_);
	assert(type_ != BuildingType::fixed);
	assert(type_ != BuildingType::neutral);
	assert(current);

	owner_ = current;
	foreach(const ResourceMap cost, cost_)
	{
		if (current->resources() >= cost)
		{
			current->addResources(gain_);
			current->substractResources(cost);
			on_build();
		}
		else
		{
			assert(false);  // throw exception -> the player does not have enough resources.
		}
	}
}

void
Building::worker_set(Player & current)
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
		owner_->addResources(Resource::prestige);
	}
	worker_ = &current;
	worker_placed(this, worker_);
	current.workers() -= 1;
}

void
Building::activate()
{
	if (!worker_)
	{
		return;
	}

	on_activate();

	worker_unset();
}

void
Building::worker_unset()
{
	worker_ = NULL;
}

void
Building::demolish()
{
	assert(!worker_);

	on_demolish();

	owner_ = 0;
}

void
Building::on_build()
{
}

void
Building::on_activate()
{
	assert(worker_);
	activation_sig(this, worker_);
}

void
Building::on_demolish()
{
}

bool Building::isBuilding() const
{
	return true;
}

std::ostream &
operator<<(std::ostream & o, const Building & b)
{
	o << b.name();
	if (b.owner())
	{
		o << " (" << BLUE << b.owner()->name() << RESET << ") ";
	}
	if (b.worker())
	{
		o << " : " << GREEN << b.worker()->name() << RESET;
	}
	return o;
}

bool Building::has(const Player * p) const
{
	return worker_ == p;
}
