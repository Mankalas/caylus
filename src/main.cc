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
#include "game-engine.hh"
#include "human.hh"
#include "logger.hh"
#include "gfx-window.hh"
#include "gfx-sprite-library.hh"

int main(int argc, char **argv)
{
	bool command_line = false;
	std::string host = "";
	int option = 0;

	while ((option = getopt(argc, argv, "ci:h:p:s")) != -1)
	{
		switch (option)
		{
			case 'c' :
				std::cout << "Command line game." << std::endl;
				command_line = true;
				break;
			case 's' :
				std::cout << "Server game." << std::endl;
				break;
			case 'h' :
				std::cout << optarg << std::endl;
				host = std::string(optarg);
				break;
			case '?':
				std::cerr << "Error" << std::endl;
		}
	}

	GameEngine g;
	boost::thread controller_thread = boost::thread(boost::ref(g));
	Logger::log("Game Engine thread launched.");

	boost::mutex mutex;
	boost::unique_lock<boost::mutex> lock(mutex);
	Logger::log("GE waiting for init to end.");
	g.waitingPlayers()->wait(lock);
	Logger::log("Game engine ready.");

	Human human(&g);
	g.subscribeView(&human);

	boost::thread human_thread = boost::thread(human);

	controller_thread.join();
	return 0;
}
