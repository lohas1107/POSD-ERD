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

// 執行移動元件
void MoveCommand::execute()
{
	_model->setNodePosition(_id, _moveTo);
	_model->clearSelected();
}

// 反向執行移動元件
void MoveCommand::unexecute()
{
	_model->setNodePosition(_id, _moveFrom);
}
