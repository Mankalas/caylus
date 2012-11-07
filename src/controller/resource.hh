/**
 * @file   resource.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Jan 6 20:07:15 2011
 *
 * @brief  Declaration of the resource class.
 */

#ifndef RESOURCE_HH_
# define RESOURCE_HH_

# include <vector>
# include <boost/foreach.hpp>
# include "enum-object.hh"

namespace controller
{

	/** \brief This class is used as an "enum object" (hence the include),
	 * please see enum-object.hh for more information.
	 *
	 * There are eight different resources in the game:
	 *   - food,
	 *   - wood,
	 *   - cloth,
	 *   - stone,
	 *   - gold,
	 *   - denier,
	 *   - prestige,
	 *   - favor.
	 *
	 * As enum objects, they can be compared and ordered (as each has a
	 * unique id) with usual operators and can therefore be used as key in
	 * maps or hash tables. Their name can be printed with << operator.
	 *
	 * Resource also define a static list of all instances (updated in the
	 * constructor) which allows ResourceMap to iterate over all possible
	 * resource types.
	 */
	class Resource : public EnumObject<Resource>
	{
		public:
			Resource (const Resource &r = Resource::food);

			static const std::list<Resource>& list ();

			static const Resource food;
			static const Resource wood;
			static const Resource cloth;
			static const Resource stone;
			static const Resource gold;
			static const Resource denier;
			static const Resource prestige;
			static const Resource favor;

		private:
			Resource (const std::string &name);

			static std::list<Resource> list_;
	};

}

# include "resource.hxx"

#endif /* !RESOURCE_HH_ */
