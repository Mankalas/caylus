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
namespace view
{
	class Human : public ActiveView
	{
	public:
		Human(controller::GameEngine *ge, bool command_line);
		virtual ~Human();

		virtual std::string askName() const;
		virtual bool isHuman() const;
		virtual bool isInteractive() const;

		virtual int askProvostShift() const;
		virtual bool askYesNo() const;
		virtual bool askJoustField() const;
		virtual controller::BoardElement* askWorkerPlacement(const std::vector<controller::BoardElement *> & buildings) const;
		virtual void boardElementActivation(const controller::BoardElement * board_elt);
		virtual void updateBoard();
		virtual unsigned askBuilding() const;
		virtual unsigned askResourceChoice() const;

		unsigned askNbHumans(unsigned max) const;
		unsigned askNbAIs(unsigned min, unsigned max) const;

		boost::signal<unsigned (unsigned)>::slot_function_type getAskNbHumansSlot() const;
		boost::signal<unsigned (unsigned, unsigned)>::slot_function_type getAskNbAIsSlot() const;

		void operator()();

	private:
		DisplayView * gui_;
	};

}

#endif
