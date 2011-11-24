/**
 * @file   main.cc
 * @author  <mankalas@localhost,>
 * @date   Sat Jan 10 18:50:52 2009
 *
 * @brief  Main file.
 *
 *
 */

#include <iostream>
#include <vector>
#include <boost/thread.hpp>
#include <stdlib.h>
#include "game-engine.hh"
#include "human.hh"
#include "debug-logger.hh"
#include "gfx-window.hh"
#include "gfx-sprite-library.hh"
#include "exceptions.hh"

int main(int argc, char **argv)
{
	bool command_line = false;
	std::string host = "";
	int option = 0;

	int nb_humans = 1;
	int nb_ais = 0;
	int max_turns = 42;

	while ((option = getopt(argc, argv, "a:h:m:")) != -1)
	{
		switch (option)
		{
		case 'a' :
			nb_ais = atoi(optarg);
			break;
		case 'c' :
			std::cout << "Command line game." << std::endl;
			command_line = true;
			break;
		case 's' :
			std::cout << "Server game." << std::endl;
			break;
		case 'h' :
			nb_humans = atoi(optarg);
			break;
		case 'm' :
			max_turns = atoi(optarg);
			break;
		case '?':
			std::cerr << "Error" << std::endl;
		}
	}

	Logger log;
	try
	{
		GameEngine g(nb_humans, nb_ais);

		log.setGE(&g);

		g.subscribeView(&log);

		g.nbTurnsMax() = max_turns;
		boost::thread controller_thread = boost::thread(boost::ref(g));
		DebugLogger::log("Game Engine thread launched.");

		Human human(&g);
		g.subscribeView(&human);

		boost::thread human_thread = boost::thread(human);

		controller_thread.join();
	}
	catch (GameOverException *)
	{
	}
	catch(Exception * ex)
	{
		std::cerr << ex->msg() << std::endl;
	}
	return 0;
}
