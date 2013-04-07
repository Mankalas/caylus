/**
 * @file   player.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Dec 14 22:03:48 2008
 *
 * @brief  Declaration of the player class.
 */

#ifndef PLAYER_HH
# define PLAYER_HH

# include <string>
# include <iostream>
# include "resource-map.hh"
# include "../signals.hh"
# include "../view/playback.hh"

class Visitor;
class ConstVisitor;

namespace controller
{
	class BoardElement;

	struct PlayerSignals
	{
		/// Ask for an integer for the Provost shift.
		i_v_signal_t ask_provost_shift;
		/// Ask for a BoardElement from a list.
		u_v_signal_t ask_board_element;
		/// Ask for a Resource from a list.
		resource_choice_signal_t ask_resource;
		/// Ask whether the player wants to removes his worker from the
		/// Inn.
		b_v_signal_t ask_inn_removal;
		/// Ask a building to construct from the buildings list.
		u_v_signal_t ask_building_to_construct;

		/// Resource the player gains.
		resource_move_signal_t gain_resource;
		/// Resource the player lose.
		resource_move_signal_t lose_resource;
	};

	/** \brief A player is the entity that's playing the game. It can
	 * be controlled by a Human, an AI, a pre-recorded set of moves,
	 * etc.
	 */
	class Player
	{
	public:
		Player(unsigned int max_worker);
		Player(const std::string & name, unsigned int max_worker);
		Player(const Player &);

		/** @name Accessors. */
		// @{

		int favorBuilding() const;
		int favorResource() const;
		int favorDenier() const;
		int favorPrestige() const;
		int prestige() const;

		const std::string & name() const;
		void setName(const std::string name);

		unsigned workers() const;
		void setWorkers(unsigned int);
		unsigned residences() const;
		const ResourceMap & resources() const;
		PlayerSignals & signals() const;

		// @}

		/** @name Operators. */
		// @{

		bool operator==(const Player & p) const;
		void addResources(const ResourceMap & r);
		void substractResources(const ResourceMap & r);
		void decrementWorkers();
		void incrementWorkers();
		void increaseIncome(unsigned int);
		void decreaseIncome(unsigned int);

		// @}

		/** @name Interactions. */
		// @{

		int askProvostShift() const;
		unsigned int askBoardElement() const;
		ResourceMap askResource(const std::vector<ResourceMap> & choice) const;
		bool askInnRemoval() const;

		// @}

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

#endif // PLAYER_HH
