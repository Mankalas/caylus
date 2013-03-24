/**
 * @file   building.hh
 * @author Nicuvëo <crucuny@gmail.com>
 * @date   June 01 19:19:31 2009
 *
 * @brief  Declaration of the building class.
 */

#ifndef BUILDING_HH_
# define BUILDING_HH_

# include <boost/smart_ptr.hpp>
# include "resource-map.hh"
# include "building-type.hh"
# include "board-element.hh"

class Visitor;
class ConstVisitor;

namespace controller
{
	class Player;

	/** \brief  It represents a building (obviously).
	 *
	 * The constructor is protected in order to force the user to declare
	 * buildings as derived classes.
	 */
	class Building : public BoardElement
	{
	public:
		/**
		 * Empty destructor.
		 */
		virtual ~Building();

		/**
		 * Construction of the current building by a player. The
		 * construction costs are deducted from the player's
		 * resources. If the player does not have enough resources, a
		 * NotEnoughResources exception is thrown (this case should
		 * not happen though: the player should only be given a
		 * construction choice with buildings he can builds with his
		 * current resources).
		 *
		 * @param current The player that builds the building.
		 */
		void build(Player & current);

		/**
		 * Callback when a player places a worker on the
		 * building.
		 *
		 * Checks if the worker can be placed (throws a
		 * OccupiedBuildingEx if not), checks if the building can
		 * receive a worker (ie., it's not a Residence, nor a Prestige
		 * building. Throws a UnactivableBuildingEx if so).
		 *
		 * If everything is OK, gives a Prestige point to the
		 * building's owner (if he is different from the worker's
		 * player), signals that a worker has been placed here and
		 * decrease the player's workers count.
		 *
		 * @param current The player who placed a worker.
		 */
		virtual void placeWorker(Player & current);

		/**
		 * Activates the building. Checks if the building can be
		 * activated (if it has a worker), performs the Building's
		 * effect and unset the worker.
		 */
		virtual void activate();

		/**
		 * Removes the worker from the building, incrementing the
		 * worker's player workers count.
		 */
		virtual void removeWorker();

		/**
		 * Delete ownership, removes the Building from the Road,
		 * replaces it in the to-be-constructed buildings pool.
		 */
		void demolish();

		/** @name Accessors. */
		//@{

		const BuildingType & type() const;
		const ResourceMap & gain() const;
		const std::vector<ResourceMap>& cost() const;
		const Player * owner() const;
		const Player * worker() const;
		virtual bool has(const Player *) const;

		//@}

		/** @name Visitors accept methods. */
		//@{

		virtual void accept(ConstVisitor &) const;
		virtual void accept(Visitor &);

		//@}

	protected:
		/**
		 * Constructor.
		 *
		 * @param name Building's name.
		 * @param type Building's type
		 * @param cost Construction costs. If the cost is represented
		 * as a vector, it is because two buildings in this game have
		 * a variable cost (the "white" cube) ; the cost is therefore
		 * represented as a list of possibilities. For all the other
		 * buildings there is only one item in the vector.
		 * @param gain Construction gain.
		 */
		Building(const std::string & name,
		         const BuildingType & type,
		         const std::vector<ResourceMap>& cost,
		         const ResourceMap & gain);

		/// Building's type.
		const BuildingType type_;
		/// Construction gain.
		const ResourceMap gain_;
		/// Building costs possibilities.
		const std::vector<ResourceMap> cost_;
		/// Building's owner (the players who built it).
		Player * owner_;
		/// Current worker (some buildings can have more than one).
		Player * worker_;

		/**
		 * Specialized actions performed by the building when built.
		 */
		virtual void onBuild();

		/**
		 * Specialized actions performed by the building when activated.
		 */
		virtual void onActivate();

		/**
		 * Specialized actions performed by the building when demolished.
		 */
		virtual void onDemolish();
	};

}

std::ostream & operator<<(std::ostream &, const controller::Building &);

typedef boost::shared_ptr<controller::Building> BuildingSmartPtr;

# include "building.hxx"

#endif /* !BUILDING_HH_ */
