#ifndef _STATE_H_
#define _STATE_H_

#include "PresentationModel.h"
#include <QPointF>

class PresentationModel;
class State
{
public:
	State(PresentationModel* presentationModel);
	virtual ~State();
	virtual void mousePressEvent(QPointF position) = 0;
	virtual void mouseMoveEvent(QPointF position) = 0;
	virtual void mouseReleaseEvent(QPointF position) = 0;

protected:
	PresentationModel* _presentationModel;
};

#endif