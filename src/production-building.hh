/*!
  \file   production-building.hh
  \brief  This file contains ProductionBuilding class declaration.

  \author nicuveo
  \date   2009-01-06
*/

#ifndef PRODUCTION_BUILDING_HH_
# define PRODUCTION_BUILDING_HH_

# include "building.hh"

namespace controller
{

	/** \brief It represents all the buildings that, when activated, give
	 * resources to the worker. The constructor takes two additional
	 * arguments:
	 *   - worker_choices: this is a vector containing the different
	 *     resources the worker can gain while working on the building.
	 *   - owner_choices: this is a vector containing the different
	 *     resources the owner can gain while somebody else work on the
	 *     building.
	 */
	class ProductionBuilding : public virtual Building
	{
		public:
			virtual ~ProductionBuilding();

			const std::vector<ResourceMap> owner_choices_;
			const std::vector<ResourceMap> worker_choices_;

		protected:
			ProductionBuilding (const std::vector<ResourceMap>& wchoice,
			                    const std::vector<ResourceMap>& ochoice);

			virtual void on_activate ();

			boost::signal<unsigned (void)> ask_resource_choice_;
	};

}

#endif /* !PRODUCTION_BUILDING_HH_ */
