/**
 * @file   view.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sat Nov 12 22:53:48 2011
 *
 * @brief  Implementation of the view class.
 */

#include <boost/bind.hpp>
#include <iostream>
#include "view.hh"
#include "game-engine.hh"
#include "board-element.hh"

using namespace std;
using namespace view;
using namespace controller;

View::View(GameEngine *ge)
	: ge_(ge)
{
}

View::View(View &v)
	: ge_(v.ge_)
{
}

View::~View() {}

ProvostShiftSlot View::getAskProvostShiftSlot() const
{
	return boost::bind(&View::askProvostShift, this);
}

WorkerPlacementSlot View::getAskWorkerPlacementSlot() const
{
	return boost::bind(&View::askWorkerPlacement, this, _1);
}

boost::signal<unsigned (void)>::slot_function_type View::getAskBuildingSlot() const
{
	return boost::bind(&View::askBuilding, this);
}

boost::signal<unsigned (void)>::slot_function_type View::getResourceChoice() const
{
	return boost::bind(&View::askResourceChoice, this);
}

boost::condition_variable *View::disconnected()
{
	return &disconnected_;
}
