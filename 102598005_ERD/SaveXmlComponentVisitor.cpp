#include "SaveXmlComponentVisitor.h"

const string STRING_EMPTY = "";
const string XML_HEADER = "<?xml version=\"1.0\"?>\n<ERDiagram>\n";
const string XML_FOOTER = "</ERDiagram>";

SaveXmlComponentVisitor::SaveXmlComponentVisitor()
{
	_xml = STRING_EMPTY;
}

SaveXmlComponentVisitor::~SaveXmlComponentVisitor()
{
}

void SaveXmlComponentVisitor::visit(EntityNode* node)
{
	_xml += "\t<Entity>\n\t\t<Id>" + to_string((long long)node->getID()) + "</Id>\n\t\t<Text>" 
		+ node->getText() + "</Text>\n\t\t<PrimaryKey>" 
		+ node->getPrimaryKeyString() + "</PrimaryKey>\n\t\t<positionX>"
		+ to_string((long long)node->getPosition().x()) + "</positionX>\n\t\t<positionY>"
		+ to_string((long long)node->getPosition().y()) + "</positionY>\n\t</Entity>\n";
}

void SaveXmlComponentVisitor::visit(AttributeNode* node)
{
	_xml += "\t<Attribute>\n\t\t<Id>" + to_string((long long)node->getID()) + "</Id>\n\t\t<Text>" 
		+ node->getText() + "</Text>\n\t\t<positionX>"
		+ to_string((long long)node->getPosition().x()) + "</positionX>\n\t\t<positionY>"
		+ to_string((long long)node->getPosition().y()) + "</positionY>\n\t</Attribute>\n";
}

void SaveXmlComponentVisitor::visit(RelationNode* node)
{
	_xml += "\t<Relation>\n\t\t<Id>" + to_string((long long)node->getID()) + "</Id>\n\t\t<Text>" 
		+ node->getText() + "</Text>\n\t\t<positionX>"
		+ to_string((long long)node->getPosition().x()) + "</positionX>\n\t\t<positionY>"
		+ to_string((long long)node->getPosition().y()) + "</positionY>\n\t</Relation>\n";
}

void SaveXmlComponentVisitor::visit(Connector* node)
{
	_xml += "\t<Connector>\n\t\t<Id>" + to_string((long long)node->getID()) + "</Id>\n\t\t<Text>" 
		+ node->getText() + "</Text>\n\t\t<Source>" 
		+ to_string((long long)node->getConnectionPair().first) + "</Source>\n\t\t<Target>" 
		+ to_string((long long)node->getConnectionPair().second) + "</Target>\n\t</Connector>\n";
}

std::string SaveXmlComponentVisitor::getContentFile()
{
	return XML_HEADER + _xml + XML_FOOTER;
}
