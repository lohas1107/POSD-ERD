#ifndef _DELETECOMPONENTCOMMAND_H_
#define _DELETECOMPONENTCOMMAND_H_

#include "Command.h"
#include "ERModel.h"
#include "ERComponent.h"

class DeleteComponentCommand : public Command
{
public:
	DeleteComponentCommand(ERModel* model, int id);
	~DeleteComponentCommand();
	void execute();
	void unexecute();

private:
	ERModel* _model;
	int _id;
	vector<pair<int, ERComponent*>> _deleteList;
};

#endif