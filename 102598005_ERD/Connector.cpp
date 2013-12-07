#include "Connector.h"
#include "ComponentFactory.h"

const string TYPE_CONNECTION = "Connection";
const string CARDINALITY_ONE = "1";
const string CARDINALITY_N = "N";
const string NEXT_LINE_STRING = "\n";
const string CONNECTION_DATA = "%9d  |  %2d  |  %2d  |\n";
const int CONNECTION_SPACE = 30;
const string STRING_EMPTY = "";
const string COMMA = ",";

Connector::Connector() : ERComponent(make_pair(connection, TYPE_CONNECTION))
{
}

Connector::Connector(int id, string text) : ERComponent(make_pair(connection, TYPE_CONNECTION))
{
	_id = id;
	_text = text;
}

Connector::~Connector()
{
}

void Connector::setText(string text)
{
	if (text == CARDINALITY_ONE || text == CARDINALITY_N)
	{
		_text = text;
	}
}

// 是否可以連接
bool Connector::canConnectTo(ERComponent* component)
{
	if (_connections.size() <= 1)
	{
		return true;
	}
	return false;
}

// 顯示連接資訊
string Connector::getConnectionLine()
{
	char buffer[CONNECTION_SPACE];
	string line = STRING_EMPTY;

	if (_connections.size() > 1)
	{
		sprintf_s(buffer, CONNECTION_SPACE, CONNECTION_DATA.c_str(), _id, _connections[0]->getID(), _connections[1]->getID());
		line = buffer;
	}

	return line;
}

// 取得連接字串
string Connector::getConnection()
{
	string connections;

	if (_connections.size() > 1)
	{
	connections += to_string((long long)_connections[0]->getID()) + COMMA + to_string((long long)_connections[1]->getID());
	}

	return connections;
}

// 取得連接 pair
pair<int, int> Connector::getConnectionPair()
{
	pair<int, int> connectionPair = make_pair(INT_MIN, INT_MIN);

	if (_connections.size() > 1)
	{
		connectionPair = make_pair(_connections[0]->getID(), _connections[1]->getID());
	}

	return connectionPair;
}

// 檢查是否為一對一
bool Connector::checkOneToOne(pair<int, int> relationPair)
{
	if (_text != CARDINALITY_ONE)
	{
		return false;
	}
	else if (relationPair.first == _connections[0]->getID() && relationPair.second == _connections[1]->getID())
	{
		return true;
	}
	else if (relationPair.first == _connections[1]->getID() && relationPair.second == _connections[0]->getID())
	{
		return true;
	}

	return false;
}

// 製作副本
ERComponent* Connector::clone()
{
	ComponentFactory factory;
	ERComponent* component = factory.createComponent(make_pair(connection, TYPE_CONNECTION));
	component->setID(_id);
	component->setText(_text);
	component->setPosition(_position);

	vector<ERComponent*> connections;
	for (unsigned i = 0; i < _connections.size(); i++)
	{
		connections.push_back(_connections[i]->clone());
	}
	((Connector*)component)->setConnection(connections);

	return component;
}
