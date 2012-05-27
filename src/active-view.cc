/**
 * @file   active-view.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun May 20 22:56:34 2012
 *
 * @brief  Declaration of the active-view class.
 */

#include "active-view.hh"
#include "player.hh"
#include "player-signals.hh"
#include "game-engine.hh"

using namespace view;
using namespace controller;

ActiveView::ActiveView(GameEngine * ge)
	: game_engine_(ge)
{
	Player * player = game_engine_->newPlayer();
	player->signals()->ask_provost_shift.connect(boost::bind(&ActiveView::askProvostShift, this));
	player->signals()->ask_worker_placement.connect(boost::bind(&ActiveView::askWorkerPlacement, this, _1));
}
