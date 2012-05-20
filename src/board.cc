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
	, FIRST_EMPTY_CASE_(6)
	, LAST_EMPTY_CASE_(33)
{
	provost_ = PROVOST_INIT_CASE;
	bailiff_ = BAILIFF_INIT_CASE;
}

Board::~Board()
{
}

bool Board::valid_provost_move(int shift) const
{
	return shift >= -3 && shift <= 3 &&
		shift + provost() <= LAST_EMPTY_CASE_ &&
		shift - provost() >= FIRST_EMPTY_CASE_;
}
