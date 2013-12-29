#ifndef _CONNECTSTATE_H_
#define _CONNECTSTATE_H_

#include "state.h"
#include "GraphicsItem.h"

class ConnectState : public State
{
public:
	ConnectState(GraphicsScene* scene);
	~ConnectState();
	void mousePressEvent(QPointF mousePosition);
	void mouseMoveEvent(QPointF mousePosition);
	void mouseReleaseEvent(QPointF mousePosition);
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