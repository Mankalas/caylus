/*!
  \file   DisplayVisitor.cc
  \brief  Implementation of the DisplayVisitor class.

  \author Mankalas
  \date   2007-10-05
*/

#include "gfx-display-visitor.hh"
#include "gfx-window.hh"
#include "gfx-sprite-library.hh"
#include "gfx-board.hh"

#include "../debug-logger.hh"

#include "../controller/game-engine.hh"
#include "../controller/board.hh"
#include "../controller/road.hh"
#include "../controller/building.hh"

using namespace gfx;
using namespace controller;

DisplayVisitor::DisplayVisitor(Window & window, Board & board)
	: window_(window)
	, board_(board)
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
	Sprite * board_sprite = board_.sprite();
	assert(board_sprite);
	window_.draw(*board_sprite);
	board->road().accept(*this);
}

void DisplayVisitor::operator()(const controller::Road * road) const
{
	Sprite * worker_sprite = SpriteLibrary::instance()->sprite("worker");
	assert(worker_sprite);
	const std::vector<BuildingSmartPtr> buildings = road->get();
	for (unsigned int road_idx = 0; road_idx < buildings.size(); ++road_idx)
	{
		BuildingSmartPtr building =  buildings[road_idx];
		if (building == NULL)
		{
			continue;
		}
		const std::string building_name = building->name();
		Sprite * building_sprite = SpriteLibrary::instance()->sprite(building_name);
		coordinates_t coordinates = board_.getCoordinatesOfCase(road_idx);
		building_sprite->center(coordinates.first, coordinates.second, board_.caseWidth(), board_.caseHeight());
		window_.draw(*building_sprite);
		if (building->worker())
		{
			Sprite * worker_sprite = SpriteLibrary::instance()->sprite("worker");
			worker_sprite->center(coordinates.first, coordinates.second, board_.caseWidth(), board_.caseHeight());
			window_.draw(*worker_sprite);
		}
	}
}
