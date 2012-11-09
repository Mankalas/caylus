/*!
  \file   DisplayVisitor.cc
  \brief  Implementation of the DisplayVisitor class.

  \author Mankalas
  \date   2007-10-05
*/

#include <SFML/Graphics.hpp>
#include "gfx-display-visitor.hh"
#include "gfx-window.hh"

using namespace gfx;
using namespace controller;

void DisplayVisitor::operator()(const Sprite & sprite)
{
	/*sf::Sprite sf_sprite = sprite.getSprite();
	  Window::window->Draw(sf_sprite);*/
}

void DisplayVisitor::operator()(const GameEngine & ge)
{
	std::cout << "DisplayVisitor : " << &ge << std::endl;
}
