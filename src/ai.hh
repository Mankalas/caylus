/**
 * @file   ai.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Fri Dec 12 16:13:39 2008
 * @brief  Declaration of the ai class.
 */

#ifndef AI_HH
# define AI_HH

# include "view.hh"

namespace view
{
	/**
	 * AI implementation.
	 */
	class AI : public View
	{
	public:

		AI(controller::GameEngine *ge);

		virtual void operator()(){}

		virtual std::string askName() const;
		virtual bool isHuman() const;
		virtual int askProvostShift() const;
		virtual bool askYesNo() const;
		virtual bool askJoustField() const;
		virtual controller::BoardElement* askWorkerPlacement(const std::vector<controller::BoardElement *> & buildings) const;
		virtual unsigned askBuilding() const;
		virtual unsigned askResourceChoice() const;
	};

}

#endif
