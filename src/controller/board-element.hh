/**
 * @file   board-element.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sat Oct 15 21:48:55 2011
 *
 * @brief  Declaration of the board-element class.
 */

#ifndef BOARD_ELEMENT_HH
#define BOARD_ELEMENT_HH

#include <string>
#include "../signals.hh"

namespace view
{
	class View;
}

namespace controller
{
	class BoardElement;
	class Player;

	/**
	 * Signals emitted by the BoardElement class.
	 */
	struct BoardElementSignals
	{
		/** Emitted when the board element is activated. */
		v_cbe_signal_t activation_sig;

		/** Emitted when a worker is placed on the board element. */
		worker_placed_signal_t worker_placed;

		/** Emitted when a player tries to place its worker while the board element is full. */
		v_cbe_signal_t already_occupied;
	};

	/**
	 * Any part of the board that can be acted upon. This includes
	 * buildings, Castle and Bridge.
	 */
	class BoardElement
	{
	public:
		/**
		 * Constructor.
		 *
		 * @param name Element's name
		 */
		BoardElement(const std::string & name);

		/**
		 * Gets the element's name.
		 *
		 * @return The element's name.
		 */
		virtual const std::string & name() const;

		/**
		 * Activates the board element and performs its effect.
		 */
		virtual void activate();

		/**
		 * Add a worker to the board element.
		 *
		 * @param worker The worker.
		 */
		virtual void add(Player & worker) = 0;

		/**
		 * Whether the current board element already has the given player.
		 *
		 * @param player The player.
		 *
		 * @return Whether the current board element already has the given
		 * player.
		 */
		virtual bool has(const Player & player) const = 0;

		/**
		 * The signals emitted by the element.
		 *
		 * @return The signals emitted by the element.
		 */
		virtual BoardElementSignals & signals() const;

	protected:
		/// Element's name.
		const std::string name_;
		/// Element's signals.
		mutable BoardElementSignals signals_;

		/**
		 * Callback when the board element is activated during the
		 * "Building activation" phase.
		 */
		virtual void onActivate_() = 0;

		/**
		 * Whether the current board element can be activated or not,
		 * globally meaning: is there any worker on the board element?
		 *
		 * @return Can be activated or not.
		 */
		virtual bool canBeActivated_() const = 0;
	};

#include "board-element.hxx"

}

#endif
