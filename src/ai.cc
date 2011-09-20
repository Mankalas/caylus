#include "ai.hh"
#include "road.hh"

AI::AI(){}

AI::AI(const std::string& name):
  Player(name){}

std::string AI::askName() const
{
  return "toto";
}

int AI::askProvostShift() const {
  return 0;
}

int AI::askWorkerPlacement(const Road& road, bool bridge) const {
  if ((workers_ == 0 || resources_[Resource::denier] == 0) && bridge)
    {
      return 34;
    }
  int i = 0;
  foreach (const BuildingSmartPtr& building, road.get())
    {
      if (building->worker() == NULL)
	{
	  return i;
	}
      i++;
    }
  return 34;
}

ResourceMap AI::askResources(const ResourceMap& choices) const {
  return ResourceMap(choices);
}

bool AI::askYesNo() const {
  return true;
}

BuildingSmartPtr AI::askBuilding(const std::vector<BuildingSmartPtr>& building_choices) const {
  return building_choices[0];
}

bool AI::askJoustField() const {
  return false;
}

int AI::askProvostShift() const
{
	return 3;
}

int AI::askWorkerPlacement() const
{
	return 2;
}

unsigned AI::askBuilding() const
{
	return 1;
}

unsigned AI::askResourceChoice() const
{
	return 0;
}
