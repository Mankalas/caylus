/**
 * @file   board-element.hxx
 * @author Vincent Boucheny <vincent.boucheny@hpc-sa.com>
 * @date   Sat Mar 30 17:48:21 2013
 *
 * @brief  Declaration of the board-element class.
 */

#ifndef BOARD_ELEMENT_HXX
#define BOARD_ELEMENT_HXX

inline
const std::string & BoardElement::name() const
{
	return name_;
}

inline
BoardElementSignals & BoardElement::signals() const
{
	return signals_;
}

#endif
