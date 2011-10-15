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

namespace view
{

	class View
	{
	public:
		View(controller::GameEngine *ge);
		~View();

		virtual std::string askName() const = 0;
		virtual bool isHuman() const = 0;

		virtual int askProvostShift() const = 0;
		virtual bool askYesNo() const = 0;
		virtual bool askJoustField() const = 0;
		virtual controller::BoardElement* askWorkerPlacement(const std::vector<controller::BoardElement*> buildings) const = 0;
		virtual unsigned askBuilding() const = 0;
		virtual unsigned askResourceChoice() const = 0;

		virtual void operator()() = 0;

		boost::signal<int (void)>::slot_function_type getAskProvostShiftSlot() const;

		boost::signal<controller::BoardElement* (std::vector<controller::BoardElement*>)>::slot_function_type getAskWorkerPlacementSlot() const;
		boost::signal<unsigned (void)>::slot_function_type getAskBuildingSlot() const;
		boost::signal<unsigned (void)>::slot_function_type getResourceChoice() const;


	protected:
		const controller::GameEngine *ge_;
		//		std::vector<controller::GameEngine::connection_t> connections_;
		boost::condition_variable *disconnected_;
	};

}
#endif
