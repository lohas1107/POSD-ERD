#include "Node.h"

Node::Node(pair<Type, string> type) : ERComponent(type)
{
}

Node::~Node()
{
}

// �O�_���s���즹 id
bool Node::hasConnection(int id)
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
