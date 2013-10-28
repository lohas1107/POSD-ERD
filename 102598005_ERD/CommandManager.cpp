#include "CommandManager.h"

CommandManager::CommandManager() 
{
}

CommandManager::~CommandManager() 
{
	clearCommandStack(_undoCommands);
	clearCommandStack(_redoCommands);
}

// �M���R�O���|
void CommandManager::clearCommandStack(stack<Command*> &stack)
{
	while (!stack.empty())
	{
		Command* command = stack.top();
		stack.pop();
		delete command;
	}
}

// �O�_�i�H undo
bool CommandManager::canUndo()
{
	if (_undoCommands.size() == 0)
	{
		return false;
	}
	return true;
}

// �O�_�i�H redo
bool CommandManager::canRedo()
{
	if (_redoCommands.size() == 0)
	{
		return false;
	}
	return true;
}

// ����R�O
void CommandManager::execute(Command* command)
{
	command->execute();
	_undoCommands.push(command);
	clearCommandStack(_redoCommands);
}

// �^�W�@�B
void CommandManager::undo()
{
	Command* command = _undoCommands.top();
	_undoCommands.pop();
	command->unexecute();
	_redoCommands.push(command);
}

// ��U�@�B
void CommandManager::redo()
{
	Command* command = _redoCommands.top();
	_redoCommands.pop();
	command->execute();
	_undoCommands.push(command);
}
