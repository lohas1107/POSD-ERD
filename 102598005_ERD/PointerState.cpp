#include "PointerState.h"
#include <iostream>
#include "..\src\corelib\io\qdebug.h"

PointerState::PointerState(GraphicsManager* scene) : State(scene)
{
}

PointerState::~PointerState()
{
}

void PointerState::sendEventToItem(QGraphicsSceneMouseEvent* mouseEvent)
{
	QGraphicsItem* item = _scene->itemAt(mouseEvent->scenePos());
	if (item != NULL)
	{
		_scene->sendEvent(item, mouseEvent);
	}
}

void PointerState::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	//sendEventToItem(mouseEvent);


}

void PointerState::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	//sendEventToItem(mouseEvent);

}

void PointerState::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	//sendEventToItem(mouseEvent);

}
