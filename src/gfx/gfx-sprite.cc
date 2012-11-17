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

using namespace gfx;

Sprite::Sprite()
	: sprite_(sf::Sprite())
	, image_(new sf::Image())
{}

Sprite::Sprite(const std::string file_name)
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

Sprite::Sprite(const Sprite & copy)
	:	sprite_(copy.sprite_)
	, image_(copy.image_)
{}

void Sprite::center(float left, float top, float width, float height)
{
	float new_left = left + (width - this->width()) / 2;
	float new_top= top + (height - this->height()) / 2;
	setPosition(new_left, new_top);
}
