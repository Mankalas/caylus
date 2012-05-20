/**
 * @file   signals.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sat Nov 12 21:17:26 2011
 *
 * @brief  Declaration of the signals class.
 */

#ifndef SIGNALS_HH
# define SIGNALS_HH

# include <boost/signals.hpp>
# include <string>

namespace controller
{
		class BoardElement;
		class Player;
		class GameEngine;
		class ResourceMap;
}

//struct Signals
/// A connection between a signal and a slot.
typedef boost::signals::connection connection_t;

typedef boost::signal<unsigned (unsigned)> u_u_signal_t;
typedef boost::signal<unsigned (unsigned, unsigned)> u_u_u_signal_t;
typedef boost::signal<const std::string (void)> s_v_signal_t;
typedef boost::signal<void (void)> v_v_signal_t;
typedef boost::signal<int (void)> i_v_signal_t;
typedef boost::signal<void (unsigned)> v_u_signal_t;
typedef boost::signal<void (const controller::Player *)> v_cp_signal_t;
typedef boost::signal<void (const controller::Player *, const controller::ResourceMap *)> v_cp_cr_signal_t;
typedef boost::signal<void (const controller::BoardElement *)> player_choice_signal_t;
typedef boost::signal<void (const std::vector<controller::BoardElement *> &)> player_choices_signal_t;
typedef boost::signal<controller::BoardElement* (const std::vector<controller::BoardElement*> &)> ask_board_element_signal_t;
typedef boost::signal<void (const controller::GameEngine *)> v_cge_signal_t;
typedef boost::signal<void (const controller::BoardElement *)> board_element_activation_signal_t;

/* Player interactions.

/// Ask how many humans are playing. First param is the max number
/// of humans that can play. Returns the actual number of humans.
u_u_signal_t ask_nb_humans;
/// Ask how many AIs are playing. First param is the minimum AIs
/// needed to play, second one is the max. Returns the actual
/// number of AIs.
u_u_u_signal_t ask_nb_ais;
/// Ask a name for a player. Returns a const string.
s_v_signal_t ask_player_name;
/// Submit a list of BoardElements to the player, who must chose
/// one of them. The elements are not const because the chosen one
/// will be modified later on the game.
ask_board_element_signal_t ask_worker_placement;

Game phases

/// The board has been updated.
v_v_signal_t board_updated;
/// The game engine is ready.
v_v_signal_t game_engine_ready;
/// A new turn has begun. First param is the current turn number.
v_u_signal_t new_turn;
/// Income collecting phase has begun.
v_v_signal_t income_collecting_begin;
/// Income collecting for a player.
v_cp_signal_t income_collecting_for_player;
/// Income collecting phase has ended.
v_v_signal_t income_collecting_end;
/// Worker placement phase has begun.
v_v_signal_t worker_placement_begin;
/// Worker placement phase has ended.
v_v_signal_t worker_placement_end;
/// Worker placement for a player.
v_cp_signal_t worker_placement_for_player;

Errors, messages and log.

/// Player is already on the bridge.
v_cp_signal_t already_on_bridge;
/// Not enough deniers to play.
v_cp_signal_t not_enough_deniers;
/// No worker left.
v_cp_signal_t no_worker_left;
/// A player has been added to the bridge.
v_cp_signal_t added_to_bridge;
/// Get the board element a player has chosen from a list.
player_choice_signal_t sig_player_has_chosen;
/// Get the choices a player has between several BoardElements.
player_choices_signal_t sig_player_choices;*/

#endif
