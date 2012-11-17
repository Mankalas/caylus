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

		Window();

		void draw(Sprite & sprite) const
		{
			window_->Draw(sprite.sfmlSprite());
		}

		void clear() const
		{
			window_->Clear();
		}

		void display() const
		{
			window_->Display();
		}

		void resize(float width, float height)
		{
			window_->SetSize(width, height);
		}

		std::pair<float, float> getClick() const;

	private:
		/** The SFML instance of a window. */
		sf::RenderWindow * window_;
	};

}

# include "gfx-window.hxx"

#endif // WINDOW_H
