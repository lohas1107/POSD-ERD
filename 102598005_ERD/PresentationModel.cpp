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

// 檢查輸入的 type
bool PresentationModel::checkInputType(string type)
{
	if (type != INPUT_E && type != INPUT_A && type != INPUT_R)
	{
		return false;
	}
	return true;
}

// 新增節點命令
void PresentationModel::addNodeCommand(string type, string name, QPointF position)
{
	_commandManager.execute(new AddComponentCommand(_erModel, make_pair(none, type), name, position));
}

// 取得 node id
int PresentationModel::getNodeID()
{
	return _erModel->getNodeID();
}

// 取得 node type
string PresentationModel::getNodeType(int id)
{
	return _erModel->getNodeType(id).second;
}

// 取得 node text
string PresentationModel::getNodeText(int id)
{
	return _erModel->getNodeText(id);
}

// 取得元件資訊
string PresentationModel::getComponentLine(Type type)
{
	return _erModel->getComponentLine(type);
}

// 取得所有元件
vector<ERComponent*> PresentationModel::getComponents()
{
	return _erModel->getComponentList();
}

// 刪除元件
void PresentationModel::deleteComponentCommand(int id)
{
	vector<Command*> commands;
	commands.push_back(new DeleteComponentCommand(_erModel, id));
	_commandManager.execute(new DeleteMultipleCommand(_erModel, commands));
}

// 連接節點命令
void PresentationModel::connectNodeCommand(int firstNodeID, int secondNodeID, string cardinality)
{
	_commandManager.execute(new ConnectComponentCommand(_erModel, firstNodeID, secondNodeID, cardinality));
}

// 取得元件數量
int PresentationModel::getComponentSize()
{
	return _erModel->getComponentSize();
}

// id 是否存在
bool PresentationModel::isIDExsit(int id)
{
	return _erModel->isIDExsit(id);
}

// 是否已有此連結
bool PresentationModel::hasConnection(int firstNodeID, int secondNodeID)
{
	return _erModel->hasConnection(firstNodeID, secondNodeID);
}

// 取得 cardinality
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

// 是否需要詢問 cardinality
bool PresentationModel::needAskCardinality(int firstNodeID, int secondNodeID)
{
	return _erModel->isType(firstNodeID, relation) && _erModel->isType(secondNodeID, entity) || 
		_erModel->isType(secondNodeID, relation) && _erModel->isType(firstNodeID, entity);
}

// 是否產生元件成功
bool PresentationModel::isCreationFail()
{
	return _erModel->isCreationFail();
}

// 顯示連結資訊
string PresentationModel::getConnectionLine()
{
	return _erModel->getConnectionLine();
}

// 是否為某種 type
bool PresentationModel::isType(int id, Type type)
{
	return _erModel->isType(id, type);
}

// 此 id 是否有 attribute
bool PresentationModel::hasAttribute(int id)
{
	return _erModel->hasAttribute(id);
}

// 是否有 entity
bool PresentationModel::hasEntity()
{
	return _erModel->hasEntity();
}

// 顯示所屬的 attribues 資訊
string PresentationModel::getAttributeLine(int id)
{
	return _erModel->getAttributeLine(id);
}

// 是否為所屬的 attributes
bool PresentationModel::isAttribute(int entityID, int attribute)
{
	return _erModel->isAttribute(entityID, attribute);
}

// 取得 primary key 字串
string PresentationModel::getPrimaryKey(int entityID)
{
	return _erModel->getPrimaryKeyString(entityID);
}

// 設定 primary key
void PresentationModel::setPrimaryKey(vector<int> primaryKey)
{
	_erModel->setPrimaryKey(primaryKey);
}

// 是否存在1對1
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

// 取得顯示 table 資訊
string PresentationModel::getTable()
{
	return _erModel->getTable();
}

// 讀取檔案
bool PresentationModel::loadFile(string filePath)
{
	return _erModel->loadFile(filePath);
}

// 儲存檔案
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

// 建立資料夾
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

// 回上一步
void PresentationModel::undo()
{
	_commandManager.undo();
}

// 是否可以 undo
bool PresentationModel::canUndo()
{
	return _commandManager.canUndo();
}

// 到下一步
void PresentationModel::redo()
{
	_commandManager.redo();
}

// 是否可以 redo
bool PresentationModel::canRedo()
{
	return _commandManager.canRedo();
}

// 座標排版
void PresentationModel::composePosition()
{
	_erModel->composePosition();
}

// 設定節點座標
void PresentationModel::setNodePosition(int id, QPointF position)
{
	_erModel->setNodePosition(id, position);
}

// 訂閱model
void PresentationModel::attach(Observer* observer)
{
	_erModel->attach(observer);
}

// 是否可以編輯
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

// 更新提醒
void PresentationModel::notify()
{
	_erModel->notify();
}

// 是否沒有任何component
bool PresentationModel::isComponentEmpty()
{
	return getComponentSize() == 0;
}

// 是否可以設定 primary key
bool PresentationModel::canSetPrimaryKey(int id)
{
	return _erModel->canSetPrimaryKey(id);
}

// 提示更新按鈕狀態
void PresentationModel::notifyButtonEnabled()
{
	_erModel->notifyButtonEnabled();
}

// 設定選取節點
void PresentationModel::setNodeSelected(int id, bool isSelected)
{
	_erModel->setNodeSelected(id, isSelected);
}

// 取得選取節點的id
vector<int> PresentationModel::getSelectedID()
{
	return _erModel->getSelectedID();
}

// 取得pointer 按鈕是否選取
bool PresentationModel::getPointerButtonChecked()
{
	return _isPointerChecked;
}

// 設定pointer 按鈕是否選取
void PresentationModel::setPointerButtonChecked(bool isChecked)
{
	_isPointerChecked = isChecked;
}

// 是否顯示刪除按鈕
bool PresentationModel::isDeleteEnabled()
{
	return _erModel->isDeleteEnabled() && _isPointerChecked;
}

// 清除選取項目
void PresentationModel::clearSelected()
{
	_erModel->clearSelected();
}

// 編輯文字
void PresentationModel::editText(int index, string text)
{
	string previousText = getComponents()[index]->getText();
	_commandManager.execute(new EditTextCommand(_erModel, index, previousText, text));
}

// 設定節點為primary key'
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
