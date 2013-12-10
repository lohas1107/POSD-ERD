#include "PointerState.h"

PointerState::PointerState(GraphicsScene* scene) : State(scene)
{
	_presentationModel->setPointerButtonChecked(true);
	_presentationModel->clearSelected();
	_presentationModel->notifyButtonEnabled();
}

PointerState::~PointerState()
{
}

// ���U�ƹ��ƥ�
void PointerState::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	getItemID(mouseEvent->scenePos());
}

// ���ʷƹ��ƥ�
void PointerState::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (_presentationModel->isIDExsit(_pointID))
	{
		_presentationModel->setNodePosition(_pointID, mouseEvent->scenePos());
	}
	_scene->draw();
}

// ��}�ƹ��ƥ�
void PointerState::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	initialize();
}
