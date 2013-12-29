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
void PointerState::mousePressEvent(QPointF mousePosition)
{
	_moveFrom = mousePosition;
	getItemID(mousePosition);
}

// ���ʷƹ��ƥ�
void PointerState::mouseMoveEvent(QPointF mousePosition)
{
	if (_presentationModel->isIDExsit(_pointID))
	{
		_presentationModel->setNodePosition(_pointID, mousePosition);
	}
	_scene->draw();
}

// ��}�ƹ��ƥ�
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
