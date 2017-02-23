#include "File.h"

#include <iostream>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <sys/mman.h>
#include <unistd.h>

namespace mr_rogers
{
	File::File() :
		m_fd(0),
		m_pos(0)
	{
	}

	File::~File()
	{
	}

	void File::createFile(const std::string& filename, size_t filesize)
	{
		auto pagesize = getpagesize();
		m_filesize = (filesize % pagesize) * pagesize;
		std::cout << "size: " << m_filesize << std::endl;
		m_fd = open(filename.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0777);

		m_pos = mmap(0, m_filesize, PROT_WRITE | PROT_READ, MAP_SHARED, m_fd, pagesize);
		if (m_pos == MAP_FAILED)
		{
			throw "File Open Failed";
		}
		std::string test = "Hello";
		// for (int i = 0; i < test.size(); ++i)
		// {
			// std::cout << "i: " << i << " " << test.c_str()[i] << std::endl;
			// m_pos[i] = test.c_str()[i];
		// }
		std::memcpy(m_pos, test.c_str(), test.size());
		std::cout << "1" << std::endl;

		if (msync(m_pos, test.size(), MS_SYNC) == -1)
		{
			perror("Could not sync the file to disk");
		}
		munmap(m_pos, m_filesize);
	}

	void File::write(const char* data, size_t datasize)
	{
	}

	void File::close()
	{
		munmap(0, m_filesize);
	}
}
