#include "SetPrimaryKeyState.h"

SetPrimaryKeyState::SetPrimaryKeyState(GraphicsScene* scene) : State(scene)
{
}

SetPrimaryKeyState::~SetPrimaryKeyState()
{
}

void SetPrimaryKeyState::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	//_item = _scene->itemAt(mouseEvent->scenePos());

	//if (_item != NULL)
	//{
	//	_id = _item->data(idData).toInt();
	//}
	getItemId(mouseEvent->scenePos());
}

void SetPrimaryKeyState::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
}

void SetPrimaryKeyState::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (_presentationModel->isIDExsit(_pointId) && _presentationModel->canSetPrimaryKey(_pointId))
	{
		ERComponent* component = _presentationModel->getComponents()[_pointId];
		bool isPrimaryKey = ((AttributeNode*)component)->isPrimaryKey();
		((AttributeNode*)component)->setPrimaryKey(!isPrimaryKey);
		_presentationModel->notify();
	}
	initialize();
}
