#ifndef MRROGERS_DATABASE_H
#define MRROGERS_DATABASE_H

#include "core/file/File.h"

#include <memory>
#include <vector>

namespace mr_rogers
{
	class Database
	{
	public:
		typedef std::shared_ptr< Database > SharedPtr;
		Database();
		~Database();

		void loadFile(const std::string& filename);
		void createFile(const std::string& filename, size_t filesize);
		void addRecord(const char*, size_t n);
		std::vector< uint64_t > getRecordsWithinDistance(const uint32_t distance);

	private:
		uint64_t m_current_file_position;

	};
}

#endif //MRROGERS_DATABASE_H
