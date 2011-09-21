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

using namespace std;

ConsoleUI::ConsoleUI()
{}

int ConsoleUI::askChoice(int from, int to) const
{
  int choice = from - 1;

  while (choice < from || choice > to)
  {
    cout << "Your choices are : ";
    for (int i = from; i < to; ++i)
      cout << i << ", ";
    cout << to << "." << endl;
    cin >> choice;
  }
  return choice;
}

int ConsoleUI::askChoice(vector<int>& choices) const
{
  vector<int>::const_iterator it = choices.end();
  int choice = -42;

  while (*it != choice)
  {
    cout << "Your choices are : ";
    foreach (int i, choices)
      cout << i << ", ";
    cout << endl;
    cin >> choice;
    if (!cin)
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    else
      it = find(choices.begin(), choices.end(), choice);
  }
  return choice;
}

void ConsoleUI::showMessage(string message) const
{
  cout << " ----- " << message
            << " -----" << endl;
}

int ConsoleUI::getInt() const
{
  int result = 0;
  cin >> result;
  return result;
}

string ConsoleUI::getString() const
{
  string result;
  cin >> result;
  return result;
}

/*int ConsoleUI::getBuilding(const Road& road, bool bridge) const
{
  int i = -1;
  vector<int> choices = vector<int>();

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
  }*/

string ConsoleUI::askName() const
{
  showMessage("What's the player's name?");
  return getString();
}

int ConsoleUI::askProvostShift() const
{
  showMessage("Provost Shift");
  return askChoice(-3, 3);
}

/*int ConsoleUI::askWorkerPlacement(const Road& road, bool bridge) const
{
  showMessage("Please place worker");
  return getBuilding(road, bridge);
  }

ResourceMap ConsoleUI::askResources(const ResourceMap& choices) const
{
  //int i = choices[Resource::gold];
  showMessage("Your must pick in your ressources");
  return ResourceMap(choices);
  }*/

bool ConsoleUI::askYesNo() const {
  showMessage("Yes / No (1 / 0)");
  return getInt() == 1;
}
