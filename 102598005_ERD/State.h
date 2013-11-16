#ifndef _STATE_H_
#define _STATE_H_

#include "PresentationModel.h"

class PresentationModel;
class State
{
public:
	State(PresentationModel* presentationModel);
	virtual ~State();
	virtual void mousePressEvent() = 0;
	virtual void mouseMoveEvent() = 0;
	virtual void mouseReleaseEvent() = 0;

private:
	PresentationModel* _presentationModel;
};

#endif