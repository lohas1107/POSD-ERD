#include "Subject.h"

Subject::Subject()
{
}

Subject::~Subject()
{
	while (!_observers.empty())
	{
		Observer* toDelete = _observers.back();
		_observers.pop_back();
		delete toDelete;
	}
}

void Subject::attach(Observer* observer)
{
	_observers.push_back(observer);
}

void Subject::detach(Observer* observer)
{
	_observers.erase(_observers.remove(_observers.begin(), _observers.end(), observer));
}

void Subject::notify()
{
	for (unsigned i = 0; i < _observers.size(); i++)
	{
		_observers[i]->update();
	}
}
