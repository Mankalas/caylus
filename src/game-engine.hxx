/**
 * @file   game-engine.hxx
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sat Jan 10 18:27:58 2009
 *
 * @brief  Inline implementation of the game-engine class.
 */

#ifndef GAME_ENGINE_HXX
# define GAME_ENGINE_HXX

# include "game-engine.hh"
# include "player.hh"

using namespace controller;

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

inline const Bridge& GameEngine::bridge() const
{
  return bridge_;
}

inline Bridge& GameEngine::bridge()
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

inline std::ostream& operator<<(std::ostream& o, const GameEngine& g)
{
  foreach (const Player* p, g.order())
    o << *p << std::endl;

  o << g.road() << std::endl;

  o << "Bridge : ";
  foreach (const Player* p, g.bridge().players())
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
