/*!
  \file   trade-building.cc
  \brief  Implementation of TradeBuilding.

  <long description>

  \author
  \date   2009-01-06
*/

#include "trade-building.hh"
#include "console-ui.hh"

TradeBuilding::~TradeBuilding()
{
}


TradeBuilding::TradeBuilding (const ResourceMap&  supply,
                              const ResourceMap&  demand,
                              const std::vector<std::pair<unsigned, unsigned> >& ratios)
  : Building("void", BuildingType::fixed, ResourceMap(0), ResourceMap(0)),
    supply (supply), demand (demand), ratios (ratios)
{
}

void
TradeBuilding::on_activate ()
{
  std::vector<std::pair<ResourceMap, ResourceMap> > exchanges = createExchangeVector();
  unsigned choice = 1;

  std::cout << "Player " << worker_->name()
            << ", what would you like to exchange?" << std::endl
            << "0. Nothing, I love to waste workers." << std::endl;

  std::pair<ResourceMap, ResourceMap> ex;
  foreach (ex, exchanges)
  {
    std::cout << choice++ << ". " << ex.first << " for "
              << ex.second << std::endl;
  }

  choice = ask_resource_choice_();
  if (0 == choice)
    return;

  const std::pair<ResourceMap, ResourceMap>& exchange = exchanges[choice - 1];
  if (worker_->resources() >= exchange.first)
  {
    worker_->resources() -= exchange.first;
    worker_->resources() += exchange.second;
  }
  else
  {
    std::cout << "Not enough resources. Try again." << std::endl;
    on_activate();
  }
}

std::vector<std::pair<ResourceMap, ResourceMap> >
TradeBuilding::createExchangeVector() const
{
  std::vector<std::pair<ResourceMap, ResourceMap> > exchanges;

  for (unsigned i = 0; i < ratios.size(); ++i)
    foreach (const Resource& sr, Resource::list())
      if (supply[sr] > 0)
	{
	  foreach (const Resource& dr, Resource::list())
	    if (demand[dr] > 0)
	      exchanges.push_back(std::make_pair(ratios[i].first * sr,
						 ratios[i].second * dr));
	}
  return exchanges;
}
