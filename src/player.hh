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

# define NB_WORKERS 1

namespace view
{
	class View;
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
		void setPrestige(int);
		int getPrestige() const;
		const ResourceMap &resources() const;
		ResourceMap &resources();
		const unsigned &workers() const;
		unsigned &workers();
		const unsigned &residences() const;
		unsigned &residences();
		const view::View *view() const;
		view::View *view();
		void setView(view::View *view);

		/// Actions.
		int askProvostShift() const;
		BoardElement* askWorkerPlacement(const std::vector<BoardElement*> buildings) const;

	private:

		void _initialize(void);

		int favor_building_;
		int favor_resource_;
		int favor_denier_;
		int favor_prestige_;
		unsigned int workers_;
		std::string name_;
		int prestige_;
		ResourceMap resources_;
		unsigned int residences_;
		view::View *view_;

		// Signals.
		boost::signal<int (void)> ask_provost_shift_signal_;
		boost::signal<BoardElement* (const std::vector<BoardElement*>)> ask_worker_placement_signal_;
	};

}

std::ostream &operator<<(std::ostream &, const controller::Player &);

# include "player.hxx"

#endif // PLAYER_H
