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
	getItemID(mouseEvent->scenePos());
}

void SetPrimaryKeyState::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
}

void SetPrimaryKeyState::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (_presentationModel->isIDExsit(_pointID) && _presentationModel->canSetPrimaryKey(_pointID))
	{
		//ERComponent* component = _presentationModel->getComponents()[_pointId];
		//bool isPrimaryKey = ((AttributeNode*)component)->isPrimaryKey();
		//((AttributeNode*)component)->setPrimaryKey(!isPrimaryKey);
		_presentationModel->setNodePrimaryKey(_pointID);
		_presentationModel->notify();
	}
	initialize();
}
