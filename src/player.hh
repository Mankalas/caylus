/*!
  \File   Player.h
  \brief  Player declaration

  \author Mankalas
  \date   2008-12-14
*/

#ifndef PLAYER_H
# define PLAYER_H

# include <string>
# include <vector>
# include <map>
# include <iostream>
# include <ostream>
# include "resource-map.hh"
# include "user-interface.hh"
# include "building.hh"

# define NB_WORKERS 1

using namespace std;

class Road;

/** \brief A player is an entity that's playing the game. It can be
 * either Human or AI.
 *
 */
class Player
{
public:
  Player();
  Player(const string& name);
  Player(const Player&);

  bool operator==(const Player& p) const;

  /// Accessors.

  void setFavorBuilding(int);
  int getFavorBuilding() const;
  void setFavorResource(int);
  int getFavorResource() const;
  void setFavorDenier(int);
  int getFavorDenier() const;
  void setFavorPrestige(int);
  int getFavorPrestige() const;
  const std::string& name() const;
  void setPrestige(int);
  int getPrestige() const;
  const ResourceMap& resources() const;
  ResourceMap& resources();
  const unsigned& workers() const;
  unsigned& workers();
  const unsigned& residences() const;
  unsigned& residences();

  virtual BuildingSmartPtr askBuilding(const std::vector<BuildingSmartPtr>&) const = 0;
  virtual std::string askName() const = 0;
  virtual int askProvostShift() const = 0;
  virtual int askWorkerPlacement(const Road&, bool = true) const = 0;
  virtual ResourceMap askResources(const ResourceMap&) const = 0;
  virtual bool askYesNo() const = 0;
  virtual bool askJoustField() const = 0;

protected:

  void _initialize(void);

  int favor_building_;
  int favor_resource_;
  int favor_denier_;
  int favor_prestige_;
  unsigned int workers_;
  string name_;
  int prestige_;
  ResourceMap resources_;
  unsigned int residences_;
};

ostream& operator<<(ostream&, const Player&);

# include "player.hxx"

#endif // PLAYER_H
