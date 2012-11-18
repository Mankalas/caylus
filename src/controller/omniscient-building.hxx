/**
 * @file   omniscient-building.hxx
 * @author  <mankalas@localhost,>
 * @date   Sun Jan 11 23:37:15 2009
 *
 * @brief
 *
 *
 */

#ifndef OMNISCIENT_BUILDING_HXX
# define OMNISCIENT_BUILDING_HXX

# include "omniscient-building.hh"

inline const GameEngine *
OmniscientBuilding::game() const
{
	return game_engine_;
}

inline GameEngine *
OmniscientBuilding::game()
{
	return game_engine_;
}

inline void
OmniscientBuilding::game(GameEngine * game_engine)
{
	game_engine_ = game_engine;
}

#endif //OMNISCIENT_BUILDING_HXX
