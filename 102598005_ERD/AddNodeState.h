#ifndef _ADDNODESTATE_H_
#define _ADDNODESTATE_H_

#include "state.h"

class AddNodeState : public State
{
public:
	AddNodeState(GraphicsManager* scene, pair<Type, string> type);
	~AddNodeState();
	void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
	void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);

private:
	pair<Type, string> _type;
	bool _isOK;
	GraphicsItem* _item;
};

#endif