#include "gtest/gtest.h"
#include <fstream>
#include "ERModel.h"

class IsPrimaryExistTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		_filePath = "testdata/test_file1.erd";
		_mkdir("testdata");
		ofstream outputFile(_filePath);
		outputFile << "E, Engineer" << endl;
		outputFile << "A, Emp_ID" << endl;
		outputFile << "R, Has" << endl;
		outputFile << "A, Name" << endl;
		outputFile << "E, PC" << endl;
		outputFile << "A, PC_ID" << endl;
		outputFile << "A, Purchase_Date" << endl;
		outputFile << "C" << endl;
		outputFile << "C" << endl;
		outputFile << "C" << endl;
		outputFile << "C" << endl;
		outputFile << "C, 1" << endl;
		outputFile << "C, 1" << endl;
		outputFile << "A, Department" << endl;
		outputFile << "C" << endl;
		outputFile << endl;
		outputFile << "7  0,1" << endl;
		outputFile << "8  0,3" << endl;
		outputFile << "9  4,5" << endl;
		outputFile << "10 4,6" << endl;
		outputFile << "11 0,2" << endl;
		outputFile << "12 2,4" << endl;
		outputFile << "14 0,13" << endl;
		outputFile << endl;
		outputFile << "0 1,3" << endl;
		outputFile << "4 5" << endl;
		outputFile.close();
		_inputFile.open(_filePath);
	}

	virtual void TearDown()
	{
		_inputFile.close();
		_rmdir("testdata");
	}
	string _filePath;
	ifstream _inputFile;
	ERModel _model;
};

// 整合測試是否為 primary key
TEST_F(IsPrimaryExistTest, testIsPrimaryExist)
{
	EXPECT_TRUE(_model.loadFile(_filePath));
	string table = _model.getTable();
	EXPECT_EQ(3, table.find("Engineer |  PK(Emp_ID, Name)"));
	EXPECT_EQ(53, table.find("PC |  PK(PC_ID)"));
	EXPECT_EQ(4294967295, table.find("PC |  PK(Purchase_Date)"));
}