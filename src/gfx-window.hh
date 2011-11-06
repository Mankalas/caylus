/**
 * @file   gfx-window.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Oct  5 17:35:53 2007
 *
 * @brief  Declaration of the gfx-window class.
 */

#ifndef WINDOW_H
# define WINDOW_H

# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>
# include "gfx-sprite.hh"

namespace gfx
{
	class Window
	{
	public:

		void draw(Sprite & sprite)
		{
			window->Draw(sprite.sfmlSprite());
		}

		void clear() const
		{
			window->Clear();
		}

		void display() const
		{
			window->Display();
		}

		void resize(float width, float height)
		{
			window->SetSize(width, height);
		}

	private:
		/** The SFML instance of a window. */
		static sf::RenderWindow * window;
	};

}

# include "gfx-window.hxx"

#endif // WINDOW_H
