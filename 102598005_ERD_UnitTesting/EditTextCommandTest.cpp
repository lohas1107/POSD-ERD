#include "gtest/gtest.h"
#include "EditTextCommand.h"

class EditTextCommandTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		_model = new ERModel();
		_model->_components.push_back(new EntityNode(0, "Before"));
		_command = new EditTextCommand(_model, 0, "Before", "After");
	}

	virtual void TearDown()
	{
		delete _model;
		delete _command;
	}

	ERModel* _model;
	EditTextCommand* _command;
};

// 測試執行編輯文字
TEST_F(EditTextCommandTest, execute)
{
	EXPECT_EQ("Before", _model->getComponent(0)->getText());
	_command->execute();
	EXPECT_EQ("After", _model->getComponent(0)->getText());
}

// 測試取消編輯文字
TEST_F(EditTextCommandTest, unexecute)
{
	EXPECT_EQ("Before", _model->getComponent(0)->getText());
	_command->execute();
	EXPECT_EQ("After", _model->getComponent(0)->getText());
	_command->unexecute();
	EXPECT_EQ("Before", _model->getComponent(0)->getText());
}