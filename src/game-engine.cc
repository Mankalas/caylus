/**
 * @file   game-engine.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Thu Jan 22 13:57:35 2009
 *
 * @brief  Implementation of the game-engine class.
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <boost/bind.hpp>
#include "game-engine.hh"
#include "resource.hh"
#include "all-buildings.hh"
#include "exceptions.hh"
#include "inn.hh"
#include "human.hh"
#include "ai.hh"
#include "logger.hh"

using namespace controller;

GameEngine::GameEngine(unsigned nb_humans, unsigned nb_ais)
	: road_(this), nb_humans_(nb_humans), nb_ais_(nb_ais), nb_turns_(0)
{
	Logger::instance()->gameInfo(this);
	mutex_.lock();
	assert(nb_humans_ <= 5);
	for (unsigned i = 0; i < nb_humans_; ++i)
	{
		Player *p = new Player();
		Logger::instance()->log("Adding new human player.");
		players_.push_back(p);
	}
	if (nb_humans_ > 1)
	{
		assert(nb_ais_ <= 5 - nb_humans_);
	}
	else
	{
		//assert(nb_ais_ > 0);
	}
	while (players_.size() < nb_ais_ + nb_humans_)
	{
		Player *p = new Player();
		Logger::instance()->log("Adding new AI player.");
		p->setName("HAL");
		players_.push_back(p);
	}

	provost_ = PROVOST_INIT_CASE;
	bailiff_ = BAILIFF_INIT_CASE;

	buildings_.push_back(BuildingSmartPtr(new Statue()));
	buildings_.push_back(BuildingSmartPtr(new Theater()));
	buildings_.push_back(BuildingSmartPtr(new College()));
	buildings_.push_back(BuildingSmartPtr(new Monument()));
	buildings_.push_back(BuildingSmartPtr(new Granary()));
	buildings_.push_back(BuildingSmartPtr(new Weaver()));
	buildings_.push_back(BuildingSmartPtr(new Cathedral()));
	buildings_.push_back(BuildingSmartPtr(new WQuarry()));
	buildings_.push_back(BuildingSmartPtr(new Workshop()));
	buildings_.push_back(BuildingSmartPtr(new WFFarm()));
	buildings_.push_back(BuildingSmartPtr(new WCFarm()));
	buildings_.push_back(BuildingSmartPtr(new SFarm()));
	buildings_.push_back(BuildingSmartPtr(new Park()));
	buildings_.push_back(BuildingSmartPtr(new WSawmill()));
	buildings_.push_back(BuildingSmartPtr(new Library()));
	buildings_.push_back(BuildingSmartPtr(new Hotel()));
	buildings_.push_back(BuildingSmartPtr(new Church()));
	buildings_.push_back(BuildingSmartPtr(new WPeddler()));
	buildings_.push_back(BuildingSmartPtr(new WMarketplace()));
	buildings_.push_back(BuildingSmartPtr(new Jeweller()));
	buildings_.push_back(BuildingSmartPtr(new Tailor()));
	buildings_.push_back(BuildingSmartPtr(new Alchemist()));
	buildings_.push_back(BuildingSmartPtr(new Bank()));
	buildings_.push_back(BuildingSmartPtr(new Lawyer(this)));
	buildings_.push_back(BuildingSmartPtr(new Architect(this)));
	buildings_.push_back(BuildingSmartPtr(new Mason(this)));
}

GameEngine::~GameEngine()
{
	mutex_.unlock();
	foreach(Player * p, players_)
	{
		delete p;
	}
}

void GameEngine::operator() ()
{
	// Waiting for the view subscription to release the mutex.
	mutex_.lock();
	_run();
}

void GameEngine::_run()
{
	while (nb_turns_ < nb_turns_max_)
	{
		++nb_turns_;
		_startOfTurn();
		collectIncome();
		placeWorkers();
		activateSpecialBuildings();
		activateBridge();
		activateBuildings();
		activateCastle();
		endOfTurn();
	}
	Logger::instance()->log("End of the game.");
}

void GameEngine::activateBuildings()
{
	for (unsigned i = 6; i <= provost_ + 1; ++i)
	{
		if (road_.get()[i] != NULL)
		{
			road_.get()[i]->activate();
		}
	}
}

void GameEngine::activateBridge()
{
	int deniers = 0;
	int shift = 0;

	foreach (Player * p, bridge_.players())
	{
		assert(p);
		deniers = p->resources()[Resource::denier];
		if (deniers == 0)
		{
			continue;
		}

		shift = p->askProvostShift();
		/* If the provost is not moved before the bridge, or over the end
		   of the board, or if the player has enough money, then move. */
		while (shift + provost_ < 6 || shift + provost_ > 33 ||
		       std::abs(shift) > deniers)
		{
			shift = p->askProvostShift();
		}
		provost_ += shift;
		p->resources() -= Resource::denier * std::abs(shift);
	}
}

void GameEngine::activateSpecialBuildings()
{
	for (unsigned i = 0; i < 6; ++i)
	{
		road_.get()[i]->activate();
	}
}

void GameEngine::activateCastle()
{
	castle_.activate();
}

void GameEngine::collectIncome()
{
	Logger::instance()->startSection(2, "Income collection");
	foreach (Player *p, players_)
	{
		ResourceMap income = Resource::denier * (2 + p->residences());
		Logger::instance()->playerIncome(p, income);
		p->resources() += income;
	}
	Logger::instance()->endSection();
}

void GameEngine::endOfTurn()
{
	Logger::instance()->endSection();
	_moveBailiff();
	if (bailiff_ == 17 || bailiff_ == 18 ||
	    bailiff_ == 30 || bailiff_ == 31 ||
	    castle_.isActivePartComplete())
	{
		castle_.score(players_);
	}
	if (players_.size() == 2)
	{
		std::swap(order_.front(), order_.back());
	}
}

void GameEngine::placeWorkers()
{
	Logger::instance()->startSection(2, "Worker placement");
	while (bridge_.players().size() != players_.size())
	{
		foreach (Player *p, order_)
		{
			assert(p);
			if (!_canPlayerPlay(p))
			{
				continue;
			}
			_playerMove(p);
		}
	}
	Logger::instance()->endSection();
}

void GameEngine::_moveBailiff()
{
	bailiff_ += (provost_ > bailiff_ ? 2 : 1);
	provost_ = bailiff_;
}

bool GameEngine::addToCastle(Player *p)
{
	assert(p);
	return castle_.add(p);
}

void GameEngine::_playerMove(Player *p)
{
	bool has_played = false;
	const BoardElement * player_choice;
	unsigned worker_cost = 0;

	while (!has_played)
	{
		const std::vector<BoardElement*> choices = getAvailableBoardElements(p);

		Logger::instance()->placementChoices(p, choices);
		player_choice = p->askWorkerPlacement(choices);
		Logger::instance()->playerBoardChoice(p, player_choice);

		if (player_choice->isBridge())
		{
			bridge_.add(p);
			has_played = true;
			continue;
		}

		worker_cost = _getWorkerCost(p);

		if (player_choice->isCastle() &&
				p->resources()[Resource::denier] >= worker_cost)
			{
				if (!castle_.add(p))
					{
						Logger::instance()->playerLog(p, " has already a worker at the castle.");
						continue;
					}
				else
					{
						p->resources() -= Resource::denier * worker_cost;
						p->workers() -= 1;
						continue;
					}
			}

		assert(player_choice->isBuilding());
		Building *b = (Building*)player_choice;

		if (p->resources()[Resource::denier] >= (b->owner() == p ? 1 : worker_cost))
		{
			try
			{
				b->worker_set(*p);
				p->resources() -= Resource::denier * (b->owner() == p ? 1 : worker_cost);
				has_played = true;
			}
			catch (OccupiedBuildingEx *)
			{
				Logger::instance()->log("Already occupied.");
				return;
			}
			catch (UnactivableBuildingEx *)
			{
				Logger::instance()->log("Does not accept workers.");
				return;
			}
		}
		else
		{
			Logger::instance()->log("Not enough denier to play ");
			return;
		}
	}
}

void GameEngine::_startOfTurn()
{
	Logger::instance()->startOfTurn(this);
	road_.clearWorkers();
	bridge_.clear();
	castle_.clear();
	foreach (Player * p, players_)
	{
		p->workers() = NB_WORKERS;
	}
	Inn *inn = (Inn *)(road_.get()[INN_CASE].get());
	if (inn->host())
	{
		inn->host()->workers() -= 1;
	}
	board_updated_();
}

bool GameEngine::_canPlayerPlay(Player *p)
{
	if (bridge_.has(p))
	{
		Logger::instance()->playerLog(p, " is on the bridge and cannot place worker anymore.");
		return false;
	}
	if (p->resources()[Resource::denier] == 0)
	{
		Logger::instance()->playerLog(p, " does not havbe any denier left. Automatically placed on the Bridge.");
		bridge_.add(p);
		return false;
	}
	if (p->workers() == 0)
	{
		Logger::instance()->playerLog(p, " does not havbe any worker left. Automatically placed on the Bridge.");
		bridge_.add(p);
		return false;
	}
	return true;
}

unsigned GameEngine::_getWorkerCost(const Player *p) const
{
	const Inn *inn = (const Inn *)(road_.get()[5].get());
	assert(inn);
	return (inn->host() == p) ? 1 : bridge_.players().size() + 1;
}

void GameEngine::build(BuildingSmartPtr &building, Player *p)
{
	BuildingSmartPtr game_b = *(std::find(buildings_.begin(), buildings_.end(), building));

	assert(p);
	assert(building);
	game_b->build(p);
	road_.build(game_b);
	buildings_.erase(std::find(buildings_.begin(), buildings_.end(), building));
}

void GameEngine::subscribeView(Human *human)
{
	Player * p = NULL;

	for (unsigned i = 0; i < nb_humans_; ++i)
	{
		p = players_[i];
		if (p->view() == NULL)
		{
			p->setView(human);
			this->board_updated_.connect(human->getUpdateBoardSlot());
		}
	}
	for (unsigned i = 0; i < nb_ais_; ++i)
	{
		Logger::instance()->log("Subcribing AI view.");
		p = players_[nb_humans_ + i];
		p->setView(new view::AI(this));
	}
	 	// Shuffle players order.
	foreach (Player * p, players_)
	{
		order_.push_back(p);
	}
	std::random_shuffle(order_.begin(), order_.end());
	// Give each player his initial denier amount.
	for (unsigned i = 1; i < players_.size(); i++)
	{
		players_[i]->resources() += Resource::denier * ((i < 3) ? 1 : 2);
	}

	mutex_.unlock();
}

const std::vector<BoardElement*>
GameEngine::getAvailableBoardElements(const Player * worker) const
{
	std::vector<BoardElement*> available_buildings(road_.getAvailableBuildings(worker));

	available_buildings.push_back((BoardElement*)&castle_);
	available_buildings.push_back((BoardElement*)&bridge_);
	return available_buildings;
}

