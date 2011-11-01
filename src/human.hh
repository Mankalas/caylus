/**
 * @file   human.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Dec 14 22:20:55 2011
 *
 * @brief  Declaration of the human class.
 */


#ifndef HUMAN_HH
# define HUMAN_HH

# include "view.hh"
# include "user-interface.hh"

namespace view
{
	class Human : public View
	{
	public:
		Human(controller::GameEngine *ge);
		virtual ~Human();

		virtual std::string askName() const;
		virtual bool isHuman() const;

		virtual int askProvostShift() const;
		virtual bool askYesNo() const;
		virtual bool askJoustField() const;
		virtual controller::BoardElement* askWorkerPlacement(const std::vector<controller::BoardElement *> & buildings) const;

		virtual unsigned askBuilding() const;
		virtual unsigned askResourceChoice() const;

		unsigned askNbHumans(unsigned max) const;
		unsigned askNbAIs(unsigned min, unsigned max) const;

		void updateBoard() const;
		boost::signal<void (void)>::slot_function_type getUpdateBoardSlot() const;
		boost::signal<unsigned (unsigned)>::slot_function_type getAskNbHumansSlot() const;
		boost::signal<unsigned (unsigned, unsigned)>::slot_function_type getAskNbAIsSlot() const;

		void operator()();

	private:
		UserInterface * user_interface_;
	};

}

#endif
