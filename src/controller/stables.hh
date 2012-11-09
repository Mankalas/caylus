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

namespace controller
{

	class Stables : public OmniscientBuilding
	{
		public:
			Stables(GameEngine * ge);

			virtual void on_activate(void);
			virtual void worker_set(Player &);
			virtual void worker_unset();

			virtual bool has(const Player *) const;

		private:
			std::vector<Player *> players_;
	};

}

#endif /* !STABLES_HH_ */
