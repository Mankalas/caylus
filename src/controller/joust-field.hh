/**
 * @file   joust-field.hh
 * @author  <mankalas@localhost,>
 * @date   Wed Feb  4 11:39:43 2009
 *
 * @brief
 *
 *
 */

#ifndef JOUST_FIELD_HH
# define JOUST_FIELD_HH

# include "building.hh"

namespace controller
{

	class JoustField : public Building
	{
		public:
			JoustField();
			virtual void on_activate(void);

		private:
			boost::signal<bool (void)> ask_proceed_;
	};

}

#endif //JOUST_FIELD_HH