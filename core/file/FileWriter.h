#pragma once

#include "core/utils/Noncopyable.hpp"

#include <memory>
#include <stdio.h>

namespace mr_rogers
{
    class FileWriter : private Noncopyable
	{
	public:
		typedef std::shared_ptr< FileWriter > SharedPtr;
		FileWriter();
		~FileWriter();

		void createFile(const std::string& filename);
		void write(const char* data, size_t datasize);
		void write(const char* data, size_t datasize, uint64_t& offset);
		void close();
		std::string getFileName() { return m_file_name; }

	private:
		std::string m_file_name;
		FILE* m_file;
		bool m_open;

	};
}
