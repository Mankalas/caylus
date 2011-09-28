/*!
  \file   SpriteLibrary.cc
  \brief  Implementation of SpriteLibrary

  \author Mankalas
  \date   2008-02-10
*/

#include "gfx-sprite-library.hh"

using namespace gfx;

SpriteLibrary *SpriteLibrary::instance_ = NULL;

SpriteLibrary::SpriteLibrary()
{
	sprites_ = std::map<std::string, Sprite *>();
	sprites_["board"] = new Sprite("../share/img/board_limited_edition.jpg");
}
