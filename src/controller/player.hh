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
# include "resource-map.hh"
# include "../player-signals.hh"
# include "../view/playback.hh"

class Visitor;
class ConstVisitor;

namespace view
{
	class Logger;
}

namespace controller
{
	class BoardElement;

	/** \brief A player is an entity that's playing the game. It can be
	 * either Human or AI.
	 *
	 */
	class Player
	{
	public:
		Player();
		Player(const std::string & name);
		Player(const Player &);

		// Operators.
		bool operator==(const Player & p) const;

		// Accessors.
		void favorBuilding(int);
		int favorBuilding() const;
		void favorResource(int);
		int favorResource() const;
		void favorDenier(int);
		int favorDenier() const;
		void favorPrestige(int);
		int favorPrestige() const;
		const std::string & name() const;
		void name(const std::string name);
		void prestige(int);
		int prestige() const;

		const ResourceMap & resources() const;
		ResourceMap & resources();
		void addResources(const ResourceMap & r);
		void substractResources(const ResourceMap & r);

		const unsigned & workers() const;
		unsigned & workers();
		const unsigned & residences() const;
		unsigned & residences();

		/// Actions.
		int askProvostShift() const;
		unsigned int askWorkerPlacement() const;

		PlayerSignals * signals() const;

			/** @name Visitors accept methods */
		//@{

		void accept(ConstVisitor &) const;
		void accept(Visitor &);

		//@}

		// So the playback change change player's name.
		friend class view::Playback;

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
		mutable PlayerSignals signals_;
	};

}

std::ostream & operator<<(std::ostream &, const controller::Player &);

# include "player.hxx"

#endif // PLAYER_H
