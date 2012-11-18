/**
 * @file   image-library.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Feb  9 17:45:03 2009
 *
 * @brief  Declaration of the gfx-image-library class.
 */

#ifndef IMAGELIBRARY_HH
# define IMAGELIBRARY_HH

# include <map>
# include <string>

namespace sf
{
	class Image;
}

namespace view
{
	/** \brief Object containing oftenly used images.
	 *
	 * This can avoid succeeding image loads and reloads. This class is
	 * a Singleton.
	 */
	class ImageLibrary
	{
	public:
		static ImageLibrary & inst();

		const sf::Image & get(std::string name) ;

	private:
		ImageLibrary();
		/** The images dictionnary. */
		std::map<std::string, sf::Image> images_;

		static ImageLibrary * instance_;
		void add(const std::string image_name, const std::string & image_path);
	};
}

#endif
