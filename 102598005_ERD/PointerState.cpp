#include "PointerState.h"

PointerState::PointerState(GraphicsScene* scene) : State(scene)
{
	_presentationModel->setPointerButtonChecked(true);
	_presentationModel->clearSelected();
	_presentationModel->notifyButtonEnabled();
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
	getItemID(mouseEvent->scenePos());
}

// 移動滑鼠事件
void PointerState::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (_presentationModel->isIDExsit(_pointID))
	{
		_presentationModel->setNodePosition(_pointID, mouseEvent->scenePos());
	}
	_scene->draw();
}

// 放開滑鼠事件
void PointerState::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	initialize();
}
