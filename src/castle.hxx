/**
 * @file   castle.hxx
 * @author  <mankalas@localhost,>
 * @date   Thu Feb 12 13:07:25 2009
 *
 * @brief
 *
 *
 */

#ifndef CASTLE_HXX
# define CASTLE_HXX

# include <vector>
# include "player.hh"
# include "castle.hh"

inline
const std::vector<Player*>& CastlePart::houses() const
{
  return houses_;
}

inline
std::vector<Player*>& CastlePart::houses()
{
  return houses_;
}

inline
const unsigned& CastlePart::prestige() const
{
  return prestige_;
}

inline
unsigned& CastlePart::prestige()
{
  return prestige_;
}

inline
const unsigned& CastlePart::capacity() const
{
  return capacity_;
}

inline
unsigned& CastlePart::capacity()
{
  return capacity_;
}

inline
const std::vector<std::pair<unsigned, int> >& CastlePart::scoreFavor() const
{
  return score_favor_;
}

inline
std::vector<std::pair<unsigned, int> >& CastlePart::scoreFavor()
{
  return score_favor_;
}

inline
const std::vector<Player*>& Castle::players() const
{
  return players_;
}

inline
std::vector<Player*>& Castle::players()
{
  return players_;
}

inline
const CastlePart* Castle::dungeon() const
{
  return parts_[0];
}

inline
CastlePart* Castle::dungeon()
{
  return parts_[0];
}

inline
const CastlePart* Castle::walls() const
{
  return parts_[1];
}

inline
CastlePart* Castle::walls()
{
  return parts_[1];
}

inline
const CastlePart* Castle::towers() const
{
  return parts_[2];
}

inline
CastlePart* Castle::towers()
{
  return parts_[2];
}

inline std::ostream& operator<<(std::ostream& o, const Castle& c)
{
  o << "Castle : ";
  foreach (const Player* p, c.players())
    if (p)
      o << p->name() << " - ";

  o << std::endl << "Dungeon : ";
  foreach (const Player* p, c.dungeon()->houses())
    if (p)
      o << p->name() << " - ";

  o << std::endl << "Walls : ";
  foreach (const Player* p, c.walls()->houses())
    if (p)
      o << p->name() << " - ";

  o << std::endl << "Towers : ";
  foreach (const Player* p, c.towers()->houses())
    if (p)
      o << p->name() << " - ";

  return o;
}

#endif //CASTLE_HXX
