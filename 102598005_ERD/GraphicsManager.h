#ifndef _GRAPHICSMANAGER_H_
#define _GRAPHICSMANAGER_H_

#include "GraphicsItem.h"
#include "ERComponent.h"

class GraphicsManager
{
public:
	GraphicsManager();
	~GraphicsManager();
	void clearItem();
	GraphicsItem* createGraphicsItem(Type type);
	void draw(QGraphicsScene* scene, vector<ERComponent*> components);

private:
	vector<GraphicsItem*> _graphicsItems;
};

#endif