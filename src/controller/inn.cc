/**
 * @file   inn.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Thu Jan 15 14:21:00 2009
 *
 * @brief  Declaration of the inn class.
 */

#include "inn.hh"
#include "../debug-logger.hh"

Inn::Inn()
	: Building(INN,
	           BuildingType::fixed,
	           ResourceMap(0),
	           ResourceMap(0)),
	host_(NULL)
{
}

void Inn::onActivate_()
{
	if (worker_)
	{
		host_ = worker_;
		worker_ = NULL;
	}
	else if (host_)
	{
		bool do_remove = host_->askInnRemoval();
		if (do_remove)
		{
			host_->incrementWorkers();
			host_ = NULL;
		}
	}
}

bool Inn::has(const Player * p) const
{
	return worker_ == p || host_ == p;
}

bool Inn::canBePlacedOn_() const
{
	return worker_ == NULL;
}

bool Inn::canBeActivated_() const
{
	return worker_ || host_;
}
