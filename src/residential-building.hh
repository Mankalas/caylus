/*!
  \file   residential-building.hh
  \brief  This file contains ResidentialBuilding class declaration.

  \author nicuveo
  \date   2009-01-06
*/

#ifndef RESIDENTIAL_BUILDING_HH_
# define RESIDENTIAL_BUILDING_HH_

# include "building.hh"

namespace controller
{

	/** \brief It represents any building that gives additional credits at
	 * the beginning of each turn. This corresponds to three buildings in
	 * the game: residences, the library and the hotel. The additional
	 * argument given to the constructor corresponds to the number of
	 * deniers the building is worth each turn.
	 */
	class ResidentialBuilding : public virtual Building
	{
	public:
		~ResidentialBuilding();

		const unsigned deniers;

	protected:
		ResidentialBuilding (unsigned deniers = 1);

		virtual void on_build ();
		virtual void on_demolish ();
	};

}

#endif /* !RESIDENTIAL_BUILDING_HH_ */
