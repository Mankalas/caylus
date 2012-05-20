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
	};
}

#endif
