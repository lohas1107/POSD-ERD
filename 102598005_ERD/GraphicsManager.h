#ifndef _GRAPHICSMANAGER_H_
#define _GRAPHICSMANAGER_H_

#include "GraphicsItem.h"
#include "ERComponent.h"

class GraphicsManager
{
public:
	GraphicsManager();
	~GraphicsManager();
	GraphicsItem* createGraphicsItem(Type type);
	//void addGraphicsItem(GraphicsItem* item);
	void draw(QGraphicsScene* scene, vector<ERComponent*> components);
	void composeDiagram();

private:
	vector<GraphicsItem*> _graphicsItems;
};

#endif