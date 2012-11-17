/**
 * @file   gfx-sprite-library.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Feb  9 17:45:03 2009
 *
 * @brief  Declaration of the gfx-sprite-library class.
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
	public:
		/** \brief Get the unique instance of the class.
		 *	\return The instance of SpriteLibrary.
		 */
		static SpriteLibrary * instance();

		/** \brief Get the images dictionnary.
		 *
		 *  \return The images dictionnary.
		 */
		std::map<const std::string, gfx::Sprite *>& getSprites();

		Sprite * sprite(const std::string & name) ;

	private:
		/** Default constructor. */
		SpriteLibrary();

		/** The unique instance of the class. */
		static SpriteLibrary * instance_;

		/** The images dictionnary. */
		std::map<const std::string, gfx::Sprite *>sprites_;

	};

}

# include "gfx-sprite-library.hxx"

#endif
