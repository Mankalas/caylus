#ifndef VIEW_HH
# define VIEW_HH

# include "game-engine.hh"
# include <vector>

class View
{
public:
  View(GameEngine* ge);
  virtual ~View();

  unsigned ask_nb_humans(unsigned max);
  unsigned ask_nb_ai(unsigned min, unsigned max);

  void operator()();

protected:
  GameEngine* ge_;

private:
  std::vector<GameEngine::connection_t> connections_;
  boost::condition_variable* disconnected_;

};

#endif
