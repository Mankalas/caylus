/*!
  \file   human.h
  \brief  Human declaration

  \author Mankalas
  \date   2008-12-14
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
		Human(controller::GameEngine* ge);
		virtual ~Human();

		virtual std::string askName() const;
		virtual bool isHuman() const;

		virtual int askProvostShift() const;
		virtual bool askYesNo() const;
		virtual bool askJoustField() const;
		virtual int askWorkerPlacement() const;
		virtual unsigned askBuilding() const;
		virtual unsigned askResourceChoice() const;

		unsigned askNbHumans(unsigned max);
		unsigned askNbAIs(unsigned min, unsigned max);

		void updateBoard();
		boost::signal<void (void)>::slot_function_type getUpdateBoardSlot() const;

		const UserInterface* userInterface() const;
		UserInterface* userInterface();

	private:
		UserInterface* user_interface_;
	};

}
# include "human.hxx"

#endif
