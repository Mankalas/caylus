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
# include "../signals.hh"

namespace view
{
	class View;
	class PlayerView;
}

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

			virtual void on_activate() = 0;

			mutable board_element_activation_signal_t activation_sig;

		protected:
			const std::string name_;
	};
}

#endif
