#pragma once

#include "core/file/FileWriter.h"
#include "core/utils/Noncopyable.hpp"
#include "IDataItem.hpp"

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

		/*
		 * Adds a record to the data file as well as a record of the
		 * distance between this record and the hyperplanes within
		 * each respective file.
		 */
		void addRecord(uint8_t* rawPoint, const std::string& data, uint64_t offset);

		/*
		 * This should be called after all the records are added and the index has been generated.
		 */
		std::vector< uint64_t > getRecordsWithinDistance(const uint32_t distance);

		/*
		 * initializeHyperplanes should be called with a representative collection of points.
		 * This is how the hyperspace is divided and clusters are formed.
		 */
		void initializeHyperplanes();

		/*
		 * getRecordsWithinDistance should only be called after generateIndex.
		 * This implementation must be in the h file because it is templated
		 */
		template< class T >
		void generateIndex()
		{
		}


	private:
		void createDataFiles(const std::string& filename);
		void writeRecord(uint8_t* distances, uint64_t fileOffset);

		std::vector< FileWriter::SharedPtr > m_data_file_ptrs;
		std::vector< FileWriter::SharedPtr > m_point_file_ptrs;
		std::string m_index_path;
		std::vector< Eigen::Hyperplane< uint8_t, 256 > > m_hyperplanes;

		std::vector< uint8_t > m_distances;
	};
}
