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

void GameEngine::operator() ()
{
	boost::mutex mutex;
	boost::unique_lock<boost::mutex> lock(mutex);
	waiting_players_.notify_one();
	game_start_.wait(lock);
	_run();
}

void GameEngine::_run()
{
	while (true)
	{
		collectIncome();
		placeWorkers();
		activateSpecialBuildings();
		activateBridge();
		activateBuildings();
		activateCastle();
		endOfTurn();
	}
}

void GameEngine::initialize()
{
	assert(nb_humans_ <= 5);
	for (unsigned i = 0; i < nb_humans_; ++i)
	{
		Player *p = new Player();
		Logger::log("Adding new human.");
		players_.push_back(p);

	}
	if (nb_humans_ > 1)
	{
		assert(nb_ais_ <= 5 - nb_humans_);
	}
	else
	{
		assert(nb_ais_ > 0);
	}
	while (players_.size() < nb_ais_ + nb_humans_)
	{
		Player *p = new Player();
		p->setView(new view::AI(this));
		Logger::log("Adding new AI.");
		players_.push_back(p);
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
	board_updated_();
}

GameEngine::GameEngine()
	: road_(this)
{
	initialize();
}

GameEngine::GameEngine(unsigned nb_humans, unsigned nb_ais)
	: road_(this), nb_humans_(nb_humans), nb_ais_(nb_ais)
{
	initialize();
}

GameEngine::~GameEngine()
{
	foreach(Player * p, players_)
	{
		delete p;
	}
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

	foreach (Player * p, bridge_)
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
	Logger::log("Collecting income... ");
	foreach (Player *p, players_)
	{
		p->resources() += Resource::denier * (2 + p->residences());
	}
	Logger::log("Done.");
}

void GameEngine::endOfTurn()
{
	Logger::log("End of turn.");
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
	Logger::log("Done.");
}

void GameEngine::placeWorkers()
{
	_startOfTurn();
	while (bridge_.size() != players_.size())
	{
		foreach (Player *p, order_)
		{
			assert(p != NULL);
			if (!_canPlayerPlay(p))
			{
				continue;
			}
			_playerMove(p);
		}
	}
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
	int player_input = 0;
	unsigned worker_cost = 0;

	while (!has_played)
	{
		player_input = p->askWorkerPlacement();

		//  Players chose the bridge.
		if (player_input == 34)
		{
			_addToBridge(p);
			has_played = true;
			return;
		}

		worker_cost = _getWorkerCost(p);
		Logger::log("wc: " << worker_cost);
		Logger::log("input : " << player_input);

		if (-1 == player_input)
		{
			if (p->resources()[Resource::denier] >= worker_cost)
			{
				if (has_played == castle_.add(p))
				{
					p->resources() -= Resource::denier * worker_cost;
					p->workers() -= 1;
					continue;
				}
			}
		}

		assert(player_input <= (int)road_.get().size());
		Building *b = road_.get()[player_input].get();

		if (p->resources()[Resource::denier] >= (b->owner() == p ? 1 : worker_cost))
		{
			try
			{
				b->worker_set(*p);
				/*Logger::log("BEFORE: " << p->resources() << std::endl
				  << "     -= " << (Resource::denier * (b->owner() == p ? 1 : worker_cost)) << std::endl;*/
				p->resources() -= Resource::denier * (b->owner() == p ? 1 : worker_cost);
				//Logger::log("AFTER:  " << p->resources() << std::endl;
				has_played = true;
			}
			catch (OccupiedBuildingEx *)
			{
				Logger::log("***** " << b->name() << " already occupied.");
				return;
			}
			catch (UnactivableBuildingEx *)
			{
				Logger::log("***** " << b->name() << " does not accept workers.");
				return;
			}
		}
		else
		{
			Logger::log("***** Not enough denier to play ");
			return;
		}
	}
}

void GameEngine::_startOfTurn()
{
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
}

void GameEngine::_addToBridge(Player *p)
{
	if (bridge_.size() == 0)
	{
		p->resources() += Resource::denier;
	}
	bridge_.push_back(p);
}

bool GameEngine::_canPlayerPlay(Player *p)
{
	// If the player is already on the bridge, he cannot play.
	if (std::find(bridge_.begin(), bridge_.end(), p) != bridge_.end())
	{
		return false;
	}
	if (p->resources()[Resource::denier] == 0 || // The player doesn't have any denier
	    p->workers() == 0) 	// No worker left for the player
	{
		// Add him to the bridge.
		_addToBridge(p);
		return false;
	}
	return true;
}

unsigned GameEngine::_getWorkerCost(const Player *p) const
{
	const Inn *inn = (const Inn *)(road_.get()[5].get());
	if (inn == NULL)
	{
		std::cerr << "The Inn isn't in the right case... returning a cost of 1 by default" << std::endl;
		return 1;
	}
	return (inn->host() == p) ? 1 : bridge_.size() + 1;
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
	Logger::log("Subcribing view.");
	foreach (Player * p, players_)
	{
		if (p->view() == NULL)
		{
			p->setView(human);
			this->board_updated_.connect(human->getUpdateBoardSlot());
		}
	}
	game_start_.notify_one();
}
