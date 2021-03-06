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
#include "view/playback-engine.hh"
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

	unsigned int nb_humans = 0;
	unsigned int nb_ais = 0;
	unsigned int max_workers = 6;
	unsigned int max_turns = INT_MAX;
	std::string dir = "";
	bool random = true;
	PlaybackEngine * playback_engine = NULL;

	while ((option = getopt(argc, argv, "a:cd:hm:ru:w:")) != -1)
	{
		switch (option)
		{
			case 'a' :
				nb_ais = atoi(optarg);
				break;
			case 'c' :
				DebugLogger::log("Command line game.");
				//	command_line = true;
				break;
			case 'd' :
				++nb_ais;
				random = false;
				playback_engine = new PlaybackEngine(optarg);
				break;
			case 's' :
				DebugLogger::log("Server game.");
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
		g.setMaxWorkers(max_workers);
		g.signals()->game_over.connect(&waitForGameOver);

		boost::thread controller_thread(boost::ref(g));
		boost::posix_time::time_duration timeout = boost::posix_time::milliseconds(0);

		controller_thread.timed_join(timeout);

		if (playback_engine)
		{
			playback_engine->linkGame(g);
		}
		else
		{
			assert(nb_humans <= 5);
			for (unsigned i = 0; i < nb_humans; ++i)
			{
				ConsoleView gui(&g);
				DebugLogger::log("Adding new human player.");
				Player * player = g.newPlayer();
				Human * human = new Human(&g, player, &gui);
				player->setName(human->askName());
			}

			assert(nb_ais <= 5 - nb_humans);
			for (unsigned i = 0; i < nb_ais; ++i)
			{
				//new AI(&g);
				DebugLogger::log("Adding new AI player.");
			}
		}

		g.playerReady();

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
		std::cerr <<"An exception occured: " << ex->msg() << std::endl;
	}

	bool problem = false;
	if (playback_engine)
	{
		problem = !playback_engine->doesOutputMatchReference();
	}
	delete playback_engine;
	playback_engine = NULL;
	if (problem)
	{
		return 1;
	}
	return 0;
}
