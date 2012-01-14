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
# include "const.hh"
# include "signals.hh"

namespace controller
{
	class GameEngine;
	class Player;
	class ResourceMap;
	class BoardElement;
}

class Logger
{
public:
	Logger();
	~Logger();

	void setGE(const controller::GameEngine * ge);

	void startOfTurn(const controller::GameEngine *);
	void playerIncome(const controller::Player *, const controller::ResourceMap &);

	void startSection(int level, const std::string & title);
	void endSection();

	void gameEngineReady();
	void newTurn();
	void incomeCollectionBegin();
	void incomeCollectionEnd();
	void incomeCollectionForPlayer(const controller::Player * player, const controller::ResourceMap & income);
	void workerPlacementBegin();
	void workerPlacementEnd();
	void workerPlacementForPlayer(const controller::Player * player);
	void alreadyOnBridge(const controller::Player * player);
	void notEnoughDeniers(const controller::Player * player);
	void noWorkerLeft(const controller::Player * player);
	void playerChoice(const controller::BoardElement * board_elt);
	void playerChoices(const std::vector<controller::BoardElement *> & choices);
	void resourceMove(const ResourceMap *);

	v_v_signal_t::slot_function_type gameEngineReadySlot();
	v_u_signal_t::slot_function_type newTurnSlot() ;
	v_v_signal_t::slot_function_type incomeCollectionBeginSlot() ;
	v_v_signal_t::slot_function_type incomeCollectionEndSlot() ;
	v_cp_cr_signal_t::slot_function_type incomeCollectionForPlayerSlot() ;
	v_v_signal_t::slot_function_type workerPlacementBeginSlot() ;
	v_v_signal_t::slot_function_type workerPlacementEndSlot() ;
	v_cp_signal_t::slot_function_type workerPlacementForPlayerSlot() ;
	v_cp_signal_t::slot_function_type alreadyOnBridgeSlot() ;
	v_cp_signal_t::slot_function_type notEnoughDeniersSlot() ;
	v_cp_signal_t::slot_function_type noWorkerLeftSlot() ;
	player_choice_signal_t::slot_function_type playerChoiceSlot() ;
	player_choices_signal_t::slot_function_type playerChoicesSlot() ;
	boost::signal<void (const controller::ResourceMap *)>::slot_function_type resourceMoveSlot();

private:
	unsigned int turn_count_;
	std::ofstream file_;
	const controller::GameEngine * ge_;
};

#endif
