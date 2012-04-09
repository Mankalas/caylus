/**
 * @file   inn.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Thu Jan 15 14:21:00 2009
 *
 * @brief  Declaration of the inn class.
 */

#include "inn.hh"
#include "const.hh"

Inn::Inn()
	: Building(INN,
	           BuildingType::fixed,
	           ResourceMap(0),
	           ResourceMap(0)),
	host_(NULL)
{
}

void Inn::on_activate()
{
	Building::on_activate();
	if (worker_)
	{
		//ask player if he wants to remove its worker
	}
	host_ = worker_;
	worker_ = NULL;
}
