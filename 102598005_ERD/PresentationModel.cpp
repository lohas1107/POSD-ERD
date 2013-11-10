#include "PresentationModel.h"
#include "AddComponentCommand.h"
#include "DeleteComponentCommand.h"
#include "ConnectComponentCommand.h"
#include "Parser.h"
#include <fstream>
#include <string>
#include <direct.h>

const string INPUT_E = "E";
const string INPUT_A = "A";
const string INPUT_R = "R";
const string CARDINALITY_ONE = "1";
const string CARDINALITY_N = "N";
const string STRING_EMPTY = "";
const char SLASH_CHAR = '\\';
const string SLASH = "\\";

using namespace std;

PresentationModel::PresentationModel()
{
}

PresentationModel::PresentationModel(ERModel* erModel)
{
	_erModel = erModel;
}

PresentationModel::~PresentationModel()
{
}

// �ˬd��J�� type
bool PresentationModel::checkInputType(string type)
{
	if (type != INPUT_E && type != INPUT_A && type != INPUT_R)
	{
		return false;
	}
	return true;
}

// �s�W�`�I�R�O
int PresentationModel::addNodeCommand(string type, string name)
{
	_commandManager.execute(new AddComponentCommand(_erModel, make_pair(none, type), name));
	int id = _erModel->getNodeID();
	return id;
}

// ���o node id
int PresentationModel::getNodeID()
{
	return _erModel->getNodeID();
}

// ���o node type
string PresentationModel::getNodeType(int id)
{
	return _erModel->getNodeType(id).second;
}

// ���o node text
string PresentationModel::getNodeText(int id)
{
	return _erModel->getNodeText(id);
}

// ���o�����T
string PresentationModel::getComponentLine(Type type)
{
	return _erModel->getComponentLine(type);
}

// ���o�Ҧ�����
vector<ERComponent*> PresentationModel::getComponents()
{
	return _erModel->getComponents();
}

// �R������
void PresentationModel::deleteComponentCommand(int id)
{
	_commandManager.execute(new DeleteComponentCommand(_erModel, id));
}

// �s���`�I�R�O
void PresentationModel::connectNodeCommand(int firstNodeID, int secondNodeID, string cardinality)
{
	_commandManager.execute(new ConnectComponentCommand(_erModel, firstNodeID, secondNodeID, cardinality));
}

// ���o����ƶq
int PresentationModel::getComponentSize()
{
	return _erModel->getComponentSize();
}

// id �O�_�s�b
bool PresentationModel::isIDExsit(int id)
{
	return _erModel->isIDExsit(id);
}

// �O�_�w�����s��
bool PresentationModel::hasConnection(int firstNodeID, int secondNodeID)
{
	return _erModel->hasConnection(firstNodeID, secondNodeID);
}

// ���o cardinality
string PresentationModel::getCardinality(int cardinality)
{
	if (cardinality == 0)
	{
		return CARDINALITY_ONE;
	}
	else if (cardinality == 1)
	{
		return CARDINALITY_N;
	}
	return STRING_EMPTY;
}

// �O�_�ݭn�߰� cardinality
bool PresentationModel::needAskCardinality(int firstNodeID, int secondNodeID)
{
	return _erModel->isType(firstNodeID, relation) || _erModel->isType(secondNodeID, relation);
}

// �O�_���ͤ��󦨥\
bool PresentationModel::isCreationFail()
{
	return _erModel->isCreationFail();
}

// ��ܳs����T
string PresentationModel::getConnectionLine()
{
	return _erModel->getConnectionLine();
}

// �O�_���Y�� type
bool PresentationModel::isType(int id, Type type)
{
	return _erModel->isType(id, type);
}

// �� id �O�_�� attribute
bool PresentationModel::hasAttribute(int id)
{
	return _erModel->hasAttribute(id);
}

// �O�_�� entity
bool PresentationModel::hasEntity()
{
	return _erModel->hasEntity();
}

// ��ܩ��ݪ� attribues ��T
string PresentationModel::getAttributeLine(int id)
{
	return _erModel->getAttributeLine(id);
}

// �O�_�����ݪ� attributes
bool PresentationModel::isAttribute(int entityID, int attribute)
{
	return _erModel->isAttribute(entityID, attribute);
}

// ���o primary key �r��
string PresentationModel::getPrimaryKey(int entityID)
{
	return _erModel->getPrimaryKeyString(entityID);
}

// �]�w primary key
void PresentationModel::setPrimaryKey(vector<int> primaryKey)
{
	_erModel->setPrimaryKey(primaryKey);
}

// �O�_��� table ��T
bool PresentationModel::displayTableCommand()
{
	vector<pair<int, int>> oneToOne = _erModel->getOneToOne();

	if (oneToOne.size() == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// ���o��� table ��T
string PresentationModel::getTable()
{
	return _erModel->getTable();
}

// Ū���ɮ�
bool PresentationModel::loadFile(string filePath)
{
	return _erModel->loadFile(filePath);
}

// �x�s�ɮ�
bool PresentationModel::saveFile(string filePath)
{
	makeDirectory(filePath);
	ofstream file(filePath);

	if (!file.is_open())
	{
		return false;
		//return "Cannot save file!!";
	}

	file << _erModel->saveComponent();
	file << _erModel->saveConnection();
	file << _erModel->savePrimaryKey();
	file.close();
	return true;
}

// �إ߸�Ƨ�
void PresentationModel::makeDirectory(string filePath)
{
	vector<string> pathList = Parser::split(filePath, SLASH_CHAR);

	string path = pathList[0];
	for (unsigned i = 1; i < pathList.size() - 1; i++)
	{
		path += SLASH + pathList[i];
		_mkdir(path.c_str());
	}
}

// �^�W�@�B
void PresentationModel::undo()
{
	_commandManager.undo();
}

// �O�_�i�H undo
bool PresentationModel::canUndo()
{
	return _commandManager.canUndo();
}

// ��U�@�B
void PresentationModel::redo()
{
	_commandManager.redo();
}

// �O�_�i�H redo
bool PresentationModel::canRedo()
{
	return _commandManager.canRedo();
}

// �y�бƪ�
void PresentationModel::composePosition()
{
	_erModel->composePosition();
}
