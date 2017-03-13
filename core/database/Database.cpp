#include "Database.h"

namespace mr_rogers
{
	Database::Database(const std::string& dataPath)
	{
		createDataFiles(dataPath);
	}

	Database::~Database()
	{
		for (uint32_t i = 0; i < m_data_file_ptrs.size(); ++i)
		{
			m_data_file_ptrs[i]->close();
		}
	}

	void Database::createDataFiles(const std::string& dataPath)
	{
		for (uint32_t i = 0; i < 256; ++i)
		{
			std::string fileName = dataPath + "/" + std::to_string(i) + ".hpd";
			auto dataFilePtr = std::make_shared< FileWriter >();
			dataFilePtr->createFile(fileName);
			m_data_file_ptrs.emplace_back(dataFilePtr);
		}
	}

	void Database::addRecord(uint8_t* rawPoint, const std::string& data, uint64_t fileOffset)
	{
		Eigen::Matrix< uint8_t, 1, 256 > point = Eigen::Matrix< uint8_t, 1, 256 >(rawPoint);
		uint8_t dists[256];
		for (uint32_t i = 0; i < 256; ++i)
		{
			dists[i] = m_hyperplanes[i].signedDistance(point);
		}
		writeRecord(dists, fileOffset);
	}

	void Database::writeRecord(uint8_t* distances, uint64_t fileOffset)
	{
		for (uint32_t i = 0; i < 256; ++i)
		{
			m_data_file_ptrs[i]->write((char*)&distances[i], 1, fileOffset);
		}
	}

	std::vector< uint64_t > Database::getRecordsWithinDistance(const uint32_t distance)
	{
	}

	void Database::initializeHyperplanes()
	{
		m_hyperplanes.clear();
		uint8_t zeros[256];
		uint8_t norm[256];

		for (uint32_t j = 0; j < 256; ++j) { zeros[j] = 0; }
		Eigen::Matrix< uint8_t, 1, 256 > initPoint = Eigen::Matrix< uint8_t, 1, 256 >(zeros);
		for (uint32_t i = 0; i < 256; ++i)
		{
			Eigen::Matrix< uint8_t, 1, 256 > point = Eigen::Matrix< uint8_t, 1, 256 >(initPoint);
			for (uint32_t j = 0; j < 256; ++j) { norm[j] = (j == i) ? 1 : 0; }
			Eigen::Matrix< uint8_t, 1, 256 > normPoint = Eigen::Matrix< uint8_t, 1, 256 >(norm);
			Eigen::Hyperplane< uint8_t, 256 > hyperplane(point, normPoint);
			m_hyperplanes.emplace_back(hyperplane);
		}
	}

}
