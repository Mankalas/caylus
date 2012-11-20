/*!
  \file   DisplayVisitor.cc
  \brief  Implementation of the DisplayVisitor class.

  \author Mankalas
  \date   2007-10-05
*/

#include "gfx-visitor.hh"

#include <SFML/Graphics.hpp>
#include <boost/lexical_cast.hpp>

#include "board.hh"
#include "image-library.hh"

#include "../debug-logger.hh"

#include "../controller/game-engine.hh"
#include "../controller/board.hh"
#include "../controller/road.hh"
#include "../controller/resource.hh"
#include "../controller/building.hh"
#include "../controller/stables.hh"

using namespace sf;
using namespace view;

DisplayVisitor::DisplayVisitor(RenderWindow & window, Board & board)
	: window_(window)
	, board_(board)
{}

void DisplayVisitor::operator()(const GameEngine & ge)
{
	window_.Clear();
	ge.board().accept(*this);
	foreach (const Player * player, ge.players())
	{
		player->accept(*this);
	}
	window_.Display();
}

void DisplayVisitor::operator()(const controller::Board & board)
{
	const Sprite & board_sprite = board_.sprite();
	window_.Draw(board_sprite);
	board.road().accept(*this);

	unsigned int baillif_case = board.bailiff();
	Vector2<unsigned int> bailiff_coordinates = board_.getCoordinatesOfCase(baillif_case);
	Sprite baillif_sprite(ImageLibrary::inst().get("bailiff"));
	baillif_sprite.SetPosition(bailiff_coordinates.x, bailiff_coordinates.y);
	window_.Draw(baillif_sprite);

	unsigned int provost_case = board.provost();
	Vector2<unsigned int> provost_coordinates = board_.getCoordinatesOfCase(provost_case);
	Sprite provost_sprite(ImageLibrary::inst().get("provost"));
	Vector2<unsigned int> case_size = board_.caseSize();
	centerSprite(provost_sprite, provost_coordinates, case_size);
	window_.Draw(provost_sprite);
}

void DisplayVisitor::drawResource(int resource, Color color, int top) const
{
	using boost::lexical_cast;
	String food(lexical_cast<std::string>(resource));
	food.SetColor(color);
	food.SetPosition(board_.width() + 15, top);
	window_.Draw(food);
}

void DisplayVisitor::operator()(const controller::Player & player)
{
	String name(player.name());
	name.SetColor(Color::White);
	name.SetPosition(board_.width() + 10, 10);
	window_.Draw(name);

	drawResource(player.resources()[controller::Resource::food], Color::Magenta, 35);
	drawResource(player.resources()[controller::Resource::wood], Color::Green, 70);
	drawResource(player.resources()[controller::Resource::cloth], Color::Blue, 114);
	drawResource(player.resources()[controller::Resource::stone], Color::White, 140);
	drawResource(player.resources()[controller::Resource::gold], Color::Yellow, 175);

	using boost::lexical_cast;
	String food(lexical_cast<std::string>(player.resources()[controller::Resource::denier]) + "$");
	food.SetColor(Color::Yellow);
	food.SetPosition(board_.width() + 15, 210);
	window_.Draw(food);
}

void DisplayVisitor::operator()(const controller::Road & road)
{
	Sprite worker_sprite(ImageLibrary::inst().get("worker"));
	const std::vector<BuildingSmartPtr> buildings = road.get();
	for (road_idx_ = 0; road_idx_ < buildings.size(); ++road_idx_)
	{
		BuildingSmartPtr building = buildings[road_idx_];
		if (building == NULL)
		{
			continue;
		}
		building->accept(*this);
	}
}

void DisplayVisitor::drawBuildingSprite(const controller::Building & building,
                                        Vector2<unsigned int> & case_coord,
                                        Vector2<unsigned int> & case_size) const
{
	const std::string building_name = building.name();
	Sprite building_sprite(ImageLibrary::inst().get(building_name));
	case_coord = board_.getCoordinatesOfCase(road_idx_);
	case_size = board_.caseSize();
	centerSprite(building_sprite, case_coord, case_size);
	window_.Draw(building_sprite);
}

void DisplayVisitor::operator()(const controller::Building & building)
{
	Vector2<unsigned int> case_coord;
	Vector2<unsigned int> case_size;
	drawBuildingSprite(building, case_coord, case_size);
	if (building.worker())
	{
		Sprite worker_sprite(ImageLibrary::inst().get("worker"));
		centerSprite(worker_sprite, case_coord, case_size);
		window_.Draw(worker_sprite);
	}
}

void DisplayVisitor::operator()(const controller::Stables & stables)
{
	Vector2<unsigned int> case_coord;
	Vector2<unsigned int> case_size;
	drawBuildingSprite(stables, case_coord, case_size);
	const std::vector<Player*> & players = stables.players();
	for (unsigned int player_idx = 0; player_idx < players.size(); ++player_idx)
	{
		Sprite worker_sprite(ImageLibrary::inst().get("worker"));
		worker_sprite.SetPosition(case_coord.x + 66, case_coord.y + (player_idx + 1) * 27 - worker_sprite.GetSize().y);
		window_.Draw(worker_sprite);
	}
}

void DisplayVisitor::centerSprite(Sprite & sprite,
                                  Vector2<unsigned int> & position,
                                  Vector2<unsigned int> & size) const
{
	sprite.SetPosition(position.x + (size.x - sprite.GetSize().x) / 2,
	                   position.y + (size.y - sprite.GetSize().y) / 2);
}
