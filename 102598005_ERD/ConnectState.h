#ifndef _CONNECTSTATE_H_
#define _CONNECTSTATE_H_

#include "state.h"
#include "GraphicsItem.h"

class ConnectState : public State
{
public:
	ConnectState(GraphicsScene* scene);
	~ConnectState();
	void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
	void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
	bool isValidConnection(int firstID, int secondID);
	string getCardinality(int firstID, int secondID);

private:
	GraphicsItem* _line;
	QLineF _linePosition;
	int _firstID;
	int _secondID;
	bool _isOK;
};

#endif