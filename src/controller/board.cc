/**
 * @file   board.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Mon Apr  9 16:07:43 2012
 *
 * @brief  Declaration of the board class.
 */

#include "board.hh"
#include "game-engine.hh"
#include "../debug-logger.hh"

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

bool Board::isProvostShiftValid(int shift) const
{
	return shift >= -3 && shift <= 3 &&
		provost() + shift <= LAST_EMPTY_CASE_ &&
		provost() - shift >= FIRST_EMPTY_CASE_;
}

void Board::shiftProvost(int shift)
{
	provost_ += shift;
	signals_.provost_shifted(shift);
}

void Board::shiftBailiff()
{
	unsigned int shift = 1;
	if (provost_ > bailiff_)
	{
		shift = 2;
	}
	bailiff_ += shift;
	provost_ = bailiff_;
	signals_.bailiff_shifted(shift);
}

std::ostream & operator<<(std::ostream & o, const Board & board)
{
	o << "Bridge : ";
	foreach(const Player * p, board.bridge().players())
	{
		o << p->name() << " - ";
	}

	o << std::endl << board.castle();

	BuildingSmartPtr bdg = board.road()[board.bailiff()];
	o << std::endl << "Bailiff : " << board.bailiff() + 1 << ": "
	  << (bdg == NULL ? "<empty>" : bdg->name()) << std::endl;

	bdg = board.road()[board.provost()];
	o << "Provost : " << board.provost() + 1 << ": "
	  << (bdg == NULL ? "<empty>" : bdg->name()) << std::endl
	  << std::endl;

	o << board.road() << std::endl;
	o << BOLDYELLOW << Bridge::CASE_NUMBER << ". " << RESET << board.bridge().name() << std::endl
	  << BOLDYELLOW << Castle::CASE_NUMBER << ". " << RESET << board.castle().name() << std::endl;
	return o;
}
