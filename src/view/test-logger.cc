/**
 * @file   test-logger.cc
 * @author Vincent Boucheny <vincent.boucheny@hpc-sa.com>
 * @date   Tue Feb 19 21:16:51 2013
 *
 * @brief  Declaration of the test-logger class.
 */

#include "test-logger.hh"
#include "../debug-logger.hh"

#include "../controller/game-engine.hh"
#include "../controller/player.hh"

using namespace controller;
using namespace view;

TestLogger::TestLogger(const GameEngine * game_engine, const std::string & output_path)
	: PassiveView(game_engine)
{
	game_engine->signals()->turn_start.connect(boost::bind(&TestLogger::newTurn, this, _1, _2));

	game_engine->board().signals().provost_shifted.connect(boost::bind(&TestLogger::provostShifted, this, _1));
	game_engine->board().signals().bailiff_shifted.connect(boost::bind(&TestLogger::bailiffShifted, this, _1));

	foreach (const BoardElement * board_element, game_engine->getEveryBoardElements())
	{
		board_element->activation_sig.connect(boost::bind(&TestLogger::activationBoardElement, this, _1, _2));
		board_element->already_occupied.connect(boost::bind(&TestLogger::boardElementAlreadyOccupied, this, _1));
		board_element->worker_placed.connect(boost::bind(&TestLogger::workerPlacement, this, _1, _2));
	}

	foreach (const Player * player, game_engine->players())
	{
		player->signals().gain_resources.connect(boost::bind(&TestLogger::playerGainsResources, this, _1, _2));
		player->signals().lose_resources.connect(boost::bind(&TestLogger::playerLosesResources, this, _1, _2));
	}

	file_.open((output_path + "/output").c_str(), std::ios::trunc);
	if (file_.fail())
	{
		std::cerr << "Fail to open " << output_path + "/output" << std::endl;
	}
}

TestLogger::~TestLogger()
{
	file_.flush();
	file_.close();
}

void TestLogger::provostShifted(int shift)
{
	unsigned int abs_shift = fabs(shift);
	std::string space = (abs_shift <= 1) ? " space " : " spaces ";
	std::string way = (shift < 0) ? "backward" : "forward";
	file_ << "Provost moves " << abs_shift << space << way << std::endl;
}

void TestLogger::bailiffShifted(unsigned int shift)
{
	std::string space = (shift <= 1) ? " space " : " spaces ";
	file_ << "Bailiff moves " << shift << space << "forward" << std::endl;
}

void TestLogger::playerGainsResources(const controller::Player * player, const controller::ResourceMap & resource_map)
{
	file_ << player->name() << " gains " << resource_map << std::endl;
}

void TestLogger::playerLosesResources(const controller::Player * player, const controller::ResourceMap & resource_map)
{
	file_ << player->name() << " loses " << resource_map << std::endl;
}

void TestLogger::newTurn(unsigned current_turn, unsigned max_turn)
{
	file_ << "Turn " << current_turn << std::endl;
}

/*void TestLogger::playerResourcesChanged(const controller::Player * player, const controller::ResourceMap & resources)
  {
  file_ << player->name();
  }*/

void TestLogger::workerPlacement(const controller::BoardElement * board_elt, const controller::Player * player)
{
	file_ << player->name() << " places a worker on " << board_elt->name() << std::endl;
}

void TestLogger::activationBoardElement(const controller::BoardElement * board_elt, const controller::Player * p)
{
	file_ <<  board_elt->name() << " activated for " << p->name() << std::endl;
}

void TestLogger::boardElementAlreadyOccupied(const controller::BoardElement * board_elt)
{
	file_ << board_elt->name() << " already occupied" << std::endl;
}
