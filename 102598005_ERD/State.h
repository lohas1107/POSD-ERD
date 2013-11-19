#ifndef _STATE_H_
#define _STATE_H_

#include "PresentationModel.h"
#include "GraphicsManager.h"
#include <QGraphicsSceneMouseEvent>

//class PresentationModel;
class GraphicsManager;
class State
{
public:
	State(GraphicsManager* scene);
	virtual ~State();
	virtual void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) = 0;
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) = 0;
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) = 0;

protected:
	GraphicsManager* _scene;
	PresentationModel* _presentationModel;
};

#endif