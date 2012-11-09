/**
 * @file   debug-logger.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sat Nov 12 23:53:57 2011
 *
 * @brief  Declaration of the debug-logger class.
 */

#ifndef DEBUG_LOGGER_HH
# define DEBUG_LOGGER_HH

# include <iostream>
# include <string>

class DebugLogger
{
public:
	static void log(const std::string & msg)
	{
		std::cerr << msg << std::endl;
	}
};

#endif
