/**
 * @file   player.hxx
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Jun 01 23:30:32 2009
 */

#ifndef PLAYER_HXX
# define PLAYER_HXX

# include "player.hh"
# include "exceptions.hh"

# include "../visitor.hh"
# include "../const.hh"

inline ResourceMap & controller::Player::resources()
{
	return resources_;
}

inline const ResourceMap & controller::Player::resources() const
{
	return resources_;
}

inline void controller::Player::favorBuilding(int new_var)
{
	this->favor_building_ = new_var;
}

inline int controller::Player::favorBuilding() const
{
	return favor_building_;
}

inline void controller::Player::favorResource(int new_var)
{
	favor_resource_ = new_var;
}

inline int controller::Player::favorResource() const
{
	return favor_resource_;
}

inline void controller::Player::favorDenier(int new_var)
{
	favor_denier_ = new_var;
}

inline int controller::Player::favorDenier() const
{
	return favor_denier_;
}

inline void controller::Player::favorPrestige(int new_var)
{
	favor_prestige_ = new_var;
}

inline int controller::Player::favorPrestige() const
{
	return favor_prestige_;
}

inline const std::string & controller::Player::name() const
{
	return name_;
}

inline void controller::Player::name(const std::string name)
{
	name_ = name;
}

inline void controller::Player::prestige(int new_var)
{
	prestige_ = new_var;
}

inline int controller::Player::prestige() const
{
	return prestige_;
}

inline const unsigned & controller::Player::workers() const
{
	return workers_;
}

inline unsigned int & controller::Player::workers()
{
	return workers_;
}

inline const unsigned & controller::Player::residences() const
{
	return residences_;
}

inline unsigned int & controller::Player::residences()
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

inline
controller::PlayerSignals * controller::Player::signals() const
{
	return &signals_;
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

#endif //PLAYER_HXX
