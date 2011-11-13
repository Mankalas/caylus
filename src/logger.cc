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

Logger::Logger()
{
	file_.open("caylus.log", ios::trunc);
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


}

void Logger::startSection(int level, const std::string & title)
{
	file_ << "<h" << level << ">" << title << "</h" << level << ">\n"
				<< "<div style=\"margin-left:50px\">\n";
}

void Logger::playerIncome(const Player * p, const ResourceMap & r)
{
	assert(p);
	file_ << "<p>Player " << p->name() << " received " << r << " for he has " << p->residences() << " residences.</p>";
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
}
void Logger::incomeCollectionEnd()
{
}
void Logger::incomeCollectionForPlayer(const controller::Player * player)
{
}
void Logger::workerPlacementBegin()
{
}
void Logger::workerPlacementEnd()
{
}
void Logger::workerPlacementForPlayer(const controller::Player * player)
{
}
void Logger::alreadyOnBridge(const controller::Player * player)
{
}
void Logger::notEnoughDeniers(const controller::Player * player)
{
}
void Logger::noWorkerLeft(const controller::Player * player)
{
}
void Logger::playerChoice(const controller::BoardElement * board_elt)
{
}
void Logger::playerChoices(const std::vector<const controller::BoardElement *> & choices)
{
}

v_v_signal_t::slot_function_type gameEngineReadySlot() const
{
	return boos::bind(&Logger::gameEngineReady, this);
}

v_u_signal_t::slot_function_type newTurnSlot() const
{
	return boost::bind(&Logger::newTurn, this, _1);
}
v_v_signal_t::slot_function_type incomeCollectionBeginSlot() const
{
	return boost::bind(&Logger::incomeCollectionBegin, this);
}
v_v_signal_t::slot_function_type incomeCollectionEndSlot() const
{
	return boost::bind(&Logger::incomeCollectionEnd, this);
}
v_cp_signal_t::slot_function_type incomeCollectionForPlayerSlot() const
{
	return boost::bind(&Logger::incomeCollectionForPlayer, this, _1);
}
v_v_signal_t::slot_function_type workerPlacementBeginSlot() const
{
	return boost::bind(&Logger::workerPlacementBegin, this);
}
v_v_signal_t::slot_function_type workerPlacementEndSlot() const
{
	return boost::bind(&Logger::workerPlacementEnd, this);
}
v_cp_signal_t::slot_function_type workerPlacementForPlayerSlot() const
{
	return boost::bind(&Logger::workerPlacementForPlayerSlot, this, _1);
}
v_cp_signal_t::slot_function_type alreadyOnBridgeSlot() const
{
	return boost::bind(&Logger::alreadyOnBridge, this, _1);
}
v_cp_signal_t::slot_function_type notEnoughDeniersSlot() const
{
	return boost::bind(&Logger::notEnoughDeniers, this, _1);
}
v_cp_signal_t::slot_function_type noWorkerLeftSlot() const
{
	return boost::bind(&Logger::noWorkerLeft, this, _1);
}
player_choice_signal_t::slot_function_type playerChoiceSlot() const
{
	return boost::bind(&Logger::playerChoice, this, _1);
}
player_choices_signal_t::slot_function_type playerChoicesSlot() const
{
	return boost::bind(&Logger::playerChoices, this, _1);
}
