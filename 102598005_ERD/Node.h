#ifndef _NODE_H_
#define _NODE_H_

#include "ERComponent.h"

const string TYPE_ENTITY = "Entity";
const string TYPE_ATTRIBUTE = "Attribute";
const string TYPE_RELATION = "Relation";

class Node : public ERComponent
{
public:
	Node(pair<Type, string> type);
	~Node();
	virtual bool canConnectTo(ERComponent* component) = 0;
	bool hasConnection(int id);
};

#endif