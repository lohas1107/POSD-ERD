#ifndef _GRAPHICSMANAGER_H_
#define _GRAPHICSMANAGER_H_

#include "GraphicsItem.h"
#include "ERComponent.h"
#include "PresentationModel.h"

class GraphicsManager : public QGraphicsScene
{
public:
	GraphicsManager(/*PresentationModel* presentationModel*/);
	~GraphicsManager();
	void clearItem();
	GraphicsItem* createGraphicsItem(Type type);
	void draw(QGraphicsScene* scene, vector<ERComponent*> components);
	//void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
	//void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
	//void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);

private:
	vector<GraphicsItem*> _graphicsItems;
	//PresentationModel* _presentationModel;
};

#endif