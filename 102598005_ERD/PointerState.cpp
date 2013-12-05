#include "PointerState.h"

PointerState::PointerState(GraphicsScene* scene) : State(scene)
{
	//_item = NULL;
}

PointerState::~PointerState()
{
	//delete _item;
}

// 按下滑鼠事件
void PointerState::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	//_item = _scene->itemAt(mouseEvent->scenePos());

	//if (_item != NULL)
	//{
	//	_id = _item->data(idData).toInt();
	//}
	getItemId(mouseEvent->scenePos());
}

// 移動滑鼠事件
void PointerState::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (_presentationModel->isIDExsit(_pointId))
	{
		_presentationModel->setNodePosition(_pointId, mouseEvent->scenePos());
	}
	_scene->draw();
}

// 放開滑鼠事件
void PointerState::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	initialize();
}
