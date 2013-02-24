/**
 * @file   ai.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Mon Apr  9 23:06:12 2012
 *
 * @brief  Declaration of the ai class.
 */

#include <time.h>
#include <stdlib.h>

#include "ai.hh"

#include "../controller/game-engine.hh"
#include "../controller/board-element.hh"

using namespace std;
using namespace view;
using namespace controller;

AI::AI(const GameEngine * ge, const Player * player)
	: ActiveView(ge, player)
{
	srand(time(NULL));
}

string AI::askName() const
{
	return "HAL";
}

BoardElement *
AI::askWorkerPlacement(const std::vector<BoardElement *> & buildings) const
{
	int choice = rand() % buildings.size();
	return buildings[choice];
}

unsigned AI::askResourceChoice(/*const ResourceMap& choices*/) const
{
	return 3;
}

unsigned AI::askChoice(unsigned int range) const
{
	return range - 1;
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

void AI::boardElementActivation(const controller::BoardElement *)
{
}

void AI::updateBoard()
{
}

bool AI::isInteractive() const
{
	return false;
}
