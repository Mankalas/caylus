/*!
  \file   road.hh
  \brief  Declaration of Road.

  \author nicuveo
  \date   2009-01-06
*/

#ifndef ROAD_HH_
# define ROAD_HH_

# include <vector>
# include "building.hh"

class GameEngine;

class Road
{
  public:
    Road (GameEngine* ge);

    const std::vector<BuildingSmartPtr>& get () const;

    BuildingSmartPtr& operator [] (unsigned i);
    const BuildingSmartPtr& operator [] (unsigned i) const;

    BuildingSmartPtr& operator [] (const std::string&);
    const BuildingSmartPtr& operator [] (const std::string&) const;

    BuildingSmartPtr build (BuildingSmartPtr bd);
    void clear();

  private:
    std::vector<BuildingSmartPtr> buildings_;
    /// Because of the GoldMine, we cannot use buildings_.push_back() to
    /// add a new building. Instead, we use this index to insert the new
    /// building into the correct slot.
    unsigned free_slot_;
};

std::ostream& operator<<(std::ostream&, const Road&);

# include "road.hxx"

#endif /* !ROAD_HH_ */
