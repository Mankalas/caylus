/**
 * @file   gfx-window.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Wed Mar  4 22:16:48 2009
 *
 * @brief  Declaration of the gfx-window class.
 */

#include <iostream>
#include <string>
#include "gfx-window.hh"

sf::RenderWindow *gfx::Window::window =	new sf::RenderWindow(sf::VideoMode(800, 600, 32),
																														 std::string("Caylus"),
																														 sf::Style::Close);
