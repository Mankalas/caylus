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

void JoustField::onActivate_()
{
	if (worker_->resources()[Resource::denier] >= 1 &&
	    worker_->resources()[Resource::cloth] >= 1)
	{
		worker_->substractResources(ResourceMap(Resource::denier + Resource::cloth));
		worker_->addResources(Resource::favor);
	}
}
