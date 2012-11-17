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
#include "../controller/board.hh"
#include "../controller/road.hh"
#include "../controller/building.hh"

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
	window_.clear();
	ge->board().accept(*this);
	window_.display();
}

void DisplayVisitor::operator()(const controller::Board * board) const
{
	DebugLogger::log("Draw board");
	Sprite * board_sprite = SpriteLibrary::instance()->sprite("board");
	assert(board_sprite);
	window_.draw(*board_sprite);
	board->road().accept(*this);
}

void DisplayVisitor::operator()(const controller::Road * road) const
{
	DebugLogger::log("Draw road");
	Sprite * worker_sprite = SpriteLibrary::instance()->sprite("worker");
	assert(worker_sprite);
	foreach(const BuildingSmartPtr building, road->get())
	{
		if (building != NULL && building->worker())
		{
			window_.draw(*worker_sprite);
		}
	}
}
