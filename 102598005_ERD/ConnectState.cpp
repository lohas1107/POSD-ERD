#include "ConnectState.h"
#include "GraphicsConnector.h"
#include <QInputDialog>

const string CARDINALITY_ONE = "1";
const string CARDINALITY_N = "N";
const string TITLE = "Enter cardinality";
const string LABEL = "Please select the cardinality";
const string STRING_EMPTY = "";

ConnectState::ConnectState(GraphicsScene* scene) : State(scene)
{
	_firstID = INT_MIN;
	_secondID = INT_MIN;
	_line = NULL;
}

ConnectState::~ConnectState()
{
	delete _line;
}

// ���U�ƹ��ƥ�
void ConnectState::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	QPointF position = mouseEvent->scenePos();
	_line = _scene->createGraphicsItem(connection);
	_scene->addItem(_line);
	_linePosition = QLineF(position.x(), position.y(), position.x(), position.y());
	((GraphicsConnector*)_line)->setLine(_linePosition);
	_scene->update(0, 0, _scene->width(), _scene->height());

	_firstID = getItemID(position);
}

// ���ʷƹ��ƥ�
void ConnectState::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	_linePosition.setP2(mouseEvent->scenePos());
	((GraphicsConnector*)_line)->setLine(_linePosition);
	_scene->update(0, 0, _scene->width(), _scene->height());
}

// ��}�ƹ��ƥ�
void ConnectState::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	_scene->removeItem(_line);
	_secondID = getItemID(mouseEvent->scenePos());
	initialize();
	if (isValidConnection(_firstID, _secondID))
	{
		string cardinality = getCardinality(_firstID, _secondID);
		_presentationModel->connectNodeCommand(_firstID, _secondID, cardinality);
		_presentationModel->notify();
	}
}

// �O�_���X�k���s��
bool ConnectState::isValidConnection(int firstID, int secondID)
{
	return _presentationModel->isIDExsit(firstID) && _presentationModel->isIDExsit(secondID) && 
		firstID != secondID && !_presentationModel->hasConnection(firstID, secondID);
}

// ���o cardinality
string ConnectState::getCardinality(int firstID, int secondID)
{
	if (_presentationModel->needAskCardinality(firstID, secondID))
	{
		QStringList choice;
		choice << CARDINALITY_ONE.c_str() << CARDINALITY_N.c_str();
		QString item = QInputDialog::getItem(NULL, TITLE.c_str(), LABEL.c_str(), choice, 0, false, &_isOK);
		return item.toStdString();
	}
	return STRING_EMPTY;
}
