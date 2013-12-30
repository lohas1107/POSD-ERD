#ifndef _COMMANDMANAGER_H_
#define  _COMMANDMANAGER_H_

#include "Command.h"
#include <stack>
#include "gtest/gtest_prod.h"

using namespace std;

class CommandManager
{
	friend class CommandManagerTest;
	FRIEND_TEST(CommandManagerTest, clearCommandStack);
	FRIEND_TEST(CommandManagerTest, canUndo);
	FRIEND_TEST(CommandManagerTest, canRedo);
	FRIEND_TEST(CommandManagerTest, execute);
	FRIEND_TEST(CommandManagerTest, undo);
	FRIEND_TEST(CommandManagerTest, redo);
	friend class PresentationModelTest;
	FRIEND_TEST(PresentationModelTest, canUndo);

public:
	CommandManager();
	~CommandManager();
	void clearCommandStack(stack<Command*> &stack);
	bool canUndo();
	bool canRedo();
	void execute(Command* command);
	void undo();
	void redo();
	void clearAllCommand();

private:
	stack<Command*> _undoCommands;
	stack<Command*> _redoCommands;
};

#endif