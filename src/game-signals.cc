/**
 * @file   game-signals.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun Jan 15 00:28:58 2012
 *
 * @brief  Implementation of the game-signals class.
 */

#include "game-signals.hh"

void GameSignals::connect(View & view)
{
	game_engine_ready.connect(view->gameEngineReadySlot());
	income_collecting_begin.connect(view->incomeCollectionBeginSlot());
	income_collecting_for_player.connect(view->incomeCollectionForPlayerSlot());
	income_collecting_end.connect(view->incomeCollectionEndSlot());
	worker_placement_begin.connect(view->workerPlacementBeginSlot());
	worker_placement_end.connect(view->workerPlacementEndSlot());
	worker_placement_for_player.connect(view->workerPlacementForPlayerSlot());

	player_choices.connect(view->playerChoicesSlot());
	player_has_chosen.connect(view->playerChoiceSlot());
}
