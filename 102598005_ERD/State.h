#ifndef _STATE_H_
#define _STATE_H_

#include "PresentationModel.h"
#include "GraphicsManager.h"
#include <QPointF>

//class PresentationModel;
class GraphicsManager;
class State
{
public:
	State(GraphicsManager* scene);
	virtual ~State();
	virtual void mousePressEvent(QPointF position) = 0;
	virtual void mouseMoveEvent(QPointF position) = 0;
	virtual void mouseReleaseEvent(QPointF position) = 0;

protected:
	GraphicsManager* _scene;
	PresentationModel* _presentationModel;
};

#endif