/*!
  \file   SpriteLibrary.cc
  \brief  Implementation of SpriteLibrary

  \author Mankalas
  \date   2008-02-10
*/

#include "gfx-sprite-library.hh"

gfx::SpriteLibrary* gfx::SpriteLibrary::instance_ = NULL;

gfx::SpriteLibrary::SpriteLibrary()
{
  sprites_ = std::map<std::string, gfx::Sprite*>();
  sprites_["board"] = new gfx::Sprite("../share/img/board_limited_edition.jpg");
}
