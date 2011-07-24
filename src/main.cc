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
#include "game-engine.hh"
#include "view.hh"

//#include "gfx-window.hh"
//#include "gfx-sprite-library.hh"

int main(int argc, char** argv)
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

  View view(g);

  g.initialize();

//   int i = 0;

//   while (++i)
//   {
//     g.collectIncome();
//     g.placeWorkers();
//     g.activateSpecialBuildings();
// //    g.activateBridge();
//     g.activateBuildings();
//     g.activateCastle();
//     g.endOfTurn();
//   }
//   std::cout << "Game Over!" << std::endl;

//   return 0;
}

