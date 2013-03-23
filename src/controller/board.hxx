/**
 * @file   board.hxx
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Mon Apr  9 16:15:44 2012
 *
 * @brief  Declaration of the board class.
 */

# include "player.hh"
# include "../visitor.hh"

inline const Road & Board::road() const
{
	return road_;
}

inline Road & Board::road()
{
	return road_;
}

inline const Bridge & Board::bridge() const
{
	return bridge_;
}

inline Bridge & Board::bridge()
{
	return bridge_;
}

inline const Castle & Board::castle() const
{
	return castle_;
}

inline Castle & Board::castle()
{
	return castle_;
}

inline const unsigned &
Board::bailiff() const
{
	return bailiff_;
}

inline const unsigned &
Board::provost() const
{
	return provost_;
}

inline
controller::BoardSignals & controller::Board::signals() const
{
	return signals_;
}

inline
void controller::Board::accept(ConstVisitor & v) const
{
	v.operator()(*this);
}

inline
void controller::Board::accept(Visitor & v)
{
	v.operator()(*this);
}
