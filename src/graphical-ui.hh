/**
 * @file   graphical-ui.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun Nov  6 17:18:07 2011
 *
 * @brief  Declaration of the graphical-ui class.
 */

#ifndef GRAPHICAL_UI_HH
# define GRAPHICAL_UI_HH

# include "user-interface.hh"
# include "gfx-window.hh"
# include "gfx-board.hh"

namespace view
{
	class GraphicalUI : public UserInterface
	{
	public:
		GraphicalUI();

		virtual void showMessage(const std::string) const{};
		virtual int getInt() const{return 1;};
		virtual std::string getString() const{return "top";};
		virtual std::string askName() const{return "Bob";};
		virtual bool askYesNo() const{return false;};

		virtual controller::BoardElement* askBuilding(const std::vector<controller::BoardElement*> & ) const;
		virtual int askProvostShift() const{return 1;};
		virtual int askChoice(int, int) const{return 4;};
		virtual int askChoice(std::vector<int>&) const{return 3;};
		virtual void updateBoard(const controller::GameEngine *) const;

	private:
		gfx::Window window_;
		gfx::LimitedEditionBoard board_;

		void drawBoard_() const;
	};
}

#endif
