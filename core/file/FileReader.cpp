#include "FileReader.h"

namespace mr_rogers
{
	FileReader::FileReader(const std::string& fileName) :
		m_current_pos(0)
	{
		int pagesize = getpagesize();
		m_file_name = fileName;
		m_fd = open(fileName.c_str(), O_RDONLY);
		m_p = mmap(0, m_sb.st_size, PROT_READ, MAP_SHARED, m_fd, pagesize);
	}

	FileReader::~FileReader()
	{
	}

	void FileReader::read(const char* data, size_t datasize)
	{
		data = (char*)m_p +  m_current_pos;
		m_current_pos += datasize;
	}

	void FileReader::close()
	{
		munmap(m_p, m_sb.st_size);
	}
}
