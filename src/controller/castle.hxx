/**
 * @file   castle.hxx
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sat Jul 14 20:01:36 2012
 *
 * @brief  Declaration of the castle class.
 */

#ifndef CASTLE_HXX
# define CASTLE_HXX

# include "castle.hh"
# include "../const.hh"

inline
const std::vector<Player *>& controller::CastlePart::houses() const
{
	return houses_;
}

inline
std::vector<Player *>& controller::CastlePart::houses()
{
	return houses_;
}

inline
const unsigned & controller::CastlePart::prestige() const
{
	return prestige_;
}

inline
unsigned & controller::CastlePart::prestige()
{
	return prestige_;
}

inline
const unsigned & controller::CastlePart::capacity() const
{
	return capacity_;
}

inline
unsigned & controller::CastlePart::capacity()
{
	return capacity_;
}

inline
const std::vector<std::pair<unsigned, int> >& controller::CastlePart::scoreFavor() const
{
	return score_favor_;
}

inline
std::vector<std::pair<unsigned, int> >& controller::CastlePart::scoreFavor()
{
	return score_favor_;
}

inline
const std::vector<Player *>& controller::Castle::players() const
{
	return players_;
}

inline
std::vector<Player *>& controller::Castle::players()
{
	return players_;
}

inline
const controller::CastlePart * controller::Castle::dungeon() const
{
	return parts_[0];
}

inline
controller::CastlePart * controller::Castle::dungeon()
{
	return parts_[0];
}

inline
const controller::CastlePart * controller::Castle::walls() const
{
	return parts_[1];
}

inline
controller::CastlePart * controller::Castle::walls()
{
	return parts_[1];
}

inline
const controller::CastlePart * controller::Castle::towers() const
{
	return parts_[2];
}

inline
controller::CastlePart * controller::Castle::towers()
{
	return parts_[2];
}

inline std::ostream & operator<<(std::ostream & o, const controller::Castle & c)
{
	o << "Castle : ";
	foreach(const Player * p, c.players())
	if (p)
	{
		o << p->name() << " - ";
	}

	o << std::endl << "Dungeon : ";
	foreach(const Player * p, c.dungeon()->houses())
	if (p)
	{
		o << p->name() << " - ";
	}

	o << std::endl << "Walls : ";
	foreach(const Player * p, c.walls()->houses())
	if (p)
	{
		o << p->name() << " - ";
	}

	o << std::endl << "Towers : ";
	foreach(const Player * p, c.towers()->houses())
	if (p)
	{
		o << p->name() << " - ";
	}

	return o;
}

#endif //CASTLE_HXX
