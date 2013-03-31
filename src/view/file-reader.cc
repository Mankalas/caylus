/**
 * @file   file-reader.cc
 * @author Vincent Boucheny <vincent.boucheny@hpc-sa.com>
 * @date   Sun Mar 31 17:03:35 2013
 *
 * @brief  Declaration of the file-reader class.
 */

#include "file-reader.hh"
#include "../exceptions.hh"
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace view;

FileReader::FileReader(const std::string & file_name)
{
	file_.open(file_name.c_str(), std::ios::in);
	if (!file_.is_open())
	{
		std::cerr << "Could not open file " << file_name << std::endl;
	}
}

FileReader::~FileReader()
{
	file_.close();
}

std::string FileReader::next_line()
{
	std::string line;
	if (std::getline(file_, line))
	{
		return line;
	}
	else
	{
		throw new controller::GameOverException();
	}
}

std::string FileReader::next_str()
{
	return next_line();
}

int FileReader::next_int()
{
	std::string line = next_line();
	return atoi(line.c_str());
}

unsigned FileReader::next_uint()
{
	std::string line = next_line();
	return strtoul(line.c_str(), NULL, 0);
}
