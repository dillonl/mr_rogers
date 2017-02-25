#ifndef MRROGERS_DATABASE_H
#define MRROGERS_DATABASE_H

#include "core/file/FileWriter.h"

#include <memory>
#include <vector>

namespace mr_rogers
{
	class Database
	{
	public:
		typedef std::shared_ptr< Database > SharedPtr;
		Database(const std::string& dataPath);
		~Database();

		void addRecord(const char*, size_t n);
		void generateIndex();
		std::vector< uint64_t > getRecordsWithinDistance(const uint32_t distance);

	private:
		void createDataFile(const std::string& filename);

		FileWriter::SharedPtr m_data_file_ptr;
		std::string m_index_path;

	};
}

#endif //MRROGERS_DATABASE_H
