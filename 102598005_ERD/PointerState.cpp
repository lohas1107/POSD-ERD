#include "PointerState.h"

PointerState::PointerState(GraphicsScene* scene) : State(scene)
{
}

PointerState::~PointerState()
{
}

// �ǰe�ƹ��ƥ� item
void PointerState::sendEventToItem(QGraphicsSceneMouseEvent* mouseEvent)
{
	QGraphicsItem* item = _scene->itemAt(mouseEvent->scenePos());
	if (item != NULL)
	{
		_scene->sendEvent(item, mouseEvent);
	}
}

// ���U�ƹ��ƥ�
void PointerState::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
}

// ���ʷƹ��ƥ�
void PointerState::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
}

// ��}�ƹ��ƥ�
void PointerState::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
}
