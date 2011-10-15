/**
 * @file   omniscient-building.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun Jan 11 23:34:09 2009
 *
 * @brief  Declaration of the omniscient-building class.
 */

#ifndef OMNISCIENT_BUILDING_HH
# define OMNISCIENT_BUILDING_HH

# include "building.hh"

namespace controller
{
	class GameEngine;

	class OmniscientBuilding : virtual public Building
	{
		protected:
			OmniscientBuilding(GameEngine *ge);

			GameEngine *game_;

		public:
			virtual ~OmniscientBuilding();

			const GameEngine *game() const;
			GameEngine *game();
			void game(GameEngine *);
	};

}
# include "omniscient-building.hxx"

#endif //OMNISCIENT_BUILDING_HH
