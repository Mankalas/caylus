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
# include "game-engine.hh"

/** \brief Everything that has to access the graphical library is in
    this namespace. */
namespace gfx {

  class Sprite;

  /** \brief This visitor pattern is used to display graphical
   * objects.
   *
   * The Visitor explores miscellaneous objects and uses the
   * configured graphical library to display them on the game's
   * screen.
   */
  class DisplayVisitor
  {
  public:
    /** \brief Display a Sprite.
     *	\param	sprite The sprite to display.
     */
    void operator()(gfx::Sprite& sprite);

    void operator()(GameEngine& game_engine);

  };

}
#endif // DISPLAYVISITOR_H
