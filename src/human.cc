#include "human.hh"
#include "console-ui.hh"

using namespace view;
using namespace controller;

Human::Human(GameEngine* ge)
	:View(ge)
{
}

Human::~Human()
{
}

std::string Human::askName() const
{
  user_interface_->showMessage("What name?");
  return user_interface_->getString();
}

int Human::askProvostShift() const {
  return 0;
}

bool Human::askYesNo() const {
  return true;
}

bool Human::askJoustField() const {
  return true;
}

void Human::_connectSignals()
{
  ge_->connectNbHumansSignal(boost::bind(&Human::askNbHumans, this, _1));
  ge_->connectNbAIsSignal(boost::bind(&Human::askNbAIs, this, _1, _2));
  ge_->connectBoardUpdatedSignal(boost::bind(&Human::updateBoard, this));
}

void Human::operator()()
{
  boost::mutex mut;
  boost::unique_lock<boost::mutex> lock(mut);
  disconnected_->wait(lock);
}

unsigned Human::askNbHumans(unsigned max)
{
  unsigned nb_humans = 0;
  while ((std::cout << "How many humans? (" << max << " max)\n") &&
	 (!(std::cin >> nb_humans) || (nb_humans > max)))
    {
      std::cout << "Bad number (0 min, " << max << "max).\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  return nb_humans;
}

unsigned Human::askNbAIs(unsigned min, unsigned max)
{
  unsigned nb_ai = min;
  while ((std::cout << "How many AIs? (" << min << " min, " << max << " max)\n") &&
	 (!(std::cin >> nb_ai) || (nb_ai > max) || (nb_ai < min)))
    {
      std::cout << "Bad number (" << min << " min, " << max << " max).\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  return nb_ai;
}

void Human::updateBoard()
{
  visitor_(*ge_);
}


int Human::askProvostShift()
{
	return 3;
}

bool Human::isHuman() const
{
	return true;
}

boost::signal<void (void)>::slot_function_type Human::getUpdateBoardSlot() const
{
	return boost::bind(&View::updateBoard, this);
}

int Human::askWorkerPlacement() const
{
	return 5;
}

unsigned Human::askBuilding() const
{
	return 3;
}

unsigned Human::askResourceChoice() const
{
	return 0;
}
