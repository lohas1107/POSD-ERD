#ifndef _RELATIONNODE_H_
#define _RELATIONNODE_H_

#include "Node.h"

class RelationNode : public Node
{
public:
	RelationNode();
	RelationNode(int id, string text);
	~RelationNode();
	bool canConnectTo(ERComponent* component);
	vector<pair<int, int>> getRelationPair();
	void accept(ComponentVisitor* visitor);
};

#endif