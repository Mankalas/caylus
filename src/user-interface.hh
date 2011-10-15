#ifndef USER_INTERFACE_HH
# define USER_INTERFACE_HH

# include <string>
# include <vector>

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

		virtual BuildingSmartPtr askBuilding(std::vector<BuildingSmartPtr> buildings) const = 0;
			virtual int askProvostShift() const = 0;
			virtual int askChoice(int, int) const = 0;
			virtual int askChoice(std::vector<int>&) const = 0;
			virtual void updateBoard(/*GameEngine &ge*/) const = 0;
	};

}
#endif
