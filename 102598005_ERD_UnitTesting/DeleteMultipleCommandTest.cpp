#include "gtest/gtest.h"
#include "DeleteMultipleCommand.h"
#include "DeleteComponentCommand.h"

class DeleteMultipleCommandTest : public ::testing::Test
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
		vector<Command*> commandList;
		commandList.push_back(new DeleteComponentCommand(_model, 0));
		commandList.push_back(new DeleteComponentCommand(_model, 3));
		commandList.push_back(new DeleteComponentCommand(_model, 4));
		_command = new DeleteMultipleCommand(_model, commandList);
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
	DeleteMultipleCommand* _command;
};

// 測試執行多重刪除
TEST_F(DeleteMultipleCommandTest, execute)
{
	EXPECT_EQ(5, _model->getComponentSize());
	_command->execute();
	EXPECT_EQ(2, _model->getComponentSize());
	EXPECT_FALSE(_model->isIDExsit(0));
	EXPECT_FALSE(_model->isIDExsit(3));
	EXPECT_FALSE(_model->isIDExsit(4));
}

// 測試取消多重刪除
TEST_F(DeleteMultipleCommandTest, unexecute)
{
	EXPECT_EQ(5, _model->getComponentSize());
	_command->execute();
	EXPECT_EQ(2, _model->getComponentSize());
	EXPECT_FALSE(_model->isIDExsit(0));
	EXPECT_FALSE(_model->isIDExsit(3));
	EXPECT_FALSE(_model->isIDExsit(4));
	_command->unexecute();
	EXPECT_EQ(5, _model->getComponentSize());
	EXPECT_TRUE(_model->isIDExsit(0));
	EXPECT_TRUE(_model->isIDExsit(3));
	EXPECT_TRUE(_model->isIDExsit(4));
}