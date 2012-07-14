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

Player::Player(const std::string &name):
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

Player::Player(const Player &player):
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

BoardElement*
Player::askWorkerPlacement(const std::vector<BoardElement*> & buildings) const
{
	assert(!signals_.ask_worker_placement.empty());

	return signals_.ask_worker_placement(buildings);
}

void Player::addResources(const ResourceMap &r)
{
	resources_ += r;
	//resource_move_(&r);
}

void Player::substractResources(const ResourceMap &r)
{
	resources_ -= r;
	//resource_move_(r * -1);
}

