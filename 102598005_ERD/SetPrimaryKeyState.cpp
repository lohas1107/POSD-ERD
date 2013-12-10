#include "SetPrimaryKeyState.h"

SetPrimaryKeyState::SetPrimaryKeyState(GraphicsScene* scene) : State(scene)
{
}

SetPrimaryKeyState::~SetPrimaryKeyState()
{
}

// ���U�ƹ��ƥ�
void SetPrimaryKeyState::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	getItemID(mouseEvent->scenePos());
}

// ���ʷƹ��ƥ�
void SetPrimaryKeyState::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
}

// ��}�ƹ��ƥ�
void SetPrimaryKeyState::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (_presentationModel->isIDExsit(_pointID) && _presentationModel->canSetPrimaryKey(_pointID))
	{
		_presentationModel->setNodePrimaryKey(_pointID);
		_presentationModel->notify();
	}
	initialize();
}
