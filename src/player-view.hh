/**
 * @file   player-view.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Mon Apr  9 21:37:08 2012
 *
 * @brief  Declaration of the player-view class.
 */

#ifndef PLAYER_VIEW_HH
# define PLAYER_VIEW_HH

# include "view.hh"

namespace controller
{
	class GameEngine;
	class BoardElement;
}

typedef boost::signal<int (void)>::slot_function_type ProvostShiftSlot;
typedef boost::signal<controller::BoardElement* (const std::vector<controller::BoardElement*> &)>::slot_function_type WorkerPlacementSlot;

namespace view
{
	class PlayerView : public View
	{
	public:
		PlayerView(const controller::GameEngine * ge);
		~PlayerView();

		virtual bool isInteractive() const = 0;

		virtual bool isHuman() const = 0;

		virtual int askProvostShift() const = 0;
		virtual bool askYesNo() const = 0;
		virtual bool askJoustField() const = 0;
		virtual controller::BoardElement* askWorkerPlacement(const std::vector<controller::BoardElement*> & tbuildings) const = 0;
		virtual unsigned askBuilding() const = 0;
		virtual unsigned askResourceChoice() const = 0;
		virtual void updateBoard() = 0;

		virtual void operator()() = 0;

		ProvostShiftSlot askProvostShiftSlot() const;
		WorkerPlacementSlot askWorkerPlacementSlot() const;
		boost::signal<unsigned (void)>::slot_function_type askBuildingSlot() const;
		boost::signal<unsigned (void)>::slot_function_type resourceChoiceSlot() const;

	protected:
		const controller::GameEngine *ge_;
	};
}

#endif
