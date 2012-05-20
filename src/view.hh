/**
 * @file   view.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Mon Sep 19 18:11:44 2011
 *
 * @brief  Declaration of the view class.
 */

#ifndef VIEW_HH
# define VIEW_HH

# include <vector>
# include <boost/signal.hpp>
# include <boost/thread.hpp>
# include "signals.hh"

namespace controller
{
	class GameEngine;
}

namespace view
{
	/**
	 * Generic view. Abstract class.
	 */
	class View
	{
	public:
		/**
		 * Constructor.
		 */
		View();

		/**
		 * Virtual destructor.
		 */
		virtual ~View() = 0;
	};

}

#endif
