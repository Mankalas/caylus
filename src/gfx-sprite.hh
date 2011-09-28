/*!
  \file   Sprite.hh
  \brief  Declaration of Sprite.

  \author Mankalas
  \date   2007-10-05
*/

#ifndef GFX_SPRITE_HH
# define GFX_SPRITE_HH

# include <SFML/Graphics.hpp>
# include <SFML/Graphics/Color.hpp>

namespace gfx
{

	/** \brief A Sprite is an object to be displayed on a screen.
	 *
	 * A home-made Sprite object in order to be graphical
	 * library-independent. A Sprite is an object that will be displayed
	 * in the rendering window. It contains data such as the image
	 * itself, the rectangle it occupies, etc.
	 */
	class Sprite
	{
		private:

			sf::Sprite sprite_;
			sf::Image *image_;

		public:

			Sprite();
			Sprite(const std::string file_name);
			Sprite(const Sprite &copy);
			~Sprite();

			float getWidth() const;
			float getHeight() const;

			float getLeft() const;
			float &getLeft();

			float getTop() const;
			float &getTop();

			void setPosition(const float left, const float top);
			void move(const float left, const float top);

			/// Accessors.
			const sf::Sprite &getSprite() const;
			const sf::Image *getImage() const;

	};

}

# include "gfx-sprite.hxx"

#endif
