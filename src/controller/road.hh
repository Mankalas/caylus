/**
 * @file   road.hh
 * @date   Tue Jan 06 15:15:57 2009
 * @author Nicuvëo
 * @brief  Declaration of the road class.
 */

#ifndef ROAD_HH_
# define ROAD_HH_

# include <vector>
# include "building.hh"

class Visitor;
class ConstVisitor;

namespace controller
{

	class GameEngine;

	/**
	 * The road represents the set of cases on which buildings are
	 * built and manages the placement of a newly built building.
	 *
	 */
	class Road
	{
	public:
		/**
		 * Constructor.
		 *
		 * @param ge The GameEngine.
		 */
		Road(GameEngine * ge);

		/**
		 * Get the vector of the built buildings.
		 * @return Buildings vector.
		 */
		const std::vector<BuildingSmartPtr>& get() const;

		/**
		 * Return the building built at case i
		 * @param i The index of the case.
		 *
		 * @return The building on this case.
		 */
		BuildingSmartPtr & operator [](unsigned i);
		const BuildingSmartPtr & operator [](unsigned i) const;

		BuildingSmartPtr & operator [](const std::string &);
		const BuildingSmartPtr & operator [](const std::string &) const;

		/** Build a building on the road.
		 *
		 * @param bd The building to be built.
		 */
		void build(BuildingSmartPtr bd);

		/**
		 * Clear the road of all workers.
		 */
		void clearWorkers();

		/**
		 * Get a list of buildings that a given player can pick to place his
		 * worker.
		 *
		 * @param worker The player who is to place his worker.
		 *
		 * @return The available buildings
		 */
		std::vector<BoardElement *> getAvailableBuildings(const Player * worker) const;

		/** @name Visitors accept methods */
		//@{

		void accept(const ConstVisitor &) const;
		void accept(Visitor &);

		//@}

	private:
		/**
		 * List of all the buildings built on the road.
		 */
		std::vector<BuildingSmartPtr> buildings_;
		/**
		 * Because of the GoldMine, we cannot use buildings_.push_back()
		 * to add a new building. Instead, we use this index to insert the
		 * new building into the correct slot.
		 */
		unsigned free_slot_;
	};

}

std::ostream & operator<<(std::ostream &, const Road &);

# include "road.hxx"

#endif /* !ROAD_HH_ */
