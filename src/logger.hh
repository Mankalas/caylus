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
# include <boost/bind.hpp>
# include "const.hh"
# include "signals.hh"

namespace controller
{
	class GameEngine;
	class Player;
	class ResourceMap;
}

class Logger
{
public:
	Logger();
	Logger(const controller::GameEngine * ge);

	void setGE(const controller::GameEngine * ge);

	static void debug(const std::string &msg);

	template <class T>
	std::string to_string(const T &t) const;

	void close();

	void startOfTurn(const controller::GameEngine *);
	void playerIncome(const controller::Player *, const controller::ResourceMap &);

	void startSection(int level, const std::string & title);
	void endSection();

	void gameEngineReady();
	v_v_signal_t::slot_function_type gameEngineReadySlot();

private:
	unsigned int turn_count_;
	std::ofstream file_;
	const controller::GameEngine * ge_;
};

# include "logger.hxx"

#endif
