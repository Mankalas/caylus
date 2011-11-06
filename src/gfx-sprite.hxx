/*!
  \file   Sprite.cc
  \brief  Implementation of the Sprite's inline members.

  \author Mankalas
  \date   2007-10-05
*/

using namespace gfx;

inline float
Sprite::width() const
{
	return sprite_.GetSize().x;
}

inline float
Sprite::height() const
{
	return sprite_.GetSize().y;
}

inline float
Sprite::left() const
{
	return sprite_.GetPosition().x;
}

inline float
Sprite::top() const{
	return sprite_.GetPosition().y;
}

inline const sf::Sprite &
Sprite::sfmlSprite() const
{
  return sprite_;
}

inline
const sf::Image* Sprite::getImage() const
{
  return image_;
}

inline
void Sprite::setPosition(const float left, const float top)
{
  sprite_.SetPosition(sf::Vector2f(left, top));
}

inline
void Sprite::move(const float left, const float top)
{
  sprite_.Move(sf::Vector2f(left, top));
}
