/**
 * @file   ai.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Fri Dec 12 16:13:39 2008
 * @brief  Declaration of the ai class.
 */

#ifndef AI_HH
# define AI_HH

# include "active-view.hh"

namespace controller
{
	class GameEngine;
	class Player;
	class BoardElement;
}

namespace view
{
	/**
	 * AI implementation.
	 */
	class AI : public ActiveView
	{
	public:

		AI(const controller::GameEngine * ge, const controller::Player * player);

		virtual bool isInteractive() const;

		virtual void operator()() {}


		virtual bool isHuman() const;

		virtual int askProvostShift() const;
		virtual std::string askName() const;
		virtual unsigned int askChoice(unsigned int range) const;
		virtual unsigned int askWorkerPlacement() const { return 0; };

		virtual controller::ResourceMap askResource(const std::vector<controller::ResourceMap>& resource_choice) const = 0;

		virtual bool askYesNo() const;
		virtual bool askJoustField() const;


		virtual controller::BoardElement * askWorkerPlacement(const std::vector<controller::BoardElement *> & buildings) const;
		virtual unsigned askBuilding() const;
		virtual unsigned askResourceChoice() const;
		virtual void boardElementActivation(const controller::BoardElement * board_elt);
		virtual void updateBoard();

	};

}

#endif
