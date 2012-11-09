/*!
  \file   SpriteLibrary.hxx
  \brief  Implementation of SpriteLibrary's inline members.
  \author Mankalas
  \date   2008-04-23
*/

inline
gfx::SpriteLibrary * gfx::SpriteLibrary::instance()
{
	if (gfx::SpriteLibrary::instance_ == NULL)
	{
		gfx::SpriteLibrary::instance_ = new gfx::SpriteLibrary();
	}
	return gfx::SpriteLibrary::instance_;
}

inline
std::map<const std::string, gfx::Sprite *>& gfx::SpriteLibrary::getSprites()
{
	return sprites_;
}
