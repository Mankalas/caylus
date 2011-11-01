/**
 * @file   logger.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun Oct 30 23:39:12 2011
 *
 * @brief  Implementation of the logger class.
 */

#include "logger.hh"

#include <iostream>

using namespace std;

Logger * Logger::instance_ = NULL;

Logger::Logger()
{
	file_.open("caylus.log", ios::trunc);
	file_ << "<html>\n<head>\n\n<style type=\"text/css\">\nbody {\n     font-family: Arial,Helvetica,sans-serif;\n     font-size: x-small;\n     color: #333333;\n     text-align: justify;\n     width:95%\n}\n\n#bridge\n{\n     color:#3a3aff\n}\n\n#castle\n{\n     color:#008000\n}\n\n.building\n{\n     color:#c89baa\n}\n\n.choice\n{\n     background-color:#F1F19B\n}\n</style>\n\n</head>\n<body>";
}

Logger::~Logger()
{
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
	file_ << "<p style=\"" << (int)actors_stack_.top() << "\">"
		<< msg << "</p>\n";
}

void Logger::stack(eGameActor actor)
{
	actors_stack_.push(actor);
}

void Logger::pop()
{
	actors_stack_.pop();
}

