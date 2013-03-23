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

Playback::Playback(const controller::GameEngine * game_engine, const controller::Player * player, std::string record_path)
	: ActiveView(game_engine, player)
{
	file_.open(record_path.append("/input").c_str(), std::ios::in);
	if (!file_.is_open())
	{
		std::cerr << "File " << record_path << " does not exists." << std::endl;
	}
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

unsigned int Playback::askWorkerPlacement() const
{
	return next_int();
}

bool Playback::askYesNo() const
{
	return true;
}
/*
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

unsigned int Playback::askChoice(unsigned int range) const
{
	return next_uint();
}
