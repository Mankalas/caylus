/**
 * @file   board.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun Nov  6 20:11:52 2011
 *
 * @brief  Implementation of the board class.
 */

#include "board.hh"

#include <iostream>

#include "image-library.hh"

#include "../const.hh"
#include "../debug-logger.hh"

using namespace view;
using namespace std;
using namespace sf;

Board::Board()
	: sprite_(ImageLibrary::inst().get("board"))
	, height_(904)
	, width_(1282)
	, case_height_(100)
	, case_width_(100)
	, house_height_(26)
	, house_width_(39)
{}

unsigned int Board::getCaseFromCoordinates(int x, int y, bool & is_click_valid) const
{
	for (unsigned int case_idx = 0; case_idx < cases_.size(); ++case_idx)
	{
		int a = cases_[case_idx].x;
		int b = cases_[case_idx].y;
		if (x >= a && x <= a + (int)case_width_ && y >= b && y <= b + (int)case_height_)
		{
			is_click_valid = true;
			return case_idx;
		}
	}
	is_click_valid = false;
	return 0;
}

bool Board::isClickInCastle(int x, int y) const
{
	return x >= 643 && x <= 668 && y >= 199 && y <= 350;
}

bool Board::isClickInBridge(int x, int y) const
{
	return x >= 910 && x <= 1228 && y >= 750 && y <= 848;
}

Vector2<unsigned int> Board::caseSize() const
{
	return Vector2<unsigned int>(case_width_, case_height_);
}

Vector2<unsigned int> Board::getCoordinatesOfCase(unsigned int case_idx) const
{
	return cases_[case_idx];
}


LimitedEditionBoard::LimitedEditionBoard()
	: Board()
{
	//sprite_ = sf::Sprite(ImageLibrary::inst().get("board"));

	const unsigned int  ROW_1 = 58;
	const unsigned int  ROW_2 = 159;
	const unsigned int  ROW_3 = 258;
	const unsigned int  ROW_4 = 355;
	const unsigned int  ROW_5 = 456;
	const unsigned int  ROW_6 = 555;
	const unsigned int  ROW_7 = 652;
	const unsigned int  ROW_8 = 753;

	const unsigned int  COL_1 = 57;
	const unsigned int  COL_2 = 164;
	const unsigned int  COL_3 = 271;
	const unsigned int  COL_4 = 377;
	const unsigned int  COL_5 = 485;
	const unsigned int  COL_6 = 591;
	const unsigned int  COL_7 = 697;
	const unsigned int  COL_8 = 803;
	const unsigned int  COL_9 = 910;
	const unsigned int  COL_10 = 1016;
	const unsigned int  COL_11 = 1122;

	/*const unsigned int HOUSE_ROW_1 = 200;
	const unsigned int HOUSE_ROW_2 = 229;
	const unsigned int HOUSE_ROW_3 = 260;
	const unsigned int HOUSE_ROW_4 = 292;
	const unsigned int HOUSE_ROW_5 = 322;

	const unsigned int HOUSE_COL_1 = 257;
	const unsigned int HOUSE_COL_2 = 300;
	const unsigned int HOUSE_COL_3 = 372;
	const unsigned int HOUSE_COL_4 = 413;
	const unsigned int HOUSE_COL_5 = 257;
	const unsigned int HOUSE_COL_6 = 488;
	const unsigned int HOUSE_COL_7 = 529;
	const unsigned int HOUSE_COL_8 = 572;

	const unsigned int BRIDGE_ROW = 494;
	const unsigned int BRIDGE_COL_1 = 1011;
	const unsigned int BRIDGE_COL_2 = 1055;
	const unsigned int BRIDGE_COL_3 = 1099;
	const unsigned int BRIDGE_COL_4 = 1143;
	const unsigned int BRIDGE_COL_5 = 1187;*/

	cases_.push_back(Vector2<unsigned int>(COL_8, ROW_5));
	cases_.push_back(Vector2<unsigned int>(COL_8, ROW_6));
	cases_.push_back(Vector2<unsigned int>(COL_9, ROW_6));
	cases_.push_back(Vector2<unsigned int>(COL_10, ROW_6));
	cases_.push_back(Vector2<unsigned int>(COL_11, ROW_6));
	cases_.push_back(Vector2<unsigned int>(COL_11, ROW_7));
	cases_.push_back(Vector2<unsigned int>(COL_8, ROW_8));
	cases_.push_back(Vector2<unsigned int>(COL_7, ROW_8));
	cases_.push_back(Vector2<unsigned int>(COL_6, ROW_8));
	cases_.push_back(Vector2<unsigned int>(COL_5, ROW_8));
	cases_.push_back(Vector2<unsigned int>(COL_4, ROW_8));
	cases_.push_back(Vector2<unsigned int>(COL_3, ROW_8));
	cases_.push_back(Vector2<unsigned int>(COL_2, ROW_8));
	cases_.push_back(Vector2<unsigned int>(COL_1, ROW_8));
	cases_.push_back(Vector2<unsigned int>(COL_1, ROW_7));
	cases_.push_back(Vector2<unsigned int>(COL_1, ROW_6));
	cases_.push_back(Vector2<unsigned int>(COL_1, ROW_5));
	cases_.push_back(Vector2<unsigned int>(COL_1, ROW_4));
	cases_.push_back(Vector2<unsigned int>(COL_1, ROW_3));
	cases_.push_back(Vector2<unsigned int>(COL_1, ROW_2));
	cases_.push_back(Vector2<unsigned int>(COL_1, ROW_1));
	cases_.push_back(Vector2<unsigned int>(COL_2, ROW_1));
	cases_.push_back(Vector2<unsigned int>(COL_3, ROW_1));
	cases_.push_back(Vector2<unsigned int>(COL_4, ROW_1));
	cases_.push_back(Vector2<unsigned int>(COL_5, ROW_1));
	cases_.push_back(Vector2<unsigned int>(COL_6, ROW_1));
	cases_.push_back(Vector2<unsigned int>(COL_7, ROW_1));
	cases_.push_back(Vector2<unsigned int>(COL_8, ROW_1));
	cases_.push_back(Vector2<unsigned int>(COL_9, ROW_1));
	cases_.push_back(Vector2<unsigned int>(COL_10, ROW_1));
	cases_.push_back(Vector2<unsigned int>(COL_11, ROW_1));
	cases_.push_back(Vector2<unsigned int>(COL_11, ROW_2));
	cases_.push_back(Vector2<unsigned int>(COL_11, ROW_3));
	cases_.push_back(Vector2<unsigned int>(COL_10, ROW_3));
}
