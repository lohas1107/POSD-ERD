#include "RelationNode.h"
#include "ComponentVisitor.h"

const int PAIR = 2;

RelationNode::RelationNode() : Node(make_pair(relation, TYPE_RELATION))
{
}

RelationNode::RelationNode(int id, string text) : Node(make_pair(relation, TYPE_RELATION))
{
	_id = id;
	_text = text;
}

RelationNode::~RelationNode()
{
}

// 是否可以連接 component
bool RelationNode::canConnectTo(ERComponent* component)
{
	if (component->isType(entity) && _connections.size() < PAIR)
	{
		return true;
	}
	return false;
}

// 取得 relation 配對
vector<pair<int, int>> RelationNode::getRelationPair()
{
	vector<pair<int, int>> relationPair;

	if (_connections.size() == PAIR)
	{
		relationPair.push_back(make_pair(_connections[0]->getID(), _id));
		relationPair.push_back(make_pair(_connections[1]->getID(), _id));
	}

	return relationPair;
}

void RelationNode::accept(ComponentVisitor* visitor)
{
	visitor->visit(this);
}
