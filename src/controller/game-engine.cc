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
#include <boost/assign/std/vector.hpp>
#include "game-engine.hh"
#include "resource.hh"
#include "all-buildings.hh"
#include "exceptions.hh"
#include "inn.hh"
#include "debug-logger.hh"
#include "board-element.hh"

using namespace controller;
using namespace boost::assign;

GameEngine::GameEngine(unsigned nb_humans, unsigned nb_ais, unsigned nb_turns_max, bool random)
	: nb_humans_(nb_humans)
	, nb_ais_(nb_ais)
	, nb_turns_(0)
	, nb_turns_max_(nb_turns_max)
	, max_workers_(1)
	, random_(random)
	, board_(this)
{
	buildings_+= BuildingSmartPtr(new Statue()), BuildingSmartPtr(new Theater()), BuildingSmartPtr(new College()), BuildingSmartPtr(new Monument()),
		BuildingSmartPtr(new Granary()), BuildingSmartPtr(new Weaver()), BuildingSmartPtr(new Cathedral()), BuildingSmartPtr(new WQuarry()),
		BuildingSmartPtr(new Workshop()), BuildingSmartPtr(new WFFarm()), BuildingSmartPtr(new WCFarm()), BuildingSmartPtr(new SFarm()),
		BuildingSmartPtr(new Park()), BuildingSmartPtr(new WSawmill()), BuildingSmartPtr(new Library()), BuildingSmartPtr(new Hotel()),
		BuildingSmartPtr(new Church()), BuildingSmartPtr(new WPeddler()), BuildingSmartPtr(new WMarketplace()), BuildingSmartPtr(new Jeweller()),
		BuildingSmartPtr(new Tailor()), BuildingSmartPtr(new Alchemist()), BuildingSmartPtr(new Bank()), BuildingSmartPtr(new Lawyer(this)),
		BuildingSmartPtr(new Architect(this)), BuildingSmartPtr(new Mason(this));
}

GameEngine::~GameEngine()
{
	foreach(Player * p, players_)
	{
		delete p;
	}
}

void GameEngine::operator()()
{
	DebugLogger::log("Game Engine launched.");
	waitForPlayers_();
	play_();
	signals_.game_over();
}

void GameEngine::waitForPlayers_()
{
	boost::unique_lock<boost::mutex> lock(mutex_);
	while (players_.size() < nb_humans_ + nb_ais_)
	{
		DebugLogger::log("Wait for players...");
		wait_for_players_.wait(lock);
		DebugLogger::log("Everyone's here");
	}
}

void GameEngine::shufflePlayers_()
{
	// Shuffle players order.
	foreach(Player * p, players_)
	{
		order_.push_back(p);
	}
	if (random_)
	{
		std::random_shuffle(order_.begin(), order_.end());
	}
}

void GameEngine::initialResource_()
{
	// Give each player his initial denier amount.
	for (unsigned i = 1; i < order_.size(); i++)
	{
		players_[i]->addResources(Resource::denier * ((i < 3) ? 1 : 2));
	}
}

void GameEngine::play_()
{
	signals_.game_engine_ready();
	shufflePlayers_();
	initialResource_();
	try
	{
		while (nb_turns_ < nb_turns_max_)
		{
			++nb_turns_;
			startOfTurn_();
			collectIncome_();
			placeWorkers_();
			activateSpecialBuildings_();
			activateBridge_();
			activateBuildings_();
			activateCastle_();
			endOfTurn_();
		}
	}
	catch (Exception * ex)
	{
		std::cerr << ex->msg() << std::endl;
	}

	DebugLogger::log("End of the game.");
}

void GameEngine::activateSpecialBuildings_()
{
	signals_.activation_special_buildings_begin();
	for (unsigned i = 0; i < Road::FIRST_NEUTRAL_CASE; ++i)
	{
		board_.activateBuildingAtCase(i);
	}
	signals_.activation_special_buildings_end();
}

void GameEngine::activateBuildings_()
{
	signals_.activationBuildings_begin();
	for (unsigned i = Road::FIRST_NEUTRAL_CASE; i <= board_.provost(); ++i)
	{
		board_.activateBuildingAtCase(i);
	}
	signals_.activationBuildings_end();
}

void GameEngine::activateBridge_()
{
	board_.bridge().activate();
}

void GameEngine::activateCastle_()
{
	board_.castle().activate();
}

void GameEngine::collectIncome_()
{
	signals_.income_collecting_begin();
	assert(players_.size() > 0);
	foreach(Player * p, order_)
	{
		ResourceMap income = Resource::denier * (2 + p->residences());
		signals_.income_collecting_for_player(p, &income);
		p->addResources(income);
	}
	signals_.income_collecting_end();
}

void GameEngine::endOfTurn_()
{
	unsigned int previous_bailiff = board_.bailiff();
	board_.shiftBailiff();
	Castle & castle = board_.castle();

	if ((previous_bailiff < Road::END_DUNGEON && board_.bailiff() >= Road::END_DUNGEON) ||
	    (previous_bailiff < Road::END_WALLS && board_.bailiff() >= Road::END_WALLS) ||
	    (previous_bailiff < Road::END_TOWERS && board_.bailiff() >= Road::END_TOWERS) ||
	    castle.isActivePartComplete())
	{
		castle.score(players_);
	}
	if (players_.size() == 2)
	{
		std::swap(order_.front(), order_.back());
	}
}

void GameEngine::placeWorkers_()
{
	signals_.worker_placement_begin();
	while (board_.bridge().players().size() != players_.size())
	{
		foreach(Player * p, order_)
		{
			assert(p);
			if (canPlayerPlay_(*p))
			{
				playerMove_(p);
			}
		}
	}
	signals_.worker_placement_end();
}

void GameEngine::playerMove_(Player * p)
{
	bool has_played = false;
	unsigned int selected_case = 0;
	unsigned int worker_cost = 1;

	signals_.worker_placement_for_player(p);
	while (!has_played)
	{
		selected_case = p->askBoardElement();
		BoardElement & board_element = board_.getBoardElement(selected_case);

		Bridge & bridge = board_.bridge();
		if (&board_element == &bridge)
		{
			bridge.add(*p);
			has_played = true;
			continue;
		}

		worker_cost = getWorkerCost_(p);

		Castle & castle = board_.castle();
		if (&board_element == &castle && p->resources()[Resource::denier] >= worker_cost)
		{
			try
			{
				castle.add(*p);
				p->substractResources(Resource::denier * worker_cost);
				has_played = true;
			}
			catch (AlreadyPlacedEx *)
			{
				DebugLogger::log("Already occupied.");
			}
			continue;
		}

		Building * selected_building = dynamic_cast<Building *>(&board_element);
		if (selected_building->owner() == p)
		{
			worker_cost = 1;
		}

		if (p->resources()[Resource::denier] >= worker_cost)
		{
			try
			{
				selected_building->add(*p);
				p->substractResources(Resource::denier * worker_cost);
				has_played = true;
			}
			catch (...)
			{
			}
		}
		else
		{
			signals_.not_enough_deniers(p);
		}
	}
	signals_.board_updated();
}

void GameEngine::startOfTurn_()
{
	signals_.turn_start(nb_turns_, nb_turns_max_);

	board_.road().clearWorkers();
	board_.bridge().clear();
	board_.castle().clear();
	signals_.board_updated();
}

bool GameEngine::canPlayerPlay_(Player & p)
{
	if (board_.isPlayerOnBridge(p))
	{
		return false;
	}
	if (p.resources()[Resource::denier] == 0)
	{
		signals_.not_enough_deniers(&p);
		board_.bridge().add(p);
		return false;
	}
	if (p.workers() == 0)
	{
		signals_.no_worker_left(&p);
		board_.bridge().add(p);
		return false;
	}
	return true;
}

unsigned GameEngine::getWorkerCost_(const Player * p) const
{
	const Inn * inn = dynamic_cast<const Inn *>(board_.road().get()[5].get());
	assert(inn);
	return (inn->host() == p) ? 1 : board_.bridge().players().size() + 1;
}

void GameEngine::build(BuildingSmartPtr & building, Player * p)
{
	BuildingSmartPtr game_b = *(std::find(buildings_.begin(), buildings_.end(), building));

	assert(p);
	assert(building);
	game_b->build(*p);
	board_.road().build(game_b);
	buildings_.erase(std::find(buildings_.begin(), buildings_.end(), building));
}

Player * GameEngine::newPlayer()
{
	Player * p = new Player(max_workers_);
	players_.push_back(p);
	return p;
}

void GameEngine::playerReady()
{
	boost::lock_guard<boost::mutex> lock(mutex_);
	wait_for_players_.notify_one();
}

BuildingSmartPtr GameEngine::getBuildingAtCase(unsigned int case_number) const
{
	std::vector<BuildingSmartPtr> buildings = board_.road().get();
	assert(case_number < buildings.size());
	return buildings[case_number];
}

Castle & GameEngine::getCastle()
{
	return board_.castle();
}

Bridge & GameEngine::getBridge()
{
	return board_.bridge();
}

const Castle & GameEngine::getCastle() const
{
	return board_.castle();
}

const Bridge & GameEngine::getBridge() const
{
	return board_.bridge();
}

std::ostream & operator<<(std::ostream & o, const controller::GameEngine & g)
{
	foreach(const Player * p, g.order())
	{
		o << *p << std::endl;
	}
	o << g.board();
	return o;
}

std::vector<const BoardElement *> GameEngine::getEveryBoardElements() const
{
	std::vector<const BoardElement *> board_elements;
	board_elements.push_back(&getBridge());
	board_elements.push_back(&getCastle());
	foreach (const BuildingSmartPtr building, board().road().get())
	{
		if (building != NULL)
		{
			board_elements.push_back(&(*building));
		}
	}
	foreach (const BuildingSmartPtr building, buildings_)
	{
		if (building != NULL)
		{
			board_elements.push_back(&(*building));
		}
	}
	return board_elements;
}

void GameEngine::setMaxWorkers(unsigned int nb)
{
	max_workers_ = nb;
	foreach (Player * player, players_)
	{
		player->setWorkers(nb);
	}
}
