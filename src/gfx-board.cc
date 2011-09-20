#include "gfx-board.hh"

gfx::Board::LimitedEditionBoard()
{
  path_to_images_= "../share/img/"
  height_ = 904;
  width_ = 1282;
  case_height_ = case_width_ = 100;

  gate_coord_ = make_pair(COL_8, ROW_5);
  trading_post_coord_ = make_pair(COL_8, ROW_6);
  merchant_guild_coord_ = make_pair(COL_9, ROW_6);
  joust_field_coord_ = make_pair(COL_10, ROW_6);
  stables_coord_ = make_pair(COL_11, ROW_6);
  inn_coord_ = make_pair(COL_11, ROW_7);
  fixed_peddler_coord_ = make_pair(COL_2, ROW_8);
  fixed_carpenter_coord_ = make_pair(COL_1, ROW_8);
  goldmine_coord_ = make_pair(COL_2, ROW_1);

  neutral_cases_ << make_pair(COL_3, ROW_8)
                 << make_pair(COL_4, ROW_8)
                 << make_pair(COL_5, ROW_8)
                 << make_pair(COL_6, ROW_8)
                 << make_pair(COL_7, ROW_8)
                 << make_pair(COL_8, ROW_8);

  empty_cases_ << make_pair(COL_1, ROW_7)
               << make_pair(COL_1, ROW_6)
               << make_pair(COL_1, ROW_5)
               << make_pair(COL_1, ROW_4)
               << make_pair(COL_1, ROW_3)
               << make_pair(COL_1, ROW_2)
               << make_pair(COL_1, ROW_1)
               << make_pair(COL_3, ROW_1)
               << make_pair(COL_4, ROW_1)
               << make_pair(COL_5, ROW_1)
               << make_pair(COL_6, ROW_1)
               << make_pair(COL_7, ROW_1)
               << make_pair(COL_8, ROW_1)
               << make_pair(COL_9, ROW_1)
               << make_pair(COL_10, ROW_1)
               << make_pair(COL_11, ROW_1)
               << make_pair(COL_11, ROW_2)
               << make_pair(COL_11, ROW_3)
               << make_pair(COL_10, ROW_3);

  house_height_ = 26;
  house_width_ = 39;

  board_img_ = "board_limited_edition.jpg";
  alchemist_img_ = "alchemist.png";
  architect_img_ = "architect.png";
  bank_img_ = "bank.png";
  cathedral_img_ = "cathedral.png";
  church_img_ = "church.png";
  college_img_ = "college.png";
  farm_cloth_img_ = "farm_cloth.png";
  farm_food_img_ = "farm_food.png";
  farm_stone_img_ = "farm_stone.png";
  fixed_carpenter_img_ = "fixed_carpenter.png";
  fixed_peddler_img_ = "fixed_peddler.png";
  gate_img_ = "gate.png";
  gold_mine_img_ = "gold_mine.png";
  granary_img_ = "granary.png";
  hotel_img_ = "hotel.png";
  inn_img_ = "inn.png";
  jeweller_img_ = "jeweller.png";
  joust_field_img_ = "joust_field.png";
  lawyer_img_ = "lawyer.png";
  library_img_ = "library.png";
  marketplace_img_ = "marketplace.png";
  mason_img_ = "mason.png";
  merchant_guild_img_ = "merchant_guild.png";
  monument_img_ = "monument.png";
  neutral_carpenter_img_ = "neutral_carpenter.png";
  neutral_farm_img_ = "neutral_farm.png";
  neutral_forest_img_ = "neutral_forest.png";
  neutral_marketplace_img_ = "neutral_marketplace.png";
  neutral_quarry_img_ = "neutral_quarry.png";
  neutral_sawmill_img_ = "neutral_sawmill.png";
  park_img_ = "park.png";
  peddler_img_ = "peddler.png";
  quarry_img_ = "quarry.png";
  residence_img_ = "residence.png";
  sawmill_img_ = "sawmill.png";
  stables_img_ = "stables.png";
  statue_img_ = "statue.png";
  tailor_img_ = "tailor.png";
  theater_img_ = "theater.png";
  trading_post_img_ = "trading_post.png";
  weaver_img_ = "weaver.png";
  workshop_img_ = "workshop.png";
}
