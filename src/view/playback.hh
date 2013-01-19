/**
 * @file   playback.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun May 20 18:58:10 2012
 *
 * @brief  Declaration of the playback class.
 */

#ifndef PLAYBACK_HH
# define PLAYBACK_HH

# include "active-view.hh"
# include <fstream>

namespace view
{
	class Playback : public ActiveView
	{
	public:
		Playback(controller::GameEngine * game_engine, std::string record_path);
		~Playback();

		virtual std::string askName() const;
		virtual int askProvostShift() const;
		virtual unsigned int askWorkerPlacement() const;
		virtual unsigned int askChoice(unsigned int range) const;

		/*virtual bool askYesNo() const;
		virtual bool askJoustField() const;

		virtual unsigned askBuilding() const;
		virtual unsigned askResourceChoice() const;
		virtual void boardElementActivation(const controller::BoardElement * board_eltx);*/

	private:
		mutable std::ifstream file_;

		std::string next_line() const;

		int next_int() const;
		unsigned next_uint() const;
		std::string next_str() const;
	};

}

#endif
