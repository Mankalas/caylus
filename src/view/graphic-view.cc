/**
 * @file   graphic-view.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun Nov  6 17:18:27 2011
 *
 * @brief  Declaration of the graphic-view class.
 */

#include "graphic-view.hh"

#include <assert.h>
#include <algorithm>

#include "../const.hh"
#include "../debug-logger.hh"

#include "../gfx/gfx-display-visitor.hh"
#include "../gfx/gfx-sprite-library.hh"
#include "../gfx/gfx-window.hh"

#include "../controller/game-engine.hh"
#include "../controller/castle.hh"
#include "../controller/board.hh"

using namespace gfx;
using namespace view;
using namespace controller;

GraphicView::GraphicView(const GameEngine * game_engine)
	: DisplayView(game_engine)
{
	game_engine_->signals()->board_updated.connect(boost::bind(&GraphicView::updateBoard, this));
}

unsigned int GraphicView::askCaseNumber() const
{
	bool is_click_valid = false;
	unsigned int case_number = 0;
	while (!is_click_valid)
	{
		std::pair<float, float> click_coordinates = window_.getClick();
		if (board_.isClickInCastle(click_coordinates.first, click_coordinates.second))
		{
			case_number = Castle::CASE_NUMBER;
			is_click_valid = true;
		}
		else if (board_.isClickInBridge(click_coordinates.first, click_coordinates.second))
		{
			case_number = Bridge::CASE_NUMBER;
			is_click_valid = true;
		}
		else
		{
			case_number = board_.getCaseFromCoordinates(click_coordinates.first, click_coordinates.second, is_click_valid);
		}
	}
	return case_number;
}

void GraphicView::updateBoard()
{
	DisplayVisitor visitor(window_, board_);
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
