/**
 * @file   game-engine.cc
 * @author  <mankalas@localhost,>
 * @date   Thu Jan 22 13:57:35 2009
 *
 * @brief  Implementation of GameEngine.
 *
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
	Logger::log("Releasing waiting_players lock.");
	waiting_players_.notify_one();
	Logger::log("Waiting for the game to start...");
	game_start_.wait(lock);
	Logger::log("HERE WE GO!");
	initialize();
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
	// Shuffle players order.
	foreach (Player* p, players_)
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
}

GameEngine::~GameEngine()
{
	foreach(Player* p, players_)
	{
		delete p;
	}
}

void GameEngine::activateBuildings()
{
	for (unsigned i = 6; i <= provost_ + 1; ++i)
		if (road_.get()[i] != NULL)
			road_.get()[i]->activate();
}

void GameEngine::activateBridge()
{
	int deniers = 0;
	int shift = 0;

	foreach (Player* p, bridge_)
	{
		assert(p);
		deniers = p->resources()[Resource::denier];
		if (deniers == 0)
		{
			//p->userInterface()->showMessage("You're too poor for corruption.");
			continue;
		}

		shift = p->askProvostShift();
		// If the provost is not moved before the bridge, or over the end
		// of the board, or if the player has enough money, then move.
		while (shift + provost_ < 6 || shift + provost_ > 33 ||
		       std::abs(shift) > deniers)
			shift = p->askProvostShift();
		provost_ += shift;
		p->resources() -= Resource::denier * std::abs(shift);
	}
}

void GameEngine::activateSpecialBuildings()
{
	for (unsigned i = 0; i < 6; ++i)
		road_.get()[i]->activate();
}

void GameEngine::activateCastle()
{
	castle_.activate();
}

void GameEngine::collectIncome()
{
	std::cout << "Collecting income... ";
	foreach (Player* p, players_)
	{
		//     std::cout << p.residences() << " => "
		//               << (Resource::denier * (2 + p.residences())) << std::endl;
		p->resources() += Resource::denier * (2 + p->residences());
	}
	std::cout << "Done." << std::endl;
}

void GameEngine::endOfTurn()
{
	std::cout << "End of turn... ";
	_moveBailiff();
	if (bailiff_ == 17 || bailiff_ == 18 ||
	    bailiff_ == 30 || bailiff_ == 31 ||
	    castle_.isActivePartComplete())
		castle_.score(players_);
	if (players_.size() == 2)
		std::swap(order_.front(), order_.back());
	std::cout << "Done." << std::endl;
}

void GameEngine::placeWorkers()
{
	_startOfTurn();
	while (bridge_.size() != players_.size())
	{
		foreach (Player* p, order_)
		{
			assert(p != NULL);
			if (!_canPlayerPlay(p))
				continue;
			_playerMove(p);
		}
	}
}

void GameEngine::_moveBailiff()
{
	bailiff_ += (provost_ > bailiff_ ? 2 : 1);
	provost_ = bailiff_;
}

bool GameEngine::addToCastle(Player* p)
{
	assert(p);
	return castle_.add(p);
}

void GameEngine::_playerMove(Player* p)
{
	bool has_played = false;
	int player_input = 0;
	unsigned worker_cost = 0;

	while (!has_played)
	{
		std::cout << *this << std::endl;

		// Get the player input.
		//p->userInterface()->showMessage("Your turn " + p->name() +
		//" (-1 for castle, 34 for the bridge)");
		player_input = p->askWorkerPlacement();

		// Players chose the bridge.
		if (player_input == 34)
		{
			_addToBridge(p);
			has_played = true;
			return;
		}

		worker_cost = _getWorkerCost(p);
		std::cout << "wc: " << worker_cost << std::endl;
		std::cout << "input : " << player_input << std::endl;

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
			else {}
			//p->userInterface()->showMessage("Not enough denier to play the castle");
		}

		assert(player_input <= (int)road_.get().size());
		Building* b = road_.get()[player_input].get();

		if (p->resources()[Resource::denier] >= (b->owner() == p ? 1 : worker_cost))
		{
			try
			{
				b->worker_set(*p);
				std::cout << "BEFORE: " << p->resources() << std::endl
				          << "     -= " << (Resource::denier * (b->owner() == p ? 1 : worker_cost)) << std::endl;
				p->resources() -= Resource::denier * (b->owner() == p ? 1 : worker_cost);
				std::cout << "AFTER:  " << p->resources() << std::endl;
				has_played = true;
			}
			catch(OccupiedBuildingEx*)
			{
				std::cout << "***** " << b->name() << " already occupied." << std::endl;
				return;
			}
			catch(UnactivableBuildingEx*)
			{
				std::cout << "***** " << b->name() << " does not accept workers."
				          << std::endl;
				return;
			}
		}
		else
		{
			std::cout << "***** Not enough denier to play " << b->name()
			          << std::endl;
			return;
		}
	}
}

void GameEngine::_startOfTurn()
{
	road_.clear();
	bridge_.clear();
	castle_.clear();
	foreach (Player* p, players_)
		p->workers() = NB_WORKERS;
	Inn* inn = (Inn*)(road_.get()[5].get());
	if (inn->host())
		inn->host()->workers() -= 1;
}
void GameEngine::_addToBridge(Player* p)
{
	if (bridge_.size() == 0)
		p->resources() += Resource::denier;
	bridge_.push_back(p);
}

bool GameEngine::_canPlayerPlay(Player* p)
{
	// If the player is already on the bridge or he doesn't have any
	// denier left, continue.
	if (std::find(bridge_.begin(), bridge_.end(), p) != bridge_.end())
		return false;
	if (p->resources()[Resource::denier] == 0)
	{
		//p->userInterface()->showMessage("No more denier, automatically added to the Bridge");
		_addToBridge(p);
		return false;
	}
	if (p->workers() == 0)
	{
		//p->userInterface()->showMessage("No more worker, automatically added to the Bridge");
		_addToBridge(p);
		return false;
	}
	return true;
}

unsigned GameEngine::_getWorkerCost(const Player* p) const
{
	const Inn* inn = (const Inn*)(road_.get()[5].get());
	if (inn == NULL)
	{
		std::cerr << "The Inn isn't in the right case... returning a cost of 1 by default" << std::endl;
		return 1;
	}
	return (inn->host() == p) ? 1 : bridge_.size() + 1;
}

void GameEngine::build(BuildingSmartPtr& building, Player* p)
{
	BuildingSmartPtr game_b = *(std::find(buildings_.begin(), buildings_.end(), building));

	assert(p);
	assert(building);
	game_b->build(p);
	road_.build(game_b);
	buildings_.erase(std::find(buildings_.begin(), buildings_.end(), building));
}

void GameEngine::subscribeView(View *view)
{
	Human *human = NULL;
	Logger::log("Subcribing view.");
	//std::cout << players_.size() << " or " << players_.empty() << " and " << view->isHuman() <<  std::endl;
	// Only the first player can set the number of other players.
	if (players_.empty() && view->isHuman())
	{
		Logger::log("GE asks view for players.");
		unsigned max_players = 5;
		human = (Human*)view;
		ask_nb_humans_.connect(human->getAskNbHumansSlot());
		nb_humans_ = ask_nb_humans_(max_players);
		Logger::log(Logger::to_string(nb_humans_) + " humans.");
		ask_nb_ais_.connect(human->getAskNbAIsSlot());
		// Register AI players.
		unsigned nb_ais_;
		if (nb_humans_ > 2)
		{
			nb_ais_ = ask_nb_ais_(0, max_players - nb_humans_);
		}
		else
		{
			nb_ais_ = ask_nb_ais_(2 - nb_humans_, max_players - nb_humans_);
		}
		Logger::log(Logger::to_string(nb_ais_) + " ais.");
		for (unsigned i = 0; i < nb_ais_; ++i)
		{
			new view::AI();
		}
	}
	// No need to update the board for AIs.
	if (view->isHuman())
	{
		board_updated_.connect(human->getUpdateBoardSlot());
	}
	// New player, linked to the subscribing view.
	Player *p = new Player();
	p->setView(view);
	Logger::log("Adding new player.");
	players_.push_back(p);
	if (players_.size() == nb_humans_ + nb_ais_)
	{
		Logger::log("Releasing the lock on game_start.");
		game_start_.notify_one();
	}
}
