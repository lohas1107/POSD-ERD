#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include "Observer.h"
#include <vector>

using namespace std;

class Subject
{
public:
	Subject();
	virtual ~Subject();
	void attach(Observer* observer);
	void detach(Observer* observer);
	void notify();

private:
	vector<Observer*> _observers;
};

#endif