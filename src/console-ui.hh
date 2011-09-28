/**
 * @file   console-ui.hh
 * @author  <mankalas@localhost,>
 * @date   Tue Jan 20 21:14:58 2009
 *
 * @brief
 *
 *
 */

#ifndef CONSOLE_UI_HH
# define CONSOLE_UI_HH

# include <string>
# include <vector>
# include "user-interface.hh"

namespace view
{
	class ConsoleUI : public UserInterface
	{
		public:

			int askProvostShift() const;
			int askChoice(int, int) const;
			int askChoice(std::vector<int>&) const;

			virtual void showMessage(const std::string) const;
			virtual int getInt() const;
			virtual std::string getString() const;
			virtual std::string askName() const;
			virtual bool askYesNo() const;
			virtual void updateBoard(/*GameEngine &ge*/) const {};
	};

}

#endif //CONSOLE_UI_HH
