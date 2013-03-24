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

struct Test
{
	Test(std::string test_d)
		: test_dir(test_d)
		, test_log(NULL)
		, playback(NULL)
	{
	}

	~Test()
	{
		delete playback;
		playback = NULL;
	}

	void linkGame(GameEngine * g)
	{
		DebugLogger::log("Adding new playback player.");
		Player * player = g->newPlayer();
		playback = new Playback(g, player, test_dir);

		std::string player_name = playback->askName();
		unsigned nb_workers = playback->askProvostShift(); // TODO : better

		player->setName(player_name);
		g->setMaxWorkers(nb_workers);

		test_log = new TestLogger(g, test_dir);
	}

	bool doesOutputMatchReference()
	{
		delete test_log;
		test_log = NULL;
		std::ifstream ref;
		std::ifstream output;

		ref.open((test_dir + "/ref").c_str(), std::ios::in);
		if (ref.fail())
		{
			DebugLogger::log("Cannot open ref file.");
			return false;
		}
		output.open((test_dir + "/output").c_str(), std::ios::in);
		if (output.fail())
		{
			DebugLogger::log("Cannot open output file.");
			return false;
		}

		std::string ref_line;
		std::string output_line;
		int line_number = 0;
		bool result = true;
		do
		{
			std::getline(ref, ref_line);
			std::getline(output, output_line);

			line_number++;
			if (ref_line != output_line)
			{
				std::cerr << "Lines " << line_number << " differ : " << std::endl
				          << "\t" << ref_line << std::endl
				          << "\t" << output_line << std::endl;
				result = false;
				break;
			}
		}
		while (ref && output);
		ref.close();
		output.close();
		return result;
	}

	std::string test_dir;
	TestLogger * test_log;
	Playback * playback;
};

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
	Test * test = NULL;

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
				test = new Test(optarg);
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

		assert(nb_humans <= 5);
		for (unsigned i = 0; i < nb_humans; ++i)
		{
			ConsoleView gui(&g);
			DebugLogger::log("Adding new human player.");
			Player * player = g.newPlayer();
			Human * human = new Human(&g, player, &gui);
			player->setName(human->askName());
		}

		if (test)
		{
			test->linkGame(&g);
		}

		assert(nb_ais <= 5 - nb_humans);
		for (unsigned i = 0; i < nb_ais; ++i)
		{
			//new AI(&g);
			DebugLogger::log("Adding new AI player.");
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
	if (test)
	{
		problem = !test->doesOutputMatchReference();
	}
	delete test;
	test = NULL;
	if (problem)
	{
		return 1;
	}
	return 0;
}
