/*!
  \file   favor-building.hh
  \brief  This file contains FavorBuilding class.

  \author nivuceo
  \date   2009-01-06
*/

#ifndef FAVOR_BUILDING_HH_
# define FAVOR_BUILDING_HH_

# include "building.hh"

/** \brief It represents the buildings which give the builder royal
 * favors. It therefore overrides the on_build method in order to
 * trigger the favor selection mechanism.
 *
 */
class FavorBuilding : virtual public Building
{
  public:
    ~FavorBuilding();

  protected:
    FavorBuilding();

    virtual void on_build ();
};

#endif /* !FAVOR_BUILDING_HH_ */
