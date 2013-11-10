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
int PresentationModel::addNodeCommand(string type, string name)
{
	_commandManager.execute(new AddComponentCommand(_erModel, make_pair(none, type), name));
	int id = _erModel->getNodeID();
	return id;
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
	return _erModel->getComponents();
}

// 刪除元件
void PresentationModel::deleteComponentCommand(int id)
{
	_commandManager.execute(new DeleteComponentCommand(_erModel, id));
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
	return _erModel->isType(firstNodeID, relation) || _erModel->isType(secondNodeID, relation);
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

// 是否顯示 table 資訊
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

// 建立資料夾
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
