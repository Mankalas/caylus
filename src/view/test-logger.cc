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

TestLogger::TestLogger(const GameEngine * game_engine)
	: PassiveView(game_engine)
{
	game_engine->signals()->turn_start.connect(boost::bind(&TestLogger::newTurn, this, _1, _2));

	game_engine->board().castle().activation_sig.connect(boost::bind(&TestLogger::activationBoardElement, this, _1, _2));
	game_engine->board().bridge().activation_sig.connect(boost::bind(&TestLogger::activationBoardElement, this, _1, _2));
	foreach(const BuildingSmartPtr b, game_engine->board().road().get())
	{
		if (b != NULL)
		{
			b->activation_sig.connect(boost::bind(&TestLogger::activationBoardElement, this, _1, _2));
			b->already_occupied.connect(boost::bind(&TestLogger::boardElementAlreadyOccupied, this, _1));
		}
	}

	file_.open("output.txt", std::ios::trunc);
}

TestLogger::~TestLogger()
{}

void TestLogger::newTurn(unsigned current_turn, unsigned max_turn)
{
	file_ << "Turn " << current_turn << std::endl;
	foreach (const Player * p, game_engine_->players())
	{
		file_ << *p << std::endl;
	}
}

/*void TestLogger::playerResourcesChanged(const controller::Player * player, const controller::ResourceMap & resources)
{
	file_ << player->name();
	}*/

void TestLogger::activationBoardElement(const controller::BoardElement * board_elt, const controller::Player * p)
{
	file_ <<  board_elt->name() << " activated for " << *p << std::endl;
}

void TestLogger::boardElementAlreadyOccupied(const controller::BoardElement * board_elt)
{
	file_ << board_elt->name() << " already occupied" << std::endl;
}
