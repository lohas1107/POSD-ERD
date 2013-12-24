#include "DeleteMultipleCommand.h"

DeleteMultipleCommand::DeleteMultipleCommand(ERModel* model, vector<Command*> commandList) : Command(model)
{
	_commandList = commandList;
}

DeleteMultipleCommand::~DeleteMultipleCommand()
{
	while(!_commandList.empty())
	{
		Command* command = _commandList.back();
		_commandList.pop_back();
		delete command;
	}
}

void DeleteMultipleCommand::execute()
{
	for (unsigned i = 0; i < _commandList.size(); i++)
	{
		_commandList[i]->execute();
	}
}

void DeleteMultipleCommand::unexecute()
{
	for (unsigned i = _commandList.size(); i > 0; i--)
	{
		_commandList[i-1]->unexecute();
	}
	_model->revertConnector();
}
