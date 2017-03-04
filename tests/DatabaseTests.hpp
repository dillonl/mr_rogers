#ifndef TEST_DATABASE_TESTS_HPP
#define TEST_DATABASE_TESTS_HPP

#include "core/database/Database.h"

TEST(DatabaseTest, DatabaseCreate)
{

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
