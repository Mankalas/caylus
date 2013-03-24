/**
 * @file   active-view.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun May 20 22:56:34 2012
 *
 * @brief  Declaration of the active-view class.
 */

#include "active-view.hh"
#include "player-signals.hh"
#include "../controller/game-engine.hh"
#include <boost/bind.hpp>

using namespace view;
using namespace controller;

ActiveView::ActiveView(const GameEngine * ge, const Player * player)
	: View(ge)
	, player_(player)
{
	player_->signals().ask_provost_shift.connect(boost::bind(&ActiveView::askProvostShift, this));
	player_->signals().ask_board_element.connect(boost::bind(&ActiveView::askBoardElement, this));
	player_->signals().ask_resource.connect(boost::bind(&ActiveView::askResource, this, _1));
}
