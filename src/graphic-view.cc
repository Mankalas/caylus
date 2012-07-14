/**
 * @file   graphic-view.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun Nov  6 17:18:27 2011
 *
 * @brief  Declaration of the graphic-view class.
 */

#include "graphic-view.hh"

#include <assert.h>
#include <boost/foreach.hpp>
#include "gfx-window.hh"
#include "gfx-sprite-library.hh"
#include "board-element.hh"
#include "const.hh"
#include "debug-logger.hh"

using namespace gfx;
using namespace view;
using namespace controller;

GraphicView::GraphicView(const GameEngine * game_engine)
	: DisplayView(game_engine)
{
	window_.clear();
	drawBoard_();
	window_.display();
}

BoardElement* GraphicView::askBuilding(const std::vector<BoardElement*> & choices) const
{
	BoardElement * chosen_element = NULL;
	while (chosen_element == NULL)
		{
			std::pair<float, float> click_coordinates = window_.getClick();
			const std::string * building_name = board_.getBuildingName(click_coordinates.first, click_coordinates.second);
			if (building_name == NULL)
				{
					DebugLogger::log("Bad click.");
					continue;
				}
			DebugLogger::log(*building_name);
			foreach (BoardElement * board_elt, choices)
				{
					if (board_elt->name() == *building_name)
						{
							chosen_element = board_elt;
							break;
						}
				}
		}
	return chosen_element;
}

void GraphicView::updateBoard(const GameEngine * ) const
{
	window_.clear();
	window_.display();
}

void GraphicView::drawBoard_() const
{
	Sprite * board_sprite = SpriteLibrary::instance()->sprite("board");
	assert(board_sprite);
	window_.draw(*board_sprite);
}
