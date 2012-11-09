/**
 * @file   player-view.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Mon Apr  9 21:39:41 2012
 *
 * @brief  Declaration of the player-view class.
 */

#include "player-view.hh"

#include <boost/bind.hpp>

#include "../controller/game-engine.hh"


using namespace view;

PlayerView::PlayerView(const controller::GameEngine * ge)
	: View()
	, game_engine_(ge)
{
	//	game_engine_->signals()->ask_provost_shift_sig_.connect(boost::bind(&PlayerView::askProvostShift, this));
	//game_engine_->signals()->ask_worker_placement
}

PlayerView::~PlayerView() {}


WorkerPlacementSlot PlayerView::askWorkerPlacementSlot() const
{
	return boost::bind(&PlayerView::askWorkerPlacement, this, _1);
}

boost::signal<unsigned (void)>::slot_function_type PlayerView::askBuildingSlot() const
{
	return boost::bind(&PlayerView::askBuilding, this);
}

boost::signal<unsigned (void)>::slot_function_type PlayerView::resourceChoiceSlot() const
{
	return boost::bind(&PlayerView::askResourceChoice, this);
}
