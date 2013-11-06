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
	_position.x = 0;
	_position.y = 0;
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

// ���o text
string ERComponent::getText()
{
	return _text;
}

// ���o�s����T
vector<ERComponent*> ERComponent::getConnection()
{
	return _connections;
}

// ���o��m
ERPoint ERComponent::getPosition()
{
	return _position;
}

// �]�w��m
void ERComponent::setPosition(ERPoint position)
{
	_position = position;
}

// �]�w text
void ERComponent::setText(string text)
{
	_text = text;
}

// �]�w�s��
void ERComponent::setConnection(vector<ERComponent*> connections)
{
	_connections = connections;
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