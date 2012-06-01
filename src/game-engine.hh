/**
 * @file   game-engine.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Thu Jan 22 14:56:27 2009
 *
 * @brief  Declaration of the game-engine class.
 */

#ifndef GAMEENGINE_H
# define GAMEENGINE_H

# include <vector>
# include <boost/smart_ptr.hpp>
# include <boost/signal.hpp>
# include <boost/thread.hpp>
# include "board.hh"
# include "logger.hh"
# include "game-signals.hh"

# define PROVOST_INIT_CASE 11
# define BAILIFF_INIT_CASE 11
# define INN_CASE 5

namespace view
{
	class PlayerView;
}

namespace controller
{
	class Building;
	class Player;

	/** Handles the global processus of the game. */
	class GameEngine
	{
	public:

		/** Default constructor. */
		GameEngine(unsigned nb_humans, unsigned nb_ais);

		/** Destructor. */
		~GameEngine();

		void addToCastle(Player *p);

		void build(BuildingSmartPtr &building, Player *p);

		/// Accessors.

		const std::vector<BuildingSmartPtr>& buildings() const;
		std::vector<BuildingSmartPtr>& buildings();

		const std::vector<Player *>& players() const;
		std::vector<Player *>& players();

		const std::vector<Player *>& order() const;
		std::vector<Player *>& order();

		const Board & board() const;
		Board & board();

		const unsigned &nbHumans() const;
		const unsigned &nbAIs() const;

		const unsigned &nbTurnsMax() const;
		unsigned &nbTurnsMax();

		const unsigned & nbTurns() const;

		void operator()();

		const std::vector<BoardElement*> getAvailableBoardElements(const Player * worker) const;

		/*void subscribeView(view::PlayerView *view);
			void subscribeView(view::Logger * log);*/

		void launch();

		GameSignals * signals() const;
		Player * newPlayer();

	private:
		/** Step 1. Calculate the income for each player at the
		 * beginning of each turn. */
		void collectIncome_();

		/** Step 2. Each player places his workers on the
		 * board. */
		void placeWorkers_();

		/** Step 3. Activate the "special" buildings (the ones before the
		 * bridge). */
		void activateSpecialBuildings_();

		/** Step 4. Activate the bridge for each player. */
		void activateBridge_();

		/** Step 5. Activate the buildings on the road (the ones after the
		 * bridge). */
		void activateBuildings_();

		/** Step 6. Activate the castle for each player in it. */
		void activateCastle_();

		/** Step 7. End of turn stuff (changes in the players' order
		 * mostly). */
		void endOfTurn_();

		/** Actions the player can do when placing his worker.
		 *
		 * @param p The player whose turn it is.
		 */
		void playerMove_(Player *p);

		/** Stuff done at the beginning of the turn. Typically refill the
		 * players with the workers, clear the board, etc. */
		void startOfTurn_();

		/** Check if a player can play at this stage of the game, ie does he
		 * have enough money or worker.
		 *
		 * @param p The player to be checked.
		 *
		 * @return Whether the player can play or not.
		 */
		bool canPlayerPlay_(Player *p);

		/** Get the worker cost for a player. This method is not concerned
		 * by the owner of the building the player wants to put his worker
		 * in.
		 *
		 * @param p The player on which the cost depends.
		 *
		 * @return The cost to place a new worker on the board.
		 */
		unsigned getWorkerCost_(const Player *p) const;

		/** The bailiff moves according to its relative position with the
				Prevost.*/
		void moveBailiff_();

		void init_();

		/// The order in which the player are "called".
		std::vector<Player *> order_;
		/// List of the players.
		std::vector<Player *> players_;
		/// List of the views.
		std::vector<view::View *> views_;

		/// List of the buildings left to build.
		std::vector<BuildingSmartPtr> buildings_;

		/// Number of humans currently playing.
		unsigned nb_humans_;
		/// Number of ais currently playing.
		unsigned nb_ais_;
		/// Number of the current turn.
		unsigned nb_turns_;
		/// Max number of turns before the game ends.
		unsigned nb_turns_max_;

		Board board_;

		/// Used to wait until a view subscribes.
		boost::mutex mutex_;

		mutable GameSignals sigs_;

	};

}
/**
 * Display operator.
 *
 * @param o Output stream.
 * @param ge GameEngine object.
 *
 * @return Output stream.
 */
std::ostream &operator<<(std::ostream &o, const GameEngine &ge);

# include "game-engine.hxx"

#endif // GAMEENGINE_H
