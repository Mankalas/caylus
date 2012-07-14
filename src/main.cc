/**
 * @file   main.cc
 * @author  <mankalas@localhost,>
 * @date   Sat Jan 10 18:50:52 2009
 *
 * @brief  Main file.
 */

#include <iostream>
#include <vector>
#include <boost/thread.hpp>
#include <stdlib.h>
#include "game-engine.hh"
#include "human.hh"
#include "ai.hh"
#include "playback.hh"
#include "debug-logger.hh"
#include "gfx-window.hh"
#include "gfx-sprite-library.hh"
#include "exceptions.hh"
#include "logger.hh"

void usage()
{
	std::cout << "caylus" << std::endl
						<< "\t-a [n]\t\tNumber of AIs" << std::endl
						<< "\t-c\t\tCommand line game" << std::endl
						<< "\t-d\t\tLast option : specify a recorded player" << std::endl
						<< "\t-h\t\tPrint this help" << std::endl
						<< "\t-u [n]\t\tNumber of humans" << std::endl
						<< "\t-m [n]\t\tNumber of turns" << std::endl;
}

int main(int argc, char **argv)
{
	bool command_line = false;
	std::string host = "";
	int option = 0;

	unsigned int nb_humans = 0;
	unsigned int nb_ais = 0;
	unsigned int max_turns = 42;
	std::string dir = "";

	while ((option = getopt(argc, argv, "a:cdhu:m:")) != -1)
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
		case 'd' :
			std::cin >> dir;
			break;
		case 's' :
			std::cout << "Server game." << std::endl;
			break;
		case 'h' :
			usage();
			return 0;
		case 'u' :
			nb_humans = atoi(optarg);
			break;
		case 'm' :
			max_turns = atoi(optarg);
			break;
		case '?':
			usage();
			return 1;
		}
	}

	try
	{
		GameEngine g(nb_humans, nb_ais);
		g.nbTurnsMax() = max_turns;

		DebugLogger::log("Game Engine thread created.");

		assert(nb_humans <= 5);
		// -1 because a first human is added the previous line
		for (unsigned i = 0; i < nb_humans; ++i)
		{
			new Human(&g);
			DebugLogger::log("Adding new human player.");
		}

		if (dir != "")
		{
			DebugLogger::log("Adding new playback player.");
			nb_ais -= nb_ais == 0 ? 0 : 1;
			new Playback(&g, dir);
		}

		assert(nb_ais <= 5 - nb_humans);
		for (unsigned i = 0; i < nb_ais; ++i)
		{
			//new AI(&g);
			DebugLogger::log("Adding new AI player.");
		}

		Logger log(&g);

		boost::thread controller_thread = boost::thread(boost::ref(g));
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
