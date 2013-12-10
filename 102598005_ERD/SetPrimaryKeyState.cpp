#include "SetPrimaryKeyState.h"

SetPrimaryKeyState::SetPrimaryKeyState(GraphicsScene* scene) : State(scene)
{
}

SetPrimaryKeyState::~SetPrimaryKeyState()
{
}

// 按下滑鼠事件
void SetPrimaryKeyState::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	getItemID(mouseEvent->scenePos());
}

// 移動滑鼠事件
void SetPrimaryKeyState::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
}

// 放開滑鼠事件
void SetPrimaryKeyState::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (_presentationModel->isIDExsit(_pointID) && _presentationModel->canSetPrimaryKey(_pointID))
	{
		_presentationModel->setNodePrimaryKey(_pointID);
		_presentationModel->notify();
	}
	initialize();
}
