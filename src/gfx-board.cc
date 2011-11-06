/**
 * @file   gfx-board.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun Nov  6 20:11:52 2011
 *
 * @brief  Implementation of the gfx-board class.
 */

#include "gfx-board.hh"
#include "gfx-sprite-library.hh"
#include "const.hh"
#include <boost/foreach.hpp>
#include <iostream>

using namespace std;
using namespace gfx;

const std::string * Board::getBuildingName(float x, float y) const
{
	foreach (const road_t::value_type & it, buildings_placement_)
		{
			unsigned int a = it.first.first;
			unsigned int b = it.first.second;
			//std::cout << "Check if (" << x << ", " << y << ") in (" << a << ", " << b << ").\n";
			if (x >= a && x <= a + case_width_ && y >= b && y <= b + case_height_)
				{
					return &it.second;
				}
		}
	return NULL;
}

LimitedEditionBoard::LimitedEditionBoard()
{
	height_ = 904;
	width_ = 1282;
	case_height_ = case_width_ = 100;

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

	buildings_placement_.insert(std::pair<coordinates_t, const std::string>(make_pair(COL_8, ROW_5), GATE));
	buildings_placement_.insert(std::pair<coordinates_t, const std::string>(make_pair(COL_8, ROW_6), TRADING_POST));
	buildings_placement_.insert(std::pair<coordinates_t, const std::string>(make_pair(COL_9, ROW_6), MERCHANT_GUILD));
	buildings_placement_.insert(std::pair<coordinates_t, const std::string>(make_pair(COL_10, ROW_6), JOUST_FIELD));
	buildings_placement_.insert(std::pair<coordinates_t, const std::string>(make_pair(COL_11, ROW_6), STABLES));
	buildings_placement_.insert(std::pair<coordinates_t, const std::string>(make_pair(COL_11, ROW_7), INN));
	buildings_placement_.insert(std::pair<coordinates_t, const std::string>(make_pair(COL_2, ROW_8), FIXED_PEDDLER));
	buildings_placement_.insert(std::pair<coordinates_t, const std::string>(make_pair(COL_1, ROW_8), FIXED_CARPENTER));
	buildings_placement_.insert(std::pair<coordinates_t, const std::string>(make_pair(COL_2, ROW_1), GOLD_MINE));

	neutral_cases_.push_back(make_pair(COL_3, ROW_8));
	neutral_cases_.push_back(make_pair(COL_4, ROW_8));
	neutral_cases_.push_back(make_pair(COL_5, ROW_8));
	neutral_cases_.push_back(make_pair(COL_6, ROW_8));
	neutral_cases_.push_back(make_pair(COL_7, ROW_8));
	neutral_cases_.push_back(make_pair(COL_8, ROW_8));

	empty_cases_.push_back(make_pair(COL_1, ROW_7));
	empty_cases_.push_back(make_pair(COL_1, ROW_6));
	empty_cases_.push_back(make_pair(COL_1, ROW_5));
	empty_cases_.push_back(make_pair(COL_1, ROW_4));
	empty_cases_.push_back(make_pair(COL_1, ROW_3));
	empty_cases_.push_back(make_pair(COL_1, ROW_2));
	empty_cases_.push_back(make_pair(COL_1, ROW_1));
	empty_cases_.push_back(make_pair(COL_3, ROW_1));
	empty_cases_.push_back(make_pair(COL_4, ROW_1));
	empty_cases_.push_back(make_pair(COL_5, ROW_1));
	empty_cases_.push_back(make_pair(COL_6, ROW_1));
	empty_cases_.push_back(make_pair(COL_7, ROW_1));
	empty_cases_.push_back(make_pair(COL_8, ROW_1));
	empty_cases_.push_back(make_pair(COL_9, ROW_1));
	empty_cases_.push_back(make_pair(COL_10, ROW_1));
	empty_cases_.push_back(make_pair(COL_11, ROW_1));
	empty_cases_.push_back(make_pair(COL_11, ROW_2));
	empty_cases_.push_back(make_pair(COL_11, ROW_3));
	empty_cases_.push_back(make_pair(COL_10, ROW_3));

	house_height_ = 26;
	house_width_ = 39;
}
