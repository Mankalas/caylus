/**
 * @file   joust-field.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Wed Feb  4 11:40:25 2009
 *
 * @brief  Declaration of the joust-field class.
 */

#include "joust-field.hh"
#include "const.hh"
#include "../debug-logger.hh"

JoustField::JoustField()
	: Building(JOUST_FIELD,
	           BuildingType::fixed,
	           ResourceMap(0),
	           ResourceMap(0))
{
}

void JoustField::on_activate(void)
{
	Building::on_activate();
	if (worker_->resources()[Resource::denier] < 1 ||
	    worker_->resources()[Resource::cloth] < 1)
	{
		DebugLogger::log("Not enough resources. Try again.");
		on_activate();
	}
	if (ask_proceed_())
	{
		worker_->addResources(ResourceMap(Resource::denier + Resource::cloth));
		worker_->substractResources(Resource::favor);
	}
}
