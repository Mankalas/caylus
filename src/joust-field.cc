/**
 * @file   joust-field.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Wed Feb  4 11:40:25 2009
 *
 * @brief  Declaration of the joust-field class.
 */

#include "joust-field.hh"
#include "const.hh"

JoustField::JoustField()
	: Building(JOUST_FIELD,
	           BuildingType::fixed,
	           ResourceMap(0),
	           ResourceMap(0))
{
}

void JoustField::on_activate(void)
{
	if (worker_->resources()[Resource::denier] < 1 ||
	    worker_->resources()[Resource::cloth] < 1)
	{
		std::cout << "Not enough resources. Try again." << std::endl;
		return;
	}
	if (ask_proceed_())
	{
		worker_->resources() -= ResourceMap(Resource::denier + Resource::cloth);
		worker_->resources() += Resource::favor;
	}
}
