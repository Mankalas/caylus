/*!
  \file   ai.h
  \brief  AI declaration

  \author Mankalas
  \date   2008-12-14
*/


#ifndef AI_HH
# define AI_HH

# include "view.hh"

namespace view
{

	class AI : public View
	{
		public:

			AI(controller::GameEngine *ge);

			virtual std::string askName() const;
			virtual bool isHuman() const;
			virtual int askProvostShift() const;
			virtual bool askYesNo() const;
			virtual bool askJoustField() const;
			virtual int askWorkerPlacement() const;
			virtual unsigned askBuilding() const;
			virtual unsigned askResourceChoice() const;
	};

}
#endif
