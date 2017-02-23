#include "Database.h"

namespace mr_rogers
{
	Database::Database() :
		m_current_file_position(0)
	{
	}

	Database::~Database()
	{
	}

	void Database::loadFile(const std::string& filename)
	{
	}

	void Database::createFile(const std::string& filename, size_t filesize)
	{
	}

	void Database::addRecord(const char*, size_t n)
	{
	}

	std::vector< uint64_t > Database::getRecordsWithinDistance(const uint32_t distance)
	{
	}

}
