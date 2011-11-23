/**
 * @file   logger.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun Sep 25 00:42:58 2011
 *
 * @brief  Declaration of the logger class.
 */

#ifndef LOGGER_HH
# define LOGGER_HH

# include <stack>
# include <fstream>
# include <vector>
# include "const.hh"

namespace controller
{
	class GameEngine;
	class Player;
	class ResourceMap;
	class BoardElement;
}

class Logger
{
public:

	static Logger * instance();

	void log(const std::string &msg);

	template <class T>
	std::string to_string(const T &t) const;

	void close();

	void gameInfo(const controller::GameEngine *);
	void startOfTurn(const controller::GameEngine *);
	void playerIncome(const controller::Player *, const controller::ResourceMap &);

	void startSection(int level, const std::string & title);
	void endSection();

	void placementChoices(const controller::Player * p, const std::vector<controller::BoardElement*> & choices);
	void playerLog(const controller::Player * p, const std::string & msg);
	void playerBoardChoice(const controller::Player * p, const controller::BoardElement * board_element);

private:
	static Logger * instance_;
	Logger();

	unsigned int turn_count_;
	std::ofstream file_;
};

# include "logger.hxx"

#endif
