#include "GraphicsManager.h"
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
#include "..\src\corelib\io\qdebug.h"

const string INPUT_E = "E";
const string INPUT_A = "A";
const string INPUT_R = "R";

GraphicsManager::GraphicsManager(PresentationModel* presentationModel)/* : QGraphicsScene()*/
{
	_presentationModel = presentationModel;
	_currentState = new PointerState(this);
}

GraphicsManager::~GraphicsManager()
{
	clearItem();
	delete _currentState;
}

// 清除圖形
void GraphicsManager::clearItem()
{
	while(!_graphicsItems.empty())
	{
		QGraphicsItem* item = _graphicsItems.back();
		_graphicsItems.pop_back();
		delete item;
	}	
}

// 產生圖形
GraphicsItem* GraphicsManager::createGraphicsItem(Type type)
{
	if (type == entity)
	{
		return new GraphicsEntity();
	}
	else if (type == attribute)
	{
		return new GraphicsAttribute();
	}
	else if (type == relation)
	{
		return new GraphicsRelation();
	}
	else if (type == connection)
	{
		return new GraphicsConnector();
	}

	return NULL;
}

// 畫圖
void GraphicsManager::draw()
{
	vector<ERComponent*> components = _presentationModel->getComponents();
	GraphicsItem* item;

	//clearItem();
	clear();

	for (unsigned i = 0; i < components.size(); i++)
	{
		item = createGraphicsItem(components[i]->getType().first);
		item->setText(components[i]->getText());
		item->setPos(QPointF(components[i]->getPosition().x(), components[i]->getPosition().y()));
		if (components[i]->getType().first == attribute)
		{
			((GraphicsAttribute*)item)->setPrimaryKey(((AttributeNode*)components[i])->isPrimaryKey());
		}
		else if (components[i]->getType().first == connection)
		{
			vector<ERComponent*> connections = components[i]->getConnection();
			QLineF line(connections[0]->getPosition().x(), connections[0]->getPosition().y(), connections[1]->getPosition().x(), connections[1]->getPosition().y());
			((GraphicsConnector*)item)->setLine(line);
			item->setZValue(-1);
		}
		addItem(item);
		//_graphicsItems.push_back(item);
	}

	update(0, 0, width(), height());
}

// 取得 PresentationModel
PresentationModel* GraphicsManager::getPresentationModel()
{
	return _presentationModel;
}

void GraphicsManager::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (mouseEvent->button() != Qt::LeftButton)
	{
		return;
	}
	//for (unsigned i = 0; i < _graphicsItems.size(); i++)
	//{
	//	sendEvent(_graphicsItems[i], mouseEvent);
	//}


	//vector<ERComponent*> components = _presentationModel->getComponents();
	//clearItem();
	//clear();
	//draw(this, components);
	//update(0, 0, width(), height());

	QGraphicsScene::mousePressEvent(mouseEvent);
	_currentState->mousePressEvent(mouseEvent->scenePos());
	//_presentationModel->mousePressEvent(mouseEvent);

}

void GraphicsManager::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{

	QGraphicsScene::mouseMoveEvent(mouseEvent);
	_currentState->mouseMoveEvent(mouseEvent->scenePos());
	//qDebug() << mouseEvent->pos();
	//_presentationModel->mouseMoveEvent(mouseEvent);
}

void GraphicsManager::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (mouseEvent->button() != Qt::LeftButton)
	{
		return;
	}

	//drawDiagram();
	QGraphicsScene::mouseReleaseEvent(mouseEvent);
	_currentState->mouseReleaseEvent(mouseEvent->scenePos());
	//_presentationModel->mouseReleaseEvent(mouseEvent);
	//if (_presentationModel->getPointerChecked())
	//{
	//	emit updateButton();
	//	_presentationModel->setPointerChecked(false);
	//}
}

//bool GraphicsManager::eventFilter(QObject *object, QEvent *event)
//{
//	return QGraphicsScene::eventFilter(object, event);
//}

// 切換狀態
void GraphicsManager::changeState(State* state)
{
	State* toDelete = _currentState;
	_currentState = state;
	delete toDelete;
}

void GraphicsManager::clickPointerEvent()
{
	changeState(new PointerState(this));
}

void GraphicsManager::clickConnectEvent()
{
	changeState(new ConnectState(this));
}

void GraphicsManager::clickAttributeEvent()
{
	changeState(new AddNodeState(this, make_pair(attribute, INPUT_A)));
}

void GraphicsManager::clickEntityEvent()
{
	changeState(new AddNodeState(this, make_pair(entity, INPUT_E)));
}

void GraphicsManager::clickRelationEvent()
{
	changeState(new AddNodeState(this, make_pair(relation, INPUT_R)));
}

void GraphicsManager::updateChecked()
{
	emit updateButton();
}