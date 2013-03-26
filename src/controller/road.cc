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
#include "game-engine.hh"
#include "road.hh"
#include "all-buildings.hh"
#include "stables.hh"
#include "gate.hh"
#include "joust-field.hh"
#include "inn.hh"
#include "merchant-guild.hh"
#include "board-element.hh"
#include "debug-logger.hh"

const unsigned int Road::FIRST_NEUTRAL_CASE = 6;
const unsigned int Road::BAILIFF_INIT_CASE = 11;
const unsigned int Road::PROVOST_INIT_CASE = Road::BAILIFF_INIT_CASE;
const unsigned int Road::LAST_CASE = 33;

Road::Road(GameEngine * ge)
	: buildings_(34)
{
	std::vector<Building *> neutral = boost::assign::list_of<Building *>
	                                  (new NFarm())
	                                  (new Forest())
	                                  (new NQuarry())
	                                  (new NSawmill())
	                                  (new NCarpenter(ge))
	                                  (new NMarketplace());
	if (ge->random())
	{
		std::srand(time(0));
		std::random_shuffle(neutral.begin(), neutral.end());
	}

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
		buildings_[i] = BuildingSmartPtr(neutral.at(i - 6));
	}

	buildings_[12] = BuildingSmartPtr(new FPeddler());
	buildings_[13] = BuildingSmartPtr(new FCarpenter(ge));
	buildings_[21] = BuildingSmartPtr(new GoldMine());

	free_slot_ = 14;
}

void
Road::build(BuildingSmartPtr bd)
{
	assert(bd);
	assert(free_slot_ < buildings_.size());

	buildings_[free_slot_++] = bd;
}

void
Road::clearWorkers()
{
	foreach(BuildingSmartPtr b, buildings_)
	{
		if (b)
		{
			b->removeWorker();
		}
	}
}

std::ostream &
operator<<(std::ostream & o, const Road & r)
{
	unsigned int i = 1;
	foreach(BuildingSmartPtr ptr, r.get())
	{
		o << BOLDYELLOW << i++ << ". " << RESET;
		if (ptr)
		{
			o << *ptr;
		}
		else
		{
			o << "<empty>";
		}
		o << std::endl;
	}
	return o;
}
