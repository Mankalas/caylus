#ifndef GFX_BOARD_HH
# define GFX_BOARD_HH

namespace gfx
{
	typedef coordinates_t std::pair<unsigned int, unsigned int>;

	class Board
	{
	public:
		Board() = 0;
		gfx::Sprite board_;

	protected:
		unsigned int height_;
		unsigned int width_;
		std::string path_to_images_;
		// All cases
		unsigned int case_height_;
		unsigned int case_width_;
		// Fixed cases
		coordinates_t gate_coord_;
		coordinates_t trading_post_coord_;
		coordinates_t merchant_guild_coord_;
		coordinates_t joust_field_coord_;
		coordinates_t stables_coord_;
		coordinates_t inn_coord_;
		coordinates_t fixed_peddler_coord_;
		coordinates_t fixed_carpenter_coord_;
		coordinates_t goldmine_coord_;
		// Neutral cases
		std::vector<coordinates_t> neutral_cases_;
		std::vector<coordinates_t> empty_cases_;

		// Castle
		unsigned int house_height_;
		unsigned int house_width_;
		// Dungeon
		coordinates_t first_dungeon_house_coord_;
		unsigned int nb_house_line_dungeon_;
		unsigned int nb_line_dungeon_;
		// Walls
		coordinates_t first_walls_house_coord_;
		unsigned int nb_house_line_walls_;
		unsigned int nb_line_walls_;
		// Towers
		coordinates_t first_towers_house_coord_;
		unsigned int nb_house_line_towers_;
		unsigned int nb_line_towers_;

		// Bridge
		coordinates_t first_bridge_slot_coord_;
		int bridge_slots_gap_;

	};

	class LimitedEditionBoard : Board
	{
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

		const unsigned int HOUSE_ROW_1 = 200;
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
		const unsigned int BRIDGE_COL_5 = 1187;


	};
}

#endif
