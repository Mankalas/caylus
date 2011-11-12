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

void Logger::close()
{
	file_ <<  "</body>\n</html>" << std::endl;
	file_.close();
}

void Logger::startOfTurn(const GameEngine * ge)
{
	assert(ge);

	file_ << "<h1>Turn " << ge->nbTurns() << "</h1>"
				<< "<div style=\"margin-left:50px\">\n";
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

v_v_signal_t::slot_function_type Logger::gameEngineReadySlot()
{
	return boost::bind(&Logger::gameEngineReady, this);
}

void Logger::setGE(const GameEngine * ge)
{
	ge_ = ge;
}
