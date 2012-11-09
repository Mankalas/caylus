/**
 * @file   playback.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun May 20 19:04:12 2012
 *
 * @brief  Declaration of the playback class.
 */

#include "playback.hh"

#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "../exceptions.hh"
#include "../const.hh"
#include "../controller/player.hh"
#include "../controller/game-engine.hh"

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
	unsigned nb_workers = next_uint();
	game_engine->maxWorkers() = nb_workers;
	player_->workers() = nb_workers;
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

controller::BoardElement * Playback::askWorkerPlacement(const std::vector<controller::BoardElement *> & buildings) const
{
	controller::BoardElement * choice = NULL;
	while (choice == NULL)
	{
		std::string s = next_str();
		foreach(controller::BoardElement * b, buildings)
		{
			if (b->name() == s)
			{
				choice = b;
				break;
			}
		}
	}
	return choice;
}

/* bool Playback::askYesNo() const;
	 bool Playback::askJoustField() const;
	 unsigned Playback::askBuilding() const;
	 unsigned Playback::askResourceChoice() const;
	 void Playback::boardElementActivation(const controller::BoardElement * board_elt);
*/

std::string Playback::next_line() const
{
	std::string line;
	if (std::getline(file_, line))
	{
		return line;
	}
	else
	{
		throw new GameOverException();
	}
}

std::string Playback::next_str() const
{
	return next_line();
}

int Playback::next_int() const
{
	return atoi(next_line().c_str());
}

unsigned Playback::next_uint() const
{
	return strtoul(next_line().c_str(), NULL, 0);
}
