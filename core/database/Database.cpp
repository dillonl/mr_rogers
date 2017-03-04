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

	void Database::addRecord(uint8_t* rawPoint, const std::string& data)
	{
		Eigen::Matrix< uint8_t, 1, 256 > point = Eigen::Matrix< uint8_t, 1, 256 >(rawPoint);
		for (auto hyperplane : m_hyperplanes)
		{
			auto dist = hyperplane.signedDistance(point);
		}
	}
	std::vector< uint64_t > Database::getRecordsWithinDistance(const uint32_t distance)
	{
	}

	void Database::initializeHyperplanes(std::vector< const uint8_t* >& initPoints, uint32_t numRecords)
	{
		m_hyperplanes.clear();
		for (auto initPoint : initPoints)
		{
			Eigen::Matrix< uint8_t, 1, 256 > point = Eigen::Matrix< uint8_t, 1, 256 >(initPoint);
			Eigen::Matrix< uint8_t, 1, 256 > rando = Eigen::Matrix< uint8_t, 1, 256 >::Random();
			Eigen::Hyperplane< uint8_t, 256 > hyperplane(point, rando);
			m_hyperplanes.emplace_back(hyperplane);
		}
		m_distances.reserve(initPoints.size() * numRecords);
	}

}
