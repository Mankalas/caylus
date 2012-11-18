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
# include "board.hh"
# include <vector>
# include <SFML/System/Vector2.hpp>

namespace sf
{
	class RenderWindow;
}

namespace view
{
	class LimitedEditionBoard;

	class GraphicView : public DisplayView
	{
	public:

		GraphicView(const controller::GameEngine * game_engine);
		virtual unsigned int askCaseNumber() const;
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
		sf::Vector2<int> getClick() const;

		sf::RenderWindow * window_;
		LimitedEditionBoard board_;
	};
}

#endif
