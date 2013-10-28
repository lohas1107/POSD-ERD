#include "CommandManager.h"

CommandManager::CommandManager() 
{
}

CommandManager::~CommandManager() 
{
	clearCommandStack(_undoCommands);
	clearCommandStack(_redoCommands);
}

// 清除命令堆疊
void CommandManager::clearCommandStack(stack<Command*> &stack)
{
	while (!stack.empty())
	{
		Command* command = stack.top();
		stack.pop();
		delete command;
	}
}

// 是否可以 undo
bool CommandManager::canUndo()
{
	if (_undoCommands.size() == 0)
	{
		return false;
	}
	return true;
}

// 是否可以 redo
bool CommandManager::canRedo()
{
	if (_redoCommands.size() == 0)
	{
		return false;
	}
	return true;
}

// 執行命令
void CommandManager::execute(Command* command)
{
	command->execute();
	_undoCommands.push(command);
	clearCommandStack(_redoCommands);
}

// 回上一步
void CommandManager::undo()
{
	Command* command = _undoCommands.top();
	_undoCommands.pop();
	command->unexecute();
	_redoCommands.push(command);
}

// 到下一步
void CommandManager::redo()
{
	Command* command = _redoCommands.top();
	_redoCommands.pop();
	command->execute();
	_undoCommands.push(command);
}
