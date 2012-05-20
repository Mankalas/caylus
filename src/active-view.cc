/**
 * @file   active-view.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun May 20 22:56:34 2012
 *
 * @brief  Declaration of the active-view class.
 */

#include "active-view.hh"

using namespace view;
using namespace controller;

ActiveView::ActiveView(GameEngine * ge)
	: game_engine_(ge)
{
}
