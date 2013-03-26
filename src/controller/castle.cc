/**
 * @file   castle.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Thu Feb 12 12:58:11 2009
 *
 * @brief  Implementation of the castle class.
 */

#include <cassert>
#include <algorithm>
#include "player.hh"
#include "castle.hh"
#include "resource-map.hh"
#include "../exceptions.hh"
#include "../const.hh"

using namespace controller;

const unsigned int Castle::CASE_NUMBER = 42;

CastlePart::CastlePart(unsigned c, unsigned p,
                       std::vector<std::pair<unsigned, int> > s):
	capacity_(c),
	prestige_(p),
	score_favor_(s),
	houses_(std::vector<Player *>())
{}

Dungeon::Dungeon():
	CastlePart(6, 5, boost::assign::list_of(std::make_pair(0, -2))
	           (std::make_pair(1, 0))(std::make_pair(2, 1)))
{}

Walls::Walls():
	CastlePart(10, 4, boost::assign::list_of(std::make_pair(0, -3))
	           (std::make_pair(1, 0))(std::make_pair(2, 1))
	           (std::make_pair(3, 2))(std::make_pair(5, 3)))
{}

Towers::Towers():
	CastlePart(14, 3, boost::assign::list_of(std::make_pair(0, -4))
	           (std::make_pair(1, 0))(std::make_pair(2, 1))
	           (std::make_pair(4, 2))(std::make_pair(6, 3)))
{}

void CastlePart::score(std::vector<Player *>& players)
{
	unsigned count = 0;
	std::pair<unsigned, int> score_favor;

	foreach(Player * gp, players)
	{
		// Count the player's houses.
		foreach(Player * cp, houses_)
		if (cp == gp)
		{
			++count;
		}

		foreach(score_favor, score_favor_)
		{
			if (score_favor.first <= count)
			{
				continue;
			}
			if (score_favor.first > count)
			{
				break;
			}
		}

		if (count == 0)
		{
			gp->substractResources(score_favor.second * Resource::prestige);
		}
		else
		{
			gp->addResources(score_favor.second * Resource::favor);
		}
	}
}

Castle::Castle() :
	BoardElement(CASTLE)
{
	players_ = std::vector<Player *>(5);
	parts_ = std::vector<CastlePart *>(3);
	parts_[0] = new Dungeon();
	parts_[1] = new Walls();
	parts_[2] = new Towers();
	part_index_ = 0;
	active_part_ = parts_[part_index_];
	nb_build_ = 0;
	favored_ = NULL;
}

Castle::~Castle()
{
	foreach(CastlePart * p, parts_)
	delete p;
}

void Castle::onActivate_()
{
	bool can_pay = false;
	unsigned current_build = 0;

	foreach(Player * p, players_)
	{
		current_build = 0;
		do
		{
			if (!checkResources_(p))
			{
				//ConsoleUI::inst()->printMessage("You don't have 3 different resources.");
				can_pay = false;
			}
			else
			{
				can_pay = true;
				ResourceMap * choice = ask_payment_();
				if (NULL == choice)
				{
					can_pay = false;
				}
				else
				{
					build_(p, choice);
					++current_build;
				}
			}
		}
		while (can_pay);
		if (current_build == 0)
		{
			p->substractResources(2 * Resource::prestige);
		}
		if (current_build > nb_build_)
		{
			favored_ = p;
			nb_build_ = current_build;
		}
	}
	nb_build_ = 0;
	// Can be NULL if no player built anything.
	if (favored_ != NULL)
	{
		favored_->addResources(Resource::favor);
	}
}

bool Castle::has(const Player * p) const
{
	return std::find(players_.begin(), players_.end(), p) != players_.end();
}

void Castle::add(Player & p)
{
	if (has(&p))
	{
		signals_.already_occupied(this);
		throw new OccupiedBuildingEx();
	}
	players_.push_back(&p);
	signals_.worker_placed(&p, this);
}

void Castle::clear()
{
	players_.clear();
}

void Castle::score(std::vector<Player *>& players)
{
	active_part_->score(players);
	// Don't increment when Towers are scored.
	if (part_index_ != 2)
	{
		active_part_ = parts_[++part_index_];
	}
}

bool Castle::isActivePartComplete() const
{
	return active_part_->houses().size() == active_part_->capacity();
}

void Castle::build_(Player * p, ResourceMap * resources)
{
	CastlePart * active_part = active_part_;

	if (isActivePartComplete())
	{
		active_part = parts_[part_index_ + 1];
	}
	p->substractResources(*resources);
	p->addResources(active_part->prestige() * Resource::prestige);
	active_part->houses().push_back(p);
}

/*std::vector<ResourceMap*>
Castle::_createResourcesVector(const Player* p) const
{
  std::vector<Resource> white_cube = boost::assign::list_of
    (Resource::wood)(Resource::cloth)(Resource::stone)(Resource::gold);
  std::vector<Resource> player_resource;
  std::vector<std::pair<Resource, Resource> > pairs;

  foreach (Resource& r, white_cube)
    if (p->resources()[r] > 0)
      player_resource.push_back(r);
  for (unsigned i = 0; i < player_resource.size(); i++)
    for (unsigned j = i + 1; j < player_resource.size(); j++)
      pairs.push_back(std::make_pair(player_resource[i], player_resource[j]));
  return pairs;
  }*/

bool Castle::checkResources_(const Player * p) const
{
	unsigned count = 0;

	if (p->resources()[Resource::food] == 0)
	{
		return false;
	}
	if (p->resources()[Resource::wood] > 0)
	{
		++count;
	}
	if (p->resources()[Resource::cloth] > 0)
	{
		++count;
	}
	if (p->resources()[Resource::stone] > 0)
	{
		++count;
	}
	if (p->resources()[Resource::gold] > 0)
	{
		++count;
	}
	return count >= 2;
}

bool Castle::canBeActivated_() const
{
	return !players_.empty();
}
