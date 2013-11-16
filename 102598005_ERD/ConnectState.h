#ifndef _CONNECTSTATE_H_
#define _CONNECTSTATE_H_

#include "state.h"

class ConnectState : public State
{
public:
	ConnectState(PresentationModel* presentationModel);
	~ConnectState();
	void mousePressEvent();
	void mouseMoveEvent();
	void mouseReleaseEvent();
};

#endif