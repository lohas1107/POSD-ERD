#include "ERModel.h"
#include "Parser.h"
#include <fstream>

const string STRING_EMPTY = "";
const string COMMA = ",";
const string COMMA_SPACE = ", ";
const char COMMA_CHAR = ',';
const int COMMA_SPACE_AMOUNT = 2;
const int PAIR_AMOUNT = 2;
const string STRING_SPACE = " ";
const string NEXT_LINE = "\n";
const int ATTRIBUTE_X = 300;
const int ATTRIBUTE_OFFSET = 50;
const int ENTITY_X = 500;
const int ENTITY_Y = -10;
const int ENTITY_OFFSET = 100;
const int RELATION_X = 700;
const int ERELATION_Y = 50;
const int RELATION_OFFSET = 100;


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
void ERModel::addComponent(pair<Type, string> type, string text)
{
	ComponentFactory factory; 
	_currentComponent = factory.createComponent(type);
	_currentComponent->setID(_componentID++);
	_currentComponent->setText(text);
	_components.push_back(_currentComponent);
}

// ���J����
void ERModel::insertComponent(int index, ERComponent* component)
{
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
	int index = findIndex(id);
	pair<int, int> connectionPair = ((Connector*)_components[index])->getConnectionPair();
	int first = findIndex(connectionPair.first);
	int second = findIndex(connectionPair.second);

	_components[first]->disconnectTo(connectionPair.second);
	_components[second]->disconnectTo(connectionPair.first);
	_components[index]->disconnectTo(connectionPair.first);
	_components[index]->disconnectTo(connectionPair.second);

	delete _components[index];
	_components.erase(_components.begin() + index);
}

// ���o�ݧR���s�� list
vector<ERComponent*> ERModel::getDeleteList(int id)
{
	vector<ERComponent*> deleteList;
	deleteList.push_back(_components[findIndex(id)]);

	for (unsigned i = 0; i < _components.size(); i++)
	{
		if (isType(_components[i]->getID(), connection) && ((Connector*)_components[i])->isInConnetion(id))
		{
			deleteList.push_back(_components[i]);
		}
	}
	return deleteList;
}

// �R������
void ERModel::deleteComponent(int id)
{
	if (isType(id, connection))
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
		insertComponent(deleteList[i].first, deleteList[i].second);

		if (deleteList[i].second->isType(connection))
		{
			pair<int, int> idPair = ((Connector*)deleteList[i].second)->getConnectionPair();
			insertConnection(deleteList[i].second->getID(), idPair.first, idPair.second);
		}
	}
}

// ���J�s��
void ERModel::insertConnection(int id, int firstID, int secondID)
{
	int index = findIndex(id);
	int first = findIndex(firstID);
	int second = findIndex(secondID);

	_components[first]->connectTo(_components[second]);
	_components[second]->connectTo(_components[first]);
	_components[index]->connectTo(_components[first]);
	_components[index]->connectTo(_components[second]);
}

// �s�W�s��
void ERModel::addConnection(int firstID, int secondID, string cardinality)
{
	if (_components[findIndex(firstID)]->canConnectTo(_components[findIndex(secondID)]))
	{
		addComponent(make_pair(connection, STRING_EMPTY), cardinality);
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
	int index = findIndex(id);
	return _components[index]->isType(type);
}

//���o�ثe�s�W�`�I�� id
int ERModel::getNodeID()
{
	return _currentComponent->getID();
}

//���o�ثe�s�W�`�I�� type
pair<Type, string> ERModel::getNodeType(int id)
{
	return _components[findIndex(id)]->getType();
}

//���o�ثe�s�W�`�I�� text
string ERModel::getNodeText(int id)
{
	return _components[findIndex(id)]->getText();
}

// ���o�Ҧ�����
vector<ERComponent*> ERModel::getComponents()
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
	return ((Node*)_components[findIndex(firstNodeID)])->hasConnection(findIndex(secondNodeID));
}

// ��ܩ��ݪ� attributes
string ERModel::getAttributeLine(int entityID)
{
	return ((EntityNode*)_components[findIndex(entityID)])->getAttributeLine();
}

// �O�_�����ݪ� attribute
bool ERModel::isAttribute(int entityID, int attributeID)
{
	return ((EntityNode*)_components[findIndex(entityID)])->isAttribute(attributeID);
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
	return ((EntityNode*)_components[findIndex(entityID)])->hasAttribute();
}

// �]�w�� primary key
void ERModel::setPrimaryKey(vector<int> primaryKey)
{
	for (unsigned i = 0; i < primaryKey.size(); i++)
	{
		((AttributeNode*)_components[findIndex(primaryKey[i])])->setPrimaryKey(true);
	}
}

// ���o primary key id
vector<int> ERModel::getPrimaryKey(int entityID)
{
	return ((EntityNode*)_components[findIndex(entityID)])->getPrimaryKey();
}

// ���o primary key id �r��
string ERModel::getPrimaryKeyString(int entityID)
{
	vector<int> primaryKey = getPrimaryKey(entityID);
	string primaryKeyString;

	for (unsigned i = 0; i < primaryKey.size(); i++)
	{
		primaryKeyString += COMMA + to_string((long long)primaryKey[i]);
	}

	if (primaryKey.size() > 0)
	{
		primaryKeyString = primaryKeyString.substr(1);
	}

	return primaryKeyString;
}

// ���o primary key �r��
std::string ERModel::getPrimaryKeyText(int entityID)
{
	vector<int> primaryKey = getPrimaryKey(entityID);
	string primaryKeyString;

	for (unsigned i = 0; i < primaryKey.size(); i++)
	{
		primaryKeyString += COMMA_SPACE + _components[findIndex(primaryKey[i])]->getText();
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
		((EntityNode*)_components[findIndex(oneToOne[i].second)])->setForeignKey(getPrimaryKeyText(oneToOne[i].first));
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
	return true;
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

		addComponent(type, text);
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
string ERModel::saveComponent()
{
	string component;
	for (unsigned i = 0; i < _components.size(); i++)
	{
		component += _components[i]->getType().second[0] + COMMA_SPACE + _components[i]->getText() + NEXT_LINE;
	}
	component += NEXT_LINE;
	return component;
}

// �x�s�s��
string ERModel::saveConnection()
{
	string connections;
	for (unsigned i = 0; i < _components.size(); i++)
	{
		if (_components[i]->isType(connection))
		{
			connections += to_string((long long)_components[i]->getID()) + STRING_SPACE + ((Connector*)_components[i])->getConnection() + NEXT_LINE;
		}
	}
	connections += NEXT_LINE;
	return connections;
}

// �x�s primary key
string ERModel::savePrimaryKey()
{
	string primaryKey;
	for (unsigned i = 0; i < _components.size(); i++)
	{
		if (_components[i]->isType(entity) && hasAttribute(_components[i]->getID()))
		{
			primaryKey += to_string((long long)_components[i]->getID()) + STRING_SPACE + getPrimaryKeyString(_components[i]->getID()) + NEXT_LINE;
		}
	}
	return primaryKey;
}

// �Ʈy��
void ERModel::composePosition()
{
	ERPoint position;

	position.x = ATTRIBUTE_X;
	position.y = 0;
	for (unsigned i = 0; i < _components.size(); i++)
	{
		if (_components[i]->isType(attribute))
		{
			position.y += ATTRIBUTE_OFFSET;
			_components[i]->setPosition(position);
		}
	}
	position.x = ENTITY_X;
	position.y = ENTITY_Y;
	for (unsigned i = 0; i < _components.size(); i++)
	{
		if (_components[i]->isType(entity))
		{
			position.y += ENTITY_OFFSET;
			_components[i]->setPosition(position);
		}
	}
	position.x = RELATION_X;
	position.y = ERELATION_Y;
	for (unsigned i = 0; i < _components.size(); i++)
	{
		if (_components[i]->isType(relation))
		{
			position.y += RELATION_OFFSET;
			_components[i]->setPosition(position);
		}
	}
}