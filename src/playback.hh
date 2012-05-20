/**
 * @file   playback.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun May 20 18:58:10 2012
 *
 * @brief  Declaration of the playback class.
 */

#ifndef PLAYBACK_HH
# define PLAYBACK_HH

# include "player-view.hh"
# include <fstream>

namespace view
{
	class Playback : public PlayerView
	{
	public:
		Playback(std::string record_path);
		~Playback();

		virtual std::string askName() const;
		virtual bool isHuman() const;
		virtual int askProvostShift() const;
		virtual bool askYesNo() const;
		virtual bool askJoustField() const;
		virtual controller::BoardElement* askWorkerPlacement(const std::vector<controller::BoardElement *> & buildings) const;
		virtual unsigned askBuilding() const;
		virtual unsigned askResourceChoice() const;
		virtual void boardElementActivation(const controller::BoardElement * board_elt);

		template<typedef T>
		T next() const;

		controller::BoardElement* next(const std::vector<controller::BoardElement *> & buildings) const;

	private:
		std::ifstream file_;
	};
}

#endif
