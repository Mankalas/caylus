/**
 * @file   graphic-view.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun Nov  6 17:18:07 2011
 *
 * @brief  Declaration of the graphic-view class.
 */

#ifndef GRAPHIC_VIEW_HH
# define GRAPHIC_VIEW_HH

# include "display-view.hh"
# include "../gfx/gfx-window.hh"
# include "../gfx/gfx-board.hh"
# include <vector>

namespace view
{
	class GraphicView : public DisplayView
	{
		public:

			GraphicView(const controller::GameEngine * game_engine);
			virtual controller::BoardElement * askBuilding(const std::vector<controller::BoardElement *> & choices) const;
			virtual void updateBoard();
			virtual int askProvostShift() const;

			virtual int askChoice(int, int) const;
			virtual int askChoice(std::vector<int>&) const;
			virtual void showMessage(const std::string) const;
			virtual int getInt() const;
			virtual std::string getString() const;
			virtual std::string askName() const;
			virtual bool askYesNo() const;

		void launch() const;

		private:
			gfx::Window window_;
			gfx::LimitedEditionBoard board_;
	};
}

#endif
