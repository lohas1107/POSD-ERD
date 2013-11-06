#include "GraphicsManager.h"
#include "GraphicsEntity.h"
#include "GraphicsAttribute.h"
#include "GraphicsRelation.h"
#include "GraphicsConnector.h"
#include "GraphicsItem.h"
#include "AttributeNode.h"

GraphicsManager::GraphicsManager()
{
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
		item->setPos(QPointF(components[i]->getPosition().x, components[i]->getPosition().y));
		if (components[i]->getType().first == attribute)
		{
			((GraphicsAttribute*)item)->setPrimaryKey(((AttributeNode*)components[i])->isPrimaryKey());
		}
		else if (components[i]->getType().first == connection)
		{
			vector<ERComponent*> connections = components[i]->getConnection();
			QLineF line(connections[0]->getPosition().x, connections[0]->getPosition().y, connections[1]->getPosition().x, connections[1]->getPosition().y);
			((GraphicsConnector*)item)->setLine(line);
			item->setZValue(-1);
		}
		scene->addItem(item);
	}
}
