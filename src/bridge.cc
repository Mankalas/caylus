/**
 * @file   bridge.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sat Oct 15 22:30:58 2011
 *
 * @brief  Declaration of the bridge class.
 */

#include "bridge.hh"
#include "player.hh"
#include "const.hh"
#include "debug-logger.hh"

Bridge::Bridge() :
	BoardElement(BRIDGE)
{}

void Bridge::add(Player * p)
{
	if (players_.size() == 0)
		{
			//Logger::instance()->playerLog(p, " is granted 1 denier for he is the first on the Bridge.");
			p->resources() += Resource::denier;
		}
	players_.push_back(p);
}

bool Bridge::has(const Player * p) const
{
	return std::find(players_.begin(), players_.end(), p) != players_.end();
}

bool Bridge::isBridge() const
{
	return true;
}
