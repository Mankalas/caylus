/**
 * @file   bridge.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sat Oct 15 22:30:58 2011
 *
 * @brief  Declaration of the bridge class.
 */

#include "bridge.hh"
#include "board.hh"
#include "player.hh"
#include "const.hh"
#include "debug-logger.hh"

Bridge::Bridge(Board & board)
	:	BoardElement(BRIDGE)
	, board_(board)
{}

void Bridge::onActivate_()
{
	foreach (Player * player, players_)
	{
		int deniers = player->resources()[Resource::denier];
		if (deniers == 0)
		{
			continue;
		}
		int shift = 0;
		bool is_shift_valid = false;
		bool has_enough_denier = false;
		/* If the provost is not moved before the bridge, or over the end
		   of the board, or if the player has enough money, then move. */
		while (!is_shift_valid || !has_enough_denier)
		{
			shift = player->askProvostShift();
			is_shift_valid = board_.isProvostShiftValid(shift);
			has_enough_denier = fabs(shift) <= deniers;
		}
		if (shift != 0)
		{
			board_.shiftProvost(shift);
			player->substractResources(Resource::denier * fabs(shift));
		}
	}
}

void Bridge::onAdd_(Player & p)
{
	players_.push_back(&p);
	if (players_.size() == 1)
	{
		p.addResources(Resource::denier);
	}
}

bool Bridge::isFull_() const
{
	// The Bridge is never full.
	return false;
}

bool Bridge::has_(const Player & p) const
{
	return std::find(players_.begin(), players_.end(), &p) != players_.end();
}

bool Bridge::has(const Player & p) const
{
	return has_(p);
}

bool Bridge::canBeActivated_() const
{
	return players_.size() > 0;
}
