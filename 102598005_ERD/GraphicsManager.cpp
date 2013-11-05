#include "GraphicsManager.h"
#include "GraphicsEntity.h"
#include "GraphicsAttribute.h"
#include "GraphicsRelation.h"
#include "GraphicsConnector.h"
#include "GraphicsItem.h"

GraphicsManager::GraphicsManager()
{
}

GraphicsManager::~GraphicsManager()
{
	while(!_graphicsItems.empty())
	{
		QGraphicsItem* item = _graphicsItems.back();
		_graphicsItems.pop_back();
		delete item;
	}
}

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

//void GraphicsManager::addGraphicsItem(GraphicsItem* item)
//{
//	_graphicsItems.push_back(item);
//}

void GraphicsManager::draw(QGraphicsScene* scene, vector<ERComponent*> components)
{
	GraphicsItem* item;

	for (unsigned i = 0; i < components.size(); i++)
	{
		item = createGraphicsItem(components[i]->getType().first);
		item->setText(components[i]->getText());
		//_graphicsItems.push_back(item);
		//item->setPos(QPointF(components[i]->getPosition().x, components[i]->getPosition().y));
		if (components[i]->getType().first != connection)
		{
			item->setPos(QPointF(components[i]->getPosition().x, components[i]->getPosition().y));
		} 
		else
		{
			vector<ERComponent*> connections = components[i]->getConnection();
			QLineF line(connections[0]->getPosition().x, connections[0]->getPosition().y, connections[1]->getPosition().x, connections[1]->getPosition().y);
			((GraphicsConnector*)item)->setLine(line);
		}

		scene->addItem(item);
	}
	//scene->update();
}

void GraphicsManager::composeDiagram()
{

}
