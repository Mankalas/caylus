/**
 * @file   human.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Dec 14 22:21:10 2011
 *
 * @brief  Declaration of the human class.
 */

#include "human.hh"

#include <iostream>
#include "debug-logger.hh"
#include "display-view.hh"
#include "board-element.hh"

#include "console-view.hh" // TODO : decide which GUI the human wants.

using namespace std;
using namespace view;
using namespace controller;

Human::Human(GameEngine *ge)
	: ActiveView(ge)
{
	gui_ = new ConsoleView(ge);
}

Human::~Human()
{
}

string Human::askName() const
{
	gui_->showMessage("What name?");
	return gui_->getString();
}

bool Human::askYesNo() const
{
	return true;
}

bool Human::askJoustField() const
{
	return true;
}

void Human::operator()()
{
	boost::mutex mut;
	boost::unique_lock<boost::mutex> lock(mut);
	//disconnected_.wait(lock);
}

boost::signal<unsigned (unsigned)>::slot_function_type Human::getAskNbHumansSlot() const
{
	return boost::bind(&Human::askNbHumans, this, _1);
}

boost::signal<unsigned (unsigned, unsigned)>::slot_function_type Human::getAskNbAIsSlot() const
{
	return boost::bind(&Human::askNbAIs, this, _1, _2);
}

unsigned Human::askNbHumans(unsigned max) const
{
	DebugLogger::log("Asking nb humans.");
	unsigned nb_humans = 0;
	while ((cout << "How many humans? (" << max << " max)\n") &&
	       (!(cin >> nb_humans) || (nb_humans > max)))
	{
		cout << "Bad number (0 min, " << max << "max).\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return nb_humans;
}

unsigned Human::askNbAIs(unsigned min, unsigned max) const
{
	unsigned nb_ai = min;
	while ((cout << "How many AIs? (" << min << " min, " << max << " max)\n") &&
	       (!(cin >> nb_ai) || (nb_ai > max) || (nb_ai < min)))
	{
		cout << "Bad number (" << min << " min, " << max << " max).\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return nb_ai;
}

void Human::updateBoard()
{
	gui_->updateBoard(game_engine_);
}


int Human::askProvostShift() const
{
	return gui_->askProvostShift();
}

bool Human::isHuman() const
{
	return true;
}

BoardElement*
Human::askWorkerPlacement(const std::vector<BoardElement *> & buildings) const
{
	return gui_->askBuilding(buildings);
}

unsigned Human::askBuilding() const
{
	return 3;
}

unsigned Human::askResourceChoice() const
{
	return 0;
}

void Human::boardElementActivation(const controller::BoardElement * board_elt)
{
	gui_->showMessage(board_elt->name() + " activated.");
}

bool Human::isInteractive() const
{
	return true;
}
