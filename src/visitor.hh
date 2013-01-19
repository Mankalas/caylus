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

	virtual void operator()(controller::GameEngine &);
	virtual void operator()(controller::Board &);
	virtual void operator()(controller::Road &);
	virtual void operator()(controller::Player &);
	virtual void operator()(controller::Stables &);
	virtual void operator()(controller::Building &);

};

class ConstVisitor
{
public:
	/** Constructor. */
	ConstVisitor(){};

	/** Destructor. */
	~ConstVisitor(){};

	virtual void operator()(const controller::GameEngine &);
	virtual void operator()(const controller::Board &);
	virtual void operator()(const controller::Road &);
	virtual void operator()(const controller::Player &);
	virtual void operator()(const controller::Stables &);
	virtual void operator()(const controller::Building &);

};
#endif
