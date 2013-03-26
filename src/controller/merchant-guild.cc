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

#include "../const.hh"
#include "../debug-logger.hh"

MerchantGuild::MerchantGuild(GameEngine * ge)
	: Building(MERCHANT_GUILD,
	           BuildingType::fixed,
	           ResourceMap(0),
	           ResourceMap(0)),
	OmniscientBuilding(ge)
{
}

void MerchantGuild::onActivate_()
{
	Board & board = game_engine_->board();
	int s = 0;

	do
	{
		s = worker_->askProvostShift();
	}
	while (!board.isProvostShiftValid(s));
	board.shiftProvost(s);
}
