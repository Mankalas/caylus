/**
 * @file   player.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Dec 14 22:03:48 2008
 *
 * @brief  Declaration of the player class.
 */

#ifndef PLAYER_H
# define PLAYER_H

# include <string>
# include <vector>
# include <map>
# include <iostream>
# include <boost/signal.hpp>
# include "resource-map.hh"
# include "board-element.hh"
# include "signals.hh"
# include "logger.hh"

# define NB_WORKERS 1

namespace view
{
	class PlayerView;
	class Logger;
}

namespace controller
{

	/** \brief A player is an entity that's playing the game. It can be
	 * either Human or AI.
	 *
	 */
	class Player
	{
	public:
		Player();
		Player(const std::string &name);
		Player(const Player &);

		// Operators.
		bool operator==(const Player &p) const;

		// Accessors.
		void setFavorBuilding(int);
		int getFavorBuilding() const;
		void setFavorResource(int);
		int getFavorResource() const;
		void setFavorDenier(int);
		int getFavorDenier() const;
		void setFavorPrestige(int);
		int getFavorPrestige() const;
		const std::string &name() const;
		void setName(const std::string name);
		void setPrestige(int);
		int getPrestige() const;

		const ResourceMap &resources() const;
		ResourceMap &resources();
		void addResources(const ResourceMap &r);
		void substractResources(const ResourceMap &r);

		const unsigned &workers() const;
		unsigned &workers();
		const unsigned &residences() const;
		unsigned &residences();

		/// Actions.
		int askProvostShift() const;
		BoardElement* askWorkerPlacement(const std::vector<BoardElement*> & buildings) const;

	private:

		int favor_building_;
		int favor_resource_;
		int favor_denier_;
		int favor_prestige_;
		unsigned int workers_;
		std::string name_;
		int prestige_;
		ResourceMap resources_;
		unsigned int residences_;

		// Signals.
		boost::signal<int (void)> ask_provost_shift_signal_;
		boost::signal<void (const ResourceMap *)> resource_move_;


		/// Submit a list of BoardElements to the player, who must chose
		/// one of them. The elements are not const because the chosen one
		/// will be modified later on the game.
		ask_board_element_signal_t sig_ask_worker_placement_;
	};

}

std::ostream &operator<<(std::ostream &, const controller::Player &);

# include "player.hxx"

#endif // PLAYER_H
