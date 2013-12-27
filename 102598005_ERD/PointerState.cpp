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

// 按下滑鼠事件
void PointerState::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	_moveFrom = mouseEvent->scenePos();
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
	QPointF moveTo = mouseEvent->scenePos();

	if (_presentationModel->isIDExsit(_pointID) && _moveFrom != moveTo)
	{
		_presentationModel->moveCommand(_pointID, _moveFrom, moveTo);
		_presentationModel->notify();
	}

	initialize();
}
