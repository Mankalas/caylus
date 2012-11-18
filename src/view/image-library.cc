/*!
  \file   ImageLibrary.cc
  \brief  Implementation of ImageLibrary

  \author Mankalas
  \date   2008-02-10
*/

#include "image-library.hh"

#include <SFML/Graphics.hpp>

#include "../const.hh"
#include "../CaylusConfig.h"

using namespace sf;
using namespace view;

ImageLibrary * ImageLibrary::instance_ = NULL;

ImageLibrary & ImageLibrary::inst()
{
	if (ImageLibrary::instance_ == NULL)
	{
		ImageLibrary::instance_ = new ImageLibrary();
	}
	return *(ImageLibrary::instance_);
}

void ImageLibrary::add(std::string image_name, const std::string & image_path)
{
	Image image;
	image.LoadFromFile(image_path);
	images_[image_name] = image;
}

ImageLibrary::ImageLibrary()
{
	images_ = std::map<std::string, Image>();

	std::string img_dir = Caylus_IMAGE_DIR;

	add("board", img_dir + "board_limited_edition.jpg");
	add("worker", img_dir + "marker_red.png");
	add("bailiff", img_dir + "baillif_prevost.png");
	add("provost", img_dir + "baillif_prevost.png");

	add(ALCHEMIST, img_dir + "alchemist.png");
	add(ARCHITECT, img_dir + "architect.png");
	add(BANK, img_dir + "bank.png");
	add(CATHEDRAL, img_dir + "cathedral.png");
	add(CHURCH, img_dir + "church.png");
	add(COLLEGE, img_dir + "college.png");
	add(FARM_CLOTH, img_dir + "farm_cloth.png");
	add(FARM_FOOD, img_dir + "farm_food.png");
	add(FARM_STONE, img_dir + "farm_stone.png");
	add(FIXED_CARPENTER, img_dir + "fixed_carpenter.png");
	add(FIXED_PEDDLER, img_dir + "fixed_peddler.png");
	add(GATE, img_dir + "gate.png");
	add(GOLD_MINE, img_dir + "gold_mine.png");
	add(GRANARY, img_dir + "granary.png");
	add(HOTEL, img_dir + "hotel.png");
	add(INN, img_dir + "inn.png");
	add(JEWELLER, img_dir + "jeweller.png");
	add(JOUST_FIELD, img_dir + "joust_field.png");
	add(LAWYER, img_dir + "lawyer.png");
	add(LIBRARY, img_dir + "library.png");
	add(WOOD_MARKETPLACE, img_dir + "marketplace.png");
	add(MASON, img_dir + "mason.png");
	add(MERCHANT_GUILD, img_dir + "merchant_guild.png");
	add(MONUMENT, img_dir + "monument.png");
	add(NEUTRAL_CARPENTER, img_dir + "neutral_carpenter.png");
	add(NEUTRAL_FARM, img_dir + "neutral_farm.png");
	add(NEUTRAL_FOREST, img_dir + "neutral_forest.png");
	add(NEUTRAL_MARKETPLACE, img_dir + "neutral_marketplace.png");
	add(NEUTRAL_QUARRY, img_dir + "neutral_quarry.png");
	add(NEUTRAL_SAWMILL, img_dir + "neutral_sawmill.png");
	add(PARK, img_dir + "park.png");
	add(WOOD_PEDDLER, img_dir + "peddler.png");
	add(WOOD_QUARRY, img_dir + "quarry.png");
	add(RESIDENCE, img_dir + "residence.png");
	add(WOOD_SAWMILL, img_dir + "sawmill.png");
	add(STABLES, img_dir + "stables.png");
	add(STATUE, img_dir + "statue.png");
	add(TAILOR, img_dir + "tailor.png");
	add(THEATER, img_dir + "theater.png");
	add(TRADING_POST, img_dir + "trading_post.png");
	add(WEAVER, img_dir + "weaver.png");
	add(WORKSHOP, img_dir + "workshop.png");
}

const Image & ImageLibrary::get(std::string name)
{
	return images_[name];
}
