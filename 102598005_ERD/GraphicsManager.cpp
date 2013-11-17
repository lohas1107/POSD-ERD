#include "GraphicsManager.h"
#include "GraphicsEntity.h"
#include "GraphicsAttribute.h"
#include "GraphicsRelation.h"
#include "GraphicsConnector.h"
#include "GraphicsItem.h"
#include "AttributeNode.h"

GraphicsManager::GraphicsManager(/*PresentationModel* presentationModel*/)
{
	//_presentationModel = presentationModel;
}

GraphicsManager::~GraphicsManager()
{
	clearItem();
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
void GraphicsManager::draw(QGraphicsScene* scene, vector<ERComponent*> components)
{
	GraphicsItem* item;
	for (unsigned i = 0; i < components.size(); i++)
	{
		item = createGraphicsItem(components[i]->getType().first);
		item->setText(components[i]->getText());
		item->setPos(QPointF(components[i]->getPosition().getX(), components[i]->getPosition().getY()));
		if (components[i]->getType().first == attribute)
		{
			((GraphicsAttribute*)item)->setPrimaryKey(((AttributeNode*)components[i])->isPrimaryKey());
		}
		else if (components[i]->getType().first == connection)
		{
			vector<ERComponent*> connections = components[i]->getConnection();
			QLineF line(connections[0]->getPosition().getX(), connections[0]->getPosition().getY(), connections[1]->getPosition().getX(), connections[1]->getPosition().getY());
			((GraphicsConnector*)item)->setLine(line);
			item->setZValue(-1);
		}
		scene->addItem(item);
		//_graphicsItems.push_back(item);
	}
}

//void GraphicsManager::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
//{
//
//	//for (unsigned i = 0; i < _graphicsItems.size(); i++)
//	//{
//	//	sendEvent(_graphicsItems[i], mouseEvent);
//	//}
//	_presentationModel->mousePressEvent(mouseEvent);
//
//	vector<ERComponent*> components = _presentationModel->getComponents();
//	clearItem();
//	clear();
//	draw(this, components);
//	update(0, 0, width(), height());
//
//	QGraphicsScene::mousePressEvent(mouseEvent);
//
//}
//
//void GraphicsManager::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
//{
//	//
//	_presentationModel->mouseMoveEvent(mouseEvent);
//	QGraphicsScene::mouseMoveEvent(mouseEvent);
//}
//
//void GraphicsManager::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
//{
//	//
//	_presentationModel->mouseReleaseEvent(mouseEvent);
//	//drawDiagram();
//	QGraphicsScene::mouseReleaseEvent(mouseEvent);
//}
