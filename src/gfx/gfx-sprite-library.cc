/*!
  \file   SpriteLibrary.cc
  \brief  Implementation of SpriteLibrary

  \author Mankalas
  \date   2008-02-10
*/

#include "gfx-sprite-library.hh"
#include "../CaylusConfig.h"

using namespace gfx;

SpriteLibrary *SpriteLibrary::instance_ = NULL;

SpriteLibrary::SpriteLibrary()
{
	sprites_ = std::map<const std::string, Sprite *>();
	std::string img_dir = Caylus_IMAGE_DIR;
	sprites_["board"] = new Sprite(img_dir + "board_limited_edition.jpg");
	sprites_["alchemist"] = new Sprite(img_dir + "alchemist.png");
	sprites_["architect"] = new Sprite(img_dir + "architect.png");
	sprites_["bank"] = new Sprite(img_dir + "bank.png");
	sprites_["cathedral"] = new Sprite(img_dir + "cathedral.png");
	sprites_["church"] = new Sprite(img_dir + "church.png");
	sprites_["college"] = new Sprite(img_dir + "college.png");
	sprites_["farm_cloth"] = new Sprite(img_dir + "farm_cloth.png");
	sprites_["farm_food"] = new Sprite(img_dir + "farm_food.png");
	sprites_["farm_stone"] = new Sprite(img_dir + "farm_stone.png");
	sprites_["fixed_carpenter"] = new Sprite(img_dir + "fixed_carpenter.png");
	sprites_["fixed_peddler"] = new Sprite(img_dir + "fixed_peddler.png");
	sprites_["gate"] = new Sprite(img_dir + "gate.png");
	sprites_["gold_mine"] = new Sprite(img_dir + "gold_mine.png");
	sprites_["granary"] = new Sprite(img_dir + "granary.png");
	sprites_["hotel"] = new Sprite(img_dir + "hotel.png");
	sprites_["inn"] = new Sprite(img_dir + "inn.png");
	sprites_["jeweller"] = new Sprite(img_dir + "jeweller.png");
	sprites_["joust_field"] = new Sprite(img_dir + "joust_field.png");
	sprites_["lawyer"] = new Sprite(img_dir + "lawyer.png");
	sprites_["library"] = new Sprite(img_dir + "library.png");
	sprites_["marketplace"] = new Sprite(img_dir + "marketplace.png");
	sprites_["mason"] = new Sprite(img_dir + "mason.png");
	sprites_["merchant_guild"] = new Sprite(img_dir + "merchant_guild.png");
	sprites_["monument"] = new Sprite(img_dir + "monument.png");
	sprites_["neutral_carpenter"] = new Sprite(img_dir + "neutral_carpenter.png");
	sprites_["neutral_farm"] = new Sprite(img_dir + "neutral_farm.png");
	sprites_["neutral_forest"] = new Sprite(img_dir + "neutral_forest.png");
	sprites_["neutral_marketplace"] = new Sprite(img_dir + "neutral_marketplace.png");
	sprites_["neutral_quarry"] = new Sprite(img_dir + "neutral_quarry.png");
	sprites_["neutral_sawmill"] = new Sprite(img_dir + "neutral_sawmill.png");
	sprites_["park"] = new Sprite(img_dir + "park.png");
	sprites_["peddler"] = new Sprite(img_dir + "peddler.png");
	sprites_["quarry"] = new Sprite(img_dir + "quarry.png");
	sprites_["residence"] = new Sprite(img_dir + "residence.png");
	sprites_["sawmill"] = new Sprite(img_dir + "sawmill.png");
	sprites_["stables"] = new Sprite(img_dir + "stables.png");
	sprites_["statue"] = new Sprite(img_dir + "statue.png");
	sprites_["tailor"] = new Sprite(img_dir + "tailor.png");
	sprites_["theater"] = new Sprite(img_dir + "theater.png");
	sprites_["trading_post"] = new Sprite(img_dir + "trading_post.png");
	sprites_["weaver"] = new Sprite(img_dir + "weaver.png");
	sprites_["workshop"] = new Sprite(img_dir + "workshop.png");
}

Sprite * SpriteLibrary::sprite(const std::string & name)
{
	return sprites_[name];
}
