/**
 * @file   gate.hh
 * @author Antoine Leblanc <nicuveo@gmail.com>
 * @date   Sat Oct 15 22:42:35 2011
 *
 * @brief  Declaration of the gate class.
 */

#ifndef GATE_HH_
# define GATE_HH_

# include "omniscient-building.hh"

namespace controller
{

	class Gate : public OmniscientBuilding
	{
	public:
		Gate(GameEngine * ge);

		virtual void onActivate(void);
	};

}
#endif /* !GATE_HH_ */
