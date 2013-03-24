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
		TestLogger(const controller::GameEngine * ge, const std::string & output_path);

		/** Destructor. */
		~TestLogger();

	private:
		void newTurn(unsigned current_turn, unsigned max_turn);
		void activationBoardElement(const controller::BoardElement * board_elt);
		void boardElementAlreadyOccupied(const controller::BoardElement * board_elt);
		void workerPlacement(const controller::Player * player, const controller::BoardElement * board_elt);
		void playerGainsResources(const controller::Player * player, const controller::ResourceMap & resource_map);
		void playerLosesResources(const controller::Player * player, const controller::ResourceMap & resource_map);
		void provostShifted(int shift);
		void bailiffShifted(unsigned int shift);

		std::ofstream file_;
	};
}

#endif
