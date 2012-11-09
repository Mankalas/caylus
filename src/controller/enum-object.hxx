/*!
  \file   enum-object.hxx
  \brief  Implementation of EnumObject.

  \author nicuveo
  \date   2009-01-06
*/

#ifndef ENUM_OBJECT_HXX_
# define ENUM_OBJECT_HXX_

# include "enum-object.hh"

template <typename Exact>
unsigned controller::EnumObject<Exact>::ids_ = 0;

template <typename Exact>
inline bool
controller::EnumObject<Exact>::operator < (const controller::EnumObject<Exact>& elt) const
{
	return id_ < elt.id_;
}

template <typename Exact>
inline bool
controller::EnumObject<Exact>::operator > (const controller::EnumObject<Exact>& elt) const
{
	return id_ > elt.id_;
}

template <typename Exact>
inline bool
controller::EnumObject<Exact>::operator <= (const controller::EnumObject<Exact>& elt) const
{
	return id_ <= elt.id_;
}

template <typename Exact>
inline bool
controller::EnumObject<Exact>::operator >= (const controller::EnumObject<Exact>& elt) const
{
	return id_ >= elt.id_;
}

template <typename Exact>
inline bool
controller::EnumObject<Exact>::operator == (const controller::EnumObject<Exact>& elt) const
{
	return id_ == elt.id_;
}

template <typename Exact>
inline bool
controller::EnumObject<Exact>::operator != (const controller::EnumObject<Exact>& elt) const
{
	return id_ != elt.id_;
}

template <typename Exact>
inline const std::string &
controller::EnumObject<Exact>::name() const
{
	return name_;
}

template <typename Exact>
controller::EnumObject<Exact>::EnumObject(const std::string & name)
	: name_(name)
{
	id_ = ++ids_;
}

template <typename Exact>
std::ostream &
operator << (std::ostream & ostr, const controller::EnumObject<Exact>& r)
{
	ostr << r.name();
	return ostr;
}

#endif /* !ENUM_OBJECT_HXX_ */
