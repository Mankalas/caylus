/**
 * @file   board.hxx
 * @author Vincent Boucheny <vincent.boucheny@hpc-sa.com>
 * @date   Sat Nov 17 19:46:15 2012
 *
 * @brief
 */

#ifndef BOARD_HXX
# define BOARD_HXX

# include "board.hh"

inline
const sf::Sprite & view::Board::sprite() const
{
	return sprite_;
}

inline
unsigned int view::Board::caseHeight() const
{
	return case_height_;
}

inline
unsigned int view::Board::caseWidth() const
{
	return case_width_;
}

#endif
