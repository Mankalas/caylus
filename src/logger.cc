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
#include "player.hh"
#include "resource-map.hh"

using namespace std;
using namespace controller;
using namespace view;

Logger::Logger(const GameEngine * game_engine)
	: PassiveView(game_engine)
{
	file_.open("caylus.html", ios::trunc);
	file_ << "<html>\n<head>\n\n<style type=\"text/css\">\nbody {\n     font-family: Arial,Helvetica,sans-serif;\n     font-size: x-small;\n     color: #333333;\n     text-align: justify;\n     width:95%\n}\n\n#bridge\n{\n     color:#3a3aff\n}\n\n#castle\n{\n     color:#008000\n}\n\n.building\n{\n     color:#c89baa\n}\n\n.choice\n{\n     background-color:#F1F19B\n}\n</style>\n\n</head>\n<body>";
}

Logger::~Logger()
{
	file_ <<  "</body>\n</html>" << std::endl;
	file_.close();
}

void Logger::startOfTurn(const GameEngine * ge)
{
	assert(ge);
	newTurn();
}

void Logger::startSection(int level, const std::string & title)
{
	file_ << "<h" << level << ">" << title << "</h" << level << ">\n"
				<< "<div style=\"margin-left:50px\">\n";
}

void Logger::playerIncome(const Player * p, const ResourceMap * r)
{
	assert(p);
	file_ << "<p>Player " << p->name() << " received " << *r << " for he has " << p->residences() << " residences.</p>" << std::endl;
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

void Logger::newTurn()
{
	file_ << "<h1>Turn " << ge_->nbTurns() << " / " << ge_->nbTurnsMax() << "</h1>"
				<< "<div style=\"margin-left:50px\">\n";
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
	file_ << "<p>" << p->name() << " receives " << *income << ".</p>";
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
void Logger::noWorkerLeft(const controller::Player * )
{
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

void Logger::boardElementActivation(const controller::BoardElement * board_elt)
{
	file_ << "<p>" << board_elt->name() << " activated." << "</p>";
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

v_v_signal_t::slot_function_type Logger::gameEngineReadySlot()
{
	return boost::bind(&Logger::gameEngineReady, this);
}

v_u_signal_t::slot_function_type Logger::newTurnSlot()
{
	return boost::bind(&Logger::newTurn, this);
}
v_v_signal_t::slot_function_type Logger::incomeCollectionBeginSlot()
{
	return boost::bind(&Logger::incomeCollectionBegin, this);
}
v_v_signal_t::slot_function_type Logger::incomeCollectionEndSlot()
{
	return boost::bind(&Logger::incomeCollectionEnd, this);
}
v_cp_cr_signal_t::slot_function_type Logger::incomeCollectionForPlayerSlot()
{
	return boost::bind(&Logger::incomeCollectionForPlayer, this, _1, _2);
}
v_v_signal_t::slot_function_type Logger::workerPlacementBeginSlot()
{
	return boost::bind(&Logger::workerPlacementBegin, this);
}
v_v_signal_t::slot_function_type Logger::workerPlacementEndSlot()
{
	return boost::bind(&Logger::workerPlacementEnd, this);
}
v_cp_signal_t::slot_function_type Logger::workerPlacementForPlayerSlot()
{
	return boost::bind(&Logger::workerPlacementForPlayer, this, _1);
}
v_cp_signal_t::slot_function_type Logger::alreadyOnBridgeSlot()
{
	return boost::bind(&Logger::alreadyOnBridge, this, _1);
}
v_cp_signal_t::slot_function_type Logger::notEnoughDeniersSlot()
{
	return boost::bind(&Logger::notEnoughDeniers, this, _1);
}
v_cp_signal_t::slot_function_type Logger::noWorkerLeftSlot()
{
	return boost::bind(&Logger::noWorkerLeft, this, _1);
}
player_choice_signal_t::slot_function_type Logger::playerChoiceSlot()
{
	return boost::bind(&Logger::playerChoice, this, _1);
}
player_choices_signal_t::slot_function_type Logger::playerChoicesSlot()
{
	return boost::bind(&Logger::playerChoices, this, _1);
}

boost::signal<void (const controller::ResourceMap *)>::slot_function_type Logger::resourceMoveSlot()
{
	return boost::bind(&Logger::resourceMove, this, _1);
}

v_v_signal_t::slot_function_type Logger::activationSpecialBuildingsBeginSlot()
{
	return boost::bind(&Logger::activationSpecialBuildingsBegin, this);
}

v_v_signal_t::slot_function_type Logger::activationSpecialBuildingsEndSlot()
{
	return boost::bind(&Logger::activationSpecialBuildingsEnd, this);
}


void Logger::resourceMove(const ResourceMap *)
{
}
