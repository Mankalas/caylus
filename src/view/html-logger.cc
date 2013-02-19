/**
 * @file   logger.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun Oct 30 23:39:12 2011
 *
 * @brief  Implementation of the logger class.
 */

#include "html-logger.hh"

#include <iostream>
#include "../debug-logger.hh"
#include "../controller/game-engine.hh"
#include "../game-signals.hh"
#include "../controller/player.hh"
#include "../controller/resource-map.hh"
#include "../controller/board.hh"
#include "../controller/bridge.hh"
#include "../controller/castle.hh"

using namespace std;
using namespace controller;
using namespace view;

HtmlLogger::HtmlLogger(const GameEngine * game_engine)
	: PassiveView(game_engine)
{
	file_.open("caylus.html", ios::trunc);
	file_ << "<html>\n<head>\n\n<style type=\"text/css\">\nbody {\n     font-family: Arial,Helvetica,sans-serif;\n     font-size: x-small;\n     color: #333333;\n     text-align: justify;\n     width:95%\n}\n\n#bridge\n{\n     color:#3a3aff\n}\n\n#castle\n{\n     color:#008000\n}\n\n.building\n{\n     color:#c89baa\n}\n\n.choice\n{\n     background-color:#F1F19B\n}\n</style>\n\n</head>\n<body>";

	// Phases
	game_engine->signals()->turn_start.connect(boost::bind(&HtmlLogger::newTurn, this, _1, _2));

	game_engine->signals()->income_collecting_begin.connect(boost::bind(&HtmlLogger::incomeCollectionBegin, this));
	game_engine->signals()->income_collecting_end.connect(boost::bind(&HtmlLogger::incomeCollectionEnd, this));
	game_engine->signals()->income_collecting_for_player.connect(boost::bind(&HtmlLogger::incomeCollectionForPlayer, this, _1, _2));

	game_engine->signals()->worker_placement_begin.connect(boost::bind(&HtmlLogger::workerPlacementBegin, this));
	game_engine->signals()->worker_placement_end.connect(boost::bind(&HtmlLogger::workerPlacementEnd, this));
	game_engine->signals()->worker_placement_for_player.connect(boost::bind(&HtmlLogger::workerPlacementForPlayer, this, _1));

	game_engine->signals()->activation_special_buildings_begin.connect(boost::bind(&HtmlLogger::activationSpecialBuildingsBegin, this));
	game_engine->signals()->activation_special_buildings_end.connect(boost::bind(&HtmlLogger::activationSpecialBuildingsEnd, this));

	game_engine->signals()->activation_bridge_begin.connect(boost::bind(&HtmlLogger::activationBridgeBegin, this));
	game_engine->signals()->activation_bridge_end.connect(boost::bind(&HtmlLogger::activationBridgeEnd, this));

	game_engine->signals()->activation_buildings_begin.connect(boost::bind(&HtmlLogger::activationBuildingsBegin, this));
	game_engine->signals()->activation_buildings_end.connect(boost::bind(&HtmlLogger::activationBuildingsEnd, this));

	game_engine->signals()->activation_castle_begin.connect(boost::bind(&HtmlLogger::activationCastleBegin, this));
	game_engine->signals()->activation_castle_end.connect(boost::bind(&HtmlLogger::activationCastleEnd, this));

	// Controls
	game_engine->signals()->no_worker_left.connect(boost::bind(&HtmlLogger::noWorkerLeft, this, _1));

	game_engine->board().castle().activation_sig.connect(boost::bind(&HtmlLogger::activationBoardElement, this, _1, _2));
	game_engine->board().bridge().activation_sig.connect(boost::bind(&HtmlLogger::activationBoardElement, this, _1, _2));
	foreach(const BuildingSmartPtr b, game_engine->board().road().get())
	{
		if (b != NULL)
		{
			b->activation_sig.connect(boost::bind(&HtmlLogger::activationBoardElement, this, _1, _2));
		}
	}

	foreach(const Player * p, game_engine->players())
	{
		if (p != NULL)
		{
			p->signals()->player_choices.connect(boost::bind(&HtmlLogger::playerChoices, this, _1));
			p->signals()->player_has_chosen.connect(boost::bind(&HtmlLogger::playerChoice, this, _1));
		}
	}
}

HtmlLogger::~HtmlLogger()
{
	file_ <<  "</body>\n</html>" << std::endl;
	file_.close();
}

void HtmlLogger::newTurn(unsigned current_turn, unsigned max_turn)
{
	if (current_turn != 1)
	{
		file_ << "</div>" << std::endl;
	}
	file_ << "<h1>Turn " << current_turn << " / " << max_turn << "</h1>"
	      << "<div style=\"margin-left:50px\">\n";
}

void HtmlLogger::startSection(int level, const std::string & title)
{
	file_ << "<h" << level << ">" << title << "</h" << level << ">\n"
	      << "<div style=\"margin-left:50px\">\n";
}

void HtmlLogger::endSection()
{
	file_ << "</div>";
}

void HtmlLogger::gameEngineReady()
{
	assert(ge_);

	file_ << "<h1>Init info</h1>"
	      << "<ul>\n<li>Number of humans : " << ge_->nbHumans() << "</li>"
	      << "<li>Number of AIs : " << ge_->nbAIs() << "</li>"
	      << "</ul>";
}

void HtmlLogger::incomeCollectionBegin()
{
	file_ << "<h1>Income collection</h1>";
}

void HtmlLogger::incomeCollectionEnd()
{
	file_ << "<p>End of collecting income.</p>";
}

void HtmlLogger::incomeCollectionForPlayer(const controller::Player * p, const controller::ResourceMap * income)
{
	file_ << "<p>Player " << p->name() << " received " << *income << " for he has " << p->residences() << " residences.</p>" << std::endl;
}
void HtmlLogger::workerPlacementBegin()
{
	file_ << "<h1>Worker placement</h1>" << std::endl;
}

void HtmlLogger::workerPlacementEnd()
{
	file_ << "<p>End of worler placement.</p>";
}

void HtmlLogger::workerPlacementForPlayer(const controller::Player * p)
{
	file_ << "<p>" << *p << "'s turn.</p>";
}

void HtmlLogger::alreadyOnBridge(const controller::Player *)
{
}
void HtmlLogger::notEnoughDeniers(const controller::Player *)
{
}
void HtmlLogger::noWorkerLeft(const controller::Player * p)
{
	file_ << "<p>No more workers for " << p->name() << ".</p>";
}
void HtmlLogger::playerChoice(const controller::BoardElement * b)
{
	file_ << "<p>" << b->name() << " is chosen.</p>";
}

void HtmlLogger::playerChoices(const std::vector<controller::BoardElement *> & choices)
{
	file_ << "<p>" << "Choices are ";
	foreach(const controller::BoardElement * elt, choices)
	{
		file_ << elt->name() << ", ";
	}
}

void HtmlLogger::activationBoardElement(const controller::BoardElement * board_elt, const controller::Player * p)
{
	file_ << "<p>" << board_elt->name() << " activated for player " << *p << "." << "</p>";
}

void HtmlLogger::updateBoard()
{
	file_ << "<p>Board was updated.</p>";
}

void HtmlLogger::activationSpecialBuildingsBegin()
{
	file_ << "<h1>Activation of special buildings</h1>" << std::endl;
}

void HtmlLogger::activationSpecialBuildingsEnd()
{
	file_ << "<p>End of special buildings activation.</p>" << std::endl;
}

void HtmlLogger::resourceMove(const ResourceMap *)
{
}

void HtmlLogger::activationBuildingsBegin()
{
	file_ << "<h1>Activation of buildings</h1>" << std::endl;
}

void HtmlLogger::activationBuildingsEnd()
{
	file_ << "<p>End of buildings activation.</p>" << std::endl;
}

void HtmlLogger::activationBridgeBegin()
{
	file_ << "<h1>Activation of the Bridge</h1>" << std::endl;
}

void HtmlLogger::activationBridgeEnd()
{
	file_ << "<p>End of bridge activation.</p>" << std::endl;
}

void HtmlLogger::activationCastleBegin()
{
	file_ << "<h1>Activation of the Castle</h1>" << std::endl;
}

void HtmlLogger::activationCastleEnd()
{
	file_ << "<p>End of castle activation.</p>" << std::endl;
}
