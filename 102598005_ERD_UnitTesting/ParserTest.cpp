#include "gtest/gtest.h"
#include "Parser.h"

class ParserTest : public ::testing::Test
{
protected:
	Parser _parser;
};

// 測試分割字串
TEST_F(ParserTest, split)
{
	vector<string> elements = _parser.split("1,2,3", ',');
	EXPECT_EQ("1", elements[0]);
	EXPECT_EQ("2", elements[1]);
	EXPECT_EQ("3", elements[2]);
}

// 測試 vector<string> 轉 vector<int>
TEST_F(ParserTest, changeToVectorInt)
{
	vector<string> stringVector;
	stringVector.push_back("a");
	vector<int> result = _parser.changeToVectorInt(stringVector);
	EXPECT_EQ(1, result.size());
	stringVector.clear();
	result.clear();
	stringVector.push_back("1");
	stringVector.push_back("2");
	stringVector.push_back("3");
	result = _parser.changeToVectorInt(stringVector);
	EXPECT_EQ(1, result[0]);
	EXPECT_EQ(2, result[1]);
	EXPECT_EQ(3, result[2]);
}