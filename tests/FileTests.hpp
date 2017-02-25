#ifndef TEST_FILETESTS_HPP
#define TEST_FILETESTS_HPP

#include "core/file/FileWriter.h"
#include "config/TestConfig.h"

#include <iostream>
#include <stdio.h>

inline bool file_exists (const std::string& name)
{
	if (FILE *file = fopen(name.c_str(), "r"))
	{
		fclose(file);
		return true;
	}
	else
	{
		return false;
	}
}

TEST(FileTest, TestFileCreate)
{
	mr_rogers::FileWriter fileWriter;
	std::string filePath = std::string(TEST_DATA_DIR);
	filePath += "/test_r.txt";
	remove(filePath.c_str());
	EXPECT_FALSE(file_exists(filePath));
	fileWriter.createFile(filePath);
	EXPECT_TRUE(file_exists(filePath));
	remove(filePath.c_str());
}

TEST(FileTest, TestFileWrite)
{
	mr_rogers::FileWriter fileWriter;
	std::string filePath = std::string(TEST_DATA_DIR);
	filePath += "/test_w.txt";
	remove(filePath.c_str());
	fileWriter.createFile(filePath);
	char* test = new char[256];
	for (int i = 0; i < 255; ++i)
	{
		test[i] = i;
	}
	for (uint32_t i = 0; i < 1; ++i)
	{
		fileWriter.write(test, 256);
	}
	fileWriter.close();
	remove(filePath.c_str());
}

#endif// TEST_FILETESTS_HPP
