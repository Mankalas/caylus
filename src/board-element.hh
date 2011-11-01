/**
 * @file   board-element.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sat Oct 15 21:48:55 2011
 *
 * @brief  Declaration of the board-element class.
 */

#ifndef BOARD_ELEMENT_HH
# define BOARD_ELEMENT_HH

# include <vector>
# include <string>

namespace controller
{
	class BoardElement
	{
	public:
		BoardElement(const std::string & name);

		virtual bool isCastle() const;
		virtual bool isBuilding() const;
		virtual bool isBridge() const;
		virtual const std::string & name() const;

	protected:
		const std::string name_;
	};
}

#endif
