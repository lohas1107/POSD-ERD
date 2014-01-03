#include "gtest/gtest.h"
#include "MoveCommand.h"

class MoveCommandTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		_model = new ERModel();
		_model->_components.push_back(new EntityNode(0, "PC"));
		_command = new MoveCommand(_model, 0, QPointF(0, 0), QPointF(100, 100));
	}

	virtual void TearDown()
	{
		delete _model;
		delete _command;
	}

	ERModel* _model;
	MoveCommand* _command;
};

// 測試執行複製
TEST_F(MoveCommandTest, execute)
{
	EXPECT_EQ(QPointF(0, 0), _model->getComponent(0)->getPosition());
	_command->execute();
	EXPECT_EQ(QPointF(100, 100), _model->getComponent(0)->getPosition());
}

// 測試取消複製
TEST_F(MoveCommandTest, unexecute)
{
	EXPECT_EQ(QPointF(0, 0), _model->getComponent(0)->getPosition());
	_command->execute();
	EXPECT_EQ(QPointF(100, 100), _model->getComponent(0)->getPosition());
	_command->unexecute();
	EXPECT_EQ(QPointF(0, 0), _model->getComponent(0)->getPosition());
}