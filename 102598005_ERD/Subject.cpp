#include "Subject.h"

Subject::Subject()
{
}

Subject::~Subject()
{
	while (!_observers.empty())
	{
		_observers.pop_back();
	}
}

void Subject::attach(Observer* observer)
{
	_observers.push_back(observer);
}

void Subject::detach(Observer* observer)
{
	for (unsigned i = 0; i < _observers.size(); i++)
	{
		if (_observers[i] == observer)
		{
			_observers.erase(_observers.begin() + i);
		}
	}
}

void Subject::notify()
{
	for (unsigned i = 0; i < _observers.size(); i++)
	{
		_observers[i]->update();
	}
}
