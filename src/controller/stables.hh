/**
 * @file   stables.hh
 * @author  Nicuveo
 * @date   Fri Jan 23 13:46:32 2009
 *
 * @brief  Declaration of the Stables.
 *
 */

#ifndef STABLES_HH_
# define STABLES_HH_

# include "omniscient-building.hh"

class Visitor;
class ConstVisitor;

namespace controller
{

	/**
	 * Stables building. Allows the players to change their play order
	 * in the game. Can holds at most 3 workers.
	 */
	class Stables : public OmniscientBuilding
	{
	public:
		/**
		 * Constructor.
		 *
		 * @param ge The Game Engine.
		 */
		Stables(GameEngine * ge);

		virtual void removeWorker();

		const std::vector<Player *> players() const;

		/** @name Visitors accept methods */
		//@{

		virtual void accept(ConstVisitor &) const;
		virtual void accept(Visitor &);

		//@}

	private:
		std::vector<Player *> players_;

		virtual void onAdd_(Player &);
		virtual bool has_(const Player &) const;
		virtual void onActivate_();
		virtual bool canBePlacedOn_() const;
		virtual bool isFull_() const;

	};

}

#endif /* !STABLES_HH_ */
