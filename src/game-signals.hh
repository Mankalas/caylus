/**
 * @file   game-signals.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Tue Jan 10 23:48:40 2012
 *
 * @brief  Declaration of the game-signals class.
 */

#ifndef GAME_SIGNALS_HH
# define GAME_SIGNALS_HH

# include "signals.hh"

namespace controller
{
	struct GameSignals
	{
		/* Player interactions. */

		/// Ask how many humans are playing. First param is the max number
		/// of humans that can play. Returns the actual number of humans.
		u_u_signal_t ask_nb_humans;
		/// Ask how many AIs are playing. First param is the minimum AIs
		/// needed to play, second one is the max. Returns the actual
		/// number of AIs.
		u_u_u_signal_t ask_nb_ais;
		/// Ask a name for a player. Returns a const string.
		s_v_signal_t ask_player_name;

		/* Game phases. */

		/// The board has been updated.
		v_v_signal_t board_updated;
		/// The game engine is ready.
		v_v_signal_t game_engine_ready;
		/// A new turn has begun. First param is the current turn number.
		v_u_u_signal_t turn_start;

		/// Income collecting phase has begun.
		v_v_signal_t income_collecting_begin;
		/// Income collecting for a player.
		v_cp_cr_signal_t income_collecting_for_player;
		/// Income collecting phase has ended.
		v_v_signal_t income_collecting_end;

		/// Worker placement phase has begun.
		v_v_signal_t worker_placement_begin;
		/// Worker placement phase has ended.
		v_v_signal_t worker_placement_end;
		/// Worker placement for a player.
		v_cp_signal_t worker_placement_for_player;

		v_v_signal_t activation_special_buildings_begin;
		v_v_signal_t activation_special_buildings_end;

		v_v_signal_t activation_bridge_begin;
		v_v_signal_t activation_bridge_end;

		v_v_signal_t activationBuildings_begin;
		v_v_signal_t activationBuildings_end;

		v_v_signal_t activation_castle_begin;
		v_v_signal_t activation_castle_end;

		v_v_signal_t game_over;

		built_signal_t built;

		/* Errors, messages and log. */

		/// Not enough deniers to play.
		v_cp_signal_t not_enough_deniers;
		/// No worker left.
		v_cp_signal_t no_worker_left;

	};
}

#endif
