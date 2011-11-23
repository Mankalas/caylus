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
	void newTurn(unsigned turn);
	void incomeCollectionBegin();
	void incomeCollectionEnd();
	void incomeCollectionForPlayer(const controller::Player * player);
	void workerPlacementBegin();
	void workerPlacementEnd();
	void workerPlacementForPlayer(const controller::Player * player);
	void alreadyOnBridge(const controller::Player * player);
	void notEnoughDeniers(const controller::Player * player);
	void noWorkerLeft(const controller::Player * player);
	void playerChoice(const controller::BoardElement * board_elt);
	void playerChoices(const std::vector<const controller::BoardElement *> & choices);

	v_v_signal_t::slot_function_type gameEngineReadySlot() const;
	v_u_signal_t::slot_function_type newTurnSlot() const;
	v_v_signal_t::slot_function_type incomeCollectionBeginSlot() const;
	v_v_signal_t::slot_function_type incomeCollectionEndSlot() const;
	v_cp_signal_t::slot_function_type incomeCollectionForPlayerSlot() const;
	v_v_signal_t::slot_function_type workerPlacementBeginSlot() const;
	v_v_signal_t::slot_function_type workerPlacementEndSlot() const;
	v_cp_signal_t::slot_function_type workerPlacementForPlayerSlot() const;
	v_cp_signal_t::slot_function_type alreadyOnBridgeSlot() const;
	v_cp_signal_t::slot_function_type notEnoughDeniersSlot() const;
	v_cp_signal_t::slot_function_type noWorkerLeftSlot() const;
	player_choice_signal_t::slot_function_type playerChoiceSlot() const;
	player_choices_signal_t::slot_function_type playerChoicesSlot() const;

private:
	unsigned int turn_count_;
	std::ofstream file_;
	const controller::GameEngine * ge_;
};

# include "logger.hxx"

#endif
