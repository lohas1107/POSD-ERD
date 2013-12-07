#ifndef _STATE_H_
#define _STATE_H_

#include "PresentationModel.h"
#include "GraphicsScene.h"
#include <QGraphicsSceneMouseEvent>

class GraphicsScene;
class State
{
public:
	State(GraphicsScene* scene);
	virtual ~State();
	virtual void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) = 0;
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) = 0;
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) = 0;
	void initialize();
	int getItemID(QPointF position);

protected:
	GraphicsScene* _scene;
	PresentationModel* _presentationModel;
	QGraphicsItem* _pointItem;
	int _pointID;
};

#endif