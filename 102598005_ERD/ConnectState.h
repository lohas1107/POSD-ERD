#ifndef _CONNECTSTATE_H_
#define _CONNECTSTATE_H_

#include "state.h"

class ConnectState : public State
{
public:
	ConnectState(GraphicsManager* scene);
	~ConnectState();
	void mousePressEvent(QPointF position);
	void mouseMoveEvent(QPointF position);
	void mouseReleaseEvent(QPointF position);
};

#endif