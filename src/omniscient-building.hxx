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

inline const GameEngine*
OmniscientBuilding::game() const
{
  return game_;
}

inline GameEngine*
OmniscientBuilding::game()
{
  return game_;
}

inline void
OmniscientBuilding::game(GameEngine* g)
{
  game_ = g;
}

#endif //OMNISCIENT_BUILDING_HXX
