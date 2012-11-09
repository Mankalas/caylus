/**
 * @file   console-view.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Tue Jan 20 21:14:58 2009
 *
 * @brief  Declaration of the console-view class.
 */

#ifndef CONSOLE_VIEW_HH
# define CONSOLE_VIEW_HH

# include "display-view.hh"

namespace view
{
	class ConsoleView : public DisplayView
	{
		public:

			ConsoleView(const controller::GameEngine * game_engine);

			virtual int askProvostShift() const;
			virtual void updateBoard(const controller::GameEngine * ge) const;
			virtual controller::BoardElement * askBuilding(const std::vector<controller::BoardElement *> & choices) const;

			virtual int askChoice(int, int) const;
			virtual int askChoice(std::vector<int>&) const;
			virtual void showMessage(const std::string) const;
			virtual int getInt() const;
			virtual std::string getString() const;
			virtual std::string askName() const;
			virtual bool askYesNo() const;

		private:
			int getInputInt_(int min, int max) const;
	};

}

#endif //CONSOLE_VIEW_HH
