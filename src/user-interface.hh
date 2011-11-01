#ifndef USER_INTERFACE_HH
# define USER_INTERFACE_HH

# include <string>
# include <vector>
# include "board-element.hh"

namespace controller
{
	class GameEngine;
}

namespace view
{
	class UserInterface
	{
	public:

		virtual void showMessage(const std::string msg) const = 0;
		virtual int getInt() const = 0;
		virtual std::string getString() const = 0;
		virtual std::string askName() const = 0;
		virtual bool askYesNo() const = 0;

		virtual controller::BoardElement* askBuilding(const std::vector<controller::BoardElement*> & choices) const = 0;
		virtual int askProvostShift() const = 0;
		virtual int askChoice(int, int) const = 0;
		virtual int askChoice(std::vector<int>&) const = 0;
		virtual void updateBoard(const controller::GameEngine * ge) const = 0;
	};

}
#endif
