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

// ���o id
int ERComponent::getID()
{
	return _id;
}

// �]�w id
void ERComponent::setID(int id)
{
	_id = id;
}

// ���o type
pair<Type, string> ERComponent::getType()
{
	return _type;
}

// �O�_���Y type
bool ERComponent::isType(Type type)
{
	if (_type.first == type)
	{
		return true;
	}
	return false;
}

// ���o text
string ERComponent::getText()
{
	return _text;
}

// �]�w text
void ERComponent::setText(string text)
{
	_text = text;
}

// ���o�s����T
vector<ERComponent*> ERComponent::getConnection()
{
	return _connections;
}

// �]�w�s��
void ERComponent::setConnection(vector<ERComponent*> connections)
{
	_connections = connections;
}

// �O�_���s���즹 id
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

// ���o��m
QPointF ERComponent::getPosition()
{
	return _position;
}

// �]�w��m
void ERComponent::setPosition(QPointF position)
{
	_position = position;
}

// �s�� component
void ERComponent::connectTo(ERComponent* component)
{
	_connections.push_back(component);
}

// ���_�s��
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

// ���o��� component ��T
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

// �s�@�ƥ�
ERComponent* ERComponent::clone()
{
	ComponentFactory factory;
	ERComponent* component = factory.createComponent(_type);
	component->setID(_id);
	component->setText(_text);
	return component;
}
