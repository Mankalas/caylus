/*!
  \file   resource-map.hh
  \brief  This file contains ResourceMap class declaration.

  \author nicuveo
  \date   2009-01-06
*/

#ifndef RESOURCE_MAP_HH_
# define RESOURCE_MAP_HH_

# include <map>
# include <vector>
# include "resource.hh"

namespace controller
{

	/** \brief It is a container that maps a quantity to each of the possible
	 * resources (obtained via the static list of Resource class).
	 * Many operators are overloaded:
	 *   - [] operator is used to directly access the associated
	 *     quantities,
	 *   - comparison operators may be used to compare all the elements
	 *     in two maps: if map1 >= map2 then for each resource in the maps
	 *     the associated quantity in r1 is greater than or equal to the
	 *     the quantity stored in r2,
	 *   - mathematical operators may be used to combine maps, as
	 *     explained below,
	 *   - cast operators and implicit constructors for the same reason.
	 *
	 * Expressions:
	 *   Resources can be added and multiplied by scalars in order to
	 *   create the associated ResourceMap:
	 *      "3 * Resource::gold + 5 * Resource::stone"
	 *   Maps themselves can be compined with + or - operators:
	 *      "(3 * Resource::gold) + (5 * Resource::stone)"
	 *   Implicit constructor allows to create a map from a resource:
	 *      "ResourceMap m = Resource::denier"
	 *   Conversion operator allow to implicitely create a vector of maps
	 *   (used mainly with building costs):
	 *      "std::vector<ResourceMap> v = 3 * Resource::denier"
	 */
	class ResourceMap
	{
	public:
		explicit ResourceMap(const unsigned & value = 0);
		ResourceMap(const Resource & k);

		operator std::vector<ResourceMap> () const;

		unsigned & operator [](const Resource & r);
		unsigned  operator [](const Resource & r) const;

		bool operator > (const ResourceMap & rmap) const;
		bool operator < (const ResourceMap & rmap) const;
		bool operator >= (const ResourceMap & rmap) const;
		bool operator <= (const ResourceMap & rmap) const;
		bool operator == (const ResourceMap & rmap) const;
		bool operator != (const ResourceMap & rmap) const;

		ResourceMap  operator + (const ResourceMap & rmap) const;
		ResourceMap  operator - (const ResourceMap & rmap) const;
		ResourceMap & operator += (const ResourceMap & rmap);
		ResourceMap & operator -= (const ResourceMap & rmap);

		ResourceMap  operator * (const unsigned & mul) const;
		ResourceMap & operator *= (const unsigned & mul);

		bool canPay(const ResourceMap & r) const;

	private:
		std::map<Resource, unsigned> map_;
	};

}

using namespace controller;

ResourceMap operator + (const Resource & k,   const ResourceMap & rmap);
ResourceMap operator - (const Resource & k,   const ResourceMap & rmap);
ResourceMap operator * (const unsigned & mul, const ResourceMap & rmap);

ResourceMap operator * (const Resource & k, unsigned i);
ResourceMap operator * (unsigned i, const Resource & k);

std::ostream & operator << (std::ostream &, const ResourceMap &);

# include "resource-map.hxx"

#endif /* !RESOURCE_MAP_HH_ */
