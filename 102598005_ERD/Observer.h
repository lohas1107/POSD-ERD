#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Observer
{
public:
	Observer();
	virtual ~Observer();
	virtual void update() = 0;
};

#endif