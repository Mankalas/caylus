/**
 * @file   view.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sat Nov 12 22:53:48 2011
 *
 * @brief  Implementation of the view class.
 */

#include <boost/bind.hpp>
#include <iostream>
#include "view.hh"
#include "game-engine.hh"
#include "board-element.hh"

using namespace std;
using namespace view;
using namespace controller;

View::View()
{
}

View::View(View &)
{
}

View::~View() {}

board_element_activation_signal_t::slot_function_type View::boardElementActivationSlot()
{
	return boost::bind(&View::boardElementActivation, this, _1);
}

v_v_signal_t::slot_function_type View::updateBoardSlot()
{
	return boost::bind(&View::updateBoard, this);
}

boost::condition_variable *View::disconnected()
{
	return &disconnected_;
}
