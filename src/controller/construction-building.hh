/**
 * @file   construction-building.hh
 * @author  <mankalas@localhost,>
 * @date   Wed Jan  7 14:25:13 2009
 *
 * @brief This file contains ConstructionBuilding class declaration.
 *
 */

#ifndef CONSTRUCTION_BUILDING_HH
# define CONSTRUCTION_BUILDING_HH

# include "omniscient-building.hh"

namespace controller
{

	/** \brief It represents all the buildings that, when activated, allow
	 * the worker to contruct new buildings. The constructor takes one
	 * additional argument: the type of building the worker is allowed to
	 * build.
	 */
	class ConstructionBuilding : public OmniscientBuilding
	{
	public:
		virtual ~ConstructionBuilding();

		const BuildingType construc_type;

	protected:
		ConstructionBuilding(GameEngine * ge, const BuildingType & construc_type);

		boost::signal<unsigned(void)> ask_building_signal_;

	private:
		virtual void onBuild_();

		virtual void onActivate_();
	};

}
#endif //CONSTRUCTION_BUILDING_HH
