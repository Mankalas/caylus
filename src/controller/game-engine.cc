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
#include "debug-logger.hh"
#include "board-element.hh"

using namespace controller;

GameEngine::GameEngine(unsigned nb_humans, unsigned nb_ais, unsigned nb_turns_max, bool random)
	: nb_humans_(nb_humans)
	, nb_ais_(nb_ais)
	, nb_turns_(0)
	, nb_turns_max_(nb_turns_max)
	, max_workers_(1)
	, random_(random)
	, board_(this)
{
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
	foreach(Player * p, players_)
	{
		delete p;
	}
}

void GameEngine::operator()()
{
	waitForPlayers_();
	init_();
	play_();
	sigs_.game_over();
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

void GameEngine::init_()
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
	// Give each player his initial denier amount.
	for (unsigned i = 1; i < players_.size(); i++)
	{
		players_[i]->resources() += Resource::denier * ((i < 3) ? 1 : 2);
		players_[i]->workers() = max_workers_;
	}
}

void GameEngine::play_()
{
	sigs_.game_engine_ready();
	init_();
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
	sigs_.activation_special_buildings_begin();
	for (unsigned i = 0; i < 6; ++i)
	{
		board_.road().get()[i]->activate();
		sigs_.board_updated();
	}
	sigs_.activation_special_buildings_end();
}

void GameEngine::activateBuildings_()
{
	sigs_.activation_buildings_begin();
	for (unsigned i = 6; i <= board_.provost() + 1; ++i)
	{
		if (board_.road().get()[i] != NULL)
		{
			board_.road().get()[i]->activate();
		}
	}
	sigs_.activation_buildings_end();
}

void GameEngine::activateBridge_()
{
	sigs_.activation_bridge_begin();
	foreach(Player * p, board_.bridge().players())
	{
		board_.bridge().activation_sig(&board_.bridge(), p);
		assert(p);
		int deniers = p->resources()[Resource::denier];
		if (deniers == 0)
		{
			continue;
		}
		int shift = 0;
		unsigned int selected_case = 0;
		bool is_shift_valid = false;
		bool has_enough_denier = false;
		/* If the provost is not moved before the bridge, or over the end
		   of the board, or if the player has enough money, then move. */
		while (!is_shift_valid || !has_enough_denier)
		{
			selected_case = p->askProvostShift();
			is_shift_valid = board_.isProvostShiftValid(selected_case);
			shift = selected_case - board_.provost();
			has_enough_denier = fabs(shift) <= deniers;
		}
		board_.provost() = selected_case;
		sigs_.board_updated();
		p->resources() -= Resource::denier * fabs(shift);
	}
	sigs_.activation_bridge_end();
}

void GameEngine::activateCastle_()
{
	sigs_.activation_castle_begin();
	board_.castle().on_activate();
	sigs_.activation_castle_end();
}

void GameEngine::collectIncome_()
{
	sigs_.income_collecting_begin();
	assert(players_.size() > 0);
	foreach(Player * p, players_)
	{
		ResourceMap income = Resource::denier * (2 + p->residences());
		sigs_.income_collecting_for_player(p, &income);
		p->resources() += income;
	}
	sigs_.income_collecting_end();
}

void GameEngine::endOfTurn_()
{
	moveBailiff_();
	if (board_.bailiff() == 17 || board_.bailiff() == 18 ||
	    board_.bailiff() == 30 || board_.bailiff() == 31 ||
	    board_.castle().isActivePartComplete())
	{
		board_.castle().score(players_);
	}
	if (players_.size() == 2)
	{
		std::swap(order_.front(), order_.back());
	}
}

void GameEngine::placeWorkers_()
{
	sigs_.worker_placement_begin();
	while (board_.bridge().players().size() != players_.size())
	{
		foreach(Player * p, order_)
		{
			assert(p);
			if (canPlayerPlay_(p))
			{
				playerMove_(p);
			}
		}
	}
	sigs_.worker_placement_end();
}

void GameEngine::moveBailiff_()
{
	board_.bailiff() += (board_.provost() > board_.bailiff() ? 2 : 1);
	board_.provost() = board_.bailiff();
}

void GameEngine::addToCastle(Player * p)
{
	assert(p);
	board_.castle().add(p);
}

void GameEngine::playerMove_(Player * p)
{
	bool has_played = false;
	unsigned int selected_case = 0;
	unsigned int worker_cost = 0;

	sigs_.worker_placement_for_player(p);
	while (!has_played)
	{
		selected_case = p->askWorkerPlacement();

		if (selected_case == Castle::CASE_NUMBER)
		{
			board_.bridge().add(p);
			has_played = true;
			continue;
		}

		worker_cost = getWorkerCost_(p);

		if (selected_case == Castle::CASE_NUMBER && p->resources()[Resource::denier] >= worker_cost)
		{
			DebugLogger::log("Castle chosen");
			board_.castle().add(p);
			p->resources() -= Resource::denier * worker_cost;
			p->workers() -= 1;
			has_played = true;
			continue;
		}

		assert(selected_case < board_.road().get().size());
		BuildingSmartPtr selected_building = board_.road().get()[selected_case];

		if (selected_building != NULL)
		{
			if (p->resources()[Resource::denier] >= (selected_building->owner() == p ? 1 : worker_cost))
			{
				try
				{
					selected_building->worker_set(*p);
					p->resources() -= Resource::denier * (selected_building->owner() == p ? 1 : worker_cost);
					has_played = true;
				}
				catch (OccupiedBuildingEx *)
				{
					DebugLogger::log("Already occupied.");
					return;
				}
				catch (UnactivableBuildingEx *)
				{
					DebugLogger::log("Does not accept workers.");
					return;
				}
			}
			else
			{
				DebugLogger::log("Not enough denier to play ");
				return;
			}
		}
		else
		{
			DebugLogger::log("Empty case.");
		}
	}
	sigs_.board_updated();
}

void GameEngine::startOfTurn_()
{
	sigs_.turn_start(nb_turns_, nb_turns_max_);

	board_.road().clearWorkers();
	board_.bridge().clear();
	board_.castle().clear();
	foreach(Player * p, players_)
	{
		p->workers() = max_workers_;
	}
	Inn * inn = dynamic_cast<Inn *>(board_.road().get()[INN_CASE].get());
	if (inn->host())
	{
		inn->host()->workers() -= 1;
	}
	sigs_.board_updated();
}

bool GameEngine::canPlayerPlay_(Player * p)
{
	if (board_.bridge().has(p))
	{
		sigs_.already_on_bridge(p);
		return false;
	}
	if (p->resources()[Resource::denier] == 0)
	{
		sigs_.not_enough_deniers(p);
		board_.bridge().add(p);
		return false;
	}
	if (p->workers() == 0)
	{
		sigs_.no_worker_left(p);
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
	game_b->build(p);
	board_.road().build(game_b);
	buildings_.erase(std::find(buildings_.begin(), buildings_.end(), building));
}

Player * GameEngine::newPlayer()
{
	Player * p = new Player();
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

std::ostream & operator<<(std::ostream & o, const controller::GameEngine & g)
{
	foreach(const Player * p, g.order())
	{
		o << *p << std::endl;
	}
	o << g.board();
	return o;
}
