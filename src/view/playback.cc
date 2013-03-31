/**
 * @file   playback.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun May 20 19:04:12 2012
 *
 * @brief  Declaration of the playback class.
 */

#include "playback.hh"
#include "file-reader.hh"

#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "../exceptions.hh"
#include "../const.hh"
#include "../controller/player.hh"
#include "../controller/game-engine.hh"

using namespace view;

Playback::Playback(const controller::GameEngine * game_engine, const controller::Player * player, FileReader & file_reader)
	: ActiveView(game_engine, player)
	, reader_(file_reader)
{
}

Playback::~Playback()
{
}

controller::ResourceMap Playback::askResource(const std::vector<controller::ResourceMap>& resource_choice) const
{
	unsigned int choice = reader_.next_uint();
	return resource_choice[choice];
}

std::string Playback::askName() const
{
	return reader_.next_str();
}

int Playback::askProvostShift() const
{
	return reader_.next_int();
}

unsigned int Playback::askBoardElement() const
{
	return reader_.next_uint();
}

bool Playback::askYesNo() const
{
	return true;
}

unsigned int Playback::askChoice(unsigned int range) const
{
	return reader_.next_uint();
}
