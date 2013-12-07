#ifndef _SETPRIMARYKEYSTATE_H_
#define _SETPRIMARYKEYSTATE_H_

#include "state.h"

class SetPrimaryKeyState : public State
{
public:
	SetPrimaryKeyState(GraphicsScene* scene);
	~SetPrimaryKeyState();
	void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
	void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
};

#endif