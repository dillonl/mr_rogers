#include "FileWriter.h"

#include <string>
#include <iostream>
#include <stdio.h>

namespace mr_rogers
{
	FileWriter::FileWriter() :
		m_file(nullptr),
		m_open(false)
	{
	}

	FileWriter::~FileWriter()
	{
		close();
	}

	void FileWriter::createFile(const std::string& filename)
	{
		if (!m_open)
		{
			m_open = true;
			m_file = fopen(filename.c_str(), "w+");
		}
	}

	void FileWriter::write(const char* data, size_t datasize)
	{
		if (m_open)
		{
			fwrite(data, sizeof(char), datasize, m_file);
		}
		else
		{
			throw "error: you are writing to an unopened file";
		}
	}

	void FileWriter::write(const char* data, size_t datasize, uint64_t& offset)
	{
		if (m_open)
		{
			offset = ftell(m_file);
			fwrite(data, sizeof(char), datasize, m_file);
		}
		else
		{
			throw "error: you are writing to an unopened file";
		}
	}

	void FileWriter::close()
	{
		if (m_open)
		{
			fclose(m_file);
			m_open = false;
		}
	}
}
