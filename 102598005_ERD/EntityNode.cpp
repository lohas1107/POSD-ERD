#include "EntityNode.h"
#include "AttributeNode.h"
#include "ComponentVisitor.h"

const string SINGLE_COMMA = ",";
const string COMMA = ", ";
const string STRING_EMPTY = "";
const int COMMA_SPACE = 2;
const string TABLE_LINE = "%11s |  PK(%s)%s%s\n";
const string FK_LEFT_PARENTHESIS = ", FK(";
const string RIGHT_PARENTHESIS = ")";
const int TABLE_SPACE = 100;

EntityNode::EntityNode() : Node(make_pair(entity, TYPE_ENTITY))
{
	_foreignKey = STRING_EMPTY;
}

EntityNode::EntityNode(int id, string text) : Node(make_pair(entity, TYPE_ENTITY))
{
	_id = id;
	_text = text;
}

EntityNode::~EntityNode()
{
}

// 是否可以連接
bool EntityNode::canConnectTo(ERComponent* component)
{
	if (component->isType(attribute) || component->isType(relation))
	{
		return true;
	}

	return false;
}

// 取得所屬的 attributes
vector<ERComponent*> EntityNode::getAttributes()
{
	vector<ERComponent*> attributes;

	for (unsigned i = 0; i < _connections.size(); i++)
	{
		if (_connections[i]->isType(attribute))
		{
			attributes.push_back(_connections[i]);
		}
	}

	return attributes;
}

// 取得顯示所屬的 attributes
string EntityNode::getAttributeLine()
{
	string line = STRING_EMPTY;

	for (unsigned i = 0; i < _connections.size(); i++)
	{
		line += _connections[i]->getData(attribute);
	}

	return line;
}

// 是否為所屬的 attribute
bool EntityNode::isAttribute(int attributeID)
{
	vector<ERComponent*> attributes = getAttributes();

	for (unsigned i = 0; i < attributes.size(); i++)
	{
		if (attributes[i]->getID() == attributeID)
		{
			return true;
		}		
	}

	return false;
}

// 是否有任何一個 attribute
bool EntityNode::hasAttribute()
{
	if (getAttributes().size() > 0)
	{
		return true;
	}		

	return false;
}

// 取得 primary key id
vector<int> EntityNode::getPrimaryKey()
{
	vector<ERComponent*> attributes = getAttributes();
	vector<int> primaryKey;

	for (unsigned i = 0; i < attributes.size(); i++)
	{
		if (((AttributeNode*)attributes[i])->isPrimaryKey())
		{
			primaryKey.push_back(attributes[i]->getID());
		}
	}

	return primaryKey;
}

// 取得 primary key 字串
std::string EntityNode::getPrimaryKeyString()
{
	vector<int> primaryKey = getPrimaryKey();
	string primaryKeyString;

	for (unsigned i = 0; i < primaryKey.size(); i++)
	{
		primaryKeyString += SINGLE_COMMA + to_string((long long)primaryKey[i]);
	}

	if (primaryKey.size() > 0)
	{
		primaryKeyString = primaryKeyString.substr(1);
	}

	return primaryKeyString;
}

// 設定 attributes 字串
void EntityNode::setAttributeString(string &primaryKey, string &attributeString)
{
	vector<ERComponent*> attributes = getAttributes();

	for (unsigned i = 0; i < attributes.size(); i++)
	{
		if (((AttributeNode*)attributes[i])->isPrimaryKey())
		{
			primaryKey += COMMA + attributes[i]->getText();
		}
		else
		{
			attributeString += COMMA + attributes[i]->getText();
		}
	}
}

// 設定 foreign key
void EntityNode::setForeignKey(string foreignKey)
{
	_foreignKey = foreignKey;
}

// 顯示 table 資訊
string EntityNode::getTable()
{
	string primaryKey;
	string attributes;
	char buffer[TABLE_SPACE];

	setAttributeString(primaryKey, attributes);

	if (primaryKey != STRING_EMPTY)
	{
		primaryKey = primaryKey.substr(COMMA_SPACE);
	}

	if (_foreignKey != STRING_EMPTY)
	{
		_foreignKey = FK_LEFT_PARENTHESIS + _foreignKey + RIGHT_PARENTHESIS;
	}

	sprintf_s(buffer, TABLE_SPACE, TABLE_LINE.c_str(), _text.c_str(), primaryKey.c_str(), attributes.c_str(), _foreignKey.c_str());
	string table = buffer;
	return table;
}

// 接受拜訪
void EntityNode::accept(ComponentVisitor* visitor)
{
	visitor->visit(this);
}
