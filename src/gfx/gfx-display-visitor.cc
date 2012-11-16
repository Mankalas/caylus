/*!
  \file   DisplayVisitor.cc
  \brief  Implementation of the DisplayVisitor class.

  \author Mankalas
  \date   2007-10-05
*/

#include "gfx-display-visitor.hh"
#include "gfx-window.hh"
#include "gfx-sprite-library.hh"

#include "../debug-logger.hh"

#include "../controller/game-engine.hh"

using namespace gfx;
using namespace controller;

DisplayVisitor::DisplayVisitor(Window & window)
	: window_(window)
{}

void DisplayVisitor::operator()(const Sprite & sprite) const
{
	/*Sprite sf_sprite = sprite.getSprite();
	  window->Draw(sf_sprite);*/
}

void DisplayVisitor::operator()(const GameEngine * ge) const
{
	DebugLogger::log("Draw board");
	window_.clear();
	Sprite * board_sprite = SpriteLibrary::instance()->sprite("board");
	assert(board_sprite);
	window_.draw(*board_sprite);
	window_.display();
}
