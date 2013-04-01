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
# include "../controller/resource-map.hh"

namespace controller
{
	class Player;
	class ResourceMap;
}

namespace view
{
	/**
	 * Views that send information to the GameEngine. Abstract class.
	 */
	class ActiveView : public View
	{
	public:
		ActiveView(const controller::GameEngine * ge, const controller::Player * player);

		//* @name Game signals. */
		// @{

		/**
		 * Ask for the provost's shift. This method assures that the
		 * returned value in within the range [-3; 3].
		 *
		 * @return The provost's shift.
		 */
		virtual int askProvostShift() const = 0;

		virtual controller::ResourceMap askResource(const std::vector<controller::ResourceMap>& resource_choice) const = 0;
		///
		virtual unsigned int askBoardElement() const = 0;

		virtual bool askInnRemoval() const = 0;

		// @}

		///
		virtual std::string askName() const = 0;
		///
		virtual unsigned int askChoice(unsigned int range) const = 0;
		///
		virtual bool askYesNo() const = 0;

	protected:
		const controller::Player * player_;
	};
}

#endif
