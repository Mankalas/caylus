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
// #include "game-engine.hh"
// #include <vector>
// #include "gfx-window.hh"
// #include "gfx-sprite-library.hh"

int main(int argc, char** argv)
{
  bool command_line = false;
  std::string host = "";
  int option = NULL;

  while ((option = getopt(argc, argv, "ci:h:p:s")) != -1)
    {
      switch (option)
	{
	case 'c' :
	  std::cout << "Command line game." << std::endl;
	  command_line = true;
	  break;
	case 'i':
	  std::cout << "number of ia : " << optarg << std::endl;
	  break;
	case 'p':
	  std::cout << "number of players : " << optarg << std::endl;
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
  return 1;

//   GameEngine g(3, 1);
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

