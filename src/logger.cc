/**
 * @file   logger.cc
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun Oct 30 23:39:12 2011
 *
 * @brief  Implementation of the logger class.
 */

#include "logger.hh"

#include <iostream>
#include <sstream>

using namespace std;

Logger::Logger()
{
	file_.open("caylus.log", ios::trunc);
}

Logger::~Logger()
{
	file_.close();
}

Logger & Logger::instance()
{
	if (Logger::instance_ == NULL)
	{
		Logger::instance_ = new Logger();
	}
	return *instance_;
}

void Logger::log(const std::string &msg)
{
	file_ << "<p style=\"" << (int)actors_stack_.top() << "\">"
		<< msg << "</p>\n";
}

template <class T>
std::string Logger::to_string(const T &t) const
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

void Logger::stack(eGameActor actor)
{
	actors_stack_.push(actor);
}

void Logger::pop()
{
	actors_stack_.pop();
}

