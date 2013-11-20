#include "PointerState.h"

PointerState::PointerState(GraphicsScene* scene) : State(scene)
{
	_item = NULL;
}

PointerState::~PointerState()
{
	delete _item;
}

// ���U�ƹ��ƥ�
void PointerState::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	_item = _scene->itemAt(mouseEvent->scenePos());

	if (_item != NULL)
	{
		_id = _item->data(idData).toInt();
	}
}

// ���ʷƹ��ƥ�
void PointerState::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (_presentationModel->isIDExsit(_id))
	{
		_presentationModel->setNodePosition(_id, mouseEvent->scenePos());
	}
	_scene->draw();
}

// ��}�ƹ��ƥ�
void PointerState::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	_item = NULL;
}
