/**
 * @file   board-element.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Fri Oct 21 00:26:25 2011
 *
 * @brief  Implementation of the board-element class.
 */

#include "board-element.hh"
#include "player.hh"
#include "../exceptions.hh"
#include "../debug-logger.hh"

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

void BoardElement::add(Player & p)
{
	if (has_(p))
	{
		signals_.already_placed(this);
		throw new AlreadyPlacedEx();
	}
	if (isFull_())
	{
		signals_.building_full(this);
		throw new BuildingFullEx();
	}
	if (!canBePlacedOn_())
	{
		signals_.unactivable_building(this);
		throw new UnactivableBuildingEx();
	}
	signals_.worker_placed(&p, this);
	onAdd_(p);
}

bool BoardElement::canBePlacedOn_() const
{
	return true;
}
