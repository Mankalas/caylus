/*!
  \file   Sprite.cc
  \brief  Implementation of the Sprite class.

  \author Mankalas
  \date   2007-10-05
*/

#include <iostream>
#include <map>
#include "gfx-sprite.hh"
#include "exceptions.hh"

gfx::Sprite::Sprite():
	sprite_(sf::Sprite()),
	image_(new sf::Image()) {}

gfx::Sprite::Sprite(const std::string file_name)
{
	image_ = new sf::Image();
	if (image_ == NULL)
	{
		//throw new MemAllocError();
	}
	if (!image_->LoadFromFile(file_name))
	{
		//throw new ImageNotFound();
	}
	sprite_ = sf::Sprite(*image_);
}

gfx::Sprite::Sprite(const gfx::Sprite &copy) :
	sprite_(copy.sprite_),
	image_(copy.image_) {}
