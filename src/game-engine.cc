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
#include "player-view.hh"
#include "debug-logger.hh"
#include "debug-logger.hh"

using namespace controller;

GameEngine::GameEngine(unsigned nb_humans, unsigned nb_ais)
	:nb_humans_(nb_humans), nb_ais_(nb_ais), nb_turns_(0), board_(this)
{
}

GameEngine::~GameEngine()
{
	foreach(Player * p, players_)
	{
		delete p;
	}
}

void GameEngine::init_()
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

	/*foreach (View * v, views_)
	{
		PlayerView * pv = dynamic_cast<PlayerView *>(v);
		foreach (BuildingSmartPtr b, buildings_)
		{
			b->subscribe(v);
			b->subscribe(pv);
		}
		foreach (BuildingSmartPtr b, board().road().get())
		{
			if (b != NULL)
			{
				b->subscribe(v);
				b->subscribe(pv);
			}
		}
		board().castle().subscribe(v);
		board().bridge().subscribe(v);
		board().castle().subscribe(pv);
		board().bridge().subscribe(pv);
		}*/

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
}

void GameEngine::launch()
{
	mutex_.unlock();
}

void GameEngine::operator() ()
{
	// Waiting for the view subscription to release the mutex.
	mutex_.lock();
	sigs_.game_engine_ready();
	init_();
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
	DebugLogger::log("End of the game.");
}

void GameEngine::activateSpecialBuildings_()
{
	sigs_.activation_special_buildings_begin();
	for (unsigned i = 0; i < 6; ++i)
	{
		board_.road().get()[i]->activate();
	}
	sigs_.activation_special_buildings_end();
}

void GameEngine::activateBuildings_()
{
	for (unsigned i = 6; i <= board_.provost() + 1; ++i)
	{
		if (board_.road().get()[i] != NULL)
		{
			board_.road().get()[i]->activate();
		}
	}
}

void GameEngine::activateBridge_()
{
	int deniers = 0;
	int shift = 0;

	foreach (Player * p, board_.bridge().players())
	{
		assert(p);
		deniers = p->resources()[Resource::denier];
		if (deniers == 0)
		{
			continue;
		}

		DebugLogger::log("Bridge activation.");
		shift = p->askProvostShift();
		/* If the provost is not moved before the bridge, or over the end
		   of the board, or if the player has enough money, then move. */
		while (!board().valid_provost_move(shift) || std::abs(shift) > deniers)
		{
			shift = p->askProvostShift();
		}
		board_.provost() += shift;
		p->resources() -= Resource::denier * std::abs(shift);
	}
}


void GameEngine::activateCastle_()
{
	board_.castle().on_activate();
}

void GameEngine::collectIncome_()
{
	sigs_.income_collecting_begin();
	assert(players_.size() > 0);
	foreach (Player *p, players_)
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
		foreach (Player *p, order_)
		{
			assert(p);
			if (!canPlayerPlay_(p))
			{
				continue;
			}
			playerMove_(p);
		}
	}
	sigs_.worker_placement_end();
}

void GameEngine::moveBailiff_()
{
	board_.bailiff() += (board_.provost() > board_.bailiff() ? 2 : 1);
	board_.provost() = board_.bailiff();
}

void GameEngine::addToCastle(Player *p)
{
	assert(p);
	board_.castle().add(p);
}

void GameEngine::playerMove_(Player *p)
{
	bool has_played = false;
	const BoardElement * player_choice;
	unsigned worker_cost = 0;

	sigs_.worker_placement_for_player(p);
	while (!has_played)
	{
		const std::vector<BoardElement*> choices = getAvailableBoardElements(p);
		sigs_.player_choices(choices);
		player_choice = p->askWorkerPlacement(choices);
		sigs_.player_has_chosen(player_choice);

		if (player_choice->isBridge())
		{
			board_.bridge().add(p);
			has_played = true;
			continue;
		}

		worker_cost = getWorkerCost_(p);

		if (player_choice->isCastle() && p->resources()[Resource::denier] >= worker_cost)
		{
			board_.castle().add(p);
			p->resources() -= Resource::denier * worker_cost;
			p->workers() -= 1;
			has_played = true;
			continue;
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
}

void GameEngine::startOfTurn_()
{
	sigs_.new_turn();

	board_.road().clearWorkers();
	board_.bridge().clear();
	board_.castle().clear();
	foreach (Player * p, players_)
	{
		p->workers() = NB_WORKERS;
	}
	Inn *inn = (Inn *)(board_.road().get()[INN_CASE].get());
	if (inn->host())
	{
		inn->host()->workers() -= 1;
	}
	sigs_.board_updated();
}

bool GameEngine::canPlayerPlay_(Player *p)
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

unsigned GameEngine::getWorkerCost_(const Player *p) const
{
	const Inn *inn = (const Inn *)(board_.road().get()[5].get());
	assert(inn);
	return (inn->host() == p) ? 1 : board_.bridge().players().size() + 1;
}

void GameEngine::build(BuildingSmartPtr &building, Player *p)
{
	BuildingSmartPtr game_b = *(std::find(buildings_.begin(), buildings_.end(), building));

	assert(p);
	assert(building);
	game_b->build(p);
	board_.road().build(game_b);
	buildings_.erase(std::find(buildings_.begin(), buildings_.end(), building));
}

/*void GameEngine::subscribeView(PlayerView *view)
{
	Player * p = new Player();
	p->setView(view);
	players_.push_back(p);
	views_.push_back(view);
	if (view->isInteractive())
	{
		sigs_.board_updated.connect(view->updateBoardSlot());
	}
}

void GameEngine::subscribeView(Logger * log)
{
	views_.push_back(log);
	sigs_.game_engine_ready.connect(log->gameEngineReadySlot());

	sigs_.income_collecting_begin.connect(log->incomeCollectionBeginSlot());
	sigs_.income_collecting_for_player.connect(log->incomeCollectionForPlayerSlot());
	sigs_.income_collecting_end.connect(log->incomeCollectionEndSlot());

	sigs_.worker_placement_begin.connect(log->workerPlacementBeginSlot());
	sigs_.worker_placement_end.connect(log->workerPlacementEndSlot());
	sigs_.worker_placement_for_player.connect(log->workerPlacementForPlayerSlot());

	sigs_.activation_special_buildings_begin.connect(log->activationSpecialBuildingsBeginSlot());
	sigs_.activation_special_buildings_end.connect(log->activationSpecialBuildingsEndSlot());

	sigs_.player_choices.connect(log->playerChoicesSlot());
	sigs_.player_has_chosen.connect(log->playerChoiceSlot());
	}*/

const std::vector<BoardElement*>
GameEngine::getAvailableBoardElements(const Player * worker) const
{
	std::vector<BoardElement*> available_buildings(board_.road().getAvailableBuildings(worker));

	available_buildings.push_back((BoardElement*)&board_.castle());
	available_buildings.push_back((BoardElement*)&board_.bridge());
	return available_buildings;
}
