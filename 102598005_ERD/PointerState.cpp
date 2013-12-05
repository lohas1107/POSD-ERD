#include "PointerState.h"

PointerState::PointerState(GraphicsScene* scene) : State(scene)
{
	//_item = NULL;
}

PointerState::~PointerState()
{
	//delete _item;
}

// ���U�ƹ��ƥ�
void PointerState::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	//_item = _scene->itemAt(mouseEvent->scenePos());

	//if (_item != NULL)
	//{
	//	_id = _item->data(idData).toInt();
	//}
	getItemId(mouseEvent->scenePos());
}

// ���ʷƹ��ƥ�
void PointerState::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (_presentationModel->isIDExsit(_pointId))
	{
		_presentationModel->setNodePosition(_pointId, mouseEvent->scenePos());
	}
	_scene->draw();
}

// ��}�ƹ��ƥ�
void PointerState::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	initialize();
}
