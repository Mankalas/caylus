#include "ai.hh"
#include "road.hh"

using namespace std;
using namespace view;
using namespace controller;

AI::AI(GameEngine *ge)
  :View(ge)
{
}

string AI::askName() const
{
  return "toto";
}

int AI::askWorkerPlacement() const {
  /*if ((workers_ == 0 || resources_[Resource::denier] == 0) && bridge)
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
      }*/
  return 5;
}

unsigned AI::askResourceChoice(/*const ResourceMap& choices*/) const {
  return 3;
}

bool AI::askYesNo() const {
  return true;
				  }

unsigned AI::askBuilding(/*const vector<BuildingSmartPtr>& building_choices*/) const
{
  return 1;
}

bool AI::askJoustField() const {
  return false;
}

int AI::askProvostShift() const
{
	return 3;
}
