#include "SetPrimaryKeyState.h"

SetPrimaryKeyState::SetPrimaryKeyState(GraphicsScene* scene) : State(scene)
{
}

SetPrimaryKeyState::~SetPrimaryKeyState()
{
}

void SetPrimaryKeyState::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	_item = _scene->itemAt(mouseEvent->scenePos());

	if (_item != NULL)
	{
		_id = _item->data(idData).toInt();
	}
}

void SetPrimaryKeyState::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
}

void SetPrimaryKeyState::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (_presentationModel->isIDExsit(_id) && _presentationModel->canSetPrimaryKey(_id))
	{
		ERComponent* component = _presentationModel->getComponents()[_id];
		bool isPrimaryKey = ((AttributeNode*)component)->isPrimaryKey();
		((AttributeNode*)component)->setPrimaryKey(!isPrimaryKey);
		_presentationModel->notify();
	}
	_item = NULL;
	_id = INT_MIN;
}
