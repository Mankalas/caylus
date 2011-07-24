/**
 * @file   console-ui.cc
 * @author  <mankalas@localhost,>
 * @date   Tue Jan 20 21:21:10 2009
 *
 * @brief
 *
 *
 */

#include <limits>
#include "console-ui.hh"
#include "player.hh"
#include "road.hh"

ConsoleUI* ConsoleUI::instance_ = NULL;

ConsoleUI::ConsoleUI()
{}

ConsoleUI* ConsoleUI::inst()
{
  if (instance_ == NULL)
    instance_ = new ConsoleUI();
  return instance_;
}

int ConsoleUI::askChoice(int from, int to) const
{
  int choice = from - 1;

  while (choice < from || choice > to)
  {
    std::cout << "Your choices are : ";
    for (int i = from; i < to; ++i)
      std::cout << i << ", ";
    std::cout << to << "." << std::endl;
    std::cin >> choice;
  }
  return choice;
}

int ConsoleUI::askChoice(std::vector<int>& choices) const
{
  std::vector<int>::const_iterator it = choices.end();
  int choice = -42;

  while (*it != choice)
  {
    std::cout << "Your choices are : ";
    foreach (int i, choices)
      std::cout << i << ", ";
    std::cout << std::endl;
    std::cin >> choice;
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
    }
    else
      it = std::find(choices.begin(), choices.end(), choice);
  }
  return choice;
}

void ConsoleUI::showMessage(std::string message) const
{
  std::cout << " ----- " << message
            << " -----" << std::endl;
}

int ConsoleUI::getInt() const
{
  int result = 0;
  std::cin >> result;
  return result;
}

std::string ConsoleUI::getString() const
{
  std::string result;
  std::cin >> result;
  return result;
}

int ConsoleUI::getBuilding(const Road& road, bool bridge) const
{
  int i = -1;
  std::vector<int> choices = std::vector<int>();

  foreach (BuildingSmartPtr b, road.get())
  {
    ++i;
    if (b == NULL || b->worker() != NULL)
      continue;
    choices.push_back(i);
  }
  choices.push_back(-1);
  if (bridge)
    choices.push_back(34);
  return askChoice(choices);
}

std::string ConsoleUI::askName() const
{
  showMessage("What's the player's name?");
  return getString();
}

int ConsoleUI::askProvostShift() const
{
  showMessage("Provost Shift");
  return askChoice(-3, 3);
}

int ConsoleUI::askWorkerPlacement(const Road& road, bool bridge) const
{
  showMessage("Please place worker");
  return getBuilding(road, bridge);
}

ResourceMap ConsoleUI::askResources(const ResourceMap& choices) const
{
  //int i = choices[Resource::gold];
  showMessage("Your must pick in your ressources");
  return ResourceMap(choices);
}

bool ConsoleUI::askYesNo() const {
  showMessage("Yes / No (1 / 0)");
  return getInt() == 1;
}
