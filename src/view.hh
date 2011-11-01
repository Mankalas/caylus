/**
 * @file   view.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Mon Sep 19 18:11:44 2011
 *
 * @brief  Declaration of the view class.
 */

#ifndef VIEW_HH
# define VIEW_HH

# include <vector>
# include <boost/signal.hpp>
# include <boost/thread.hpp>

namespace controller
{
	class GameEngine;
	class BoardElement;
}

typedef boost::signal<int (void)>::slot_function_type ProvostShiftSlot;
typedef boost::signal<controller::BoardElement* (const std::vector<controller::BoardElement*> &)>::slot_function_type WorkerPlacementSlot;

namespace view
{

	class View
	{
	public:
		View(controller::GameEngine *ge);
		/**
		 * Copy contructor, in order to avoir compilation errors due to
		 * the non-copyable propertie of the View's condition_variable.
		 *
		 * @param v The copied view.
		 */
		View(View &v);
		virtual ~View();

		virtual std::string askName() const = 0;
		virtual bool isHuman() const = 0;

		virtual int askProvostShift() const = 0;
		virtual bool askYesNo() const = 0;
		virtual bool askJoustField() const = 0;
		virtual controller::BoardElement* askWorkerPlacement(const std::vector<controller::BoardElement*> & tbuildings) const = 0;
		virtual unsigned askBuilding() const = 0;
		virtual unsigned askResourceChoice() const = 0;

		virtual void operator()() = 0;

		ProvostShiftSlot getAskProvostShiftSlot() const;
		WorkerPlacementSlot getAskWorkerPlacementSlot() const;
		boost::signal<unsigned (void)>::slot_function_type getAskBuildingSlot() const;
		boost::signal<unsigned (void)>::slot_function_type getResourceChoice() const;

		boost::condition_variable *disconnected();

	protected:
		const controller::GameEngine *ge_;
		boost::condition_variable disconnected_;
	};

}

#endif
