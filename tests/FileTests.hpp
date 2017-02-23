#ifndef TEST_FILETESTS_HPP
#define TEST_FILETESTS_HPP

#include "core/file/FileWriter.h"

#include <iostream>

TEST(FileTest, TestFileCreate)
{
	mr_rogers::FileWriter fileWriter;
	fileWriter.createFile("test.txt");
}

#endif// TEST_FILETESTS_HPP
