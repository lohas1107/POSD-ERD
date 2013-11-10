#include "gtest/gtest.h"
#include "PresentationModel.h"
#include <fstream>

class PresentationModelTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		_presentation = new PresentationModel(&_model);
		_presentation->addNodeCommand("E", "PC");
		_presentation->addNodeCommand("A", "Name");
		_presentation->addNodeCommand("R", "Has");
		_presentation->addNodeCommand("C", "");
		_presentation->addNodeCommand("C", "1");
	}

	// Ū���s�����
	void loadConnection()
	{
		vector<string> content;
		content.push_back("3 0,1");
		content.push_back("4 0,2");
		_model.loadConnection(content);
	}

	// �]�w primary key ���
	void setPrimaryKey(int id)
	{
		vector<int> primaryKey;
		primaryKey.push_back(id);
		_model.setPrimaryKey(primaryKey);
	}

	// �[�J�@��@���
	void addOneToOne()
	{
		_model._componentID = 5;
		_model.addComponent(make_pair(entity, ""), "Person");
		_model.addComponent(make_pair(attribute, ""), "ID");
		_model.addConnection(2, 5, "1");
		_model.addConnection(5, 6, "");
		setPrimaryKey(1);
		setPrimaryKey(6);
	}
	ERModel _model;
	PresentationModel* _presentation; 
};

// �����ˬd��J��type
TEST_F(PresentationModelTest, checkInputType)
{
	EXPECT_TRUE(_presentation->checkInputType("E"));
	EXPECT_TRUE(_presentation->checkInputType("A"));
	EXPECT_TRUE(_presentation->checkInputType("R"));
	EXPECT_FALSE(_presentation->checkInputType("X"));
}

// ���շs�W����
TEST_F(PresentationModelTest, addNodeCommand)
{
	_model.clearComponent();
	_model.initialize();
	EXPECT_EQ(0, _presentation->addNodeCommand("E", "PC"));
	EXPECT_EQ(1, _presentation->addNodeCommand("A", "ID"));
	EXPECT_EQ(2, _presentation->addNodeCommand("R", "Has"));
}

// ���ը��o����id
TEST_F(PresentationModelTest, getNodeID)
{
	_presentation->addNodeCommand("E", "Person");
	EXPECT_EQ(5, _presentation->getNodeID());
}

// ���ը��o����type
TEST_F(PresentationModelTest, getNodeType)
{
	_presentation->addNodeCommand("E", "Person");
	EXPECT_EQ("Entity", _presentation->getNodeType(5));
}

// ���ը��o����text
TEST_F(PresentationModelTest, getNodeText)
{
	_presentation->addNodeCommand("E", "Person");
	EXPECT_EQ("Person", _presentation->getNodeText(5));
}

// ���ը��o�����T
TEST_F(PresentationModelTest, getComponentLine)
{
	EXPECT_EQ("   E  |   0  |  PC\n   A  |   1  |  Name\n   R  |   2  |  Has\n   C  |   3  |  \n   C  |   4  |  1\n", _presentation->getComponentLine(all));
	EXPECT_EQ("   E  |   0  |  PC\n", _presentation->getComponentLine(entity));
	EXPECT_EQ("   A  |   1  |  Name\n", _presentation->getComponentLine(attribute));
	EXPECT_EQ("   R  |   2  |  Has\n", _presentation->getComponentLine(relation));
	EXPECT_EQ("   C  |   3  |  \n   C  |   4  |  1\n", _presentation->getComponentLine(connection));
	_model.clearComponent();
	EXPECT_EQ("", _presentation->getComponentLine(all));
}

// ���էR������R�O
TEST_F(PresentationModelTest, deleteComponentCommand)
{
	loadConnection();
	_presentation->deleteComponentCommand(1);
	EXPECT_EQ(3, _presentation->getComponentSize());
	EXPECT_EQ(0, _model._components[0]->getID());
	EXPECT_EQ(2, _model._components[1]->getID());
	EXPECT_EQ(4, _model._components[2]->getID());
}

// ���ճs������R�O
TEST_F(PresentationModelTest, connectNodeCommand)
{
	_presentation->connectNodeCommand(0, 0, "");
	EXPECT_TRUE(_presentation->isCreationFail());
	_presentation->connectNodeCommand(0, 1, "");
	EXPECT_FALSE(_presentation->isCreationFail());
	EXPECT_EQ(6, _presentation->getComponentSize());
	EXPECT_EQ(5, _presentation->getNodeID());
	EXPECT_EQ("Connection", _presentation->getNodeType(5));
	EXPECT_EQ("", _presentation->getNodeText(5));
}

// ���ը��o����ƶq
TEST_F(PresentationModelTest, getComponentSize)
{
	EXPECT_EQ(5, _presentation->getComponentSize());
	_model.clearComponent();
	EXPECT_EQ(0, _presentation->getComponentSize());
}

// ����id�O�_�s�b
TEST_F(PresentationModelTest, isIDExsit)
{
	for (unsigned i = 0; i < (unsigned)_presentation->getComponentSize(); i++)
	{
		EXPECT_TRUE(_presentation->isIDExsit(i));
	}
	EXPECT_FALSE(_presentation->isIDExsit(-1));
	EXPECT_FALSE(_presentation->isIDExsit(5));
}

// ���լO�_�����s��
TEST_F(PresentationModelTest, hasConnection)
{
	EXPECT_FALSE(_presentation->hasConnection(0, 1));
	EXPECT_FALSE(_presentation->hasConnection(0, 2));
	loadConnection();
	EXPECT_TRUE(_presentation->hasConnection(0, 1));
	EXPECT_TRUE(_presentation->hasConnection(0, 2));
}

// ���ը��o cardinality
TEST_F(PresentationModelTest, getCardinality)
{
	EXPECT_EQ("1", _presentation->getCardinality(0));
	EXPECT_EQ("N", _presentation->getCardinality(1));
}

// ���լO�_�ݭn�߰� cardinality
TEST_F(PresentationModelTest, needAskCardinality)
{
	EXPECT_FALSE(_presentation->needAskCardinality(0, 1));
	EXPECT_FALSE(_presentation->needAskCardinality(3, 4));
	EXPECT_TRUE(_presentation->needAskCardinality(1, 2));
}

// ���ը��o�s����T
TEST_F(PresentationModelTest, getConnectionLine)
{
	loadConnection();
	EXPECT_EQ("        3  |   0  |   1  |\n        4  |   0  |   2  |\n", _presentation->getConnectionLine());
	_model.clearComponent();
	EXPECT_EQ("", _presentation->getConnectionLine());
}

// ���լO�_���Ytype
TEST_F(PresentationModelTest, isType)
{
	EXPECT_TRUE(_presentation->isType(0, entity));
	EXPECT_TRUE(_presentation->isType(1, attribute));
	EXPECT_TRUE(_presentation->isType(2, relation));
	EXPECT_TRUE(_presentation->isType(3, connection));
}

// ���լO�_�� attribute
TEST_F(PresentationModelTest, hasAttribute)
{
	EXPECT_FALSE(_presentation->hasAttribute(0));
	loadConnection();
	EXPECT_TRUE(_presentation->hasAttribute(0));
}

// ���լO�_�� entity
TEST_F(PresentationModelTest, hasEntity)
{
	EXPECT_TRUE(_presentation->hasEntity());
	_model.clearComponent();
	EXPECT_FALSE(_presentation->hasEntity());
}

// ���ը��o attribute ��T
TEST_F(PresentationModelTest, getAttributeLine)
{
	EXPECT_EQ("", _presentation->getAttributeLine(0));
	loadConnection();
	EXPECT_EQ("   A  |   1  |  Name\n", _presentation->getAttributeLine(0));
}

// ���լO�_���� attribute
TEST_F(PresentationModelTest, isAttribute)
{
	EXPECT_FALSE(_presentation->isAttribute(0, 1));
	loadConnection();
	EXPECT_TRUE(_presentation->isAttribute(0, 1));
}

// ���ը��oprimary key
TEST_F(PresentationModelTest, getPrimaryKey)
{
	EXPECT_EQ("", _presentation->getPrimaryKey(0));
	loadConnection();
	vector<int> primaryKey;
	primaryKey.push_back(1);
	_model.setPrimaryKey(primaryKey);
	EXPECT_EQ("1", _presentation->getPrimaryKey(0));
}

// ���ճ]�wprimary key
TEST_F(PresentationModelTest, setPrimaryKey)
{
	EXPECT_FALSE(((AttributeNode*)_model._components[1])->isPrimaryKey());
	setPrimaryKey(1);
	EXPECT_TRUE(((AttributeNode*)_model._components[1])->isPrimaryKey());
}

// ������ܸ�Ʈw���
TEST_F(PresentationModelTest, displayTableCommand)
{
	EXPECT_FALSE(_presentation->displayTableCommand());
	loadConnection();
	addOneToOne();
	EXPECT_TRUE(_presentation->displayTableCommand());
}

// ���ը��o������
TEST_F(PresentationModelTest, getTable)
{
	vector<pair<int, int>> oneToOne;
	EXPECT_EQ("         PC |  PK()\n", _presentation->getTable());
	loadConnection();
	addOneToOne();
	oneToOne = _model.getOneToOne();
	EXPECT_EQ("         PC |  PK(Name)\n     Person |  PK(ID), FK(Name)\n", _presentation->getTable());
}

// ����Ū���ɮ�
TEST_F(PresentationModelTest, loadFile)
{
	EXPECT_FALSE(_presentation->loadFile("test/nofile.erd"));
	_mkdir("test");
	ofstream outputFile("test/file.erd");
	outputFile << endl;
	outputFile << endl;
	outputFile << endl;
	outputFile.close();
	EXPECT_TRUE(_presentation->loadFile("test/file.erd"));
	_rmdir("test");
}

// �����x�s�ɮ�
TEST_F(PresentationModelTest, saveFile)
{
	EXPECT_FALSE(_presentation->saveFile("C:\\"));
	_mkdir("test");
	EXPECT_TRUE(_presentation->saveFile("test/file.erd"));
	remove("test/file.erd");
	_rmdir("test");
}

// ���իإ߸�Ƨ�
TEST_F(PresentationModelTest, makeDirectory)
{
	string filePath = ".\\test\\test\\file.erd";
	_presentation->makeDirectory(filePath);
	ofstream file(filePath);
	EXPECT_TRUE(file.is_open());
	file.close();
	remove("test/test/file.erd");
	_rmdir("test/test");
	_rmdir("test");
}

// ���զ^�W�@�B
TEST_F(PresentationModelTest, undo)
{
	_presentation->addNodeCommand("E", "Test");
	EXPECT_EQ(6, _presentation->getComponentSize());
	EXPECT_EQ(5, _presentation->getNodeID());
	EXPECT_EQ("Entity", _presentation->getNodeType(5));
	EXPECT_EQ("Test", _presentation->getNodeText(5));
	_presentation->undo();
	EXPECT_FALSE(_presentation->isIDExsit(5));
}

// ���լO�_�i�H�^�W�@�B
TEST_F(PresentationModelTest, canUndo)
{
	loadConnection();
	for (unsigned i = 0; i < 5; i++)
	{
		EXPECT_TRUE(_presentation->canUndo());
		_presentation->undo();
	}
	EXPECT_FALSE(_presentation->canUndo());
}

// ���ը�U�@�B
TEST_F(PresentationModelTest, redo)
{
	_presentation->addNodeCommand("E", "Test");
	EXPECT_EQ(6, _presentation->getComponentSize());
	EXPECT_EQ(5, _presentation->getNodeID());
	EXPECT_EQ("Entity", _presentation->getNodeType(5));
	EXPECT_EQ("Test", _presentation->getNodeText(5));
	_presentation->undo();
	EXPECT_FALSE(_presentation->isIDExsit(5));
	_presentation->redo();
	EXPECT_EQ(6, _presentation->getComponentSize());
	EXPECT_EQ(5, _presentation->getNodeID());
	EXPECT_EQ("Entity", _presentation->getNodeType(5));
	EXPECT_EQ("Test", _presentation->getNodeText(5));
}

// ���լO�_�i�H��U�@�B
TEST_F(PresentationModelTest, canRedo)
{
	EXPECT_FALSE(_presentation->canRedo());
	_presentation->addNodeCommand("E", "Test");
	EXPECT_EQ(6, _presentation->getComponentSize());
	EXPECT_EQ(5, _presentation->getNodeID());
	EXPECT_EQ("Entity", _presentation->getNodeType(5));
	EXPECT_EQ("Test", _presentation->getNodeText(5));
	_presentation->undo();
	EXPECT_TRUE(_presentation->canRedo());
}