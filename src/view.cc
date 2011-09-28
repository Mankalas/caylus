#include <boost/bind.hpp>
#include <iostream>
#include "view.hh"
#include "game-engine.hh"

using namespace std;
using namespace view;
using namespace controller;

View::View(GameEngine *ge)
	: ge_(ge)
{
}

View::~View() {}

boost::signal<int (void)>::slot_function_type View::getAskProvostShiftSlot() const
{
	return boost::bind(&View::askProvostShift, this);
}

boost::signal<int (void)>::slot_function_type View::getAskWorkerPlacementSlot() const
{
	return boost::bind(&View::askWorkerPlacement, this);
}

boost::signal<unsigned (void)>::slot_function_type View::getAskBuildingSlot() const
{
	return boost::bind(&View::askBuilding, this);
}

boost::signal<unsigned (void)>::slot_function_type View::getResourceChoice() const
{
	return boost::bind(&View::askResourceChoice, this);
}
