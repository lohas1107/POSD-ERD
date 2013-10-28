#include "gtest/gtest.h"
#include <fstream>
#include "ERModel.h"
#include "PresentationModel.h"

class RedoConnectComponentTest : public ::testing::Test
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
		_presentation = PresentationModel(&_model);
	}

	virtual void TearDown()
	{
		_inputFile.close();
		_rmdir("testdata");
	}
	string _filePath;
	ifstream _inputFile;
	ERModel _model;
	PresentationModel _presentation;
};

// 整合測是重複做連結元件命令
TEST_F(RedoConnectComponentTest, testRedoConnectComponent)
{
	EXPECT_TRUE(_presentation.loadFile(_filePath));
	_presentation.addNodeCommand("E", "Test");
	EXPECT_EQ(16, _model.getComponentSize());
	EXPECT_EQ(15, _model.getNodeID());
	EXPECT_EQ(entity, _model.getNodeType(15).first);
	EXPECT_EQ("Test", _model.getNodeText(15));
	_presentation.addNodeCommand("A", "Test Attr");
	EXPECT_EQ(17, _model.getComponentSize());
	EXPECT_EQ(16, _model.getNodeID());
	EXPECT_EQ(attribute, _model.getNodeType(16).first);
	EXPECT_EQ("Test Attr", _model.getNodeText(16));
	_presentation.connectNodeCommand(15, 16, "");
	EXPECT_EQ(15, _model._components[17]->getConnection()[0]->getID());
	EXPECT_EQ(16, _model._components[17]->getConnection()[1]->getID());
	_presentation.undo();
	EXPECT_EQ(0, _model._components[15]->getConnection().size());
	EXPECT_EQ(0, _model._components[16]->getConnection().size());
	_presentation.redo();
	EXPECT_EQ(15, _model._components[17]->getConnection()[0]->getID());
	EXPECT_EQ(16, _model._components[17]->getConnection()[1]->getID());
}