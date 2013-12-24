#ifndef _DELETEMULTIPLECOMMAND_H_
#define _DELETEMULTIPLECOMMAND_H_

#include "command.h"

class DeleteMultipleCommand : public Command
{
public:
	DeleteMultipleCommand(ERModel* model, vector<Command*> commandList);
	~DeleteMultipleCommand();
	void execute();
	void unexecute();

private:
	vector<Command*> _commandList;
};

#endif