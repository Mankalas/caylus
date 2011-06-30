/*!
  \file   building-type.hh
  \brief  This file contains BuildingType class.

  \author nicuveo
  \date   2009-01-06
*/

#ifndef BUILDING_TYPE_HH_
# define BUILDING_TYPE_HH_

# include "enum-object.hh"

/** \brief This class is used as an "enum object" (hence the include),
    please see enum-object.hh for more information.
 *
 *  A building can be one of those six types:
 *   - fixed (drawn on the board),
 *   - neutral (pink tiles placed at the beginning),
 *   - made of wood,
 *   - made of stone,
 *   - residential (the residences)
 *   - prestige
 *
 * As enum objects, they can be compared and ordered (as each has a
 * unique id) with usual operators and can therefore be used as key
 * in maps or hash tables. Their name can be printed with << operator.
 */
class BuildingType : public EnumObject<BuildingType>
{
public:
  BuildingType (const BuildingType& r = BuildingType::neutral);

  static const BuildingType fixed;
  static const BuildingType neutral;
  static const BuildingType wood;
  static const BuildingType stone;
  static const BuildingType residential;
  static const BuildingType prestige;

private:
  BuildingType (const std::string& name);
};

#endif /* !BUILDING_TYPE_HH_ */
