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

#include <SFML/Graphics.hpp>

#include "../const.hh"
#include "../debug-logger.hh"

#include "gfx-visitor.hh"
#include "image-library.hh"

#include "../controller/game-engine.hh"
#include "../controller/castle.hh"
#include "../controller/board.hh"

using namespace sf;
using namespace view;
using namespace controller;

GraphicView::GraphicView(const GameEngine * game_engine)
	: DisplayView(game_engine)
{
	window_ = new sf::RenderWindow(sf::VideoMode(1500, 900), "Caylus",
	                               sf::Style::Resize | sf::Style::Close);
}

Vector2<int> GraphicView::getClick() const
{
	Event event;
	while (window_->GetEvent(event))
	{
		// Close window : exit
		if (event.Type == Event::MouseButtonPressed)
		{
			return Vector2<int>(event.MouseButton.X, event.MouseButton.Y);
		}
	}
	return Vector2<int>(0, 0);
}

unsigned int GraphicView::askCaseNumber() const
{
	bool is_click_valid = false;
	unsigned int case_number = 0;
	while (!is_click_valid)
	{
		Vector2<int> click_coordinates = getClick();
		if (board_.isClickInCastle(click_coordinates.x, click_coordinates.y))
		{
			case_number = Castle::CASE_NUMBER;
			is_click_valid = true;
		}
		else if (board_.isClickInBridge(click_coordinates.x, click_coordinates.y))
		{
			case_number = Bridge::CASE_NUMBER;
			is_click_valid = true;
		}
		else
		{
			case_number = board_.getCaseFromCoordinates(click_coordinates.x, click_coordinates.y, is_click_valid);
		}
	}
	return case_number;
}

void GraphicView::updateBoard()
{
	DisplayVisitor visitor(*window_, board_);
	game_engine_->accept(visitor);
}

int GraphicView::askProvostShift() const
{
	bool is_click_valid = false;
	unsigned int case_number = 0;
	while (!is_click_valid)
	{
		Vector2<int> click_coordinates = getClick();
		case_number =	board_.getCaseFromCoordinates(click_coordinates.x, click_coordinates.y, is_click_valid);
	}
	return case_number;
}

int GraphicView::askChoice(int, int) const
{
	return 0;
}
int GraphicView::askChoice(std::vector<int>&) const
{
	return 0;
}

void GraphicView::showMessage(const std::string) const
{}

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
