/**
 * @file   gfx-window.cc
 * @author  <mankalas@magicwood>
 * @date   Wed Mar  4 22:16:48 2009
 *
 * @brief  Implementation of the Window class.
 */

#include <iostream>
#include <string>
#include "gfx-window.hh"

sf::RenderWindow *gfx::Window::window =
    new sf::RenderWindow(sf::VideoMode(800, 600, 32),
                         std::string("Caylus"),
                         sf::Style::Close);

gfx::Window::Window():
	height_(gfx::Window::window->GetHeight()),
	width_(gfx::Window::window->GetWidth()),
	view_(sf::View(gfx::Window::window->GetView()))
{
	//gfx::Window::window->SetView(_view);
}

gfx::Window::~Window() {}

void gfx::Window::moveView(int x, int y)
{
	view_.SetCenter(gfx::Window::window->GetFrameTime() * x,
	                gfx::Window::window->GetFrameTime() * y);
	gfx::Window::window->SetView(view_);
}
