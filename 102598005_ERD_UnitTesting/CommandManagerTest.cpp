#include "gtest/gtest.h"
#include "CommandManager.h"
#include "AddComponentCommand.h"

class CommandManagerTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		_model = new ERModel();
	}

	virtual void TearDown()
	{
		delete _model;
	}

	void addCommand()
	{
		_manager._redoCommands.push(new AddComponentCommand(_model, make_pair(entity, ""), "PC", QPointF(0, 0)));
		_manager._undoCommands.push(new AddComponentCommand(_model, make_pair(entity, ""), "PC", QPointF(0, 0)));
	}
	CommandManager _manager;
	ERModel* _model;
};

// 測試清除命令
TEST_F(CommandManagerTest, clearCommandStack)
{
	addCommand();
	_manager.clearCommandStack(_manager._undoCommands);
	_manager.clearCommandStack(_manager._redoCommands);
	EXPECT_EQ(0, _manager._undoCommands.size());
	EXPECT_EQ(0, _manager._redoCommands.size());
}

// 測試是否可以回上一步
TEST_F(CommandManagerTest, canUndo)
{
	EXPECT_FALSE(_manager.canUndo());
	addCommand();
	EXPECT_TRUE(_manager.canUndo());
}

// 測試是否可以到下一步
TEST_F(CommandManagerTest, canRedo)
{
	EXPECT_FALSE(_manager.canRedo());
	addCommand();
	EXPECT_TRUE(_manager.canRedo());
}

// 測試執行命令
TEST_F(CommandManagerTest, execute)
{
	_manager.execute(new AddComponentCommand(_model, make_pair(entity, ""), "PC", QPointF(0, 0)));
	EXPECT_EQ(1, _model->getComponentSize());
	EXPECT_EQ(1, _manager._undoCommands.size());
	EXPECT_EQ(0, _manager._redoCommands.size());
}

// 測試回上一步
TEST_F(CommandManagerTest, undo)
{
	addCommand();
	_model->addComponent(make_pair(entity, ""), "PC", QPointF(0, 0));
	_manager.undo();
	EXPECT_EQ(0, _model->getComponentSize());
	EXPECT_EQ(0, _manager._undoCommands.size());
	EXPECT_EQ(2, _manager._redoCommands.size());
}

// 測試到下一步
TEST_F(CommandManagerTest, redo)
{
	addCommand();
	_manager.redo();
	EXPECT_EQ(1, _model->getComponentSize());
	EXPECT_EQ(2, _manager._undoCommands.size());
	EXPECT_EQ(0, _manager._redoCommands.size());
}