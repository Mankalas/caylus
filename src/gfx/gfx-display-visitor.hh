/*!
  \file   DisplayVisitor.hh
  \brief  Declaration of DisplayVisitor.

  \author Mankalas
  \date   2007-10-05
*/

#ifndef DISPLAYVISITOR_H
# define DISPLAYVISITOR_H

# include <sstream>
# include <list>
# include "gfx-sprite.hh"
# include "../controller/game-engine.hh"
# include "../visitor.hh"

/** \brief Everything that has to access the graphical library is in
    this namespace. */
namespace gfx
{
	class Window;

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
		DisplayVisitor(Window &);


		/** \brief Display a Sprite.
		 *	\param	sprite The sprite to display.
		 */
		void operator()(const gfx::Sprite & sprite) const;

		virtual void operator()(const controller::GameEngine * game_engine) const;

		virtual void operator()(const controller::Board *) const;
		virtual void operator()(const controller::Road *) const;

	private:

		Window & window_;

	};

}

#endif // DISPLAYVISITOR_H
