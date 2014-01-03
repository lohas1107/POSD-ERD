#include "gtest/gtest.h"
#include "PasteCommand.h"

class PasteCommandTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		_model = new ERModel();
		_model->_clipboard.push_back(new EntityNode(0, "PC"));
		_model->_clipboard.push_back(new AttributeNode(1, "Name"));
		_model->_clipboard.push_back(new RelationNode(2, "Has"));

		_command = new PasteCommand(_model);
	}

	virtual void TearDown()
	{
		delete _model;
		delete _command;
	}

	ERModel* _model;
	PasteCommand* _command;
};

// 測試執行複製
TEST_F(PasteCommandTest, execute)
{
	EXPECT_EQ(0, _model->getComponentSize());
	_command->execute();
	EXPECT_EQ(3, _model->getComponentSize());
	EXPECT_EQ(entity, _model->getComponent(0)->getType().first);
	EXPECT_EQ("PC", _model->getComponent(0)->getText());
	EXPECT_EQ(attribute, _model->getComponent(1)->getType().first);
	EXPECT_EQ("Name", _model->getComponent(1)->getText());
	EXPECT_EQ(relation, _model->getComponent(2)->getType().first);
	EXPECT_EQ("Has", _model->getComponent(2)->getText());
}

// 測試取消複製
TEST_F(PasteCommandTest, unexecute)
{
	EXPECT_EQ(0, _model->getComponentSize());
	_command->execute();
	EXPECT_EQ(3, _model->getComponentSize());
	EXPECT_EQ(entity, _model->getComponent(0)->getType().first);
	EXPECT_EQ("PC", _model->getComponent(0)->getText());
	EXPECT_EQ(attribute, _model->getComponent(1)->getType().first);
	EXPECT_EQ("Name", _model->getComponent(1)->getText());
	EXPECT_EQ(relation, _model->getComponent(2)->getType().first);
	EXPECT_EQ("Has", _model->getComponent(2)->getText());
	_command->unexecute();
	EXPECT_EQ(0, _model->getComponentSize());
}