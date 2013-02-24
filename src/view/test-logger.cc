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
	file_.open("output.txt", std::ios::trunc);
}

TestLogger::~TestLogger()
{}

void TestLogger::newTurn(unsigned current_turn, unsigned max_turn)
{
	file_ << "Turn " << current_turn << " / " << max_turn << std::endl;
	foreach (const Player * p, game_engine_->players())
	{
		file_ << *p << std::endl;
	}
}
