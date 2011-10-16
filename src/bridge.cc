/**
 * @file   bridge.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sat Oct 15 22:30:58 2011
 *
 * @brief  Declaration of the bridge class.
 */

#include "bridge.hh"
#include "player.hh"

void Bridge::add(Player * p)
{
	if (players_.size() == 0)
		{
			p->resources() += Resource::denier;
		}
	players_.push_back(p);
}

bool Bridge::has(const Player * p) const
{
	return std::find(players_.begin(), players_.end(), p) != players_.end();
}