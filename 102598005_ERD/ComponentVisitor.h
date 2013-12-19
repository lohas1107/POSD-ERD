#ifndef _COMPONENTVISITOR_H_
#define _COMPONENTVISITOR_H_

#include "EntityNode.h"
#include "AttributeNode.h"
#include "RelationNode.h"
#include "Connector.h"

//class EntityNode;
//class AttributeNode;
//class RelationNode;
//class Connector;
class ComponentVisitor
{
public:
	ComponentVisitor();
	virtual ~ComponentVisitor();
	virtual void visit(EntityNode* node) = 0;
	virtual void visit(AttributeNode* node) = 0;
	virtual void visit(RelationNode* node) = 0;
	virtual void visit(Connector* node) = 0;
};

#endif