#ifndef _POINTERSTATE_H_
#define _POINTERSTATE_H_

#include "state.h"

class PointerState : public State
{
public:
	PointerState(GraphicsScene* scene);
	~PointerState();
	void mousePressEvent(QPointF mousePosition);
	void mouseMoveEvent(QPointF mousePosition);
	void mouseReleaseEvent(QPointF mousePosition);

private:
	QPointF _moveFrom;
};

#endif