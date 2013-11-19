#ifndef _ADDNODESTATE_H_
#define _ADDNODESTATE_H_

#include "state.h"

class AddNodeState : public State
{
public:
	AddNodeState(GraphicsManager* scene, pair<Type, string> type);
	~AddNodeState();
	void mousePressEvent(QPointF position);
	void mouseMoveEvent(QPointF position);
	void mouseReleaseEvent(QPointF position);

private:
	pair<Type, string> _type;
	bool _isOK;
	GraphicsItem* _item;
};

#endif