/**
 * @file   merchant_guild.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Thu Jan 15 14:20:15 2009
 *
 * @brief Implementation of the MerchantGuild.
 *
 */

#include "merchant-guild.hh"
#include "game-engine.hh"
#include "const.hh"

MerchantGuild::MerchantGuild(GameEngine *ge)
	: Building(MERCHANT_GUILD,
	           BuildingType::fixed,
	           ResourceMap(0),
	           ResourceMap(0)),
	OmniscientBuilding(ge)
{
}

void MerchantGuild::on_activate()
{
	assert(worker_);
	int s = worker_->askProvostShift();
	while (s < -3 || s > 3 || s + game_->board().provost() < 6 ||
	       s + game_->board().provost() > 33)
	{
		s = worker_->askProvostShift();
	}
	game_->board().provost() += s;
}
