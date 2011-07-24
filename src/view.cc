#include "view.hh"

View::View(GameEngine& ge)
  :ge_(ge)
{
  connections_.push_back(ge_.connectAskNbHumans(boost::bind(&View::ask_nb_humans, this, _1)));
  connections_.push_back(ge_.connectAskNbAi(boost::bind(&View::ask_nb_ai, this, _1, _2)));
}

View::~View()
{
  foreach(GameEngine::connection_t& cnx, connections_)
    {
      ge_.disconnect(cnx);
    }
}

unsigned View::ask_nb_humans(unsigned max) const
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

unsigned View::ask_nb_ai(unsigned min, unsigned max) const
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
