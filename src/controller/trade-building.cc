/**
 * @file   trade-building.cc
 * @author Nicuvëo <crucuny@gmail.com>
 * @date   Jun 6 22:15:11 2011
 *
 * @brief  Declaration of the trade-building class.
 */

#include "trade-building.hh"
#include "../const.hh"
#include "../debug-logger.hh"

TradeBuilding::~TradeBuilding()
{
}


TradeBuilding::TradeBuilding(const ResourceMap & supply,
                             const ResourceMap & demand,
                             const std::vector<std::pair<unsigned, unsigned> >& ratios)
	: Building("void", BuildingType::fixed, ResourceMap(0), ResourceMap(0)),
	  supply(supply), demand(demand), ratios(ratios)
{
}

void
TradeBuilding::on_activate()
{
	Building::on_activate();
	std::vector<std::pair<ResourceMap, ResourceMap> > exchanges = createExchangeVector();
	unsigned choice = 1;

	std::pair<ResourceMap, ResourceMap> ex;
	choice = worker_->signals()->ask_choice(1);
	if (0 == choice)
	{
		return;
	}

	const std::pair<ResourceMap, ResourceMap>& exchange = exchanges[choice - 1];
	if (worker_->resources() >= exchange.first)
	{
		worker_->substractResources(exchange.first);
		worker_->addResources(exchange.second);
	}
	else
	{
		DebugLogger::log("Not enough resources. Try again.");
		on_activate();
	}
}

std::vector<std::pair<ResourceMap, ResourceMap> >
TradeBuilding::createExchangeVector() const
{
	std::vector<std::pair<ResourceMap, ResourceMap> > exchanges;

	for (unsigned i = 0; i < ratios.size(); ++i)
		foreach(const Resource & sr, Resource::list())
		if (supply[sr] > 0)
		{
			foreach(const Resource & dr, Resource::list())
			if (demand[dr] > 0)
				exchanges.push_back(std::make_pair(ratios[i].first * sr,
				                                   ratios[i].second * dr));
		}
	return exchanges;
}
