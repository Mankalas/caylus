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
# include "../visitor.hh"

inline
const std::vector<BuildingSmartPtr>& controller::GameEngine::buildings() const
{
	return buildings_;
}

inline
std::vector<BuildingSmartPtr>& controller::GameEngine::buildings()
{
	return buildings_;
}

inline
const std::vector<Player *>& controller::GameEngine::order() const
{
	return order_;
}

inline
std::vector<Player *>& controller::GameEngine::order()
{
	return order_;
}

inline
const std::vector<Player *>& controller::GameEngine::players() const
{
	return players_;
}

inline
std::vector<Player *>& controller::GameEngine::players()
{
	return players_;
}

inline
unsigned & controller::GameEngine::maxWorkers()
{
	return max_workers_;
}

inline
unsigned controller::GameEngine::nbTurnsMax() const
{
	return nb_turns_max_;
}

inline
unsigned controller::GameEngine::nbTurns() const
{
	return nb_turns_;
}

inline
unsigned controller::GameEngine::nbHumans() const
{
	return nb_humans_;
}

inline
unsigned controller::GameEngine::nbAIs() const
{
	return nb_ais_;
}

inline
const Board & controller::GameEngine::board() const
{
	return board_;
}

inline
Board & controller::GameEngine::board()
{
	return board_;
}

inline
GameSignals * controller::GameEngine::signals() const
{
	return &sigs_;
}

inline
bool controller::GameEngine::random() const
{
	return random_;
}

inline
std::ostream & operator<<(std::ostream & o, const controller::GameEngine & g)
{
	foreach(const Player * p, g.order())
	o << *p << std::endl;
	o << g.board();
	return o;
}

inline
void controller::GameEngine::accept(const ConstVisitor & v) const
{
	v.operator()(*this);
}

inline
void controller::GameEngine::accept(Visitor & v)
{
	v.operator()(*this);
}

#endif //GAME_ENGINE_HXX
