#include "view.hh"
#include <boost/bind.hpp>

View::View(GameEngine* ge)
  :ge_(ge)
{
  ge_->subscribe(this);
  disconnected_ = ge_->disconnectViews();
  ge_->connectNbHumansSignal(boost::bind(&View::ask_nb_humans, this, _1));
  ge_->connectNbAIsSignal(boost::bind(&View::ask_nb_ai, this, _1, _2));
  std::cout << "View connecting...\n";
  ge_->waitingViews()->notify_one();
}

View::~View()
{
  /*  foreach(GameEngine::connection_t& cnx, connections_)
    {
      //ge_->disconnect(cnx);
    }
  */
}

void View::operator()()
{
  boost::mutex mut;
  boost::unique_lock<boost::mutex> lock(mut);
  disconnected_->wait(lock);
}

unsigned View::ask_nb_humans(unsigned max)
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

unsigned View::ask_nb_ai(unsigned min, unsigned max)
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
