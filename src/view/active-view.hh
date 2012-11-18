/**
 * @file   active-view.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun May 20 22:17:18 2012
 *
 * @brief  Declaration of the active-view class.
 */

#ifndef ACTIVE_VIEW_HH
# define ACTIVE_VIEW_HH

# include <vector>
# include <string>
# include "view.hh"

namespace controller
{
	class Player;
	class BoardElement;
}

namespace view
{
	/**
	 * Views that send information to the GameEngine. Abstract class.
	 */
	class ActiveView : public View
	{
	public:
		ActiveView(controller::GameEngine * ge);

		///
		virtual int askProvostShift() const = 0;
		///
		virtual unsigned int askWorkerPlacement() const = 0;
		///
		virtual std::string askName() const = 0;

	protected:
		controller::GameEngine * game_engine_;
		controller::Player * player_;
	};
}

#endif
