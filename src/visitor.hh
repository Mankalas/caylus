/**
 * @file   visitor.hh
 * @author Vincent Boucheny <vincent.boucheny@hpc-sa.com>
 * @date   Sat Jan 19 21:53:56 2013
 *
 * @brief  Declaration of the visitor class.
 */
#ifndef VISITOR_HH
#define VISITOR_HH

namespace controller
{
	class GameEngine;
	class Road;
	class Board;
	class Player;
	class Building;
	class Stables;
}

class Visitor
{
public:
	/** Constructor. */
	Visitor(){};

	/** Destructor. */
	~Visitor(){};

	virtual void operator()(controller::GameEngine &) = 0;
	virtual void operator()(controller::Board &) = 0;
	virtual void operator()(controller::Road &) = 0;
	virtual void operator()(controller::Player &) = 0;
	virtual void operator()(controller::Stables &) = 0;
	virtual void operator()(controller::Building &) = 0;

};

class ConstVisitor
{
public:
	/** Constructor. */
	ConstVisitor(){};

	/** Destructor. */
	~ConstVisitor(){};

	virtual void operator()(const controller::GameEngine &) = 0;
	virtual void operator()(const controller::Board &) = 0;
	virtual void operator()(const controller::Road &) = 0;
	virtual void operator()(const controller::Player &) = 0;
	virtual void operator()(const controller::Stables &) = 0;
	virtual void operator()(const controller::Building &) = 0;

};

#endif
