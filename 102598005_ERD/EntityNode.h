#ifndef _ENTITYNODE_H_
#define _ENTITYNODE_H_

#include "Node.h"
#include <vector>

class EntityNode : public Node
{
public:
	EntityNode();
	EntityNode(int id, string text);
	~EntityNode();
	bool canConnectTo(ERComponent* component);
	vector<ERComponent*> getAttributes();
	string getAttributeLine();
	bool isAttribute(int attributeID);
	bool hasAttribute();
	vector<int> getPrimaryKey();
	void setAttributeString(string &primaryKey, string &attributeString);
	void setForeignKey(string foreignKey);
	string getTable();

private:
	string _foreignKey;
};

#endif