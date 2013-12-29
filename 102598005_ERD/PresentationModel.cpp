#include "PresentationModel.h"
#include "AddComponentCommand.h"
#include "DeleteComponentCommand.h"
#include "ConnectComponentCommand.h"
#include "Parser.h"
#include <fstream>
#include <string>
#include <direct.h>
#include "EditTextCommand.h"
#include "SetPrimaryKeyCommand.h"
#include <QDebug>
#include "SaveComponentVisitor.h"
#include "SaveXmlComponentVisitor.h"
#include "DeleteMultipleCommand.h"
#include "PasteCommand.h"
#include "MoveCommand.h"

const string INPUT_E = "E";
const string INPUT_A = "A";
const string INPUT_R = "R";
const string CARDINALITY_ONE = "1";
const string CARDINALITY_N = "N";
const string STRING_EMPTY = "";
const char SLASH_CHAR = '\\';
const string SLASH = "\\";

using namespace std;

PresentationModel::PresentationModel(ERModel* erModel)
{
	_erModel = erModel;
	_isPointerChecked = false;
	_isDeleteEnabled = false;
}

PresentationModel::~PresentationModel()
{
	delete _erModel;
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
void PresentationModel::addNodeCommand(string type, string name, QPointF position)
{
	_commandManager.execute(new AddComponentCommand(_erModel, make_pair(none, type), name, position));
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
	return _erModel->getComponentList();
}

// �R������
void PresentationModel::deleteComponentCommand(int id)
{
	vector<Command*> commands;
	commands.push_back(new DeleteComponentCommand(_erModel, id));
	_commandManager.execute(new DeleteMultipleCommand(_erModel, commands));
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
	return _erModel->isType(firstNodeID, relation) && _erModel->isType(secondNodeID, entity) || 
		_erModel->isType(secondNodeID, relation) && _erModel->isType(firstNodeID, entity);
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

// �O�_�s�b1��1
bool PresentationModel::isOneToOneExist()
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
	ComponentVisitor* visitor;

	if (!file.is_open())
	{
		return false;
	}
	else if (filePath.find(".xml") == ULONG_MAX)
	{
		visitor = new SaveComponentVisitor();
		file << _erModel->saveFile(visitor);
		savePosition(filePath, visitor);
	}
	else
	{
		visitor = new SaveXmlComponentVisitor();
		file << _erModel->saveFile(visitor);
	}

	file.close();
	delete visitor;
	return true;
}

void PresentationModel::savePosition(string filePath, ComponentVisitor* visitor)
{
	ofstream position(filePath.substr(0, filePath.find(".erd")) + ".pos");

	if (position.is_open())
	{
		position << ((SaveComponentVisitor*)visitor)->getPositionFile();
	}

	position.close();
}

// �إ߸�Ƨ�
void PresentationModel::makeDirectory(string filePath)
{
	if (filePath == STRING_EMPTY)
	{
		return;
	}

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

// �]�w�`�I�y��
void PresentationModel::setNodePosition(int id, QPointF position)
{
	_erModel->setNodePosition(id, position);
}

// �q�\model
void PresentationModel::attach(Observer* observer)
{
	_erModel->attach(observer);
}

// �O�_�i�H�s��
bool PresentationModel::isEditable(int index)
{
	ERComponent* component = _erModel->getComponentList()[index];
	if (_erModel->isType(component->getID(), connection))
	{
		pair<int, int> connectionPair = ((Connector*)component)->getConnectionPair();
		return needAskCardinality(connectionPair.first, connectionPair.second);
	}
	return true;
}

// ��s����
void PresentationModel::notify()
{
	_erModel->notify();
}

// �O�_�S������component
bool PresentationModel::isComponentEmpty()
{
	return getComponentSize() == 0;
}

// �O�_�i�H�]�w primary key
bool PresentationModel::canSetPrimaryKey(int id)
{
	return _erModel->canSetPrimaryKey(id);
}

// ���ܧ�s���s���A
void PresentationModel::notifyButtonEnabled()
{
	_erModel->notifyButtonEnabled();
}

// �]�w����`�I
void PresentationModel::setNodeSelected(int id, bool isSelected)
{
	_erModel->setNodeSelected(id, isSelected);
}

// ���o����`�I��id
vector<int> PresentationModel::getSelectedID()
{
	return _erModel->getSelectedID();
}

// ���opointer ���s�O�_���
bool PresentationModel::getPointerButtonChecked()
{
	return _isPointerChecked;
}

// �]�wpointer ���s�O�_���
void PresentationModel::setPointerButtonChecked(bool isChecked)
{
	_isPointerChecked = isChecked;
}

// �O�_��ܧR�����s
bool PresentationModel::isDeleteEnabled()
{
	return _erModel->isDeleteEnabled() && _isPointerChecked;
}

// �M���������
void PresentationModel::clearSelected()
{
	_erModel->clearSelected();
}

// �s���r
void PresentationModel::editText(int index, string text)
{
	string previousText = getComponents()[index]->getText();
	_commandManager.execute(new EditTextCommand(_erModel, index, previousText, text));
}

// �]�w�`�I��primary key'
void PresentationModel::setNodePrimaryKey(int pointID)
{
	_commandManager.execute(new SetPrimaryKeyCommand(_erModel, pointID));
}

void PresentationModel::deleteMultipleCommand()
{
	vector<int> idList = _erModel->getSelectedID();
	vector<Command*> commandList;

	for (unsigned i = 0; i < idList.size(); i++)
	{
		commandList.push_back(new DeleteComponentCommand(_erModel, idList[i]));
	}
	_commandManager.execute(new DeleteMultipleCommand(_erModel, commandList));
}

void PresentationModel::cut()
{
	_erModel->copy();
	deleteMultipleCommand();
}

void PresentationModel::copy()
{
	_erModel->copy();
}

void PresentationModel::paste()
{
	_commandManager.execute(new PasteCommand(_erModel));
}

void PresentationModel::moveCommand(int pointID, QPointF moveFrom, QPointF moveTo)
{
	_commandManager.execute(new MoveCommand(_erModel, pointID, moveFrom, moveTo));
}

string PresentationModel::getGUITable()
{
	if (!isOneToOneExist())
	{
		return "It has no table to display.";
	}
	else
	{
		return _erModel->getGUITable();
	}
}
