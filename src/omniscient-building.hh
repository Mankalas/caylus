/**
 * @file   omniscient-building.hh
 * @author  <mankalas@localhost,>
 * @date   Sun Jan 11 23:34:09 2009
 *
 * @brief
 *
 *
 */

#ifndef OMNISCIENT_BUILDING_HH
# define OMNISCIENT_BUILDING_HH

# include "building.hh"
# include "game-engine.hh"

namespace controller
{

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
