/*!
  \file   ai.h
  \brief  AI declaration

  \author Mankalas
  \date   2008-12-14
*/


#ifndef AI_HH
# define AI_HH

# include "player.hh"
# include "resource-map.hh"

class Road;

class AI : public Player
{
public:

  AI();
  AI(const std::string& name);

  virtual std::string askName() const;
  virtual int askProvostShift() const;
  virtual int askWorkerPlacement(const Road&, bool = true) const;
  virtual ResourceMap askResources(const ResourceMap&) const;
  virtual bool askYesNo() const;
  virtual BuildingSmartPtr askBuilding(const std::vector<BuildingSmartPtr>&) const;
  virtual bool askJoustField() const;
};

#endif
