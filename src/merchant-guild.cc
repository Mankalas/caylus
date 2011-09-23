/**
 * @file   merchant_guild.cc
 * @author  <mankalas@localhost,>
 * @date   Thu Jan 15 14:20:15 2009
 *
 * @brief Implementation of the MerchantGuild.
 *
 */

#include "merchant-guild.hh"

MerchantGuild::MerchantGuild(GameEngine* ge)
  : Building("Merchant guild",
             BuildingType::fixed,
             ResourceMap(0),
             ResourceMap(0)),
    OmniscientBuilding(ge)
{
}

void MerchantGuild::on_activate()
{
  std::cout << *game_ << std::endl;
  int s = this->worker()->askProvostShift();
  while (s < -3 || s > 3 || s + game_->provost() < 6 ||
         s + game_->provost() > 33)
    s = this->worker()->askProvostShift();
  game_->provost() += s;
}
