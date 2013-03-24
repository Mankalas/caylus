/**
 * @file   building.hxx
 * @author Nicuvëo (crucuny@gmail.com)
 * @date   Jun 6 21:39:08 2011
 *
 * @brief  Inline implementation of the building class.
 */

#ifndef BUILDING_HXX_
# define BUILDING_HXX_

# include "building.hh"
# include "player.hh"
# include "../visitor.hh"

inline const BuildingType &
Building::type() const
{
	return type_;
}

inline const ResourceMap &
Building::gain() const
{
	return gain_;
}

inline const std::vector<ResourceMap>&
Building::cost() const
{
	return cost_;
}

inline const Player *
Building::owner() const
{
	return owner_;
}

inline const Player *
Building::worker() const
{
	return worker_;
}

inline
void Building::accept(ConstVisitor & v) const
{
	v.operator()(*this);
}

inline
void Building::accept(Visitor & v)
{
	v.operator()(*this);
}

#endif /* !BUILDING_HXX_ */
