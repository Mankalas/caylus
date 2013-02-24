/**
 * @file   display-view.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun May 20 22:30:08 2012
 *
 * @brief  Declaration of the display-view class.
 */

#ifndef DISPLAY_VIEW_HH
# define DISPLAY_VIEW_HH

# include "passive-view.hh"
# include <vector>
# include <string>

namespace controller
{
	class GameEngine;
}

namespace view
{
	class DisplayView : public PassiveView
	{
	public:
		DisplayView(const controller::GameEngine * ge);

		virtual int askProvostShift() const = 0;
		virtual void updateBoard() = 0;
		virtual unsigned int askCaseNumber() const = 0;

		virtual int askChoice(int, int) const = 0;
		virtual int askChoice(std::vector<int>&) const = 0;
		virtual void showMessage(const std::string) const = 0;
		virtual int getInt() const = 0;
		virtual std::string getString() const = 0;
		virtual std::string askName() const = 0;
		virtual bool askYesNo() const = 0;

	private:
	};
}

#endif
