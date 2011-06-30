/*!
  \file   human.h
  \brief  Human declaration

  \author Mankalas
  \date   2008-12-14
*/


#ifndef HUMAN_HH
# define HUMAN_HH

# include "player.hh"
# include "resource-map.hh"
# include "user-interface.hh"

class Road;

class Human : public Player
{
public:

  Human();
  Human(const std::string& name);

  virtual BuildingSmartPtr askBuilding(const std::vector<BuildingSmartPtr>&) const;
  virtual std::string askName() const;
  virtual int askProvostShift() const;
  virtual int askWorkerPlacement(const Road&, bool) const;
  virtual ResourceMap askResources(const ResourceMap&) const;
  virtual bool askYesNo() const;
  virtual bool askJoustField() const;
  const UserInterface* userInterface() const;
  UserInterface* userInterface();

private:
  UserInterface* user_interface_;
};

# include "human.hxx"

#endif
