#include "PointerState.h"

PointerState::PointerState(GraphicsScene* scene) : State(scene)
{
}

PointerState::~PointerState()
{
}

// 傳送滑鼠事件給 item
void PointerState::sendEventToItem(QGraphicsSceneMouseEvent* mouseEvent)
{
	QGraphicsItem* item = _scene->itemAt(mouseEvent->scenePos());
	if (item != NULL)
	{
		_scene->sendEvent(item, mouseEvent);
	}
}

// 按下滑鼠事件
void PointerState::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
}

// 移動滑鼠事件
void PointerState::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
}

// 放開滑鼠事件
void PointerState::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
}
