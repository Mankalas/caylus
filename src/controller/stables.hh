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

	class Stables : public OmniscientBuilding
	{
	public:
		Stables(GameEngine * ge);

		virtual void onActivate(void);
		virtual void placeWorker(Player &);
		virtual void removeWorker();

		virtual bool has(const Player *) const;
		const std::vector<Player *> players() const;

		/** @name Visitors accept methods */
		//@{

		virtual void accept(ConstVisitor &) const;
		virtual void accept(Visitor &);

		//@}

	private:
		std::vector<Player *> players_;
	};

}

#endif /* !STABLES_HH_ */
