/**
 * @file   gfx-window.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Wed Mar  4 22:16:48 2009
 *
 * @brief  Implementation of the gfx-window class.
 */

#include <iostream>
#include <string>
#include "gfx-window.hh"

using namespace gfx;

Window::Window()
{
	window_ =	new sf::RenderWindow(sf::VideoMode(1300, 950, 32),
																 std::string("Caylus"),
																 sf::Style::Resize | sf::Style::Close);
}

std::pair<float, float> Window::getClick() const
{
	bool done = false;
	while (!done)
		{
			sf::Event Event;
			while (window_->GetEvent(Event))
				{
					if (Event.Type == sf::Event::KeyPressed)
						{
							std::cout << Event.Key.Code << std::endl;
						}
					if (Event.Type == sf::Event::MouseButtonPressed)
						{
							//std::cout << Event.MouseButton.X << ", " << Event.MouseButton.Y << std::endl;
							return std::pair<float, float>(Event.MouseButton.X, Event.MouseButton.Y);
						}
				}
		}
	return std::pair<float, float>(0, 0);
}
