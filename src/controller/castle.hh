/**
 * @file   castle.hh
 * @author  <mankalas@localhost,>
 * @date   Thu Feb 12 12:54:46 2009
 *
 * @brief
 *
 */

#ifndef CASTLE_HH
# define CASTLE_HH

# include <vector>
# include <boost/signal.hpp>
# include "board-element.hh"

namespace controller
{
	class Player;
	class ResourceMap;

	/** A CastlePart is one of the following element of the castle :
	 * dungeon, walls, towers. Due to their identical behaviour, they are
	 * generalized with this class. It handles all the counting (prestige,
	 * penalty, etc) plus the scoring (when the part is over).
	 */
	class CastlePart
	{
	public:
		/** Constructor. Initialize the attributes.
		 *
		 * @param c Capacity (ie number of houses a player can build).
		 * @param p Prestige points earned when a house is built.
		 * @param s The ratio of favors gained according to the houses built
		 * when scoring.
		 */
		CastlePart(unsigned c, unsigned p,
		           std::vector<std::pair<unsigned, int> > s);

		/** To score is to "close" a part of the castle to build the next
		 * one. A score occurs when the current part is entirely built or
		 * when the bailiff reaches a certain case of the board.
		 *
		 * @param players The players of the game.
		 */
		void score(std::vector<Player *>& players);

		/// Accessors

		const std::vector<Player *>& houses() const;
		std::vector<Player *>& houses();

		const unsigned & prestige() const;
		unsigned & prestige();

		const unsigned & capacity() const;
		unsigned & capacity();

		const std::vector<std::pair<unsigned, int> >& scoreFavor() const;
		std::vector<std::pair<unsigned, int> >& scoreFavor() ;

	protected:
		/// The maximum number of houses.
		unsigned capacity_;
		/// How many prestige points earned when a house is built.
		unsigned prestige_;
		/// The ratio of favors gained according to the houses built when
		/// scoring.
		std::vector<std::pair<unsigned, int> > score_favor_;
		/// The houses built.
		std::vector<Player *> houses_;
	};

	class Dungeon : public CastlePart
	{
	public:
		Dungeon();
	};

	class Towers : public CastlePart
	{
	public:
		Towers();
	};

	class Walls : public CastlePart
	{
	public:
		Walls();
	};

	/** The Castle itself. Contains the players who placed a worker in the
	 * Castle plus the three Castle Parts (dungeon, walls, towers).
	 */
	class Castle : public BoardElement
	{
	public:
		/** Constructor. */
		Castle();
		~Castle();

		/** Add a player to the castle. Check the player's presence.
		 *
		 * @param p The player to add.
		 */
		virtual void add(Player & p);

		/**
		 * Whether a player has already a worker in the caslte or not.
		 *
		 * @param p The player.
		 *
		 * @return True or false.
		 */
		bool has(const Player * p) const;

		/** Clear the Castle of the workers. */
		void clear();

		/** General scoring. Call the score of the active part and
		 * "increment" it. */
		void score(std::vector<Player *>& players);

		/** Check if all the houses in the active part are built, ie do we
		 * have to score?
		 *
		 * @return Whether the active part is completed or not.
		 */
		bool isActivePartComplete() const;

		/// Accessors.

		const std::vector<Player *>& players() const;
		std::vector<Player *>& players();

		const CastlePart * dungeon() const;
		CastlePart * dungeon();

		const CastlePart * walls() const;
		CastlePart * walls();

		const CastlePart * towers() const;
		CastlePart * towers();

		/// This is the 'case number' of the castle, used by an active
		/// view to communicate the player's choice.
		static const unsigned int CASE_NUMBER;

	private:
		/// The players' workers.
		std::vector<Player *> players_;
		/// The three parts of the Castle.
		std::vector<CastlePart *> parts_;
		/// The index of the active part (more practical to increment).
		unsigned part_index_;
		/// The active part of the Castle.
		CastlePart * active_part_;
		boost::signal<ResourceMap * (void)> ask_payment_;
		///
		//unsigned prestige_;
		/// The greatest number of houses built during this activation.
		unsigned nb_build_;
		/// The player who built the greatest number of houses.
		Player * favored_;

		/** Check the resources of a player to determine if he can build a
		 * house.
		 *
		 * @param p The player who's building.
		 *
		 * @return Whether the player can afford a houses or not.
		 */
		bool checkResources_(const Player * p) const;

		/** To ease the choice of the resources the player will use to build
		 * a house, this method generates a vector with all the possibles
		 * pairs made from the player's usable resources.
		 *
		 * @param p The player who's building.
		 *
		 * @return The possible resources combinations.
		 */
		/*std::vector<ResourceMap*>
			_createResourcesVector(const Player* p) const;*/

		/** Actually build a house.
		 *
		 * @param p The player who's building.
		 * @param resources The two resources used to build the house.
		 */
		void build_(Player * p, ResourceMap * resources);

		/** Resolve the Castle's activation. */
		virtual void onActivate_();

		virtual bool canBeActivated_() const;
	};

}

std::ostream & operator<<(std::ostream & o, const controller::Castle & ge);

# include "castle.hxx"

#endif //CASTLE_HH
