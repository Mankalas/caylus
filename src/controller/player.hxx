/**
 * @file   player.hxx
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Jun 01 23:30:32 2009
 */

#ifndef PLAYER_HXX
# define PLAYER_HXX

# include "player.hh"

# include "../visitor.hh"
# include "../const.hh"

inline const ResourceMap & controller::Player::resources() const
{
	return resources_;
}

inline int controller::Player::favorBuilding() const
{
	return favor_building_;
}

inline int controller::Player::favorResource() const
{
	return favor_resource_;
}

inline int controller::Player::favorDenier() const
{
	return favor_denier_;
}

inline int controller::Player::favorPrestige() const
{
	return favor_prestige_;
}

inline const std::string & controller::Player::name() const
{
	return name_;
}

inline void controller::Player::setName(const std::string name)
{
	name_ = name;
}

inline int controller::Player::prestige() const
{
	return prestige_;
}

inline unsigned int controller::Player::workers() const
{
	return workers_;
}

inline PlayerSignals & controller::Player::signals() const
{
	return signals_;
}

inline unsigned int controller::Player::residences() const
{
	return residences_;
}

inline bool controller::Player::operator==(const controller::Player & p) const
{
	return this == &p;
}

inline std::ostream & operator<<(std::ostream & o, const controller::Player & player)
{
	o << "Player " << GREEN << player.name() << RESET << " - " << player.resources()
	  << " - Workers left : " << player.workers();
	return o;
}

inline int controller::Player::askProvostShift() const
{
	return signals_.ask_provost_shift();
}

inline ResourceMap controller::Player::askResource(const std::vector<ResourceMap> & choice) const
{
	return signals_.ask_resource(choice);
}

inline void controller::Player::decrementWorkers()
{
	--workers_;
}

inline void controller::Player::incrementWorkers()
{
	++workers_;
}

inline
void controller::Player::accept(ConstVisitor & v) const
{
	v.operator()(*this);
}

inline
void controller::Player::accept(Visitor & v)
{
	v.operator()(*this);
}

inline
void controller::Player::increaseIncome(unsigned int i)
{
	residences_ += i;
}

inline
void controller::Player::decreaseIncome(unsigned int i)
{
	residences_ -= i;
}

inline
void controller::Player::setWorkers(unsigned int nb)
{
	workers_ = nb;
}

#endif //PLAYER_HXX
