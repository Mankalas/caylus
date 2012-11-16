/**
 * @file   graphic-view.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun Nov  6 17:18:27 2011
 *
 * @brief  Declaration of the graphic-view class.
 */

#include "graphic-view.hh"

#include <assert.h>

#include "../const.hh"
#include "../debug-logger.hh"

#include "../gfx/gfx-display-visitor.hh"
#include "../gfx/gfx-sprite-library.hh"
#include "../gfx/gfx-window.hh"

#include "../controller/game-engine.hh"

using namespace gfx;
using namespace view;
using namespace controller;

GraphicView::GraphicView(const GameEngine * game_engine)
	: DisplayView(game_engine)
{
	game_engine_->signals()->board_updated.connect(boost::bind(&GraphicView::updateBoard, this));
}

BoardElement * GraphicView::askBuilding(const std::vector<BoardElement *> & choices) const
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
		foreach(BoardElement * board_elt, choices)
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

void GraphicView::updateBoard()
{
	DisplayVisitor visitor(window_);
	game_engine_->accept(visitor);
}

int GraphicView::askProvostShift() const
{
	return 0;
}



int GraphicView::askChoice(int, int) const
{
	return 0;
}
int GraphicView::askChoice(std::vector<int>&) const
{
	return 0;
}
void GraphicView::showMessage(const std::string) const {}
int GraphicView::getInt() const
{
	return 0;
}
std::string GraphicView::getString() const
{
	return "";
}
std::string GraphicView::askName() const
{
	return "";
}
bool GraphicView::askYesNo() const
{
	return false;
}
