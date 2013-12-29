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

// 拜訪entity
void SaveComponentVisitor::visit(EntityNode* node)
{
	_components += getNodeInformation(node);

	if (node->hasAttribute())
	{
		_primaryKeys += to_string((long long)node->getID()) + STRING_SPACE + node->getPrimaryKeyString() + NEXT_LINE;
	}

	setPositions(node->getPosition().x(), node->getPosition().y());
}

// 拜訪attribute
void SaveComponentVisitor::visit(AttributeNode* node)
{
	_components += getNodeInformation(node);
	setPositions(node->getPosition().x(), node->getPosition().y());
}

// 拜訪relation
void SaveComponentVisitor::visit(RelationNode* node)
{
	_components += getNodeInformation(node);
	setPositions(node->getPosition().x(), node->getPosition().y());
}

// 拜訪connector
void SaveComponentVisitor::visit(Connector* node)
{
	_components += getNodeInformation(node);
	_connections += to_string((long long)node->getID()) + STRING_SPACE + node->getConnection() + NEXT_LINE;
}

// 取得元件資訊
std::string SaveComponentVisitor::getNodeInformation(ERComponent* node)
{
	return node->getType().second[0] + COMMA_SPACE + node->getText() + NEXT_LINE;;
}

// 取得檔案內容
string SaveComponentVisitor::getContentFile()
{
	return _components + NEXT_LINE + _connections + NEXT_LINE + _primaryKeys;
}

// 儲存位置
void SaveComponentVisitor::setPositions(int x, int y)
{
	_positions += to_string((long long)x) + STRING_SPACE + to_string((long long)y) + NEXT_LINE;
}

// 取得位置檔案內容
string SaveComponentVisitor::getPositionFile()
{
	return _positions;
}
