#ifndef _ADDNODESTATE_H_
#define _ADDNODESTATE_H_

#include "state.h"

class AddNodeState : public State
{
public:
	AddNodeState(PresentationModel* presentationModel);
	~AddNodeState();
	void mousePressEvent();
	void mouseMoveEvent();
	void mouseReleaseEvent();
};

#endif