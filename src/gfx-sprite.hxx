/*!
  \file   Sprite.cc
  \brief  Implementation of the Sprite's inline members.

  \author Mankalas
  \date   2007-10-05
*/

inline
sf::Sprite gfx::Sprite::getSprite() const
{
  return sprite_;
}

inline
const sf::Image* gfx::Sprite::getImage() const
{
  return image_;
}

inline
float gfx::Sprite::getWidth() const
{
  return sprite_.GetSize().y;
}

inline
float gfx::Sprite::getHeight() const
{
  return sprite_.GetSize().y;
}

inline
float gfx::Sprite::getLeft() const
{
  return sprite_.GetPosition().x;
}

inline
float gfx::Sprite::getTop() const
{
  return sprite_.GetPosition().y;
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
