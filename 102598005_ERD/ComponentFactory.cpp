#include "ComponentFactory.h"

const string INPUT_E = "E";
const string INPUT_A = "A";
const string INPUT_R = "R";
const string INPUT_C = "C";

ComponentFactory::ComponentFactory()
{
}

ComponentFactory::~ComponentFactory()
{
}

// ¥Í²£ component
ERComponent* ComponentFactory::createComponent(pair<Type, string> type)
{
	if (type.first == entity || type.second == INPUT_E)
	{
		return new EntityNode();
	}
	else if (type.first == attribute || type.second == INPUT_A)
	{
		return new AttributeNode();
	}
	else if (type.first == relation || type.second == INPUT_R)
	{
		return new RelationNode();
	}
	else if (type.first == connection || type.second == INPUT_C)
	{
		return new Connector();
	}
	
	return NULL;	
}