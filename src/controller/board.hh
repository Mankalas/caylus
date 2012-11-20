/**
 * @file   board.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Mon Apr  9 16:03:14 2012
 *
 * @brief  Declaration of the board class.
 */

#ifndef BOARD_HH
# define BOARD_HH

# include "road.hh"
# include "bridge.hh"
# include "castle.hh"

class Visitor;
class ConstVisitor;

namespace controller
{
	class GameEngine;

	class Board
	{
	public:
		Board(GameEngine * ge);
		~Board();

		const Road & road() const;
		Road & road();

		const Bridge & bridge() const;
		Bridge & bridge();

		const Castle & castle() const;
		Castle & castle();

		const unsigned & bailiff() const;
		unsigned & bailiff();

		const unsigned & provost() const;
		unsigned & provost();

		bool isProvostShiftValid(int shift) const;
		void shiftProvost(int shift);

		/** @name Visitors accept methods */
		//@{

		void accept(ConstVisitor &) const;
		void accept(Visitor &);

		//@}

	private:
		/// The "road" on the board of the game.
		Road road_;
		/// List of players at the castle.
		Castle castle_;
		/// Bridge
		Bridge bridge_;
		/// Road's index of the building the provost is in.
		unsigned provost_;
		/// Road's index of the building the bailiff is in.
		unsigned bailiff_;

		const unsigned FIRST_EMPTY_CASE_;
		const unsigned LAST_EMPTY_CASE_;
	};
}

std::ostream & operator<<(std::ostream & o, const Board & b);

#include "board.hxx"

#endif
