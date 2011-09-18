#ifndef GFX_BOARD_HH
# define GFX_BOARD_HH

namespace gfx
{
  typedef coordinates_t std::pair<unsigned int, unsigned int>;

  class Board
  {
  public:
    gfx::Sprite board_;

  private:
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
    coordinates_t neutral_1_coord_;
    coordinates_t neutral_2_coord_;
    coordinates_t neutral_3_coord_;
    coordinates_t neutral_4_coord_;
    coordinates_t neutral_5_coord_;
    coordinates_t neutral_6_coord_;
    // Empty cases

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
}

#endif
