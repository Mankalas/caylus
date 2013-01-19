/**
 * @file   player-signals.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Mon May 21 01:12:10 2012
 *
 * @brief  Declaration of the player-signals class.
 */

#ifndef PLAYER_SIGNALS_HH
# define PLAYER_SIGNALS_HH

# include "signals.hh"

namespace controller
{
	struct PlayerSignals
	{
		i_v_signal_t ask_provost_shift;
		u_v_signal_t ask_worker_placement;
		u_u_signal_t ask_choice;

		/// Get the board element a player has chosen from a list.
		player_choice_signal_t player_has_chosen;
		/// Get the choices a player has between several BoardElements.
		player_choices_signal_t player_choices;
	};
}

#endif
