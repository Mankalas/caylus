/**
 * @file   bridge.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sat Oct 15 21:47:48 2011
 *
 * @brief  Declaration of the bridge class.
 */

#ifndef BRIDGE_HH
# define BRIDGE_HH

# include <vector>
# include "board-element.hh"

namespace controller
{
	class Player;
	class Board;

	/**
	 * The board's Bridge.
	 */
	class Bridge : public BoardElement
	{
	public :

		/**
		 * Constructor.
		 *
		 * @param board The game's Board (in order to move the Provost).
		 */
		Bridge(Board & board);

		/**
		 * Clears the bridge of all markers.
		 */
		void clear();

		/** Add a player to the bridge. Checks whether he is the first and
		 * give him the bonus denier accordingly.
		 *
		 * @param p The player to add.
		 */
		void add(Player & p);

		// See BoardElement.
		virtual bool has(const Player & p) const;

		/** @name Accessors. */
		// @{

		const std::vector<Player *>& players() const;
		std::vector<Player *>& players();

		// @}

		/// This is the 'case number' of the bridge, used by an active
		/// view to communicate the player's choice.
		static const unsigned int CASE_NUMBER = 69;

	private:
		/// Players' markers.
		std::vector<Player *> players_;
		/// The game's Board.
		Board & board_;

		// See BoardElement.
		virtual void onActivate_();

		// See BoardElement.
		virtual bool canBeActivated_() const;
	};
}

# include "bridge.hxx"

#endif
