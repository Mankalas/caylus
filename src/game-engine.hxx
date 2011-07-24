/**
 * @file   game-engine.hxx
 * @author  <mankalas@localhost,>
 * @date   Sat Jan 10 18:27:58 2009
 *
 * @brief  Inline implementation for GameEngine
 *
 *
 */

#ifndef GAME_ENGINE_HXX
# define GAME_ENGINE_HXX

# include "game-engine.hh"

inline const std::vector<BuildingSmartPtr>& GameEngine::buildings() const
{
  return buildings_;
}

inline std::vector<BuildingSmartPtr>& GameEngine::buildings()
{
  return buildings_;
}

inline const Road& GameEngine::road() const
{
  return road_;
}

inline Road& GameEngine::road()
{
  return road_;
}

inline const std::vector<Player*>& GameEngine::order() const
{
  return order_;
}

inline std::vector<Player*>& GameEngine::order()
{
  return order_;
}

inline const std::vector<Player*>& GameEngine::players() const
{
  return players_;
}

inline std::vector<Player*>& GameEngine::players()
{
  return players_;
}

inline const std::vector<Player*>& GameEngine::bridge() const
{
  return bridge_;
}

inline std::vector<Player*>& GameEngine::bridge()
{
  return bridge_;
}

inline const Castle& GameEngine::castle() const
{
  return castle_;
}

inline Castle& GameEngine::castle()
{
  return castle_;
}

inline const unsigned&
GameEngine::bailiff() const
{
  return bailiff_;
}

inline unsigned&
GameEngine::bailiff()
{
  return bailiff_;
}

inline const unsigned&
GameEngine::provost() const
{
  return provost_;
}

inline unsigned&
GameEngine::provost()
{
  return provost_;
}

inline boost::mutex&
GameEngine::mutex()
{
  return mutex_;
}

inline boost::condition_variable*
GameEngine::waitingPlayers()
{
  return &waiting_players_;
}

inline boost::condition_variable*
GameEngine::waitingViews()
{
  return &waiting_views_;
}

inline boost::condition_variable*
GameEngine::disconnectViews()
{
  return &disconnect_views_;
}

inline void
GameEngine::connectNbHumansSignal(GameEngine::nb_humans_signal_t::slot_function_type subscriber)
{
  ask_nb_humans_.connect(subscriber);
}

inline void
GameEngine::connectNbAIsSignal(GameEngine::nb_ais_signal_t::slot_function_type subscriber)
{
  ask_nb_ais_.connect(subscriber);
}

inline void
GameEngine::subscribe(View* view)
{
  views_.push_back(view);
}

inline std::ostream& operator<<(std::ostream& o, const GameEngine& g)
{
  foreach (const Player* p, g.order())
    o << *p << std::endl;

  o << g.road() << std::endl;

  o << "Bridge : ";
  foreach (const Player* p, g.bridge())
    o << p->name() << " - ";

  o << std::endl << g.castle();

  BuildingSmartPtr b = g.road()[g.bailiff()];
  o << std::endl << "Bailiff : " << g.bailiff() + 1 << ": "
    << (b == NULL ? "<empty>" : b->name()) << std::endl;

  b = g.road()[g.provost()];
  o << "Provost : " << g.provost() + 1 << ": "
    << (b == NULL ? "<empty>" : b->name()) << std::endl
    << std::endl;

  return o;
}

#endif //GAME_ENGINE_HXX
