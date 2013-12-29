#ifndef _ADDNODESTATE_H_
#define _ADDNODESTATE_H_

#include "state.h"

class AddNodeState : public State
{
public:
	AddNodeState(GraphicsScene* scene, pair<Type, string> type);
	~AddNodeState();
	void mousePressEvent(QPointF mousePosition);
	void mouseMoveEvent(QPointF mousePosition);
	void mouseReleaseEvent(QPointF mousePosition);

private:
	pair<Type, string> _type;
	bool _isOK;
	GraphicsItem* _item;
};

#endif