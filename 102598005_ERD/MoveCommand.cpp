#include "MoveCommand.h"

MoveCommand::MoveCommand(ERModel* model, int id, QPointF moveFrom, QPointF moveTo) : Command(model)
{
	_id = id;
	_moveFrom = moveFrom;
	_moveTo = moveTo;
}

MoveCommand::~MoveCommand()
{
}

void MoveCommand::execute()
{
	_model->setNodePosition(_id, _moveTo);
}

void MoveCommand::unexecute()
{
	_model->setNodePosition(_id, _moveFrom);
}
