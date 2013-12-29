#ifndef _SETPRIMARYKEYSTATE_H_
#define _SETPRIMARYKEYSTATE_H_

#include "state.h"

class SetPrimaryKeyState : public State
{
public:
	SetPrimaryKeyState(GraphicsScene* scene);
	~SetPrimaryKeyState();
	void mousePressEvent(QPointF mousePosition);
	void mouseMoveEvent(QPointF mousePosition);
	void mouseReleaseEvent(QPointF mousePosition);
};

#endif