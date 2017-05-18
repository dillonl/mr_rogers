#pragma once

#include "core/utils/Noncopyable.hpp"

#include <memory>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

namespace mr_rogers
{
    class FileReader : private Noncopyable
	{
	public:
		typedef std::shared_ptr< FileReader > SharedPtr;
		FileReader(const std::string& fileName);
		~FileReader();

		void read(const char* data, size_t datasize);
		void close();
		std::string getFileName() { return m_file_name; }

	private:
		struct stat m_sb;
		std::string m_file_name;
		/* FILE* m_file; */
		int m_fd;
		void* m_p;
		bool m_open;
		uint64_t m_current_pos;

	};
}
