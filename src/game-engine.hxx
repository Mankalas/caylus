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

inline unsigned&
GameEngine::nbTurnsMax()
{
	return nb_turns_max_;
}

inline const unsigned&
GameEngine::nbTurnsMax() const
{
	return nb_turns_max_;
}

inline const unsigned &
GameEngine::nbTurns() const
{
	return nb_turns_;
}

inline boost::mutex&
GameEngine::mutex()
{
  return mutex_;
}

inline
const unsigned & GameEngine::nbHumans() const
{
	return nb_humans_;
}

inline
const unsigned & GameEngine::nbAIs() const
{
	return nb_ais_;
}

inline
const Board & GameEngine::board() const
{
	return board_;
}

inline
Board & GameEngine::board()
{
	return board_;
}

inline
GameSignals * GameEngine::signals() const
{
	return &sigs_;
}

inline std::ostream& operator<<(std::ostream& o, const GameEngine& g)
{
  foreach (const Player* p, g.order())
    o << *p << std::endl;

	o << g.board();

  return o;
}

#endif //GAME_ENGINE_HXX
