#include "gtest/gtest.h"
#include "SetPrimaryKeyCommand.h"

class SetPrimaryKeyCommandTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		_model = new ERModel();
		_model->_components.push_back(new EntityNode(0, "PC"));
		_model->_components.push_back(new AttributeNode(1, "Name"));
		_model->_components.push_back(new RelationNode(2, "Has"));
		_model->_components.push_back(new Connector(3, ""));
		_model->_components.push_back(new Connector(4, "1"));
		loadConnection();
		_command = new SetPrimaryKeyCommand(_model, 1);
	}

	virtual void TearDown()
	{
		delete _model;
		delete _command;
	}

	// 讀取連結資料
	void loadConnection()
	{
		vector<string> content;
		content.push_back("3 0,1");
		content.push_back("4 0,2");
		_model->loadConnection(content);
	}

	ERModel* _model;
	SetPrimaryKeyCommand* _command;
};

// 測試執行設定primary key
TEST_F(SetPrimaryKeyCommandTest, execute)
{
	EXPECT_FALSE(((AttributeNode*)_model->getComponent(1))->isPrimaryKey());
	_command->execute();
	EXPECT_TRUE(((AttributeNode*)_model->getComponent(1))->isPrimaryKey());
	SetPrimaryKeyCommand* commandDelete = _command;
	_command = new SetPrimaryKeyCommand(_model, 1);
	delete commandDelete;
	_command->execute();
	EXPECT_FALSE(((AttributeNode*)_model->getComponent(1))->isPrimaryKey());
}

// 測試取消設定primary key
TEST_F(SetPrimaryKeyCommandTest, unexecute)
{
	EXPECT_FALSE(((AttributeNode*)_model->getComponent(1))->isPrimaryKey());
	_command->execute();
	EXPECT_TRUE(((AttributeNode*)_model->getComponent(1))->isPrimaryKey());
	_command->unexecute();
	EXPECT_FALSE(((AttributeNode*)_model->getComponent(1))->isPrimaryKey());
}