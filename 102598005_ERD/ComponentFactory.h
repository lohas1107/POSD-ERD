#ifndef _COMPONENTFACTORY_H_
#define _COMPONENTFACTORY_H_

#include "ERComponent.h"
#include "EntityNode.h"
#include "AttributeNode.h"
#include "RelationNode.h"
#include "Connector.h"

class ComponentFactory
{
public:
	ComponentFactory();
	~ComponentFactory();
	ERComponent* createComponent(pair<Type, string> type);
};

#endif