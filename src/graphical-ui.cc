/**
 * @file   graphical-ui.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun Nov  6 17:18:27 2011
 *
 * @brief  Declaration of the graphical-ui class.
 */

#include <assert.h>
#include "graphical-ui.hh"
#include "gfx-window.hh"
#include "gfx-sprite-library.hh"
#include "board-element.hh"
#include <boost/foreach.hpp>
#include "const.hh"
#include "logger.hh"

using namespace gfx;
using namespace view;
using namespace controller;

GraphicalUI::GraphicalUI()
{
	window_.clear();
	drawBoard_();
	window_.display();
}

BoardElement* GraphicalUI::askBuilding(const std::vector<BoardElement*> & choices) const
{
	BoardElement * chosen_element = NULL;
	while (chosen_element == NULL)
		{
			std::pair<float, float> click_coordinates = window_.getClick();
			const std::string * building_name = board_.getBuildingName(click_coordinates.first, click_coordinates.second);
			if (building_name == NULL)
				{
					Logger::debug("Bad click.");
					continue;
				}
			Logger::debug(*building_name);
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

void GraphicalUI::updateBoard(const GameEngine * ) const
{
	window_.clear();
	window_.display();
}

void GraphicalUI::drawBoard_() const
{
	Sprite * board_sprite = SpriteLibrary::instance()->sprite("board");
	assert(board_sprite);
	window_.draw(*board_sprite);
}
