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
# include "building.hh"
# include "player.hh"
# include "road.hh"
# include "castle.hh"
# include "bridge.hh"

# define PROVOST_INIT_CASE 11
# define BAILIFF_INIT_CASE 11
# define INN_CASE 5

namespace view
{
	class Human;
}

namespace controller
{
	/** Handles the global processus of the game. */
	class GameEngine
	{
	public:

		typedef boost::signals::connection connection_t;

		typedef boost::signal<unsigned (unsigned)> nb_humans_signal_t;
		typedef boost::signal<unsigned (unsigned, unsigned)> nb_ais_signal_t;
		typedef boost::signal<void (void)> board_updated_signal_t;

	public:

		void connectNbHumansSignal(nb_humans_signal_t::slot_function_type subscriber);
		void connectNbAIsSignal(nb_ais_signal_t::slot_function_type subscriber);
		void connectBoardUpdatedSignal(board_updated_signal_t::slot_function_type subscriber);

		void subscribeView(view::Human *human);

		/** Default constructor. */
		GameEngine();

		GameEngine(unsigned nb_humans, unsigned nb_ais);

		/** Destructor. */
		~GameEngine();

		/** Initialize the current object. Used for code factorization,
		 * shared by the constructors. */
		void initialize();

		/** Step 1. Calculate the income for each player at the
		 * beginning of each turn. */
		void collectIncome();

		/** Step 2. Each player places his workers on the
		 * board. */
		void placeWorkers();

		/** Step 3. Activate the "special" buildings (the ones before the
		 * bridge). */
		void activateSpecialBuildings();

		/** Step 4. Activate the bridge for each player. */
		void activateBridge();

		/** Step 5. Activate the buildings on the road (the ones after the
		 * bridge). */
		void activateBuildings();

		/** Step 6. Activate the castle for each player in it. */
		void activateCastle();

		/** Step 7. End of turn stuff (changes in the players' order
		 * mostly). */
		void endOfTurn();

		bool addToCastle(Player *p);

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

		boost::mutex &mutex();
		boost::condition_variable *waitingPlayers();
		boost::condition_variable *waitingViews();
		boost::condition_variable *disconnectViews();
		void operator()();

	private:
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
		unsigned nb_humans_;
		unsigned nb_ais_;

		///
		std::vector<view::View *> views_;
		///
		boost::mutex mutex_;
		///
		nb_humans_signal_t ask_nb_humans_;
		///
		nb_ais_signal_t ask_nb_ais_;
		///
		board_updated_signal_t board_updated_;
		///
		boost::condition_variable game_start_;
		boost::condition_variable waiting_players_;


		/** Actions the player can do when placing his worker.
		 *
		 * @param p The player whose turn it is.
		 */
		void _playerMove(Player *p);

		/** Stuff done at the beginning of the turn. Typically refill the
		 * players with the workers, clear the board, etc. */
		void _startOfTurn();

		/** Check if a player can play at this stage of the game, ie does he
		 * have enough money or worker.
		 *
		 * @param p The player to be checked.
		 *
		 * @return Whether the player can play or not.
		 */
		bool _canPlayerPlay(Player *p);

		/** Get the worker cost for a player. This method is not concerned
		 * by the owner of the building the player wants to put his worker
		 * in.
		 *
		 * @param p The player on which the cost depends.
		 *
		 * @return The cost to place a new worker on the board.
		 */
		unsigned _getWorkerCost(const Player *p) const;

		/** The bailiff moves according to its relative position with the
				Prevost.*/
		void _moveBailiff();
		void _run();
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
