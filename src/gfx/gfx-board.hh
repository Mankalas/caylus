#ifndef GFX_BOARD_HH
# define GFX_BOARD_HH

# include <utility>
# include <vector>
# include <string>
# include "gfx-sprite.hh"

namespace gfx
{
	typedef std::pair<unsigned int, unsigned int> coordinates_t;

	class Board
	{
	public:
		Sprite * board_;
		const std::string * getBuildingName(float x, float y) const;

	protected:
		unsigned int height_;
		unsigned int width_;
		std::string path_to_images_;
		// All cases
		unsigned int case_height_;
		unsigned int case_width_;
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

		typedef std::map<coordinates_t, const std::string> road_t;
		road_t buildings_placement_;

	};

	class LimitedEditionBoard : public Board
	{
	public :
		LimitedEditionBoard();
	};
}

#endif
