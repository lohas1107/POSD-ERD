#ifndef _ADDNODESTATE_H_
#define _ADDNODESTATE_H_

#include "state.h"

class AddNodeState : public State
{
public:
	AddNodeState(PresentationModel* presentationModel);
	~AddNodeState();
	void mousePressEvent(QPointF position);
	void mouseMoveEvent(QPointF position);
	void mouseReleaseEvent(QPointF position);

private:
	bool _isOK;
};

#endif