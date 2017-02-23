#ifndef MRROGERS_FILE_H
#define MRROGERS_FILE_H

#include <memory>
#include <fcntl.h>

namespace mr_rogers
{
	class File
	{
	public:
		typedef std::shared_ptr< File > SharedPtr;
		File();
		~File();

		void createFile(const std::string& filename, size_t filesize);
		void write(const char* data, size_t datasize);
		void close();

	private:
		FILE* m_file;
		int m_fd;
		void* m_pos;
		size_t m_filesize;

	};
}

#endif //MRROGERS_FILE_H
