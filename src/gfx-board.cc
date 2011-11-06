#include "gfx-board.hh"
#include "gfx-sprite-library.hh"

using namespace std;
using namespace gfx;

LimitedEditionBoard::LimitedEditionBoard()

{
	path_to_images_ = "../share/img/";

	board_ = SpriteLibrary::instance()->sprite("board");

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

	gate_coord_ = make_pair(COL_8, ROW_5);
	trading_post_coord_ = make_pair(COL_8, ROW_6);
	merchant_guild_coord_ = make_pair(COL_9, ROW_6);
	joust_field_coord_ = make_pair(COL_10, ROW_6);
	stables_coord_ = make_pair(COL_11, ROW_6);
	inn_coord_ = make_pair(COL_11, ROW_7);
	fixed_peddler_coord_ = make_pair(COL_2, ROW_8);
	fixed_carpenter_coord_ = make_pair(COL_1, ROW_8);
	goldmine_coord_ = make_pair(COL_2, ROW_1);

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
