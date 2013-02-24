/**
 * @file   view.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Mon Sep 19 18:11:44 2011
 *
 * @brief  Declaration of the view class.
 */

#ifndef VIEW_HH
# define VIEW_HH

namespace controller
{
	class GameEngine;
}

namespace view
{
	/**
	 * Generic view. Abstract class. No constructor with a GameEngine
	 * parameter for passive views have a const instance, and active
	 * views have not.
	 */
	class View
	{
	public:
		/**
		 * Constructor.
		 */
		View(const controller::GameEngine * ge);

		/**
		 * Virtual destructor.
		 */
		virtual ~View() = 0;

	protected:
		const controller::GameEngine * game_engine_;
	};

}

#endif
