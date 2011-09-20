/*!
  \file   player.cc
  \brief  Implementation of Player.

  \author Mankalas
  \date   2009-01-06
*/

#include "player.hh"

using namespace controller;

Player::Player():
  favor_building_(0),
  favor_resource_(0),
  favor_denier_(0),
  favor_prestige_(0),
  workers_(NB_WORKERS),
  name_("Chiche"),
  prestige_(0),
  resources_(Resource::denier * 5 + Resource::food * 2 + Resource::wood),
  residences_(0)
{
}

Player::Player(const std::string& name):
  favor_building_(0),
  favor_resource_(0),
  favor_denier_(0),
  favor_prestige_(0),
  workers_(NB_WORKERS),
  name_(name),
  prestige_(0),
  resources_(10 * (Resource::denier * 5 + Resource::food * 2 + Resource::wood +
                   Resource::cloth + Resource::stone + Resource::gold)),
  residences_(0)
{
}

Player::Player(const Player& player):
  favor_building_(player.favor_building_),
  favor_resource_(player.favor_resource_),
  favor_denier_(player.favor_denier_),
  favor_prestige_(player.favor_prestige_),
  workers_(player.workers_),
  name_(player.name_),
  prestige_(player.prestige_),
  resources_(player.resources_),
  residences_(player.residences_)
{
}
