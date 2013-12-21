#ifndef _SAVEXMLCOMPONENTVISITOR_H_
#define _SAVEXMLCOMPONENTVISITOR_H_

#include "ComponentVisitor.h"

class SaveXmlComponentVisitor : public ComponentVisitor
{
public:
	SaveXmlComponentVisitor();
	~SaveXmlComponentVisitor();
	void visit(EntityNode* node);
	void visit(AttributeNode* node);
	void visit(RelationNode* node);
	void visit(Connector* node);
	string getContentFile();

private:
	string _xml;
};

#endif