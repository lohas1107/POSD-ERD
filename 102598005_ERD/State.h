#ifndef _STATE_H_
#define _STATE_H_

#include "PresentationModel.h"
#include "GraphicsScene.h"

class GraphicsScene;
class State
{
public:
	State(GraphicsScene* scene);
	virtual ~State();
	virtual void mousePressEvent(QPointF mousePosition) = 0;
	virtual void mouseMoveEvent(QPointF mousePosition) = 0;
	virtual void mouseReleaseEvent(QPointF mousePosition) = 0;
	void initialize();
	int getItemID(QPointF position);

protected:
	GraphicsScene* _scene;
	PresentationModel* _presentationModel;
	QGraphicsItem* _pointItem;
	int _pointID;
};

#endif