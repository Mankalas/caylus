/*!
  \file   resource.hxx
  \brief  Inline implementations for Resource.

  \author nicuveo
  \date   2009-01-06
*/

#ifndef RESOURCE_HXX_
# define RESOURCE_HXX_

# include <boost/assign/list_of.hpp>
# include "resource.hh"

inline const std::list<Resource>&
Resource::list ()
{
  return list_;
}

#endif /* !RESOURCE_HXX_ */
