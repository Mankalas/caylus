/**
 * @file   human.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Dec 14 22:20:55 2011
 *
 * @brief  Declaration of the human class.
 */


#ifndef HUMAN_HH
# define HUMAN_HH

# include "active-view.hh"
# include "display-view.hh"
# include <vector>
# include <boost/signal.hpp>

namespace controller
{
	class GameEngine;
	class Player;
}

namespace view
{
	class Human : public ActiveView
	{
	public:
		Human(const controller::GameEngine * ge, const controller::Player * player, DisplayView *);
		virtual ~Human();


		virtual bool isHuman() const;
		virtual bool isInteractive() const;

		virtual bool askYesNo() const;
		virtual bool askJoustField() const;

		virtual int askProvostShift() const;
		virtual unsigned int askWorkerPlacement() const;
		virtual std::string askName() const;
		virtual unsigned int askChoice(unsigned int range) const;

		virtual void updateBoard();
		virtual unsigned askBuilding() const;
		virtual unsigned askResourceChoice() const;


		unsigned askNbHumans(unsigned max) const;
		unsigned askNbAIs(unsigned min, unsigned max) const;

		boost::signal<unsigned(unsigned)>::slot_function_type getAskNbHumansSlot() const;
		boost::signal<unsigned(unsigned, unsigned)>::slot_function_type getAskNbAIsSlot() const;

		void operator()();

	private:
		DisplayView * gui_;
	};

}

#endif
