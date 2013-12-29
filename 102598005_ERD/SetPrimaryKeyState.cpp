#include "SetPrimaryKeyState.h"

SetPrimaryKeyState::SetPrimaryKeyState(GraphicsScene* scene) : State(scene)
{
}

SetPrimaryKeyState::~SetPrimaryKeyState()
{
}

// ���U�ƹ��ƥ�
void SetPrimaryKeyState::mousePressEvent(QPointF mousePosition)
{
	getItemID(mousePosition);
}

// ���ʷƹ��ƥ�
void SetPrimaryKeyState::mouseMoveEvent(QPointF mousePosition)
{
}

// ��}�ƹ��ƥ�
void SetPrimaryKeyState::mouseReleaseEvent(QPointF mousePosition)
{
	if (_presentationModel->isIDExsit(_pointID) && _presentationModel->canSetPrimaryKey(_pointID))
	{
		_presentationModel->setNodePrimaryKey(_pointID);
		_presentationModel->notify();
	}
	initialize();
}
