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

	class Bridge : public BoardElement
	{
	public :

		Bridge(Board & board);

		void clear();

		/** Add a player to the bridge. Checks whether he is the first and
		 * give him the bonus denier accordingly.
		 *
		 * @param p The player to add.
		 */
		void add(Player * p);

		/**
		 * Check whether a player is already on the bridge or not.
		 *
		 * @param p The player to check.
		 *
		 * @return
		 */
		bool has(const Player * p) const;

		// Accessors.
		const std::vector<Player *>& players() const;
		std::vector<Player *>& players();

		/// This is the 'case number' of the bridge, used by an active
		/// view to communicate the player's choice.
		static const unsigned int CASE_NUMBER = 69;

	private:
		std::vector<Player *> players_;
		Board & board_;

		virtual void onActivate_();

		virtual bool canBeActivated_() const;
	};
}

# include "bridge.hxx"

#endif
