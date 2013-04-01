/**
 * @file   stables.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Thu Jan 15 14:17:13 2009
 *
 * @brief Implementation of the Stables.
 *
 */

#include "stables.hh"

#include <algorithm>

#include "player.hh"
#include "exceptions.hh"
#include "game-engine.hh"

#include "../visitor.hh"
#include "../exceptions.hh"

using namespace controller;

Stables::Stables(GameEngine * ge)
	: Building(STABLES,
	           BuildingType::fixed,
	           ResourceMap(0),
	           ResourceMap(0)),
	OmniscientBuilding(ge)
{
}

void Stables::add(Player & current)
{
	if (has(&current))
	{
		signals_.already_occupied(this);
		throw new AlreadyPlacedEx();
	}

	if (players_.size() == 3)
	{
		signals_.already_occupied(this);
		throw new AlreadyPlacedEx();
	}

	players_.push_back(&current);
	current.decrementWorkers();

	// If no worker, Building::activate will not call onActivate.
	worker_ = &current;
	signals_.worker_placed(&current, this);
}

void Stables::removeWorker()
{
	foreach (Player * player, players_)
	{
		player->incrementWorkers();
	}
	players_.clear();
}

void Stables::onActivate_()
{
	std::vector<Player *>& order = game_engine_->order();
	std::vector<Player *>::iterator it;
	Player * p;

	for (unsigned i = 0; i < players_.size(); ++i)
	{
		p = players_[i];
		it = std::find(order.begin(), order.end(), p);

		assert(p);
		assert(it != order.end());

		std::swap(*it, order[i]);
	}

	// See above.
	worker_ = 0;
}

bool Stables::has(const Player * p) const
{
	return std::find(players_.begin(), players_.end(), p) != players_.end();
}

void Stables::accept(ConstVisitor & v) const
{
	v.operator()(*this);
}

void Stables::accept(Visitor & v)
{
	v.operator()(*this);
}

const std::vector<Player *> Stables::players() const
{
	return players_;
}
