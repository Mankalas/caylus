/*!
  \file   enum-object.hh
  \brief  This file contains EnumObject templated class.

  \author nicuveo
  \date   2009-01-06
*/

#ifndef ENUM_OBJECT_HH_
# define ENUM_OBJECT_HH_

# include <iostream>
# include <string>
# include <list>

/** \brief It is made to be used as the base class to any enum
 * object. It uses static inheritance: the Exact template type
 * corresponds to the real derived type.
 *
 * The main idea is simple: with a static unsigned attribute, each
 * created instance has a unique id. As each usual comparison operator
 * is declared, they can be easily compared (in a switch statement) or
 * used as keys in standard containers.
 *
 * The constructor takes a string which is the name each enum field
 * will use when printed by operator <<.
 *
 * The way instances can be copied (or not) has to be defined in
 * derived classes.
 *
 */
template <typename Exact>
class EnumObject
{
public:
  bool operator <  (const EnumObject& elt) const;
  bool operator >  (const EnumObject& elt) const;
  bool operator <= (const EnumObject& elt) const;
  bool operator >= (const EnumObject& elt) const;
  bool operator == (const EnumObject& elt) const;
  bool operator != (const EnumObject& elt) const;

  const std::string& name () const;

protected:
  EnumObject (const std::string& name);

  static unsigned ids_;

  std::string name_;
  unsigned id_;
};

template <typename Exact>
std::ostream& operator << (std::ostream&, const EnumObject<Exact>&);

#include "enum-object.hxx"

#endif /* !ENUM_OBJECT_HH_ */
