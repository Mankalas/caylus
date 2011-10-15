/**
 * @file   road.hh
 * @author Nicuvëo
 * @date   Tue Jan 06 15:15:57 2009
 * @brief  Implementation of the road class.
 */

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include "road.hh"
#include "all-buildings.hh"
#include "stables.hh"
#include "gate.hh"
#include "joust-field.hh"
#include "inn.hh"
#include "merchant-guild.hh"

Road::Road (GameEngine *ge)
	: buildings_ (34)
{
	std::cout << "Initializing Road... ";
	std::vector<Building *> neutral = boost::assign::list_of<Building *>
	                                  (new NFarm ())
	                                  (new Forest ())
	                                  (new NQuarry ())
	                                  (new NSawmill ())
	                                  (new NCarpenter (ge))
	                                  (new NMarketplace ());

	std::srand(time(0));
	std::random_shuffle(neutral.begin(), neutral.end());

	BuildingSmartPtr gate(new Gate(ge));
	buildings_[0] = gate;
	BuildingSmartPtr trading_post(new TradingPost());
	buildings_[1] = trading_post;
	BuildingSmartPtr merchant_guild(new MerchantGuild(ge));
	buildings_[2] = merchant_guild;
	BuildingSmartPtr joust_field(new JoustField());
	buildings_[3] = joust_field;
	BuildingSmartPtr stables(new Stables(ge));
	buildings_[4] = stables;
	BuildingSmartPtr inn(new Inn());
	buildings_[5] = inn;

	for (unsigned i = 6; i < 12; ++i)
	{
		unsigned tmp = (unsigned) (neutral.size() * (rand() / ((double) RAND_MAX)));
		BuildingSmartPtr ptr(neutral[tmp]);
		buildings_[i] = ptr;
		neutral.erase (neutral.begin () + tmp);
	}

	buildings_[12] = BuildingSmartPtr(new FPeddler());
	buildings_[13] = BuildingSmartPtr(new FCarpenter(ge));
	buildings_[21] = BuildingSmartPtr(new GoldMine());

	free_slot_ = 14;

	std::cout << "Done." << std::endl;
}

void
Road::build(BuildingSmartPtr bd)
{
	assert(bd);
	assert(free_slot_ < buildings_.size ());

	buildings_[free_slot_++] = bd;
}

void
Road::clearWorkers()
{
	foreach (BuildingSmartPtr b, buildings_)
	{
		if (b)
		{
			b->worker_unset();
		}
	}
}

std::vector<BuildingSmartPtr>
Road::getAvailableBuildingsForPlayer() const
{
	std::vector<BuildingSmartPtr> available_buildings;

	foreach (BuildingSmartPtr b, buildings_)
	{
		if (b->worker() == NULL)
		{
			available_buildings.push_back(b);
		}
	}
	return available_buildings;
}
