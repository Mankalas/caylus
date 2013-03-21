/**
 * @file   test-logger.hh
 * @author Vincent Boucheny <vincent.boucheny@hpc-sa.com>
 * @date   Tue Feb 19 21:12:52 2013
 *
 * @brief  Declaration of the test-logger class.
 */
#ifndef TEST_LOGGER_HH
#define TEST_LOGGER_HH

#include "passive-view.hh"
#include <fstream>

namespace controller
{
	class Player;
	class ResourceMap;
	class BoardElement;
}

namespace view
{
	class TestLogger : public PassiveView
	{
	public:
		/** Constructor. */
		TestLogger(const controller::GameEngine * ge);

		/** Destructor. */
		~TestLogger();

	private:
		void newTurn(unsigned current_turn, unsigned max_turn);
		void activationBoardElement(const controller::BoardElement * board_elt, const controller::Player * p);
		void boardElementAlreadyOccupied(const controller::BoardElement * board_elt);

		std::ofstream file_;
	};
}

#endif
