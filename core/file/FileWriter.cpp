#include "FileWriter.h"

#include <string>

namespace mr_rogers
{
	FileWriter::FileWriter() :
		m_file(nullptr)
	{
	}

	FileWriter::~FileWriter()
	{
		close();
	}

	void FileWriter::createFile(const std::string& filename)
	{
		m_file = fopen(filename.c_str(), "wb");
	}

	void FileWriter::write(const char* data, size_t datasize)
	{
		fwrite(data, sizeof(char), datasize, m_file);
	}

	void FileWriter::close()
	{
		fclose(m_file);
	}
}
