#ifndef _POINTERSTATE_H_
#define _POINTERSTATE_H_

#include "state.h"

class PointerState : public State
{
public:
	PointerState(PresentationModel* presentationModel);
	~PointerState();
	void mousePressEvent(QPointF position);
	void mouseMoveEvent(QPointF position);
	void mouseReleaseEvent(QPointF position);
};

#endif