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

// ���沾�ʤ���
void MoveCommand::execute()
{
	_model->setNodePosition(_id, _moveTo);
	_model->clearSelected();
}

// �ϦV���沾�ʤ���
void MoveCommand::unexecute()
{
	_model->setNodePosition(_id, _moveFrom);
}
