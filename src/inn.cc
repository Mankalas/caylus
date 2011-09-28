/**
 * @file   inn.cc
 * @author  <mankalas@localhost,>
 * @date   Thu Jan 15 14:21:00 2009
 *
 * @brief
 *
 *
 */

#include "inn.hh"

Inn::Inn()
	: Building("Inn",
	           BuildingType::fixed,
	           ResourceMap(0),
	           ResourceMap(0)),
	host_(NULL)
{
}

void Inn::on_activate()
{
	if (worker_)
	{
		//ask player if he wants to remove its worker
	}
	host_ = worker_;
	worker_ = NULL;
}
