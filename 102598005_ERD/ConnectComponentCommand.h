#ifndef _CONNECTCOMPONENTCOMMAND_H_
#define _CONNECTCOMPONENTCOMMAND_H_

#include "Command.h"
#include "ERModel.h"

class ConnectComponentCommand : public Command
{
public:
	ConnectComponentCommand();
	ConnectComponentCommand(ERModel* model, int firstNodeID, int secondNodeID, string cardinality);
	~ConnectComponentCommand();
	void execute();
	void unexecute();

private:
	ERModel* _model;
	int _firstID;
	int _secondID;
	string _cardinality;
};

#endif