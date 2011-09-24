/**
 * @file   logger.hh
 * @author Vincent Boucheny <vincent.boucheny@hpc-sa.com>
 * @date   Sun Sep 25 00:42:58 2011
 *
 * @brief
 *
 *
 */

#ifndef LOGGER_HH
# define LOGGER_HH

# include <iostream>
# include <sstream>

class Logger
{
public:
	static void log(const std::string& msg)
	{
		std::cout << msg << std::endl;
	}

	template <class T>
	static std::string to_string(const T& t)
	{
		std::stringstream ss;
		ss << t;
		return ss.str();
	}
};

#endif
