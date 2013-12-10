#include "Subject.h"

Subject::Subject()
{
}

Subject::~Subject()
{
	_observers.clear(); 
}

// 訂閱
void Subject::attach(Observer* observer)
{
	_observers.push_back(observer);
}

// 取消訂閱
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

// 提示更新
void Subject::notify()
{
	for (unsigned i = 0; i < _observers.size(); i++)
	{
		_observers[i]->update();
	}
}

// 提示更新按鈕狀態
void Subject::notifyButtonEnabled()
{
	for (unsigned i = 0; i < _observers.size(); i++)
	{
		_observers[i]->updateButtonEnabled();
	}
}
