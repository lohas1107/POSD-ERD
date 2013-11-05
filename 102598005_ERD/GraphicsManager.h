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
	void draw();

private:
	vector<GraphicsItem*> _graphicsItems;
};

#endif