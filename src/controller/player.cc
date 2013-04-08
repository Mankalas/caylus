/**
 * @file   player.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Jun 06 19:47:49 2011
 *
 * @brief  Implementation of the player class.
 */

#include "player.hh"
#include "debug-logger.hh"
#include "board-element.hh"

using namespace controller;

Player::Player(unsigned int max_worker):
	favor_building_(0),
	favor_resource_(0),
	favor_denier_(0),
	favor_prestige_(0),
	workers_(max_worker),
	name_("Chiche"),
	prestige_(0),
	resources_(Resource::denier * 5 + Resource::food * 2 + Resource::wood),
	residences_(0)
{
}

Player::Player(const std::string & name, unsigned int max_worker):
	favor_building_(0),
	favor_resource_(0),
	favor_denier_(0),
	favor_prestige_(0),
	workers_(max_worker),
	name_(name),
	prestige_(0),
	resources_(10 * (Resource::denier * 5 + Resource::food * 2 + Resource::wood +
	                 Resource::cloth + Resource::stone + Resource::gold)),
	residences_(0)
{
}

Player::Player(const Player & player):
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

unsigned int Player::askBoardElement() const
{
	unsigned int choice = signals_.ask_board_element();
	return choice;
}

void Player::addResources(const ResourceMap & r)
{
	resources_ += r;
	signals_.gain_resource(this, r);
}

void Player::substractResources(const ResourceMap & r)
{
	resources_ -= r;
	signals_.lose_resource(this, r);
}

bool Player::askInnRemoval() const
{
	return signals_.ask_inn_removal();
}

unsigned int Player::askTrade(const std::vector<std::pair<ResourceMap, ResourceMap> > & trade) const
{
	return signals_.ask_trade(trade);
}
