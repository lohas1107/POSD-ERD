#include "ERComponent.h"
#include "ComponentFactory.h"

const string STRING_EMPTY = "";
const string DATA_LINE = "%4c  |  %2d  |  %s\n";
const int DATA_SPACE = 50;

ERComponent::ERComponent(pair<Type, string> type)
{
	_id = 0;
	_type = type;
	_text = STRING_EMPTY;
}

ERComponent::~ERComponent()
{
}

// 取得 id
int ERComponent::getID()
{
	return _id;
}

// 設定 id
void ERComponent::setID(int id)
{
	_id = id;
}

// 取得 type
pair<Type, string> ERComponent::getType()
{
	return _type;
}

// 是否為某 type
bool ERComponent::isType(Type type)
{
	if (_type.first == type)
	{
		return true;
	}
	return false;
}

// 取得 text
string ERComponent::getText()
{
	return _text;
}

// 設定 text
void ERComponent::setText(string text)
{
	_text = text;
}

// 取得連結資訊
vector<ERComponent*> ERComponent::getConnection()
{
	return _connections;
}

// 設定連結
void ERComponent::setConnection(vector<ERComponent*> connections)
{
	_connections = connections;
}

// 是否有連結到此 id
bool ERComponent::hasConnection(int id)
{
	for (unsigned i = 0; i < _connections.size(); i++)
	{
		if (_connections[i]->getID() == id)
		{
			return true;
		}
	}

	return false;
}

// 取得位置
QPointF ERComponent::getPosition()
{
	return _position;
}

// 設定位置
void ERComponent::setPosition(QPointF position)
{
	_position = position;
}

// 連接 component
void ERComponent::connectTo(ERComponent* component)
{
	_connections.push_back(component);
}

// 切斷連結
void ERComponent::disconnectTo(int id)
{
	int index = INT_MIN;

	for (unsigned i = 0; i < _connections.size(); i++)
	{
		if (_connections[i]->getID() == id)
		{
			index = i;
		}
	}

	if (index != INT_MIN)
	{
		_connections.erase(_connections.begin() + index);
	}
}

// 取得顯示 component 資訊
string ERComponent::getData(Type type)
{
	char data[DATA_SPACE];
	string result = STRING_EMPTY;

	if (type == all || isType(type))
	{
		sprintf_s(data, DATA_SPACE, DATA_LINE.c_str(), _type.second[0], _id, _text.c_str());
		result = data;
	}

	return result;
}

// 製作副本
ERComponent* ERComponent::clone()
{
	ComponentFactory factory;
	ERComponent* component = factory.createComponent(_type);
	component->setID(_id);
	component->setText(_text);
	return component;
}
