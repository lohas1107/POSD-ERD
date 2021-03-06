#include "gtest/gtest.h"
#include <fstream>
#include "ERModel.h"
#include "PresentationModel.h"

class IntegrationTest : public ::testing::Test
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
		_model = new ERModel();
		_presentation = new PresentationModel(_model);
	}

	virtual void TearDown()
	{
		_inputFile.close();
		remove(_filePath.c_str());
		_rmdir("testdata");
		delete _presentation;
	}
	string _filePath;
	ifstream _inputFile;
	ERModel* _model;
	PresentationModel* _presentation;
};

// 整合測試讀取不存在的檔案
TEST_F(IntegrationTest, testLoadFileNotExist)
{
	EXPECT_FALSE(_model->loadFile("testdata/file_not_exist.erd"));
}

// 整合測試是否為 primary key
TEST_F(IntegrationTest, testIsPrimaryExist)
{
	EXPECT_TRUE(_model->loadFile(_filePath));
	string table = _model->getTable();
	EXPECT_EQ(3, table.find("Engineer |  PK(Emp_ID, Name)"));
	EXPECT_EQ(53, table.find("PC |  PK(PC_ID)"));
	EXPECT_EQ(4294967295, table.find("PC |  PK(Purchase_Date)"));
}

// 整合測試回復刪除元件
TEST_F(IntegrationTest, testUndoDeleteComponent)
{
	EXPECT_TRUE(_presentation->loadFile(_filePath));
	_presentation->addNodeCommand("E", "Test", QPointF(0, 0));
	EXPECT_EQ(16, _model->getComponentSize());
	EXPECT_EQ(15, _model->getNodeID());
	EXPECT_EQ(entity, _model->getNodeType(15).first);
	EXPECT_EQ("Test", _model->getNodeText(15));
	_presentation->deleteComponentCommand(15);
	EXPECT_EQ(15, _model->getComponentSize());
	EXPECT_FALSE(_presentation->isIDExsit(15));
	_presentation->undo();
	EXPECT_EQ(16, _model->getComponentSize());
	EXPECT_EQ(entity, _model->getNodeType(15).first);
	EXPECT_EQ("Test", _model->getNodeText(15));
}

// 整合測是重複做連結元件命令
TEST_F(IntegrationTest, testRedoConnectComponent)
{
	EXPECT_TRUE(_presentation->loadFile(_filePath));
	_presentation->addNodeCommand("E", "Test", QPointF(0, 0));
	EXPECT_EQ(16, _model->getComponentSize());
	EXPECT_EQ(15, _model->getNodeID());
	EXPECT_EQ(entity, _model->getNodeType(15).first);
	EXPECT_EQ("Test", _model->getNodeText(15));
	_presentation->addNodeCommand("A", "Test Attr", QPointF(0, 0));
	EXPECT_EQ(17, _model->getComponentSize());
	EXPECT_EQ(16, _model->getNodeID());
	EXPECT_EQ(attribute, _model->getNodeType(16).first);
	EXPECT_EQ("Test Attr", _model->getNodeText(16));
	_presentation->connectNodeCommand(15, 16, "");
	EXPECT_EQ(15, _model->_components[17]->getConnection()[0]->getID());
	EXPECT_EQ(16, _model->_components[17]->getConnection()[1]->getID());
	_presentation->undo();
	EXPECT_EQ(0, _model->_components[15]->getConnection().size());
	EXPECT_EQ(0, _model->_components[16]->getConnection().size());
	_presentation->redo();
	EXPECT_EQ(15, _model->_components[17]->getConnection()[0]->getID());
	EXPECT_EQ(16, _model->_components[17]->getConnection()[1]->getID());
}

// 整合測試命令使用
TEST_F(IntegrationTest, testCommonUsage)
{
	EXPECT_TRUE(_presentation->loadFile(_filePath));
	_presentation->addNodeCommand("E", "Work Diary", QPointF(0, 0));
	EXPECT_EQ(16, _model->getComponentSize());
	EXPECT_EQ(15, _model->getNodeID());
	EXPECT_EQ(entity, _model->getNodeType(15).first);
	EXPECT_EQ("Work Diary", _model->getNodeText(15));
	_presentation->addNodeCommand("R", "Write", QPointF(0, 0));
	EXPECT_EQ(17, _model->getComponentSize());
	EXPECT_EQ(16, _model->getNodeID());
	EXPECT_EQ(relation, _model->getNodeType(16).first);
	EXPECT_EQ("Write", _model->getNodeText(16));
	_presentation->connectNodeCommand(0, 16, "1");
	EXPECT_EQ(0, _model->_components[17]->getConnection()[0]->getID());
	EXPECT_EQ(16, _model->_components[17]->getConnection()[1]->getID());
	_presentation->connectNodeCommand(15, 16, "");
	EXPECT_EQ(15, _model->_components[18]->getConnection()[0]->getID());
	EXPECT_EQ(16, _model->_components[18]->getConnection()[1]->getID());
	_presentation->addNodeCommand("A", "Content", QPointF(0, 0));
	EXPECT_EQ(20, _model->getComponentSize());
	EXPECT_EQ(19, _model->getNodeID());
	EXPECT_EQ(attribute, _model->getNodeType(19).first);
	EXPECT_EQ("Content", _model->getNodeText(19));
	_presentation->addNodeCommand("A", "WD_ID", QPointF(0, 0));
	EXPECT_EQ(21, _model->getComponentSize());
	EXPECT_EQ(20, _model->getNodeID());
	EXPECT_EQ(attribute, _model->getNodeType(20).first);
	EXPECT_EQ("WD_ID", _model->getNodeText(20));
	_presentation->addNodeCommand("A", "WD_date", QPointF(0, 0));
	EXPECT_EQ(22, _model->getComponentSize());
	EXPECT_EQ(21, _model->getNodeID());
	EXPECT_EQ(attribute, _model->getNodeType(21).first);
	EXPECT_EQ("WD_date", _model->getNodeText(21));
	_presentation->connectNodeCommand(15, 19, "");
	EXPECT_EQ(15, _model->_components[22]->getConnection()[0]->getID());
	EXPECT_EQ(19, _model->_components[22]->getConnection()[1]->getID());
	_presentation->connectNodeCommand(15, 20, "");
	EXPECT_EQ(15, _model->_components[23]->getConnection()[0]->getID());
	EXPECT_EQ(20, _model->_components[23]->getConnection()[1]->getID());
	_presentation->connectNodeCommand(15, 21, "");
	EXPECT_EQ(15, _model->_components[24]->getConnection()[0]->getID());
	EXPECT_EQ(21, _model->_components[24]->getConnection()[1]->getID());
	vector<int> wdID;
	wdID.push_back(20);
	_presentation->setPrimaryKey(wdID);
	EXPECT_TRUE(((AttributeNode*)_model->_components[20])->isPrimaryKey());
	EXPECT_TRUE(_presentation->isAttribute(15, 20));
	string table = _presentation->getTable();
	EXPECT_EQ(103, table.find("Work Diary"));
	EXPECT_EQ(103, table.find("Work Diary |  PK(WD_ID)"));
	_presentation->deleteComponentCommand(15);
	EXPECT_FALSE(_presentation->isIDExsit(15));
	EXPECT_EQ(1, _model->_components[_model->findIndex(16)]->getConnection().size());
	EXPECT_EQ(0, _model->_components[_model->findIndex(16)]->getConnection()[0]->getID());
	EXPECT_EQ(0, _model->_components[_model->findIndex(19)]->getConnection().size());
	EXPECT_EQ(0, _model->_components[_model->findIndex(20)]->getConnection().size());
	EXPECT_EQ(0, _model->_components[_model->findIndex(21)]->getConnection().size());
	table = _presentation->getTable();
	EXPECT_EQ(4294967295, table.find("Work Diary"));
	EXPECT_EQ(3, table.find("Engineer |  PK(Emp_ID, Name)"));
	_presentation->undo();
	table = _presentation->getTable();
	EXPECT_EQ(103, table.find("Work Diary |  PK(WD_ID)"));
	_presentation->redo();
	table = _presentation->getTable();
	EXPECT_EQ(4294967295, table.find("Work Diary"));
	EXPECT_EQ(3, table.find("Engineer |  PK(Emp_ID, Name)"));
}