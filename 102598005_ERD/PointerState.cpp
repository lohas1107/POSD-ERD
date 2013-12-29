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
void PointerState::mousePressEvent(QPointF mousePosition)
{
	_moveFrom = mousePosition;
	getItemID(mousePosition);
}

// 移動滑鼠事件
void PointerState::mouseMoveEvent(QPointF mousePosition)
{
	if (_presentationModel->isIDExsit(_pointID))
	{
		_presentationModel->setNodePosition(_pointID, mousePosition);
	}
	_scene->draw();
}

// 放開滑鼠事件
void PointerState::mouseReleaseEvent(QPointF mousePosition)
{
	QPointF moveTo = mousePosition;

	if (_presentationModel->isIDExsit(_pointID) && _moveFrom != moveTo)
	{
		_presentationModel->moveCommand(_pointID, _moveFrom, moveTo);
		_presentationModel->notify();
	}

	initialize();
}
