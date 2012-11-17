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
		Board();
		unsigned int getCaseFromCoordinates(float x, float y) const;
		coordinates_t getCoordinatesOfCase(unsigned int case_idx) const;

		/** @name Accessors. */
		//@{

		Sprite * sprite() const;
		unsigned int caseHeight() const;
		unsigned int caseWidth() const;

		//@}

	protected:
		// The board's sprite.
		Sprite * sprite_;

		unsigned int height_;
		unsigned int width_;
		std::string path_to_images_;
		// All cases
		unsigned int case_height_;
		unsigned int case_width_;
		// Neutral cases
		std::vector<coordinates_t> cases_;

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

	class LimitedEditionBoard : public Board
	{
	public :
		LimitedEditionBoard();
	};
}

# include "gfx-board.hxx"

#endif
