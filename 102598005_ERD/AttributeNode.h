#ifndef _ATTRIBUTENODE_H_
#define _ATTRIBUTENODE_H_

#include "Node.h"

class AttributeNode : public Node
{
public:
	AttributeNode();
	AttributeNode(int id, string text);
	~AttributeNode();
	void setPrimaryKey(bool isPrimaryKey);
	bool isPrimaryKey();	
	bool canConnectTo(ERComponent* component);
	ERComponent* clone();
	void accept(ComponentVisitor* visitor);

private:
	bool _isPrimaryKey;
};

#endif