#ifndef GRAPHICAL_UI_HH
# define GRAPHICAL_UI_HH

namespace view
{
	class GraphicalUI : public UserInterface
	{

		virtual void showMessage(const std::string msg) const {};
		virtual int getInt() const {};
		virtual std::string getString() const {};
		virtual std::string askName() const {};
		virtual bool askYesNo() const {};

		virtual int askProvostShift() const {};
		virtual int askChoice(int, int) const {};
		virtual int askChoice(std::vector<int>&) const {};
		virtual void updateBoard(/*GameEngine &ge*/) const {};
	};
}

#endif
