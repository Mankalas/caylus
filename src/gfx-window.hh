/*!
  \file   Window.hh
  \brief  Declaration of the Window class.

  \author Mankalas
  \date   2007-10-05
*/

#ifndef WINDOW_H
# define WINDOW_H

# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>

namespace gfx
{

	/** \brief Handle the window's behaviour. */
	class Window
	{
		private:

			unsigned int height_;
			unsigned int width_;
			sf::View view_;

		public:

			/** The SFML instance of a window. */
			static sf::RenderWindow *window;

			/** Default constructor. */
			Window();

			/** Default destructor. */
			~Window();

			/** \brief Resize the window.
			 * @param  width
			 * @param  height
			 */
			void resize(const unsigned int width, const unsigned int height);

			/** \brief Move the current view according to offsets.
			 *
			 *  \param x X offset.
			 *	\param y Y offset.
			 */
			void moveView(const int x, const int y);

			/** \brief Set the current view position.
			 *
			 *  \param x X coord.
			 *	\param y Y coord.
			 */
			void setViewPos(const int x, const int y);

			/// Accessors.

			void setHeight(const unsigned int height);
			unsigned int getHeight() const;
			void setWidth (const unsigned int width);
			unsigned int getWidth() const;
	};

}

# include "gfx-window.hxx"

#endif // WINDOW_H
