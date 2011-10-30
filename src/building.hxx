/*!
  \file   building.hxx
  \brief  Inline implementations for Building

  \author nicuveo
  \date   2009-01-06
*/

#ifndef BUILDING_HXX_
# define BUILDING_HXX_

# include "building.hh"
# include "player.hh"

inline const std::string&
Building::name() const
{
  return name_;
}

inline const BuildingType&
Building::type() const
{
  return type_;
}

inline const ResourceMap&
Building::gain() const
{
  return gain_;
}

inline const std::vector<ResourceMap>&
Building::cost() const
{
  return cost_;
}

inline Player*
Building::owner()
{
  return owner_;
}

inline const Player*
Building::owner() const
{
  return owner_;
}

inline Player*
Building::worker()
{
  return worker_;
}

inline const Player*
Building::worker() const
{
  return worker_;
}

inline void
Building::worker(Player* p)
{
  worker_ = p;
}

#endif /* !BUILDING_HXX_ */
