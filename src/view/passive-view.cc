/**
 * @file   passive-view.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun May 20 22:57:46 2012
 *
 * @brief  Declaration of the passive-view class.
 */

#include "passive-view.hh"

using namespace view;
using namespace controller;

PassiveView::PassiveView(const GameEngine * ge)
	: game_engine_(ge)
{
}


