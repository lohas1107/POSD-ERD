#ifndef _SETPRIMARYKEYCOMMAND_H_
#define _SETPRIMARYKEYCOMMAND_H_

#include "command.h"

class SetPrimaryKeyCommand : public Command
{
public:
	SetPrimaryKeyCommand(ERModel* model, int id);
	~SetPrimaryKeyCommand();
	void execute();
	void unexecute();

private:
	int _id;
	bool _isPrimaryKey;
};

#endif