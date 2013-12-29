#include "ERModel.h"
#include "Parser.h"
#include <fstream>
#include "SaveComponentVisitor.h"
#include "SaveXmlComponentVisitor.h"
#include <QDebug>

const string STRING_EMPTY = "";
const string COMMA = ",";
const string COMMA_SPACE = ", ";
const char COMMA_CHAR = ',';
const int COMMA_SPACE_AMOUNT = 2;
const int PAIR_AMOUNT = 2;
const string STRING_SPACE = " ";
const string NEXT_LINE = "\n";
const float ATTRIBUTE_X = 300;
const float ATTRIBUTE_OFFSET = 50;
const float ENTITY_X = 500;
const float ENTITY_Y = -10;
const float ENTITY_OFFSET = 100;
const float RELATION_X = 700;
const float ERELATION_Y = 50;
const float RELATION_OFFSET = 100;
const string PRIMARY_KEY_IMAGE = "<img src=\"Resources/primary_key.png\" width=\"20\" height=\"20\">";
const string FOREIGN_KEY_IMAGE = "<img src=\"Resources/foreign_key.png\" width=\"20\" height=\"20\">";

ERModel::ERModel()
{
	initialize();
}

ERModel::~ERModel()
{
	clearComponent();
}

// ��l��
void ERModel::initialize()
{
	_componentID = 0;
	_currentComponent = NULL;
}

// �M���`�I
void ERModel::clearComponent()
{
	while (!_components.empty())
	{
		ERComponent* component = _components.back();
		_components.pop_back();
		delete component;
	}
}

//�s�W�`�I
void ERModel::addComponent(pair<Type, string> type, string text, QPointF position)
{
	ComponentFactory factory; 
	_currentComponent = factory.createComponent(type);
	_currentComponent->setID(_componentID++);
	_currentComponent->setText(text);
	_currentComponent->setPosition(position);
	_components.push_back(_currentComponent);
}

// ���J����
void ERModel::insertComponent(int index, ERComponent* component)
{
	int count = 0;
	while (count < _components.size() && _components[count]->getID() < component->getID())
	{
		index = count;
		count++;
	}
	index = count;

	_components.insert(_components.begin() + index, component->clone());
}

// �j�M�� id �� index
int ERModel::findIndex(int id)
{
	for (unsigned i = 0; i < _components.size(); i++)
	{
		if (_components[i]->getID() == id)
		{
			return i;
		}
	}

	return INT_MIN;
}

// �R���̫�@�Ӥ���
void ERModel::deleteLastComponent()
{
	_componentID--;
	if (isType(_components.back()->getID(), connection))
	{
		deleteConnection(_components.back()->getID());
		return;
	}

	delete _components.back();
	_components.erase(_components.begin() + _components.size() - 1);
}

// �R���s��
void ERModel::deleteConnection(int id)
{
	pair<int, int> connectionPair = ((Connector*)getComponent(id))->getConnectionPair();

	getComponent(connectionPair.first)->disconnectTo(connectionPair.second);
	getComponent(connectionPair.second)->disconnectTo(connectionPair.first);
	getComponent(id)->disconnectTo(connectionPair.first);
	getComponent(id)->disconnectTo(connectionPair.second);

	int index = findIndex(id);
	delete getComponent(id);
	_components.erase(_components.begin() + index);
}

// ���o�ݧR���s�� list
vector<ERComponent*> ERModel::getDeleteList(int id)
{
	vector<ERComponent*> deleteList;
	deleteList.push_back(getComponent(id));

	for (unsigned i = 0; i < _components.size(); i++)
	{
		if (isType(_components[i]->getID(), connection) && _components[i]->hasConnection(id))
		{
			deleteList.push_back(_components[i]);
		}
	}
	return deleteList;
}

// �R������
void ERModel::deleteComponent(int id)
{
	if (isIDExsit(id) && isType(id, connection))
	{
		deleteConnection(id);
	}
	else
	{
		vector<ERComponent*> unwanted = getDeleteList(id);
		for (unsigned i = 1; i < unwanted.size(); i++)
		{
			deleteConnection(unwanted[i]->getID());
		}

		int index = findIndex(id);
		delete _components[index];
		_components.erase(_components.begin() + index);
	}
}

// �_��R������
void ERModel::revertComponent(vector<pair<int, ERComponent*>> deleteList)
{
	for (unsigned i = 0; i < deleteList.size(); i++)
	{
		if (deleteList[i].second->isType(connection))
		{
			_buffer.push_back(deleteList[i]);
		} 
		else
		{
			insertComponent(deleteList[i].first, deleteList[i].second);
		}


		//if (deleteList[i].second->isType(connection))
		//{
		//	pair<int, int> idPair = ((Connector*)deleteList[i].second)->getConnectionPair();
		//	getComponent(deleteList[i].second->getID())->disconnectTo(idPair.first);
		//	getComponent(deleteList[i].second->getID())->disconnectTo(idPair.second);
		//	insertConnection(deleteList[i].second->getID(), idPair.first, idPair.second);
		//}
	}
}

void ERModel::revertConnector()
{
	for (unsigned i = 0; i < _buffer.size(); i++)
	{
		if (!isIDExsit(_buffer[i].second->getID()))
		{
			insertComponent(_buffer[i].first, _buffer[i].second);

			pair<int, int> idPair = ((Connector*)_buffer[i].second)->getConnectionPair();
			getComponent(_buffer[i].second->getID())->disconnectTo(idPair.first);
			getComponent(_buffer[i].second->getID())->disconnectTo(idPair.second);
			insertConnection(_buffer[i].second->getID(), idPair.first, idPair.second);
		}
	}
	_buffer.clear();
}

// ���J�s��
void ERModel::insertConnection(int id, int firstID, int secondID)
{
	getComponent(firstID)->connectTo(getComponent(secondID));
	getComponent(secondID)->connectTo(getComponent(firstID));
	getComponent(id)->connectTo(getComponent(firstID));
	getComponent(id)->connectTo(getComponent(secondID));
}

// �s�W�s��
void ERModel::addConnection(int firstID, int secondID, string cardinality)
{
	if (getComponent(firstID)->canConnectTo(getComponent(secondID)) && getComponent(secondID)->canConnectTo(getComponent(firstID)))
	{
		addComponent(make_pair(connection, STRING_EMPTY), cardinality, QPointF(0, 0));
		insertConnection(getNodeID(), firstID, secondID);
		_creationFail = false;
	}
	else
	{
		_creationFail = true;
	}
}

// �O�_�إ߸`�I����
bool ERModel::isCreationFail()
{
	return _creationFail;
}

// id �O�_�s�b
bool ERModel::isIDExsit(int id)
{
	for (unsigned i = 0; i < _components.size(); i++)
	{
		if (_components[i]->getID() == id)
		{
			return true;
		}		
	}

	return false;
}

// �O�_���Y type
bool ERModel::isType(int id, Type type)
{
	return getComponent(id)->isType(type);
}

//���o�ثe�s�W�`�I�� id
int ERModel::getNodeID()
{
	return _currentComponent->getID();
}

//���o�ثe�s�W�`�I�� type
pair<Type, string> ERModel::getNodeType(int id)
{
	return getComponent(id)->getType();
}

//���o�ثe�s�W�`�I�� text
string ERModel::getNodeText(int id)
{
	return getComponent(id)->getText();
}

// ���o�Yid������
ERComponent* ERModel::getComponent(int id)
{
	return _components[findIndex(id)];
}

// ���o�Ҧ�����
vector<ERComponent*> ERModel::getComponentList()
{
	return _components;
}

// ���ocomponent size
int ERModel::getComponentSize()
{
	return _components.size();
}

// ��ܤ����T
string ERModel::getComponentLine(Type type)
{
	string lines = STRING_EMPTY;

	for(unsigned i = 0; i < _components.size(); i++)
	{
		lines += _components[i]->getData(type);
	}

	return lines;
}

// ���o��ܳs����T
string ERModel::getConnectionLine()
{
	string line = STRING_EMPTY;

	for (unsigned i = 0; i < _components.size(); i++)
	{
		if (_components[i]->isType(connection))
		{
			line += ((Connector*)_components[i])->getConnectionLine();
		}
	}

	return line;
}

// �O�_���o�ճs��
bool ERModel::hasConnection(int firstNodeID, int secondNodeID)
{
	return getComponent(firstNodeID)->hasConnection(secondNodeID);
}

// ��ܩ��ݪ� attributes
string ERModel::getAttributeLine(int entityID)
{
	return ((EntityNode*)getComponent(entityID))->getAttributeLine();
}

// �O�_�����ݪ� attribute
bool ERModel::isAttribute(int entityID, int attributeID)
{
	return ((EntityNode*)getComponent(entityID))->isAttribute(attributeID);
}

// �O�_������ Entity
bool ERModel::hasEntity()
{
	bool hasEntity = false;
	for (unsigned i = 0; i < _components.size(); i++)
	{
		if (_components[i]->isType(entity))
		{
			hasEntity = true;
		}
	}
	return hasEntity;
}

// �O�_������ attribute
bool ERModel::hasAttribute(int entityID)
{
	return ((EntityNode*)getComponent(entityID))->hasAttribute();
}

// �]�w�� primary key
void ERModel::setPrimaryKey(vector<int> primaryKey)
{
	for (unsigned i = 0; i < primaryKey.size(); i++)
	{
		((AttributeNode*)getComponent(primaryKey[i]))->setPrimaryKey(true);
	}
}

// ���o primary key id
vector<int> ERModel::getPrimaryKey(int entityID)
{
	return ((EntityNode*)getComponent(entityID))->getPrimaryKey();
}

// ���o primary key id �r��
string ERModel::getPrimaryKeyString(int entityID)
{
	//vector<int> primaryKey = getPrimaryKey(entityID);
	//string primaryKeyString;

	//for (unsigned i = 0; i < primaryKey.size(); i++)
	//{
	//	primaryKeyString += COMMA + to_string((long long)primaryKey[i]);
	//}

	//if (primaryKey.size() > 0)
	//{
	//	primaryKeyString = primaryKeyString.substr(1);
	//}

	//return primaryKeyString;
	return ((EntityNode*)getComponent(entityID))->getPrimaryKeyString();
}

// ���o primary key �r��
std::string ERModel::getPrimaryKeyText(int entityID)
{
	vector<int> primaryKey = getPrimaryKey(entityID);
	string primaryKeyString;

	for (unsigned i = 0; i < primaryKey.size(); i++)
	{
		primaryKeyString += COMMA_SPACE + getComponent(primaryKey[i])->getText();
	}

	if (primaryKey.size() > 0)
	{
		primaryKeyString = primaryKeyString.substr(COMMA_SPACE_AMOUNT);
	}

	return primaryKeyString;
}

// ��� table ��T
string ERModel::getTable()
{
	string table = STRING_EMPTY;
	vector<pair<int, int>> oneToOne = getOneToOne();

	for (unsigned i = 0; i < oneToOne.size(); i++)
	{
		((EntityNode*)getComponent(oneToOne[i].second))->setForeignKey(getPrimaryKeyText(oneToOne[i].first));
	}

	for (unsigned i = 0; i < _components.size(); i++)
	{
		if (_components[i]->isType(entity))
		{
			table += ((EntityNode*)_components[i])->getTable();
		}
	}

	return table;
}

// ���o�@��@
vector<pair<int, int>> ERModel::getOneToOne()
{
	vector<pair<int, int>> oneToOne;

	for (unsigned i = 0; i < _components.size(); i++)
	{
		if (_components[i]->isType(relation))
		{
			vector<pair<int, int>> relationPair = ((RelationNode*)_components[i])->getRelationPair();

			if (relationPair.size() == PAIR_AMOUNT && checkOneToOne(relationPair[0]) && checkOneToOne(relationPair[1]))
			{
				oneToOne.push_back(make_pair(relationPair[0].first, relationPair[1].first));
			}
		}
	}

	return oneToOne;
}

// �ˬd�O�_���@��@
bool ERModel::checkOneToOne(pair<int, int> relationPair)
{
	for (unsigned i = 0; i < _components.size(); i++)
	{
		if (_components[i]->isType(connection))
		{
			if (((Connector*)_components[i])->checkOneToOne(relationPair))
			{
				return true;
			}
		}
	}

	return false;
}

// Ū���ɮ�
bool ERModel::loadFile(string filePath)
{
	ifstream file(filePath);
	if (!file.is_open())
	{
		return false;
	}

	clearComponent();
	initialize();
	vector<vector<string>> content = getFileContent(file);
	loadComponent(content[0]);
	loadConnection(content[1]);
	loadPrimaryKey(content[PAIR_AMOUNT]);

	ifstream positionFile(filePath.substr(0, filePath.find(".erd")) + ".pos");
	if (!positionFile.is_open())
	{
		composePosition();
	}
	else
	{
		loadPosition(getFilePosition(positionFile));
	}

	return true;
}

vector<QPointF> ERModel::getFilePosition(ifstream &file)
{
	string line;
	Parser parser;
	vector<QPointF> positionList;

	while (getline(file, line))
	{
		if (line != STRING_EMPTY)
		{
			vector<int> position = parser.changeToVectorInt(parser.split(line, ' '));
			QPointF point = QPointF(position[0], position[1]);
			positionList.push_back(point);
		}
	}

	file.close();
	return positionList;
}

void ERModel::loadPosition(vector<QPointF> positionList)
{
	int j = 0;
	for (unsigned i = 0; i < _components.size(); i++)
	{
		if (!_components[i]->isType(connection))
		{
			_components[i]->setPosition(positionList[j]);	
			j++;
		}
	}
}

// ���o�ɮפ��q���e
vector<vector<string>> ERModel::getFileContent(ifstream &file)
{	
	string line;
	vector<string> part;
	vector<vector<string>> contents;

	while (getline(file, line))
	{
		if (line != STRING_EMPTY)
		{
			part.push_back(line);
			continue;
		}
		contents.push_back(part);
		part.clear();
	}

	contents.push_back(part);
	file.close();
	return contents;
}

// Ū������
void ERModel::loadComponent(vector<string> content)
{
	for (unsigned i = 0; i < content.size(); i++)
	{
		string line = content[i];
		pair<Type, string> type = make_pair(none, line.substr(0, line.find_first_of(STRING_SPACE) - 1));
		string text;

		if (line.length() > 1)
		{
			text = line.substr(line.find_last_of(STRING_SPACE) + 1);
		}

		addComponent(type, text, QPointF(0, 0));
	}
}

// Ū���s��
void ERModel::loadConnection(vector<string> content)
{
	for (unsigned i = 0; i < content.size(); i++)
	{
		string line = content[i];
		int id = atoi(line.substr(0, line.find_first_of(STRING_SPACE)).c_str());
		string ids = line.substr(line.find_last_of(STRING_SPACE) + 1);
		vector<int> connections = Parser::changeToVectorInt(Parser::split(ids, COMMA_CHAR));

		insertConnection(id, connections[0], connections[1]);
	}
}

// Ū�� primary key
void ERModel::loadPrimaryKey(vector<string> content)
{
	for (unsigned i = 0; i < content.size(); i++)
	{
		string line = content[i];
		string ids = line.substr(line.find_last_of(STRING_SPACE) + 1);
		vector<int> primaryKey = Parser::changeToVectorInt(Parser::split(ids, COMMA_CHAR));

		setPrimaryKey(primaryKey);
	}

}

// �x�s����
//string ERModel::saveComponent()
//{
//	string component;
//	for (unsigned i = 0; i < _components.size(); i++)
//	{
//		component += _components[i]->getType().second[0] + COMMA_SPACE + _components[i]->getText() + NEXT_LINE;
//	}
//	component += NEXT_LINE;
//	return component;
//}
//
//// �x�s�s��
//string ERModel::saveConnection()
//{
//	string connections;
//	for (unsigned i = 0; i < _components.size(); i++)
//	{
//		if (_components[i]->isType(connection))
//		{
//			connections += to_string((long long)_components[i]->getID()) + STRING_SPACE + ((Connector*)_components[i])->getConnection() + NEXT_LINE;
//		}
//	}
//	connections += NEXT_LINE;
//	return connections;
//}
//
//// �x�s primary key
//string ERModel::savePrimaryKey()
//{
//	string primaryKey;
//	for (unsigned i = 0; i < _components.size(); i++)
//	{
//		if (_components[i]->isType(entity) && hasAttribute(_components[i]->getID()))
//		{
//			primaryKey += to_string((long long)_components[i]->getID()) + STRING_SPACE + getPrimaryKeyString(_components[i]->getID()) + NEXT_LINE;
//		}
//	}
//	return primaryKey;
//}

// �x�s�ɮ�
string ERModel::saveFile(ComponentVisitor* visitor)
{
	for (unsigned i = 0; i < _components.size(); i++)
	{
		_components[i]->accept(visitor);
	}

	return visitor->getContentFile();
}

// �Ʈy��
void ERModel::composePosition()
{
	QPointF attributePosition(ATTRIBUTE_X, 0);
	QPointF entityPosition(ENTITY_X, ENTITY_Y);
	QPointF relationPosition(RELATION_X, ERELATION_Y);

	for (unsigned i = 0; i < _components.size(); i++)
	{
		if (_components[i]->isType(attribute))
		{
			attributePosition += QPointF(0, ATTRIBUTE_OFFSET);
			_components[i]->setPosition(attributePosition);
		}
		else if (_components[i]->isType(entity))
		{
			entityPosition += QPointF(0, ENTITY_OFFSET);
			_components[i]->setPosition(entityPosition);
		}
		else if (_components[i]->isType(relation))
		{
			relationPosition += QPointF(0, RELATION_OFFSET);
			_components[i]->setPosition(relationPosition);
		}
	}
}

// �]�w�`�I�y��
void ERModel::setNodePosition(int id, QPointF position)
{
	getComponent(id)->setPosition(position);
}

// �O�_�i�H�]�w�� primary key
bool ERModel::canSetPrimaryKey(int id)
{
	if (getComponent(id)->isType(attribute) && !getComponent(id)->getConnection().empty())
	{
		return true;
	}
	return false;
}

// �]�w����`�I
void ERModel::setNodeSelected(int id, bool isSelected)
{
	getComponent(id)->setSelected(isSelected);
}

// ���o����`�I��id
vector<int> ERModel::getSelectedID()
{
	vector<int> idList;
	for (unsigned i = 0; i < _components.size(); i++)
	{
		if (_components[i]->isSelected())
		//{
		//	return _components[i]->getID();
		//}
		{
			idList.push_back(_components[i]->getID());
		}
	}
	//return INT_MIN;
	return idList;
}

// �O�_�i�H��ܧR�����s
bool ERModel::isDeleteEnabled()
{
	if (getSelectedID().size() > 0)
	{
		return true;
	}
	return false;
}

// �M�����
void ERModel::clearSelected()
{
	for (unsigned i = 0; i < _components.size(); i++)
	{
		_components[i]->setSelected(false);
	}
}

// �]�w�`�I��r
void ERModel::setNodeText(int index, string text)
{
	_components[index]->setText(text);
}

// �]�w�`�I�� primary key
void ERModel::setNodePrimaryKey(int id, bool isPrimaryKey)
{
	((AttributeNode*)getComponent(id))->setPrimaryKey(isPrimaryKey);
}

void ERModel::deleteMultiple(vector<int> deleteList)
{
	for (unsigned i = 0; i < deleteList.size(); i++)
	{
		this->deleteComponent(deleteList[i]);
	}
}

void ERModel::copy()
{
	vector<int> idList = getSelectedID();

	_clipboard.clear();
	for (unsigned i = 0; i < idList.size(); i++)
	{
		_clipboard.push_back(getComponent(idList[i])->clone());
	}
}

void ERModel::paste()
{
	vector<pair<int, int>> idTable;
	_copyCount = 0;

	for (unsigned i = 0; i < _clipboard.size(); i++)
	{
		if (!_clipboard[i]->isType(connection))
		{
			ERComponent* copyClone = _clipboard[i]->clone();
			int oldID = copyClone->getID();
			int newID = _componentID++;
			idTable.push_back(make_pair(oldID, newID));
			copyClone->setID(newID);
			copyClone->setPosition(copyClone->getPosition() + QPointF(5, 5));
			insertComponent(_components.size(), copyClone);
			_copyCount++;
		}
	}

	pasteConnection(idTable);
}

void ERModel::pasteConnection(vector<pair<int, int>> idTable)
{
	for (unsigned i = 0; i < _clipboard.size(); i++)
	{
		if (_clipboard[i]->isType(connection))
		{
			pair<int, int> idPair = ((Connector*)_clipboard[i])->getConnectionPair();
			pair<int, int> pastedID = getPastedID(idTable, idPair);

			if (pastedID.first != INT_MIN && pastedID.second != INT_MIN)
			{
				int newID = _componentID++;
				_clipboard[i]->setID(newID);
				insertComponent(_components.size(), _clipboard[i]);
				getComponent(_clipboard[i]->getID())->disconnectTo(idPair.first);
				getComponent(_clipboard[i]->getID())->disconnectTo(idPair.second);
				insertConnection(_clipboard[i]->getID(), pastedID.first, pastedID.second);
				_copyCount++;
			}
		}
	}
}

pair<int, int> ERModel::getPastedID(vector<pair<int, int>> idTable, pair<int, int> idPair)
{
	pair<int, int> pastedID = make_pair(INT_MIN, INT_MIN);

	for (unsigned i = 0; i < idTable.size(); i++)
	{
		if (idTable[i].first == idPair.first)
		{
			pastedID.first = idTable[i].second;
		}
		else if (idTable[i].first == idPair.second)
		{
			pastedID.second = idTable[i].second;
		}
	}

	return pastedID;
}

void ERModel::unPaste()
{
	for (unsigned i = 0; i < _copyCount; i++)
	{
		deleteLastComponent();
	}
}

string ERModel::getGUITable()
{
	string table = STRING_EMPTY;
	vector<pair<int, int>> oneToOne = getOneToOne();
	vector<pair<int, string>> tableLine;
	for (unsigned i = 0; i < oneToOne.size(); i++)
	{
		if (getTableLine(oneToOne[i].first, tableLine) == INT_MIN)
		{
			tableLine.push_back(make_pair(oneToOne[i].first, getGUIPrimaryKey(oneToOne[i].first)));
		}
		if (getTableLine(oneToOne[i].second, tableLine) == INT_MIN)
		{
			tableLine.push_back(make_pair(oneToOne[i].second, getGUIPrimaryKey(oneToOne[i].second) + getGUIForeignKey(oneToOne[i].first)));
		}
		else
		{
			tableLine[getTableLine(oneToOne[i].second, tableLine)].second += getGUIForeignKey(oneToOne[i].first);
		}
	}
	for (unsigned i = 0; i < tableLine.size(); i++)
	{
		table += ((EntityNode*)getComponent(tableLine[i].first))->getText() + "<table border=\"1\"><tr>" + tableLine[i].second + "</tr></table><br><br>";
	}
	return table;
}

int ERModel::getTableLine(int id, vector<pair<int, string>> tableLine)
{
	for (unsigned i = 0; i < tableLine.size(); i++)
	{
		if (tableLine[i].first == id)
		{
			return i;
		}
	}
	return INT_MIN;
}

std::string ERModel::getGUIPrimaryKey(int id)
{
	string primaryKey = STRING_EMPTY;
	vector<ERComponent*> attributes = ((EntityNode*)getComponent(id))->getAttributes();

	for (unsigned i = 0; i < attributes.size(); i++)
	{
		if (((AttributeNode*)attributes[i])->isPrimaryKey())
		{
			primaryKey += "<td>" + PRIMARY_KEY_IMAGE + attributes[i]->getText() + "</td>";
		}
		else
		{
			primaryKey += "<td>" + attributes[i]->getText() + "</td>";
		}
	}
	return primaryKey;
}

std::string ERModel::getGUIForeignKey(int id)
{
	string foreignKey = STRING_EMPTY;
	vector<ERComponent*> attributes = ((EntityNode*)getComponent(id))->getAttributes();

	for (unsigned i = 0; i < attributes.size(); i++)
	{
		if (((AttributeNode*)attributes[i])->isPrimaryKey())
		{
			foreignKey += "<td>" + FOREIGN_KEY_IMAGE + attributes[i]->getText() + "</td>";
		}
	}

	return foreignKey;
}

bool ERModel::canPaste()
{
	return !_clipboard.empty();
}
