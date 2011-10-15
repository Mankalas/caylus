/**
 * @file   gate.cc
 * @author  <mankalas@localhost,>
 * @date   Thu Jan 15 14:18:10 2009
 *
 * @brief Implementation of the Gate
 */

#include "exceptions.hh"
#include "gate.hh"
#include "console-ui.hh"

Gate::Gate(GameEngine *ge)
	: Building("Gate",
	           BuildingType::fixed,
	           ResourceMap(0),
	           ResourceMap(0)),
	OmniscientBuilding(ge)
{
}

void Gate::on_activate()
{
	BuildingSmartPtr building;

	try
	{
		building = worker_->askWorkerPlacement(game_.road().getAvailableBuildingsForPlayer());
	}
	catch (OccupiedBuildingEx *)
	{
		on_activate();
	}
	catch (UnactivableBuildingEx *)
	{
		on_activate();
	}
}
