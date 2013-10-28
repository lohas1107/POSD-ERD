#include "AttributeNode.h"
#include "ComponentFactory.h"

AttributeNode::AttributeNode() : Node(make_pair(attribute, TYPE_ATTRIBUTE))
{
	_isPrimaryKey = false;
}

AttributeNode::AttributeNode(int id, string text)  : Node(make_pair(attribute, TYPE_ATTRIBUTE))
{
	_id = id;
	_text = text;
	_isPrimaryKey = false;
}

AttributeNode::~AttributeNode()
{
}

// 設定為 primary key
void AttributeNode::setPrimaryKey(bool isPrimaryKey)
{
	_isPrimaryKey = isPrimaryKey;
}

// 是否為 primary key
bool AttributeNode::isPrimaryKey()
{
	return _isPrimaryKey;
}

// 檢查type是否能夠連接
bool AttributeNode::canConnectTo(ERComponent* component)
{
	if (component->isType(entity) && _connections.size() == 0)
	{
		return true;
	}
	return false;
}

// 製作副本
ERComponent* AttributeNode::clone()
{
	ComponentFactory factory;
	ERComponent* component = factory.createComponent(make_pair(attribute, TYPE_ATTRIBUTE));
	component->setID(_id);
	component->setText(_text);
	((AttributeNode*)component)->setPrimaryKey(_isPrimaryKey);
	return component;
}
