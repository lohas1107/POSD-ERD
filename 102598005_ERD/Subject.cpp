#include "Subject.h"

Subject::Subject()
{
}

Subject::~Subject()
{
	_observers.clear(); 
}

// �q�\
void Subject::attach(Observer* observer)
{
	_observers.push_back(observer);
}

// �����q�\
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

// ���ܧ�s
void Subject::notify()
{
	for (unsigned i = 0; i < _observers.size(); i++)
	{
		_observers[i]->update();
	}
}

// ���ܧ�s���s���A
void Subject::notifyButtonEnabled()
{
	for (unsigned i = 0; i < _observers.size(); i++)
	{
		_observers[i]->updateButtonEnabled();
	}
}
