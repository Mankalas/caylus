/**
 * @file   test-logger.cc
 * @author Vincent Boucheny <vincent.boucheny@hpc-sa.com>
 * @date   Tue Feb 19 21:16:51 2013
 *
 * @brief  Declaration of the test-logger class.
 */

#include "test-logger.hh"

#include "../controller/game-engine.hh"
#include "../controller/player.hh"

using namespace controller;
using namespace view;

TestLogger::TestLogger(const GameEngine * game_engine, std::string output_path)
	: PassiveView(game_engine)
{
	game_engine->signals()->turn_start.connect(boost::bind(&TestLogger::newTurn, this, _1, _2));

	foreach (const BoardElement * board_element, game_engine->getEveryBoardElements())
	{
		board_element->activation_sig.connect(boost::bind(&TestLogger::activationBoardElement, this, _1, _2));
		board_element->already_occupied.connect(boost::bind(&TestLogger::boardElementAlreadyOccupied, this, _1));
		board_element->worker_placed.connect(boost::bind(&TestLogger::workerPlacement, this, _1, _2));
	}

	std::string output_file = output_path.erase(output_path.size() - 6, 6).append("/output");
	file_.open(output_file.c_str(), std::ios::trunc);
	if (file_.fail())
	{
		std::cerr << "Fail to open " << output_file << std::endl;
	}
}

TestLogger::~TestLogger()
{
	file_.flush();
	file_.close();
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
