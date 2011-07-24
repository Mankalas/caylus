/*!
  \file   Window.cc
  \brief  Implementation of the Window's inline members.

  \author Mankalas
  \date   2007-10-05
*/

inline
void gfx::Window::setHeight (const unsigned int height)
{
  height_ = height;
}

inline
unsigned int gfx::Window::getHeight() const
{
  return gfx::Window::window->GetHeight();
}

inline
void gfx::Window::setWidth (const unsigned int width)
{
  width_ = width;
}

inline
unsigned int gfx::Window::getWidth() const
{
  return gfx::Window::window->GetWidth();
}

inline
void gfx::Window::resize (const unsigned int width,
                          const unsigned int height)
{
  height_ = height;
  width_ = width;
}

inline
void gfx::Window::setViewPos(const int x, const int y)
{
  view_.SetCenter(x, y);
}
