/*!
  \file   building.hh
  \brief  This file contains Building class declaration.

  \author nicuveo
  \date   2009-01-06
*/

#ifndef BUILDING_HH_
# define BUILDING_HH_

# include <boost/smart_ptr.hpp>
# include "resource-map.hh"
# include "building-type.hh"
# include "board-element.hh"

namespace controller
{
	class Player;

	/** \brief  It represents a building (obviously).
	 *
	 * Every fixed attribute is stored as a public const value and
	 * initialized in the constructor.  Those three attributes are:
	 *      - its type (please see building-type.hh),
	 *      - its cost, which is represented as a vector of ResourceMap,
	 *      - the gain it gives to the player that builds it.
	 *
	 * If the cost is represented as a vector, it is because two buildings
	 * in this game have a variable cost (the "white" cube) ; the cost is
	 * therefore represented as a list of possibilities. For all the other
	 * buildings there is only one item in the vector.
	 *
	 * The constructor is protected in order to force the user to declare
	 * buildings as derived classes.
	 *
	 */
	class Building : public BoardElement
	{
		public:
			virtual ~Building();
			void build(Player * current = 0);
			virtual void worker_set(Player & current);
			void activate();
			virtual void worker_unset();
			void demolish();
			virtual bool isBuilding() const;

			// Accessors.
			const BuildingType & type() const;
			const ResourceMap & gain() const;
			const std::vector<ResourceMap>& cost() const;

			Player * owner();
			const Player * owner() const;

			Player * worker();
			const Player * worker() const;
			void worker(Player *);

			virtual bool has(const Player *) const;

		protected:
			Building(const std::string & name,
			         const BuildingType & type,
			         const std::vector<ResourceMap>& cost,
			         const ResourceMap & gain);

			const BuildingType type_;
			const ResourceMap gain_;
			const std::vector<ResourceMap> cost_;
			Player * owner_;
			Player * worker_;

			virtual void on_build();
			virtual void on_activate();
			virtual void on_demolish();
	};

}
std::ostream & operator<<(std::ostream &, const controller::Building &);

typedef boost::shared_ptr<controller::Building> BuildingSmartPtr;

# include "building.hxx"

#endif /* !BUILDING_HH_ */
