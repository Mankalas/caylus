/*!
  \file   resource-map.hxx
  \brief  Inline implementations for ResourceMap

  \author nicuveo
  \date   2009-01-06
*/

#ifndef RESOURCE_MAP_HXX_
# define RESOURCE_MAP_HXX_

# include <boost/assign/list_of.hpp>
# include "resource-map.hh"

inline controller::ResourceMap::operator std::vector<controller::ResourceMap> () const
{
	return boost::assign::list_of(*this);
}

inline controller::ResourceMap
operator + (const Resource & k, const controller::ResourceMap & rmap)
{
	return rmap + k;
}

inline controller::ResourceMap
operator - (const Resource & k, const controller::ResourceMap & rmap)
{
	return controller::ResourceMap(k) - rmap;
}

inline controller::ResourceMap
operator * (const unsigned & mul, const controller::ResourceMap & rmap)
{
	return rmap * mul;
}

inline controller::ResourceMap
operator * (const Resource & k, unsigned i)
{
	return controller::ResourceMap(k) * i;
}

inline controller::ResourceMap
operator * (unsigned i, const Resource & k)
{
	return controller::ResourceMap(k) * i;
}

#endif /* !RESOURCE_MAP_HXX_ */
