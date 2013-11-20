#ifndef _POINTERSTATE_H_
#define _POINTERSTATE_H_

#include "state.h"

class PointerState : public State
{
public:
	PointerState(GraphicsScene* scene);
	~PointerState();
	void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
	void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);

private:
	QGraphicsItem* _item;
	int _id;
};

#endif