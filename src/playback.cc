/**
 * @file   playback.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun May 20 19:04:12 2012
 *
 * @brief  Declaration of the playback class.
 */

#include "playback.hh"

using namespace view;

Playback::Playback(std::string record_path)
{
	file_.open(record_path, ios::in);
}

Playback::~Playback()
{
	file_.close();
}

bool Playback::isInteractive() const
{
	return false;
}
