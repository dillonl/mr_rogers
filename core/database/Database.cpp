#include "Database.h"

#include <random>

namespace mr_rogers
{
	Database::Database(const std::string& dataPath, uint32_t dimensions) : m_file_locks(256), m_dimensions(dimensions), m_data_file_ptr(std::make_shared< FileWriter >()), m_data_path(dataPath)
	{
		createDataFiles(dataPath);
		initializeHyperplanes();
		ThreadPool::Instance()->start();
	}

	Database::~Database()
	{
		for (uint32_t i = 0; i < m_dist_file_ptrs.size(); ++i)
		{
			m_dist_file_ptrs[i]->close();
		}
	}

	void Database::createDataFiles(const std::string& dataPath)
	{
		std::string dataFileName = dataPath + "/data.dat";
		m_data_file_ptr->createFile(dataFileName);
		for (uint32_t i = 0; i < 256; ++i)
		{
			std::string fileName = dataPath + "/" + std::to_string(i) + ".hpd";
			auto dataFilePtr = std::make_shared< FileWriter >();
			dataFilePtr->createFile(fileName);
			m_dist_file_ptrs.emplace_back(dataFilePtr);
		}
	}

	void Database::addRecord(uint8_t* rawPoint, const std::string& data)
	{
		uint64_t idx;
		m_data_file_ptr->write(data.c_str(), data.size(), idx);
		auto pointPtr = std::make_shared< Eigen::Matrix< uint8_t, 1, 256 > >(rawPoint);
		auto funct = [this, pointPtr, idx]()
            {
				for (uint32_t i = 0; i < m_dimensions; ++i)
				{
                    uint8_t dist = m_hyperplanes[i].signedDistance(*pointPtr);
					CustomRecord ct;
					ct.distance = dist;
					ct.filePosition = idx;
					{
						std::lock_guard< std::mutex > l(m_file_locks[i]);
						// std::cout << (int)dist << std::endl;
						m_dist_file_ptrs[i]->write((char*)&ct, sizeof(ct));
						// m_dist_file_ptrs[i]->write((char*)&idx, sizeof(idx));
						// m_dist_file_ptrs[i]->write((char*)&dist, sizeof(dist));
						// std::cout << (int)ct.distance << " " << (int)ct.filePosition << std::endl;
					}
				}
            };
		ThreadPool::Instance()->enqueue(funct);
	}

	std::vector< uint64_t > Database::getRecordsWithinDistance(const uint32_t distance)
	{
	}

	void Database::closeFiles()
	{
		for (uint32_t i = 0; i < m_dist_file_ptrs.size(); ++i)
		{
			m_dist_file_ptrs[i]->close();
		}
	}

	void Database::sortFiles()
	{
		for (uint32_t i = 0; i < m_dist_file_ptrs.size(); ++i)
		{
			auto funct = [this, i]()
			{
				std::cout << "starting: " << i << std::endl;
				external_sort::SplitParams sp;
				external_sort::MergeParams mp;
				sp.mem.size = 1000;
				sp.mem.unit = external_sort::MB;
				mp.mem = sp.mem;

				sp.spl.ifile = m_data_path + std::to_string(i) +  ".hpd";
				mp.mrg.ofile = m_data_path + std::to_string(i) +  ".spd";

				using ValueType = CustomRecord;

				// run external sort
				external_sort::sort< CustomRecord >(sp, mp);
				if (sp.err.none && mp.err.none)
				{
					auto sortedDataFilePtr = std::make_shared< FileReader >(mp.mrg.ofile);
					std::lock_guard< std::mutex > l(m_sorted_dist_file_ptrs_lock);
					m_sorted_dist_file_ptrs.emplace_back(sortedDataFilePtr);
				}
				else
				{
					std::cout << "External sort failed!" << std::endl;
					if (sp.err)
					{
						std::cout << "Split failed: " << sp.err.msg() << std::endl;
					}
					else
					{
						std::cout << "Merge failed: " << mp.err.msg() << std::endl;
					}
				}
				std::cout << "ending: " << i << std::endl;
			};
			ThreadPool::Instance()->enqueue(funct);
		}
		ThreadPool::Instance()->joinAll();
	}

	void Database::generateIndex()
	{
		closeFiles();
		sortFiles();
		generatePointIndex();
	}

	void Database::generatePointIndex()
	{
		std::cout << "reading" << std::endl;
		for (auto sortedFileReaderPtr : m_sorted_dist_file_ptrs)
		{
			CustomRecord ct;
			sortedFileReaderPtr->read((char*)&ct, sizeof(ct));
			std::cout << ct.distance << " " << ct.filePosition << std::endl;
		}
	}

	void Database::initializeHyperplanes()
	{
		m_hyperplanes.clear();
		uint8_t norm[256];

		for (uint32_t i = 0; i < m_dimensions; ++i)
		{
			for (uint32_t j = 0; j < 256; ++j) { norm[j] = (j == i) ? 1 : 0; }
			Eigen::Matrix< uint8_t, 1, 256 > normPoint = Eigen::Matrix< uint8_t, 1, 256 >(norm);
			normPoint.normalize();
			Eigen::Hyperplane< uint8_t, 256 > hyperplane(normPoint, 0);
			m_hyperplanes.emplace_back(hyperplane);
		}
	}

}
