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
#include <limits.h>

#include "debug-logger.hh"
#include "exceptions.hh"
#include "signals.hh"

#include "controller/game-engine.hh"

#include "view/human.hh"
#include "view/ai.hh"
#include "view/playback.hh"
#include "view/html-logger.hh"
#include "view/test-logger.hh"
#include "view/graphic-view.hh"
#include "view/console-view.hh"

using namespace view;
using namespace controller;

void usage()
{
	std::cout << "caylus" << std::endl
	          << "\t-a [n]\t\tNumber of AIs" << std::endl
	          << "\t-c\t\tCommand line game" << std::endl
	          << "\t-d\t\tLast option : specify a recorded player" << std::endl
	          << "\t-h\t\tPrint this help" << std::endl
	          << "\t-m [n]\t\tNumber of turns" << std::endl
	          << "\t-r\t\tNo random at the game init" << std::endl
	          << "\t-u [n]\t\tNumber of humans" << std::endl;
}

boost::condition_variable wait_for_gameover;

void waitForGameOver()
{
	wait_for_gameover.notify_one();
}

int main(int argc, char **argv)
{
	//	bool command_line = false;
	std::string host = "";
	int option = 0;

	unsigned int nb_humans = 1;
	unsigned int nb_ais = 0;
	unsigned int max_workers = 6;
	unsigned int max_turns = INT_MAX;
	std::string dir = "";
	bool random = true;

	while ((option = getopt(argc, argv, "a:cdhm:ru:w:")) != -1)
	{
		switch (option)
		{
			case 'a' :
				nb_ais = atoi(optarg);
				break;
			case 'c' :
				std::cout << "Command line game." << std::endl;
				//	command_line = true;
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
			case 'r':
				random = false;
				break;
			case 'u' :
				nb_humans = atoi(optarg);
				break;
			case 'm' :
				max_turns = atoi(optarg);
				break;
			case 'w' :
				max_workers = atoi(optarg);
				break;
			case '?':
				usage();
				return 1;
		}
	}

	try
	{
		GameEngine g(nb_humans, nb_ais, max_turns, random);
		g.maxWorkers() = max_workers;
		g.signals()->game_over.connect(&waitForGameOver);

		boost::thread controller_thread(boost::ref(g));
		boost::posix_time::time_duration timeout = boost::posix_time::milliseconds(00);
		controller_thread.timed_join(timeout);

		ConsoleView gui(&g);

		assert(nb_humans <= 5);
		// -1 because a first human is added the previous line
		for (unsigned i = 0; i < nb_humans; ++i)
		{
			new Human(&g, &gui);
			g.playerReady();
			DebugLogger::log("Adding new human player.");
		}

		if (dir != "")
		{
			DebugLogger::log("Adding new playback player.");
			nb_ais -= nb_ais == 0 ? 0 : 1;
			new Playback(&g, dir);
			g.playerReady();
		}

		assert(nb_ais <= 5 - nb_humans);
		for (unsigned i = 0; i < nb_ais; ++i)
		{
			//new AI(&g);
			DebugLogger::log("Adding new AI player.");
		}

		TestLogger log(&g);

		boost::mutex gameOverMutex;
		boost::unique_lock<boost::mutex> lock(gameOverMutex);
		wait_for_gameover.wait(lock);
	}
	catch (GameOverException *)
	{
		std::cerr << "Game OVER" << std::endl;
	}
	catch (Exception * ex)
	{
		std::cerr << ex->msg() << std::endl;
	}
	return 0;
}
