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
#include "player-view.hh"

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
	Building::on_activate();
	int s = ask_provost_shift_sig_();

	while (!game_->board().valid_provost_move(s))
	{
		s = ask_provost_shift_sig_();
	}
	game_->board().provost() += s;
}
