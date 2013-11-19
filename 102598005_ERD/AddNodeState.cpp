#include "AddNodeState.h"
#include "PointerState.h"
#include <QtGui/QDialog>
#include <QInputDialog>
#include "../src/corelib/io/qdebug.h"
#include "GraphicsManager.h"
#include "GraphicsItem.h"

AddNodeState::AddNodeState(GraphicsManager* scene, pair<Type, string> type) : State(scene)
{
	_type = type;
	_item = _scene->createGraphicsItem(_type.first);
	_scene->addItem(_item);
}

AddNodeState::~AddNodeState()
{
	delete _item;
}

void AddNodeState::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	_scene->removeItem(_item);
}

void AddNodeState::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	_item->setPos(mouseEvent->scenePos());
}

void AddNodeState::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	QString text = QInputDialog::getText(NULL, "Enter text", "Please enter the text", QLineEdit::Normal, "", &_isOK);

	if (_isOK && !text.isEmpty())
	{
		_presentationModel->addNodeCommand(_type.second, text.toStdString());
		_presentationModel->setNodePosition(_presentationModel->getNodeID(), mouseEvent->scenePos());
		_scene->draw();
		_scene->updateChecked();
	}

	_scene->changeState(new PointerState(_scene));
}
