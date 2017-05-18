#pragma once

#include "IDataItem.hpp"
#include "core/file/FileWriter.h"
#include "core/file/FileReader.h"
#include "core/utils/Noncopyable.hpp"
#include "core/utils/ThreadPool.hpp"

#include "Eigen/Dense"
#include "Eigen/Geometry"

#include "external_sort.hpp"

#include <mutex>
#include <memory>
#include <vector>
#include <functional>

struct CustomRecord
{
		uint64_t filePosition;
		uint8_t distance;
};
struct CustomRecordComparator
{
		bool operator()(const CustomRecord& x, const CustomRecord& y) const {
				return x.distance < y.distance;
		}
};

struct CustomRecord2Str
{
		std::string operator()(const CustomRecord& x)
				{
						return std::to_string(x.distance);
				}
};

namespace external_sort {
		template <>
		struct ValueTraits<CustomRecord>
		{
				using Comparator = CustomRecordComparator;
				/* using Generator = CustomRecordGenerator; */
				using Value2Str = CustomRecord2Str;
		};
}

namespace mr_rogers
{
	class Database : private Noncopyable
	{
	public:
		typedef std::shared_ptr< Database > SharedPtr;
		Database(const std::string& dataPath, uint32_t dimensions);
		~Database();

		/*
		 * Adds a record to the data file as well as a record of the
		 * distance between this record and the hyperplanes within
		 * each respective file.
		 */
		void addRecord(uint8_t* rawPoint, const std::string& data);

		/*
		 * This should be called after all the records are added and the index has been generated.
		 */
		std::vector< uint64_t > getRecordsWithinDistance(const uint32_t distance);

		/*
		 * getRecordsWithinDistance should only be called after generateIndex.
		 * This implementation must be in the h file because it is templated
		 */
		void generateIndex();


	private:
		/*
		 * initializeHyperplanes should be called with a representative collection of points.
		 * This is how the hyperspace is divided and clusters are formed.
		 */
		void initializeHyperplanes();
		void createDataFiles(const std::string& filename);
		void closeFiles();
		void sortFiles();
		void generatePointIndex();

		FileWriter::SharedPtr m_data_file_ptr;
		std::vector< FileWriter::SharedPtr > m_dist_file_ptrs;
        std::vector< FileReader::SharedPtr > m_sorted_dist_file_ptrs;
		std::vector< std::mutex > m_file_locks;
		std::mutex m_sorted_dist_file_ptrs_lock;
		std::string m_index_path;
		std::string m_data_path;
		std::vector< Eigen::Hyperplane< uint8_t, 256 > > m_hyperplanes;

		std::vector< uint8_t > m_distances;
		uint32_t m_dimensions;
	};
}
