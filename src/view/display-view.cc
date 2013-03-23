/**
 * @file   display-view.cc
 * @author Vincent Boucheny <vincent.boucheny@hpc-sa.com>
 * @date   Sat Mar 23 21:30:55 2013
 *
 * @brief  Declaration of the display-view class.
 */
#include "display-view.hh"

using namespace view;

DisplayView::DisplayView(const controller::GameEngine * ge)
	: PassiveView(ge)
{}
