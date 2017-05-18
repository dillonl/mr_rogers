#ifndef TEST_DATABASE_TESTS_HPP
#define TEST_DATABASE_TESTS_HPP

#include "core/database/Database.h"
#include "core/utils/ThreadPool.hpp"

#include <random>

TEST(DatabaseTest, DatabaseCreate)
{
	std::string dataPath = TEST_DATA_DIR;
	mr_rogers::Database db(dataPath, 256);

	// First create an instance of an engine.
	std::random_device rnd_device;
	// Specify the engine and distribution.
	std::mt19937 mersenne_engine(rnd_device());
	std::uniform_int_distribution<int> dist(0, 256);

	auto gen = std::bind(dist, mersenne_engine);
	std::vector<uint8_t> vec(256);
	for (int i = 0; i < 10; ++i)
	{
		generate(begin(vec), end(vec), gen);
		db.addRecord(&vec[0], "");
	}
    mr_rogers::ThreadPool::Instance()->joinAll();
	db.generateIndex();
}

TEST(DatabaseTest, TestHyperplaneCreate)
{
	/*
	std::vector< Eigen::Hyperplane< float, 256 > > m_hyperplanes;
	for (uint32_t i = 0; i < 256; ++i)
	{
		Eigen::Matrix< float, 1, 256 > rando1 = Eigen::Matrix< float, 1, 256 >::Random();
		Eigen::Matrix< float, 1, 256 > rando2= Eigen::Matrix< float, 1, 256 >::Random();
		Eigen::Hyperplane< float, 256 > hyperPlane(rando1, rando2);
		m_hyperplanes.emplace_back(hyperPlane);
	}


	std::vector< Eigen::Matrix< float, 1, 256 > > points;
	for (uint32_t i = 0; i < 1000000; ++i)
	{
		Eigen::Matrix< float, 1, 256 > rando= Eigen::Matrix< float, 1, 256 >::Random();
		points.emplace_back(rando);
	}
	int count = 0;
	std::vector< float > dists;
	for (auto plane : m_hyperplanes)
	{
		for (auto p : points)
		{
			auto dist = plane.signedDistance(p);
			dists.emplace_back(dist);
		}
		std::cout << count++ << std::endl;
	}
	*/
}

#endif //TEST_DATABASE_TESTS_HPP
