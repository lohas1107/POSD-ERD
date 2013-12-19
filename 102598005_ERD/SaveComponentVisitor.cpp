#include "SaveComponentVisitor.h"

const string STRING_EMPTY = "";
const string COMMA_SPACE = ", ";
const string NEXT_LINE = "\n";
const string STRING_SPACE = " ";

SaveComponentVisitor::SaveComponentVisitor()
{
	_components = STRING_EMPTY;
	_connections = STRING_EMPTY;
	_primaryKeys = STRING_EMPTY;
	_positions = STRING_EMPTY;
}

SaveComponentVisitor::~SaveComponentVisitor()
{
}

void SaveComponentVisitor::visit(EntityNode* node)
{
	_components += getNodeInformation(node);

	if (node->hasAttribute())
	{
		_primaryKeys += to_string((long long)node->getID()) + STRING_SPACE + node->getPrimaryKeyString() + NEXT_LINE;
	}
}

void SaveComponentVisitor::visit(AttributeNode* node)
{
	_components += getNodeInformation(node);
}

void SaveComponentVisitor::visit(RelationNode* node)
{
	_components += getNodeInformation(node);
}

void SaveComponentVisitor::visit(Connector* node)
{
	_components += getNodeInformation(node);
	_connections += to_string((long long)node->getID()) + STRING_SPACE + node->getConnection() + NEXT_LINE;
}

std::string SaveComponentVisitor::getNodeInformation(ERComponent* node)
{
	return node->getType().second[0] + COMMA_SPACE + node->getText() + NEXT_LINE;;
}

string SaveComponentVisitor::getContentFile()
{
	return _components + NEXT_LINE + _connections + NEXT_LINE + _primaryKeys;
}

string SaveComponentVisitor::getPositionFile()
{
	return _positions;
}
