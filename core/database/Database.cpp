#include "Database.h"

namespace mr_rogers
{
	Database::Database(const std::string& dataPath)
	{
		createDataFile(dataPath);
	}

	Database::~Database()
	{
		m_data_file_ptr->close();
	}

	void Database::createDataFile(const std::string& filename)
	{
		m_data_file_ptr = std::make_shared< FileWriter >();
		m_data_file_ptr->createFile(filename);
	}

	void Database::generateIndex()
	{
	}

	void Database::addRecord(const char* data, size_t n)
	{
		m_data_file_ptr->write(data, n);
	}

	std::vector< uint64_t > Database::getRecordsWithinDistance(const uint32_t distance)
	{
	}

}
