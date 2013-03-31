/**
 * @file   file-reader.hh
 * @author Vincent Boucheny <vincent.boucheny@hpc-sa.com>
 * @date   Sun Mar 31 17:02:50 2013
 *
 * @brief  Declaration of the file-reader class.
 */

#ifndef FILE_READER_HH
#define FILE_READER_HH

#include <fstream>

namespace view
{
	class FileReader
	{
	public:
		/** Constructor. */
		FileReader(const std::string & file_name);

		/** Destructor. */
		~FileReader();

		std::string next_line();
		int next_int();
		unsigned next_uint();
		std::string next_str();

	private:
		std::ifstream file_;
	};
}

#endif
