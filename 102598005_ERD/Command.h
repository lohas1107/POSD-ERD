#ifndef _COMMAND_H_
#define _COMMAND_H_

class Command
{
public:
	Command();
	virtual ~Command();
	virtual void execute() = 0;
	virtual void unexecute() = 0;
};

#endif