#include "human.hh"
#include "console-ui.hh"

Human::Human(){}

Human::Human(const std::string& name):
  Player(name){
  ConsoleUI* u = ConsoleUI::inst();
  this->user_interface_ = u;
}

std::string Human::askName() const
{
  user_interface_->showMessage("What name?");
  return user_interface_->getString();
}

int Human::askProvostShift() const {
  return 0;
}

int Human::askWorkerPlacement(const Road& road, bool bridge) const {
  return user_interface_->askWorkerPlacement(road, bridge);
}

ResourceMap Human::askResources(const ResourceMap& choices) const {
  return ResourceMap(choices);
}

bool Human::askYesNo() const {
  return true;
}

BuildingSmartPtr Human::askBuilding(const std::vector<BuildingSmartPtr>& buildings_list) const {

  return buildings_list[0];
}

bool Human::askJoustField() const {
  return true;
}
