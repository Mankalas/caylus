/**
 * @file   logger.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun Sep 25 00:42:58 2011
 *
 * @brief  Declaration of the logger class.
 */

#ifndef LOGGER_HH
# define LOGGER_HH

# include <stack>
# include <fstream>
# include <boost/bind.hpp>
# include "passive-view.hh"
# include "const.hh"
# include "signals.hh"

namespace controller
{
	class Player;
	class ResourceMap;
	class BoardElement;
}

namespace view
{
	class Logger : public PassiveView
	{
	public:
		Logger(const controller::GameEngine * ge);
		~Logger();

		void setGE(const controller::GameEngine * ge);

		void startOfTurn(const controller::GameEngine *);
		void playerIncome(const controller::Player *, const controller::ResourceMap *);

		void startSection(int level, const std::string & title);
		void endSection();

		void gameEngineReady();
		void newTurn();

		void incomeCollectionBegin();
		void incomeCollectionEnd();
		void incomeCollectionForPlayer(const controller::Player * player, const controller::ResourceMap * income);

		void workerPlacementBegin();
		void workerPlacementEnd();
		void workerPlacementForPlayer(const controller::Player * player);

		void activationSpecialBuildingsBegin();
		void activationSpecialBuildingsEnd();

		void activationBuildingsBegin();
		void activationBuildingsEnd();

		void activationBridgeBegin();
		void activationBridgeEnd();

		void activationCastleBegin();
		void activationCastleEnd();

		void alreadyOnBridge(const controller::Player * player);
		void notEnoughDeniers(const controller::Player * player);
		void noWorkerLeft(const controller::Player * player);
		void playerChoice(const controller::BoardElement * board_elt);
		void playerChoices(const std::vector<controller::BoardElement *> & choices);
		void resourceMove(const ResourceMap *);

		virtual void boardElementActivation(const controller::BoardElement * board_elt);
		virtual void updateBoard();

	private:
		unsigned int turn_count_;
		std::ofstream file_;
		const controller::GameEngine * ge_;
	};
}

#endif
