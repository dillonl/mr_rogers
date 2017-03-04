#pragma once

#include "core/file/FileWriter.h"
#include "core/utils/Noncopyable.hpp"

#include "Eigen/Dense"
#include "Eigen/Geometry"

#include <memory>
#include <vector>
#include <functional>

namespace mr_rogers
{
	class Database : private Noncopyable
	{
	public:
		typedef std::shared_ptr< Database > SharedPtr;
		Database(const std::string& dataPath);
		~Database();

		void addRecord(uint8_t* rawPoint, const std::string& data);

		std::vector< uint64_t > getRecordsWithinDistance(const uint32_t distance);
		void initializeHyperplanes(std::vector< const uint8_t* >& points, uint32_t numRecords);

	private:
		void createDataFile(const std::string& filename);

		FileWriter::SharedPtr m_data_file_ptr;
		std::string m_index_path;
		std::vector< Eigen::Hyperplane< uint8_t, 256 > > m_hyperplanes;

		std::vector< uint8_t > m_distances;
	};
}
