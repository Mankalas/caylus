/**
 * @file   bridge.hxx
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sat Oct 15 22:02:19 2011
 */

#include "bridge.hh"
#include "player.hh"

inline
const std::vector<Player *>& Bridge::players() const
{
	return players_;
}

inline
std::vector<Player *>& Bridge::players()
{
	return players_;
}

inline
void Bridge::clear()
{
	players_.clear();
}
