/**
 * @file   passive-view.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun May 20 22:20:57 2012
 *
 * @brief  Declaration of the passive-view class.
 */

#ifndef PASSIVE_VIEW_HH
# define PASSIVE_VIEW_HH

# include "view.hh"

namespace view
{
	/**
	 * Views that only receive information from the GameEngine. Abstract class.
	 */
	class PassiveView : public View
	{
	public:
		PassiveView(const controller::GameEngine * ge);
	};
}

#endif
