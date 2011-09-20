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

using namespace controller;

inline ResourceMap::operator std::vector<ResourceMap> () const
{
  return boost::assign::list_of (*this);
}

inline ResourceMap
operator + (const Resource& k, const ResourceMap& rmap)
{
  return rmap + k;
}

inline ResourceMap
operator - (const Resource& k, const ResourceMap& rmap)
{
  return ResourceMap (k) - rmap;
}

inline ResourceMap
operator * (const unsigned& mul, const ResourceMap& rmap)
{
  return rmap * mul;
}

inline ResourceMap
operator * (const Resource& k, unsigned i)
{
  return ResourceMap (k) * i;
}

inline ResourceMap
operator * (unsigned i, const Resource& k)
{
  return ResourceMap (k) * i;
}

#endif /* !RESOURCE_MAP_HXX_ */
