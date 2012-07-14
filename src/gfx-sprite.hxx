/*!
  \file   Sprite.cc
  \brief  Implementation of the Sprite's inline members.

  \author Mankalas
  \date   2007-10-05
*/

inline float
gfx::Sprite::width() const
{
	return sprite_.GetSize().x;
}

inline float
gfx::Sprite::height() const
{
	return sprite_.GetSize().y;
}

inline float
gfx::Sprite::left() const
{
	return sprite_.GetPosition().x;
}

inline float
gfx::Sprite::top() const{
	return sprite_.GetPosition().y;
}

inline const sf::Sprite &
gfx::Sprite::sfmlSprite() const
{
  return sprite_;
}

inline
const sf::Image* gfx::Sprite::getImage() const
{
  return image_;
}

inline
void gfx::Sprite::setPosition(const float left, const float top)
{
  sprite_.SetPosition(sf::Vector2f(left, top));
}

inline
void gfx::Sprite::move(const float left, const float top)
{
  sprite_.Move(sf::Vector2f(left, top));
}
