/**
 * @file   building.cc
 * @author Nicuvëo (crucuny@gmail.com)
 * @date   Jun  6 21:22:56 2009
 *
 * @brief  Declaration of the building class.
 */

#include <cassert>
#include "building.hh"
#include "../exceptions.hh"
#include "player.hh"
#include "../const.hh"

Building::Building(const std::string & name,
                   const BuildingType & type,
                   const std::vector<ResourceMap>& cost,
                   const ResourceMap & gain)
	: BoardElement(name)
	, type_(type)
	, gain_(gain)
	, cost_(cost)
	, owner_(NULL)
	, worker_(NULL)
{
}

Building::~Building()
{
}

void
Building::build(Player & current)
{
	assert(!owner_);
	assert(type_ != BuildingType::fixed);
	assert(type_ != BuildingType::neutral);

	owner_ = &current;
	foreach(const ResourceMap cost, cost_)
	{
		if (current.resources() >= cost)
		{
			current.addResources(gain_);
			current.substractResources(cost);
			onBuild();
		}
		else
		{
			throw new NotEnoughResourceEx();
		}
	}
}

void
Building::placeWorker(Player & current)
{
	if (worker_)
	{
		signals_.already_occupied(this);
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
	signals_.worker_placed(worker_, this);
	current.decrementWorkers();
}

void
Building::activate()
{
	if (worker_)
	{
		onActivate();
		removeWorker();
	}
}

void
Building::removeWorker()
{
	if (worker_)
	{
		worker_->incrementWorkers();
		worker_ = NULL;
	}
}

void
Building::demolish()
{
	assert(!worker_);
	onDemolish();
	owner_ = NULL;
}

void
Building::onBuild()
{
}

void
Building::onActivate()
{
	BoardElement::onActivate();
	assert(worker_);
}

void
Building::onDemolish()
{
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
