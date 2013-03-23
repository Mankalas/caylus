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

BoardElement::BoardElement(const std::string & name) :
	name_(name)
{
}

bool BoardElement::isCastle() const
{
	return false;
}

bool BoardElement::isBridge() const
{
	return false;
}

bool BoardElement::isBuilding() const
{
	return false;
}

const std::string & BoardElement::name() const
{
	return name_;
}
