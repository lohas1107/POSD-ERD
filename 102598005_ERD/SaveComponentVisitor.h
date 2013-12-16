#ifndef _SAVECOMPONENTVISITOR_H_
#define _SAVECOMPONENTVISITOR_H_

#include "ComponentVisitor.h"

class SaveComponentVisitor : public ComponentVisitor
{
public:
	SaveComponentVisitor();
	~SaveComponentVisitor();
	void visit(EntityNode* node);
	void visit(AttributeNode* node);
	void visit(RelationNode* node);
	void visit(Connector* node);
};

#endif