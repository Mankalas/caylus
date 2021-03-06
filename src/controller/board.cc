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
	, bridge_(*this)
{
	provost_ = Road::PROVOST_INIT_CASE;
	bailiff_ = Road::BAILIFF_INIT_CASE;
}

Board::~Board()
{
}

bool Board::isProvostShiftValid(int shift) const
{
	return shift >= -3 && shift <= 3 &&
		provost() + shift <= Road::LAST_CASE &&
		provost() - shift >= Road::FIRST_NEUTRAL_CASE;
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
	signals_.bailiff_shifted(shift);
	shiftProvost(bailiff_ - provost_);
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

void Board::activateBuildingAtCase(unsigned int i)
{
	BuildingSmartPtr & building = road_[i];
	if (building)
	{
		building->activate();
	}
}

BoardElement & Board::getBoardElement(unsigned int board_case)
{
	if (board_case == Castle::CASE_NUMBER)
	{
		return castle_;
	}
	if (board_case == Bridge::CASE_NUMBER)
	{
		return bridge_;
	}
	assert(--board_case < road_.get().size());
	return *(road_[board_case]);
}

bool Board::isPlayerOnBridge(const Player & p) const
{
	return bridge_.has(p);
}
