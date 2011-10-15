/**
 * @file   board-element.hxx
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sat Oct 15 21:49:05 2011
 */

#include "board-element.hh"

using namespace controller;

inline
bool BoardElement::isCastle() const
{
	return false;
}

inline
bool BoardElement::isBridge() const
{
	return false;
}

inline
bool BoardElement::isBuilding() const
{
	return false;
}
