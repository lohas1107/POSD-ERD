#ifndef _MOVECOMMAND_H_
#define _MOVECOMMAND_H_

#include "command.h"

class MoveCommand : public Command
{
public:
	MoveCommand(ERModel* model, int id, QPointF moveFrom, QPointF moveTo);
	~MoveCommand();
	void execute();
	void unexecute();

private:
	int _id;
	QPointF _moveFrom;
	QPointF _moveTo;
};

#endif