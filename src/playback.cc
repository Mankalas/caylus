/**
 * @file   playback.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun May 20 19:04:12 2012
 *
 * @brief  Declaration of the playback class.
 */

#include "playback.hh"
#include <iostream>
#include "player.hh"

using namespace view;

Playback::Playback(controller::GameEngine * game_engine, std::string record_path)
	: ActiveView(game_engine)
{
	file_.open(record_path.c_str(), std::ios::in);
	if (!file_.is_open())
	{
		std::cerr << "File " << record_path << " does not exists." << std::endl;
	}
	player_->name(askName());
}

Playback::~Playback()
{
	file_.close();
}

std::string Playback::askName() const
{
	return next_str();
}

int Playback::askProvostShift() const
{
	return next_int();
}

controller::BoardElement* Playback::askWorkerPlacement(const std::vector<controller::BoardElement *> & buildings) const
{
	return buildings[next_int()];
}

/* bool Playback::askYesNo() const;
		 bool Playback::askJoustField() const;
		 unsigned Playback::askBuilding() const;
		 unsigned Playback::askResourceChoice() const;
		 void Playback::boardElementActivation(const controller::BoardElement * board_elt);
*/

std::string Playback::next_str() const
{
	/*std::stringstream line;
	file_ >> line;
	return line;*/
	return "Pedro";
}

int Playback::next_int() const
{
/*	int i;
	file_ >> i;
	return i;*/
	return 1;
}
