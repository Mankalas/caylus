/**
 * @file   board-element.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Fri Oct 21 00:26:25 2011
 *
 * @brief  Implementation of the board-element class.
 */

#include "board-element.hh"
#include "player.hh"

using namespace controller;

BoardElement::BoardElement(const std::string & name)
	: name_(name)
{
}

void BoardElement::activate()
{
	if (canBeActivated_())
	{
		signals_.activation_sig(this);
		onActivate_();
	}
}
