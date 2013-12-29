#include "GraphicsScene.h"
#include "GraphicsEntity.h"
#include "GraphicsAttribute.h"
#include "GraphicsRelation.h"
#include "GraphicsConnector.h"
#include "GraphicsItem.h"
#include "AttributeNode.h"
#include "State.h"
#include "PointerState.h"
#include "AddNodeState.h"
#include "ConnectState.h"
#include "SetPrimaryKeyState.h"
#include <QMessageBox>
#include <QGraphicsSceneMouseEvent>

const string INPUT_E = "E";
const string INPUT_A = "A";
const string INPUT_R = "R";

GraphicsScene::GraphicsScene(PresentationModel* presentationModel)
{
	_presentationModel = presentationModel;
	_currentState = new PointerState(this);
}

GraphicsScene::~GraphicsScene()
{
	delete _currentState;
}

// ���͹ϧ�
GraphicsItem* GraphicsScene::createGraphicsItem(Type type)
{
	if (type == entity)
	{
		return new GraphicsEntity(_presentationModel);
	}
	else if (type == attribute)
	{
		return new GraphicsAttribute(_presentationModel);
	}
	else if (type == relation)
	{
		return new GraphicsRelation(_presentationModel);
	}
	else if (type == connection)
	{
		return new GraphicsConnector(_presentationModel);
	}

	return NULL;
}

// �e��
void GraphicsScene::draw()
{
	vector<ERComponent*> components = _presentationModel->getComponents();

	clear();
	for (unsigned i = 0; i < components.size(); i++)
	{
		GraphicsItem* item = createGraphicsItem(components[i]->getType().first);
		item->setData(idData, components[i]->getID());
		item->setData(textData, QString::fromStdString(components[i]->getText()));
		item->setPos(QPointF(components[i]->getPosition().x(), components[i]->getPosition().y()));
		if (components[i]->getType().first == attribute)
		{
			((GraphicsAttribute*)item)->setPrimaryKey(((AttributeNode*)components[i])->isPrimaryKey());
		}
		else if (components[i]->getType().first == connection && components[i]->getConnection().size() > 1)
		{
			vector<ERComponent*> connections = components[i]->getConnection();
			QLineF line(connections[0]->getPosition().x(), connections[0]->getPosition().y(), connections[1]->getPosition().x(), connections[1]->getPosition().y());
			((GraphicsConnector*)item)->setLine(line);
			item->setZValue(-1);
		}
		addItem(item);
	}
	update(0, 0, width(), height());
}

// ���o PresentationModel
PresentationModel* GraphicsScene::getPresentationModel()
{
	return _presentationModel;
}

// �ƹ����U�ƥ�
void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (mouseEvent->button() != Qt::LeftButton)
	{
		return;
	}
	_currentState->mousePressEvent(mouseEvent->scenePos());
	QGraphicsScene::mousePressEvent(mouseEvent);
}

// ���ʷƹ��ƥ�
void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	_currentState->mouseMoveEvent(mouseEvent->scenePos());
	QGraphicsScene::mouseMoveEvent(mouseEvent);
}

// ��}�ƹ��ƥ�
void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (mouseEvent->button() != Qt::LeftButton)
	{
		return;
	}
	_currentState->mouseReleaseEvent(mouseEvent->scenePos());
	QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

// �������A
void GraphicsScene::changeState(State* state)
{
	State* toDelete = _currentState;
	_currentState = state;
	delete toDelete;
}

// �I�� pointer �ƥ�
void GraphicsScene::clickPointerEvent()
{
	changeState(new PointerState(this));
	((QGraphicsView*)parent())->setMouseTracking(false);
}

// �I�� connect �ƥ�
void GraphicsScene::clickConnectEvent()
{
	changeState(new ConnectState(this));
	((QGraphicsView*)parent())->setMouseTracking(false);
}

// �I�� attribute �ƥ�
void GraphicsScene::clickAttributeEvent()
{
	changeState(new AddNodeState(this, make_pair(attribute, INPUT_A)));
	((QGraphicsView*)parent())->setMouseTracking(true);
}

// �I�� entity �ƥ�
void GraphicsScene::clickEntityEvent()
{
	changeState(new AddNodeState(this, make_pair(entity, INPUT_E)));
	((QGraphicsView*)parent())->setMouseTracking(true);
}

// �I�� relation �ƥ�
void GraphicsScene::clickRelationEvent()
{
	changeState(new AddNodeState(this, make_pair(relation, INPUT_R)));
	((QGraphicsView*)parent())->setMouseTracking(true);
}

// �I�� primary key �ƥ�
void GraphicsScene::clickPrimaryKeyEvent()
{
	changeState(new SetPrimaryKeyState(this));
	((QGraphicsView*)parent())->setMouseTracking(false);
}
