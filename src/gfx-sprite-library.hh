/*!
  \file   SpriteLibrary.hh
  \brief  Declaration of SpriteLibrary.

  \author Mankalas
  \date   2008-02-09
*/

#ifndef SPRITELIBRARY_HH
# define SPRITELIBRARY_HH

# include <map>
# include <string>
# include "gfx-sprite.hh"

namespace gfx
{

  /** \brief Object containing oftenly used images.
   *
   * This can avoid succeeding image loads and reloads. This class is
   * a Singleton.
   */
  class SpriteLibrary
  {
  private:
    /** Default constructor. */
    SpriteLibrary();

    /** The unique instance of the class. */
    static SpriteLibrary* instance_;

    /** The images dictionnary. */
    std::map<std::string, gfx::Sprite*>	sprites_;

  public:
    /** \brief Get the unique instance of the class.
     *	\return The instance of SpriteLibrary.
     */
    static SpriteLibrary* instance();

    /** \brief Get the images dictionnary.
     *
     *  \return The images dictionnary.
     */
    std::map<std::string, gfx::Sprite*>& getSprites();
  };

}

# include "gfx-sprite-library.hxx"

#endif
