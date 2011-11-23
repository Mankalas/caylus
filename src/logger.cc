/**
 * @file   logger.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun Oct 30 23:39:12 2011
 *
 * @brief  Implementation of the logger class.
 */

#include "logger.hh"

#include <iostream>
#include "game-engine.hh"
#include "player.hh"
#include "resource-map.hh"

using namespace std;
using namespace controller;

Logger * Logger::instance_ = NULL;

Logger::Logger()
{
	file_.open("caylus.html", ios::trunc);
	file_ << "<html>\n<head>\n\n<style type=\"text/css\">\nbody {\n     font-family: Arial,Helvetica,sans-serif;\n     font-size: x-small;\n     color: #333333;\n     text-align: justify;\n     width:95%\n}\n\n#bridge\n{\n     color:#3a3aff\n}\n\n#castle\n{\n     color:#008000\n}\n\n.building\n{\n     color:#c89baa\n}\n\n.choice\n{\n     background-color:#F1F19B\n}\n</style>\n\n</head>\n<body>";
}

void Logger::close()
{
	file_ <<  "</body>\n</html>" << std::endl;
	file_.close();
}

Logger * Logger::instance()
{
	if (instance_ == NULL)
	{
		instance_ = new Logger();
	}
	return instance_;
}

void Logger::log(const std::string &msg)
{
	std::cout << msg << std::endl;
}

void Logger::gameInfo(const GameEngine * ge)
{
	assert(ge);

	file_ << "<h1>Init info</h1>"
				<< "<ul>\n<li>Number of humans : " << ge->nbHumans() << "</li>"
				<< "<li>Number of AIs : " << ge->nbAIs() << "</li>"
				<< "</ul>";
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

void Logger::playerLog(const Player * p, const std::string & msg)
{
	assert(p);
	file_ << "<p>" << p->name() << " " << msg << "</p>\n";
}

void Logger::placementChoices(const Player * p, const std::vector<BoardElement*> & choices)
{
	assert(p);
	file_ << "<p>" << p->name() << " can place his worker on { ";
	foreach (const BoardElement * board_element, choices)
	{
//		if (board_element != *choices.end())
		{
			file_ << board_element->name() << ", ";
		}
	}
	file_ << "}</p>\n";
}

void Logger::playerBoardChoice(const Player * p, const BoardElement * board_element)
{
	assert(p);
	assert(board_element);
	file_ << "<p>" << p->name() << " has chosen " << board_element->name() << "</p>";
}
