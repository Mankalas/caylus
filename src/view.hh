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
# include "signals.hh"

namespace view
{

	class View
	{
	public:
		View();
		/**
		 * Copy contructor, in order to avoir compilation errors due to
		 * the non-copyable propertie of the View's condition_variable.
		 *
		 * @param v The copied view.
		 */
		View(View &v);
		virtual ~View();

		virtual void boardElementActivation(const controller::BoardElement * board_elt) = 0;
		virtual void updateBoard() = 0;

		boost::signal<void (void)>::slot_function_type updateBoardSlot();
		board_element_activation_signal_t::slot_function_type boardElementActivationSlot();

		boost::condition_variable *disconnected();

	protected:
		boost::condition_variable disconnected_;
	};

}

#endif
