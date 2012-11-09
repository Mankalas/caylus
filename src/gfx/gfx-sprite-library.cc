/*!
  \file   SpriteLibrary.cc
  \brief  Implementation of SpriteLibrary

  \author Mankalas
  \date   2008-02-10
*/

#include "gfx-sprite-library.hh"

#include "../const.hh"
#include "../CaylusConfig.h"

using namespace gfx;

SpriteLibrary *SpriteLibrary::instance_ = NULL;

SpriteLibrary::SpriteLibrary()
{
	sprites_ = std::map<const std::string, Sprite *>();
	std::string img_dir = Caylus_IMAGE_DIR;
	sprites_["board"] = new Sprite(img_dir + "board_limited_edition.jpg");
	sprites_[ALCHEMIST] = new Sprite(img_dir + "alchemist.png");
	sprites_[ARCHITECT] = new Sprite(img_dir + "architect.png");
	sprites_[BANK] = new Sprite(img_dir + "bank.png");
	sprites_[CATHEDRAL] = new Sprite(img_dir + "cathedral.png");
	sprites_[CHURCH] = new Sprite(img_dir + "church.png");
	sprites_[COLLEGE] = new Sprite(img_dir + "college.png");
	sprites_[FARM_CLOTH] = new Sprite(img_dir + "farm_cloth.png");
	sprites_[FARM_FOOD] = new Sprite(img_dir + "farm_food.png");
	sprites_[FARM_STONE] = new Sprite(img_dir + "farm_stone.png");
	sprites_[FIXED_CARPENTER] = new Sprite(img_dir + "fixed_carpenter.png");
	sprites_[FIXED_PEDDLER] = new Sprite(img_dir + "fixed_peddler.png");
	sprites_[GATE] = new Sprite(img_dir + "gate.png");
	sprites_[GOLD_MINE] = new Sprite(img_dir + "gold_mine.png");
	sprites_[GRANARY] = new Sprite(img_dir + "granary.png");
	sprites_[HOTEL] = new Sprite(img_dir + "hotel.png");
	sprites_[INN] = new Sprite(img_dir + "inn.png");
	sprites_[JEWELLER] = new Sprite(img_dir + "jeweller.png");
	sprites_[JOUST_FIELD] = new Sprite(img_dir + "joust_field.png");
	sprites_[LAWYER] = new Sprite(img_dir + "lawyer.png");
	sprites_[LIBRARY] = new Sprite(img_dir + "library.png");
	sprites_[WOOD_MARKETPLACE] = new Sprite(img_dir + "marketplace.png");
	sprites_[MASON] = new Sprite(img_dir + "mason.png");
	sprites_[MERCHANT_GUILD] = new Sprite(img_dir + "merchant_guild.png");
	sprites_[MONUMENT] = new Sprite(img_dir + "monument.png");
	sprites_[NEUTRAL_CARPENTER] = new Sprite(img_dir + "neutral_carpenter.png");
	sprites_[NEUTRAL_FARM] = new Sprite(img_dir + "neutral_farm.png");
	sprites_[NEUTRAL_FOREST] = new Sprite(img_dir + "neutral_forest.png");
	sprites_[NEUTRAL_MARKETPLACE] = new Sprite(img_dir + "neutral_marketplace.png");
	sprites_[NEUTRAL_QUARRY] = new Sprite(img_dir + "neutral_quarry.png");
	sprites_[NEUTRAL_SAWMILL] = new Sprite(img_dir + "neutral_sawmill.png");
	sprites_[PARK] = new Sprite(img_dir + "park.png");
	sprites_[WOOD_PEDDLER] = new Sprite(img_dir + "peddler.png");
	sprites_[WOOD_QUARRY] = new Sprite(img_dir + "quarry.png");
	sprites_[RESIDENCE] = new Sprite(img_dir + "residence.png");
	sprites_[WOOD_SAWMILL] = new Sprite(img_dir + "sawmill.png");
	sprites_[STABLES] = new Sprite(img_dir + "stables.png");
	sprites_[STATUE] = new Sprite(img_dir + "statue.png");
	sprites_[TAILOR] = new Sprite(img_dir + "tailor.png");
	sprites_[THEATER] = new Sprite(img_dir + "theater.png");
	sprites_[TRADING_POST] = new Sprite(img_dir + "trading_post.png");
	sprites_[WEAVER] = new Sprite(img_dir + "weaver.png");
	sprites_[WORKSHOP] = new Sprite(img_dir + "workshop.png");
}

Sprite * SpriteLibrary::sprite(const std::string & name)
{
	return sprites_[name];
}
