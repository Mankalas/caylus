/**
 * @file   logger.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun Oct 30 23:39:12 2011
 *
 * @brief  Implementation of the logger class.
 */

#include "debug-logger.hh"

#include <iostream>
#include "game-engine.hh"
#include "game-signals.hh"
#include "player.hh"
#include "resource-map.hh"
#include "board.hh"
#include "bridge.hh"
#include "castle.hh"

using namespace std;
using namespace controller;
using namespace view;

Logger::Logger(const GameEngine * game_engine)
	: PassiveView(game_engine)
{
	file_.open("caylus.html", ios::trunc);
	file_ << "<html>\n<head>\n\n<style type=\"text/css\">\nbody {\n     font-family: Arial,Helvetica,sans-serif;\n     font-size: x-small;\n     color: #333333;\n     text-align: justify;\n     width:95%\n}\n\n#bridge\n{\n     color:#3a3aff\n}\n\n#castle\n{\n     color:#008000\n}\n\n.building\n{\n     color:#c89baa\n}\n\n.choice\n{\n     background-color:#F1F19B\n}\n</style>\n\n</head>\n<body>";

	// Phases
	game_engine->signals()->turn_start.connect(boost::bind(&Logger::newTurn, this, _1, _2));

	game_engine->signals()->income_collecting_begin.connect(boost::bind(&Logger::incomeCollectionBegin, this));
	game_engine->signals()->income_collecting_end.connect(boost::bind(&Logger::incomeCollectionEnd, this));
	game_engine->signals()->income_collecting_for_player.connect(boost::bind(&Logger::incomeCollectionForPlayer, this, _1, _2));

	game_engine->signals()->worker_placement_begin.connect(boost::bind(&Logger::workerPlacementBegin, this));
	game_engine->signals()->worker_placement_end.connect(boost::bind(&Logger::workerPlacementEnd, this));
	game_engine->signals()->worker_placement_for_player.connect(boost::bind(&Logger::workerPlacementForPlayer, this, _1));

	game_engine->signals()->activation_special_buildings_begin.connect(boost::bind(&Logger::activationSpecialBuildingsBegin, this));
	game_engine->signals()->activation_special_buildings_end.connect(boost::bind(&Logger::activationSpecialBuildingsEnd, this));

	game_engine->signals()->activation_bridge_begin.connect(boost::bind(&Logger::activationBridgeBegin, this));
	game_engine->signals()->activation_bridge_end.connect(boost::bind(&Logger::activationBridgeEnd, this));

	game_engine->signals()->activation_buildings_begin.connect(boost::bind(&Logger::activationBuildingsBegin, this));
	game_engine->signals()->activation_buildings_end.connect(boost::bind(&Logger::activationBuildingsEnd, this));

	game_engine->signals()->activation_castle_begin.connect(boost::bind(&Logger::activationCastleBegin, this));
	game_engine->signals()->activation_castle_end.connect(boost::bind(&Logger::activationCastleEnd, this));

	// Controls
	game_engine->signals()->player_choices.connect(boost::bind(&Logger::playerChoices, this, _1));
	game_engine->signals()->player_has_chosen.connect(boost::bind(&Logger::playerChoice, this, _1));
	game_engine->signals()->no_worker_left.connect(boost::bind(&Logger::noWorkerLeft, this, _1));

	game_engine->board().castle().activation_sig.connect(boost::bind(&Logger::activationBoardElement, this, _1, _2));
	game_engine->board().bridge().activation_sig.connect(boost::bind(&Logger::activationBoardElement, this, _1, _2));
	foreach (BuildingSmartPtr b, game_engine->board().road().get())
	{
		if (b != NULL)
		{
			b->activation_sig.connect(boost::bind(&Logger::activationBoardElement, this, _1, _2));
		}
	}
}

Logger::~Logger()
{
	file_ <<  "</body>\n</html>" << std::endl;
	file_.close();
}

void Logger::newTurn(unsigned current_turn, unsigned max_turn)
{
	if (current_turn != 1)
	{
		file_ << "</div>" << std::endl;
	}
	file_ << "<h1>Turn " << current_turn << " / " << max_turn << "</h1>"
				<< "<div style=\"margin-left:50px\">\n";
}

void Logger::startSection(int level, const std::string & title)
{
	file_ << "<h" << level << ">" << title << "</h" << level << ">\n"
				<< "<div style=\"margin-left:50px\">\n";
}

void Logger::endSection()
{
	file_ << "</div>";
}

void Logger::gameEngineReady()
{
	assert(ge_);

	file_ << "<h1>Init info</h1>"
				<< "<ul>\n<li>Number of humans : " << ge_->nbHumans() << "</li>"
				<< "<li>Number of AIs : " << ge_->nbAIs() << "</li>"
				<< "</ul>";
}

void Logger::setGE(const GameEngine * ge)
{
	ge_ = ge;
}

void Logger::incomeCollectionBegin()
{
	file_ << "<h1>Income collection</h1>";
}

void Logger::incomeCollectionEnd()
{
	file_ << "<p>End of collecting income.</p>";
}

void Logger::incomeCollectionForPlayer(const controller::Player * p, const controller::ResourceMap * income)
{
	file_ << "<p>Player " << p->name() << " received " << *income << " for he has " << p->residences() << " residences.</p>" << std::endl;
}
void Logger::workerPlacementBegin()
{
	file_ << "<h1>Worker placement</h1>" << std::endl;
}

void Logger::workerPlacementEnd()
{
	file_ << "<p>End of worler placement.</p>";
}

void Logger::workerPlacementForPlayer(const controller::Player * p)
{
	file_ << "<p>" << p->name() << "'s turn.</p>";
}

void Logger::alreadyOnBridge(const controller::Player * )
{
}
void Logger::notEnoughDeniers(const controller::Player * )
{
}
void Logger::noWorkerLeft(const controller::Player * p)
{
	file_ << "<p>No more workers for " << p->name() << ".</p>";
}
void Logger::playerChoice(const controller::BoardElement * b)
{
	file_ << "<p>" << b->name() << " is chosen.</p>";
}

void Logger::playerChoices(const std::vector<controller::BoardElement *> & choices)
{
	file_ << "<p>" << "Choices are ";
	foreach(const controller::BoardElement * elt, choices)
	{
		file_ << elt->name() << ", ";
	}
}

void Logger::activationBoardElement(const controller::BoardElement * board_elt, const controller::Player * p)
{
	file_ << "<p>" << board_elt->name() << " activated for player " << *p << "." << "</p>";
}

void Logger::updateBoard()
{
	file_ << "<p>Board was updated.</p>";
}

void Logger::activationSpecialBuildingsBegin()
{
	file_ << "<h1>Activation of special buildings</h1>" << std::endl;
}

void Logger::activationSpecialBuildingsEnd()
{
	file_ << "<p>End of special buildings activation.</p>" << std::endl;
}

void Logger::resourceMove(const ResourceMap *)
{
}

void Logger::activationBuildingsBegin()
{
	file_ << "<h1>Activation of buildings</h1>" << std::endl;
}

void Logger::activationBuildingsEnd()
{
	file_ << "<p>End of buildings activation.</p>" << std::endl;
}

void Logger::activationBridgeBegin()
{
	file_ << "<h1>Activation of the Bridge</h1>" << std::endl;
}

void Logger::activationBridgeEnd()
{
	file_ << "<p>End of bridge activation.</p>" << std::endl;
}

void Logger::activationCastleBegin()
{
	file_ << "<h1>Activation of the Castle</h1>" << std::endl;
}

void Logger::activationCastleEnd()
{
	file_ << "<p>End of castle activation.</p>" << std::endl;
}
