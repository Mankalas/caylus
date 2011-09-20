#include <boost/bind.hpp>
#include "view.hh"

using namespace view;
using namespace controller;

View::View(GameEngine* ge)
  :ge_(ge)
{
  ge->subscribe(this);
  disconnected_ = ge_->disconnectViews();
  _connectSignals();
  std::cout << "View connecting...\n";
  ge->waitingViews()->notify_one();
}

boost::signal<int (void)>::slot_function_type View::getAskProvostShiftSlot() const
{
	return boost::bind(&View::askProvostShift, this);
}

boost::signal<unsigned (unsigned)>::slot_function_type View::getAskNbHumansSlot() const
{
	return boost::bind(&View::askNbHumans, this, _1);
}

boost::signal<unsigned (unsigned, unsigned)>::slot_function_type View::getAskNbAIsSlot() const
{
	return boost::bind(&View::askNbAIs, this, _1, _2);
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

void View::operator()()
{
  boost::mutex mut;
  boost::unique_lock<boost::mutex> lock(mut);
  disconnected_->wait(lock);
}

bool View::isHuman() const
{
	return false;
}
