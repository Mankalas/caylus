#include "ai.hh"
#include "game-engine.hh"

using namespace std;
using namespace view;
using namespace controller;

AI::AI(GameEngine *ge)
	: View(ge)
{
}

string AI::askName() const
{
	return "toto";
}

BoardElement*
AI::askWorkerPlacement(const std::vector<BoardElement*> buildings) const
{
	return buildings[0];
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
