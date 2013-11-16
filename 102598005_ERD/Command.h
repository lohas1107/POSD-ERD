#ifndef _COMMAND_H_
#define _COMMAND_H_
#include "ERModel.h"

class Command
{
public:
	Command();
	Command(ERModel* model);
	virtual ~Command();
	virtual void execute() = 0;
	virtual void unexecute() = 0;

protected:
	ERModel* _model;
};

#endif