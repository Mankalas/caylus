/*!
  \file   resource.hxx
  \brief  Inline implementations for Resource.

  \author nicuveo
  \date   2009-01-06
*/

#ifndef RESOURCE_HXX_
# define RESOURCE_HXX_

# include "resource.hh"

inline const std::list<controller::Resource>&
controller::Resource::list()
{
	return list_;
}

#endif /* !RESOURCE_HXX_ */
