/*!
  \file   DisplayVisitor.cc
  \brief  Implementation of the DisplayVisitor class.

  \author Mankalas
  \date   2007-10-05
*/

#include "gfx-display-visitor.hh"

//
// ATOMIC SECTION
//

void gfx::DisplayVisitor::operator()(gfx::Sprite* sprite)
{
  sf::Sprite sf_sprite = sprite->getSprite();
  gfx::Window::_window->Draw(sf_sprite);
}

void gfx::DisplayVisitor::operator()(GameEngine& game_engine)
{

}
