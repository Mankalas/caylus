/*!
  \file   player.hxx
  \brief  Inline implementation for Player.

  \author Mankalas
  \date   2009-01-06
*/

#ifndef PLAYER_HXX
# define PLAYER_HXX

# include "player.hh"

inline ResourceMap& Player::resources()
{
  return resources_;
}

inline const ResourceMap& Player::resources() const
{
  return resources_;
}

inline void Player::setFavorBuilding(int new_var)
{
  this->favor_building_ = new_var;
}

inline int Player::getFavorBuilding() const
{
  return favor_building_;
}

inline void Player::setFavorResource(int new_var)
{
  favor_resource_ = new_var;
}

inline int Player::getFavorResource() const
{
  return favor_resource_;
}

inline void Player::setFavorDenier(int new_var)
{
  favor_denier_ = new_var;
}

inline int Player::getFavorDenier() const
{
  return favor_denier_;
}

inline void Player::setFavorPrestige(int new_var)
{
  favor_prestige_ = new_var;
}

inline int Player::getFavorPrestige() const
{
  return favor_prestige_;
}

inline const std::string& Player::name() const
{
  return name_;
}

inline void Player::setPrestige(int new_var)
{
  prestige_ = new_var;
}

inline int Player::getPrestige() const
{
  return prestige_;
}

inline const unsigned& Player::workers() const
{
  return workers_;
}

inline unsigned int& Player::workers()
{
  return workers_;
}

inline const unsigned& Player::residences() const
{
  return residences_;
}

inline unsigned int& Player::residences()
{
  return residences_;
}

inline bool Player::operator==(const Player& p) const
{
  return this == &p;
}

inline std::ostream& operator<<(std::ostream& o, const Player& player)
{
  o << "Player " << player.name() << " - " << player.resources()
    << " - Workers left : " << player.workers();
  return o;
}

#endif //PLAYER_HXX
