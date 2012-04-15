/**
 * @file   board.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Mon Apr  9 16:07:43 2012
 *
 * @brief  Declaration of the board class.
 */

#include "board.hh"
#include "game-engine.hh"

using namespace controller;

Board::Board(GameEngine * ge)
	: road_(ge)
{
	provost_ = PROVOST_INIT_CASE;
	bailiff_ = BAILIFF_INIT_CASE;
}

Board::~Board()
{
}
