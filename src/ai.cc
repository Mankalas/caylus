#include "ai.hh"
#include "game-engine.hh"
#include "logger.hh"
#include "building.hh"
#include <time.h>
#include <stdlib.h>

using namespace std;
using namespace view;
using namespace controller;

AI::AI(GameEngine *ge)
	: View(ge)
{
	srand(time(NULL));
}

string AI::askName() const
{
	return "toto";
}

BoardElement*
AI::askWorkerPlacement(const std::vector<BoardElement *> & buildings) const
{
	int choice = rand() % buildings.size();
	Logger::instance()->log(Logger::instance()->to_string<int>(choice));
	return buildings[choice];
}

unsigned AI::askResourceChoice(/*const ResourceMap& choices*/) const
{
	return 3;
}

bool AI::askYesNo() const
{
	return true;
}

unsigned AI::askBuilding(/*const vector<BoardElement*>& building_choices*/) const
{
	return 1;
}

bool AI::askJoustField() const
{
	return false;
}

int AI::askProvostShift() const
{
	return 3;
}

bool AI::isHuman() const
{
	return false;
}
