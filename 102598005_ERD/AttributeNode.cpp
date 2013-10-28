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

// �]�w�� primary key
void AttributeNode::setPrimaryKey(bool isPrimaryKey)
{
	_isPrimaryKey = isPrimaryKey;
}

// �O�_�� primary key
bool AttributeNode::isPrimaryKey()
{
	return _isPrimaryKey;
}

// �ˬdtype�O�_����s��
bool AttributeNode::canConnectTo(ERComponent* component)
{
	if (component->isType(entity) && _connections.size() == 0)
	{
		return true;
	}
	return false;
}

// �s�@�ƥ�
ERComponent* AttributeNode::clone()
{
	ComponentFactory factory;
	ERComponent* component = factory.createComponent(make_pair(attribute, TYPE_ATTRIBUTE));
	component->setID(_id);
	component->setText(_text);
	((AttributeNode*)component)->setPrimaryKey(_isPrimaryKey);
	return component;
}
