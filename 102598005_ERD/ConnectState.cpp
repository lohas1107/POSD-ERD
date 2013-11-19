#include "ConnectState.h"
#include "GraphicsConnector.h"
#include "..\src\gui\dialogs\qinputdialog.h"

ConnectState::ConnectState(GraphicsManager* scene) : State(scene)
{
	_firstID = INT_MIN;
	_secondID = INT_MIN;
}

ConnectState::~ConnectState()
{
	delete _line;
}

void ConnectState::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	QPointF position = mouseEvent->scenePos();
	_line = _scene->createGraphicsItem(connection);
	_scene->addItem(_line);
	_linePosition = QLineF(position.x(), position.y(), position.x(), position.y());
	((GraphicsConnector*)_line)->setLine(_linePosition);
	_scene->update(0, 0, _scene->width(), _scene->height());


	_firstID = getItemId(position);
}

void ConnectState::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	_linePosition.setP2(mouseEvent->scenePos());
	((GraphicsConnector*)_line)->setLine(_linePosition);
	_scene->update(0, 0, _scene->width(), _scene->height());
}

void ConnectState::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	_scene->removeItem(_line);
	_secondID = getItemId(mouseEvent->scenePos());
	if (isValidConnection(_firstID, _secondID))
	{
		string cardinality = getCardinality(_firstID, _secondID);
		_presentationModel->connectNodeCommand(_firstID, _secondID, cardinality);
		_scene->draw();
	}
}

int ConnectState::getItemId(QPointF position)
{
	QGraphicsItem* item = _scene->itemAt(position);

	if (item != NULL)
	{
		return item->data(0).toInt();
	}

	return INT_MIN;
}

bool ConnectState::isValidConnection(int firstID, int secondID)
{
	return _presentationModel->isIDExsit(firstID) && _presentationModel->isIDExsit(secondID) && 
		firstID != secondID && !_presentationModel->hasConnection(firstID, secondID);
}

string ConnectState::getCardinality(int firstID, int secondID)
{
	if (_presentationModel->needAskCardinality(firstID, secondID))
	{
		QStringList choice;
		choice << "1" << "N";
		QString item = QInputDialog::getItem(NULL, "Enter cardinality", "Please select the cardinality", choice, 0, false, &_isOK);
		if (_isOK)
		{
			return item.toStdString();
		}
		else
		{
			return "1";
		}
	}

	return "";
}
