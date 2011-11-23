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
# include "road.hh"
# include "castle.hh"
# include "bridge.hh"
# include "signals.hh"
# include "logger.hh"

# define PROVOST_INIT_CASE 11
# define BAILIFF_INIT_CASE 11
# define INN_CASE 5

namespace view
{
	class Human;
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

		const Road &road() const;
		Road &road();

		const std::vector<Player *>& players() const;
		std::vector<Player *>& players();

		const std::vector<Player *>& order() const;
		std::vector<Player *>& order();

		const Bridge& bridge() const;
		Bridge& bridge();

		const Castle &castle() const;
		Castle &castle();

		const unsigned &bailiff() const;
		unsigned &bailiff();

		const unsigned &provost() const;
		unsigned &provost();

		const unsigned &nbHumans() const;
		const unsigned &nbAIs() const;

		const unsigned &nbTurnsMax() const;
		unsigned &nbTurnsMax();

		const unsigned & nbTurns() const;

		boost::mutex &mutex();

		void operator()();

		const std::vector<BoardElement*> getAvailableBoardElements(const Player * worker) const;

		void subscribeView(view::Human *human);
		void subscribeView(Logger * log);


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

		/// The order in which the player are "called".
		std::vector<Player *> order_;
		/// List of the players.
		std::vector<Player *> players_;
		/// List of the buildings left to build.
		std::vector<BuildingSmartPtr> buildings_;
		/// The "road" on the board of the game.
		Road road_;
		/// List of players at the castle.
		Castle castle_;
		/// Bridge
		Bridge bridge_;
		/// Road's index of the building the provost is in.
		unsigned provost_;
		/// Road's index of the building the bailiff is in.
		unsigned bailiff_;
					/// Number of humans currently playing.
		unsigned nb_humans_;
					/// Number of ais currently playing.
		unsigned nb_ais_;
					/// Number of the current turn.
		unsigned nb_turns_;
					/// Max number of turns before the game ends.
		unsigned nb_turns_max_;

		/// Used to wait until a view subscribes.
		boost::mutex mutex_;

		struct Signals_
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
			v_v_signal_t new_turn;
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

			/* Errors, messages and log. */

			/// Player is already on the bridge.
			v_cp_signal_t already_on_bridge;
			/// Not enough deniers to play.
			v_cp_signal_t not_enough_deniers;
			/// No worker left.
			v_cp_signal_t no_worker_left;
			/// A player has been added to the bridge.
			v_cp_signal_t added_to_bridge;
			/// Get the board element a player has chosen from a list.
			player_choice_signal_t player_has_chosen;
			/// Get the choices a player has between several BoardElements.
			player_choices_signal_t player_choices;

		};

		Signals_ sigs_;

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
