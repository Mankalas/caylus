/**
 * @file   logger.hxx
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Tue Nov  1 19:57:56 2011
 *
 * @brief  Declaration of the logger class.
 */

#include "logger.hh"
#include <sstream>

template <class T>
std::string Logger::to_string(const T &t) const
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

