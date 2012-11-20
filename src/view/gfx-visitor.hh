/*!
  \file   DisplayVisitor.hh
  \brief  Declaration of DisplayVisitor.

  \author Mankalas
  \date   2007-10-05
*/

#ifndef DISPLAYVISITOR_H
# define DISPLAYVISITOR_H

# include "../visitor.hh"

namespace sf
{
	class RenderWindow;
	class Sprite;
	template<class T>
	class Vector2;
	class Color;
}

/**-namespace controller
{
	class GameEngine;
	class Road;
	class Board;
	class Player;
	class Building;
	class Stables;
	}*/

/** \brief Everything that has to access the graphical library is in
    this namespace. */
namespace view
{
	class Board;

	/** \brief This visitor pattern is used to display graphical
	 * objects.
	 *
	 * The Visitor explores miscellaneous objects and uses the
	 * configured graphical library to display them on the game's
	 * screen.
	 */
	class DisplayVisitor : public ConstVisitor
	{
	public:
		DisplayVisitor(sf::RenderWindow &, Board &);

		virtual void operator()(const controller::GameEngine &);
		virtual void operator()(const controller::Board &);
		virtual void operator()(const controller::Road &);
		virtual void operator()(const controller::Player &);
		virtual void operator()(const controller::Stables & stables);
		virtual void operator()(const controller::Building & building);

	private:
		sf::RenderWindow & window_;
		Board & board_;
		/// To remember which case of the road we are visiting.
		unsigned int road_idx_;

		void centerSprite(sf::Sprite & sprite,
		                  sf::Vector2<unsigned int> & position,
		                  sf::Vector2<unsigned int> & size) const;

		void drawResource(int resource, sf::Color color, int top) const;
	};
}

#endif // DISPLAYVISITOR_H
