#include "gtest/gtest.h"
#include "ERModel.h"
#include <vector>

using namespace std;

class ERModelTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		_model._components.push_back(new EntityNode(0, "PC"));
		_model._components.push_back(new AttributeNode(1, "Name"));
		_model._components.push_back(new RelationNode(2, "Has"));
		_model._components.push_back(new Connector(3, ""));
		_model._components.push_back(new Connector(4, "1"));
	}

	// 讀取連結資料
	void loadConnection()
	{
		vector<string> content;
		content.push_back("3 0,1");
		content.push_back("4 0,2");
		_model.loadConnection(content);
	}

	// 設定 primary key 資料
	void setPrimaryKey(int id)
	{
		vector<int> primaryKey;
		primaryKey.push_back(id);
		_model.setPrimaryKey(primaryKey);
	}

	// 加入一對一資料
	void addOneToOne()
	{
		_model._componentID = 5;
		_model.addComponent(make_pair(entity, ""), "Person", QPointF(0, 0));
		_model.addComponent(make_pair(attribute, ""), "ID", QPointF(0, 0));
		_model.addConnection(2, 5, "1");
		_model.addConnection(5, 6, "");
		setPrimaryKey(1);
		setPrimaryKey(6);
	}
	ERModel _model;
};

TEST_F(ERModelTest, clearComponent)
{
	_model.clearComponent();
	EXPECT_EQ(0, _model.getComponentSize());
}

// 測試新增元件
TEST_F(ERModelTest, addComponent)
{
	ERComponent* component;
	for (unsigned i = 0; i < 4; i++)
	{
		component = _model._components[i];
		_model._components.erase(_model._components.begin() + i);
		_model.addComponent(component->getType(), component->getText(), QPointF(0, 0));
		EXPECT_EQ(i, _model._components.back()->getID());
		EXPECT_EQ(component->getType(), _model._components.back()->getType());
		EXPECT_EQ(component->getText(), _model._components.back()->getText());
	}
}

// 測試插入元件
TEST_F(ERModelTest, insertComponent)
{
	for (unsigned i = 0; i < 4; i++)
	{
		_model.insertComponent(i, _model._components[i]);
		EXPECT_EQ(_model._components[i + 1]->getID(), _model._components[i]->getID());
		EXPECT_EQ(_model._components[i + 1]->getType(), _model._components[i]->getType());
		EXPECT_EQ(_model._components[i + 1]->getText(), _model._components[i]->getText());
	}
}

// 測試尋找 index
TEST_F(ERModelTest, findIndex)
{
	for (unsigned i = 0; i < _model._components.size(); i++)
	{
		EXPECT_EQ(i, _model.findIndex(_model._components[i]->getID()));
	}
	EXPECT_EQ(INT_MIN, _model.findIndex(-1));
	EXPECT_EQ(INT_MIN, _model.findIndex(6));
}

// 測試刪除最後一個元件
TEST_F(ERModelTest, deleteLastComponent)
{
	loadConnection();
	_model._componentID = 4;
	_model.deleteLastComponent();
	EXPECT_EQ(3, _model._componentID);
	EXPECT_EQ(4, _model.getComponentSize());
	_model.deleteLastComponent();
	_model.deleteLastComponent();
	EXPECT_EQ(1, _model._componentID);
	EXPECT_EQ(2, _model.getComponentSize());
}

// 測試刪除連結
TEST_F(ERModelTest, deleteConnection)
{
	loadConnection();
	_model.deleteConnection(3);
	EXPECT_EQ(4, _model.getComponentSize());
	_model.deleteConnection(4);
	EXPECT_EQ(3, _model.getComponentSize());
}

// 測試取得刪除資料
TEST_F(ERModelTest, getDeleteList)
{
	loadConnection();
	vector<ERComponent*> deleteList = _model.getDeleteList(1);
	EXPECT_EQ(1, deleteList[0]->getID());
	EXPECT_EQ(3, deleteList[1]->getID());
	deleteList = _model.getDeleteList(4);
	EXPECT_EQ(4, deleteList[0]->getID());
}

// 測試刪除元件
TEST_F(ERModelTest, deleteComponent)
{
	loadConnection();
	_model.deleteComponent(1);
	EXPECT_EQ(3, _model.getComponentSize());
	EXPECT_EQ(0, _model._components[0]->getID());
	EXPECT_EQ(2, _model._components[1]->getID());
	EXPECT_EQ(4, _model._components[2]->getID());
	_model.deleteComponent(4);
	EXPECT_EQ(2, _model.getComponentSize());
	EXPECT_EQ(0, _model._components[0]->getID());
	EXPECT_EQ(2, _model._components[1]->getID());
	_model.deleteComponent(0);
	EXPECT_EQ(1, _model.getComponentSize());
	EXPECT_EQ(2, _model._components[0]->getID());
}

// 測試回復元件
TEST_F(ERModelTest, revertComponent)
{
	loadConnection();
	vector<pair<int, ERComponent*>> deleteList;
	ERComponent* component = _model._components[1]->clone();
	deleteList.push_back(make_pair(1, component));
	component = _model._components[3]->clone();
	deleteList.push_back(make_pair(3, component));

	delete _model._components[1];
	_model._components.erase(_model._components.begin() + 1);
	delete _model._components[3];
	_model._components.erase(_model._components.begin() + 3);
	EXPECT_EQ(3, _model.getComponentSize());

	_model.revertComponent(deleteList);
	_model.revertConnector();
	EXPECT_EQ(4, _model.getComponentSize());
	EXPECT_EQ(1, _model._components[1]->getID());
	EXPECT_EQ(attribute, _model._components[1]->getType().first);
	EXPECT_EQ("Name", _model._components[1]->getText());
	EXPECT_EQ(3, _model._components[3]->getID());
	EXPECT_EQ(connection, _model._components[3]->getType().first);
	EXPECT_EQ("", _model._components[3]->getText());
}

// 測試插入連結
TEST_F(ERModelTest, insertConnection)
{
	_model.insertConnection(3, 0, 1);
	EXPECT_EQ(2, _model._components[3]->getConnection().size());
	EXPECT_EQ(0, _model._components[3]->getConnection()[0]->getID());
	EXPECT_EQ(1, _model._components[3]->getConnection()[1]->getID());

	EXPECT_EQ(1, _model._components[0]->getConnection().size());
	EXPECT_EQ(1, _model._components[0]->getConnection()[0]->getID());

	EXPECT_EQ(1, _model._components[1]->getConnection().size());
	EXPECT_EQ(0, _model._components[1]->getConnection()[0]->getID());
}

// 測試加入連結
TEST_F(ERModelTest, addConnection)
{
	_model._componentID = 5;
	_model.addConnection(0, 0, "");
	EXPECT_TRUE(_model._creationFail);
	_model.addConnection(0, 1, "");
	EXPECT_FALSE(_model._creationFail);
	EXPECT_EQ(6, _model.getComponentSize());
	EXPECT_EQ(5, _model._components[5]->getID());
	EXPECT_EQ(connection, _model._components[5]->getType().first);
	EXPECT_EQ("", _model._components[5]->getText());
}

// 測試id是否存在
TEST_F(ERModelTest, isIDExsit)
{
	for (unsigned i = 0; i < _model._components.size(); i++)
	{
		EXPECT_TRUE(_model.isIDExsit(_model._components[i]->getID()));
	}
	EXPECT_FALSE(_model.isIDExsit(-1));
	EXPECT_FALSE(_model.isIDExsit(5));
}

// 測試是否為某 type
TEST_F(ERModelTest, isType)
{
	EXPECT_TRUE(_model.isType(0, entity));
	EXPECT_TRUE(_model.isType(1, attribute));
	EXPECT_TRUE(_model.isType(2, relation));
	EXPECT_TRUE(_model.isType(3, connection));
}

// 測試取得元件 id
TEST_F(ERModelTest, getNodeID)
{
	_model._currentComponent = new EntityNode();
	for (unsigned i = 0; i < 3; i++)
	{
		_model._currentComponent->setID(i);
		EXPECT_EQ(i, _model.getNodeID());
	}
}

// 測試取得元件 type
TEST_F(ERModelTest, getNodeType)
{
	EXPECT_EQ(entity, _model.getNodeType(0).first);
	EXPECT_EQ(attribute, _model.getNodeType(1).first);
	EXPECT_EQ(relation, _model.getNodeType(2).first);
	EXPECT_EQ(connection, _model.getNodeType(3).first);
}

// 測試取得元件 text
TEST_F(ERModelTest, getNodeText)
{
	EXPECT_EQ("PC", _model.getNodeText(0));
	EXPECT_EQ("Name", _model.getNodeText(1));
	EXPECT_EQ("Has", _model.getNodeText(2));
	EXPECT_EQ("", _model.getNodeText(3));
	EXPECT_EQ("1", _model.getNodeText(4));
}

// 測試取得元件資料
TEST_F(ERModelTest, getComponentLine)
{
	EXPECT_EQ("   E  |   0  |  PC\n   A  |   1  |  Name\n   R  |   2  |  Has\n   C  |   3  |  \n   C  |   4  |  1\n", _model.getComponentLine(all));
	EXPECT_EQ("   E  |   0  |  PC\n", _model.getComponentLine(entity));
	EXPECT_EQ("   A  |   1  |  Name\n", _model.getComponentLine(attribute));
	EXPECT_EQ("   R  |   2  |  Has\n", _model.getComponentLine(relation));
	EXPECT_EQ("   C  |   3  |  \n   C  |   4  |  1\n", _model.getComponentLine(connection));
	_model.clearComponent();
	EXPECT_EQ("", _model.getComponentLine(all));
}

// 測試取得連結資料
TEST_F(ERModelTest, getConnectionLine)
{
	loadConnection();
	EXPECT_EQ("        3  |   0  |   1  |\n        4  |   0  |   2  |\n", _model.getConnectionLine());
	_model.clearComponent();
	EXPECT_EQ("", _model.getConnectionLine());
}

// 測試是否有此連結
TEST_F(ERModelTest, hasConnection)
{
	EXPECT_FALSE(_model.hasConnection(0, 1));
	EXPECT_FALSE(_model.hasConnection(0, 2));
	loadConnection();
	EXPECT_TRUE(_model.hasConnection(0, 1));
	EXPECT_TRUE(_model.hasConnection(0, 2));
}

// 測試取得 attirbute 資料
TEST_F(ERModelTest, getAttributeLine)
{
	EXPECT_EQ("", _model.getAttributeLine(0));
	loadConnection();
	EXPECT_EQ("   A  |   1  |  Name\n", _model.getAttributeLine(0));
}

// 測試是否為所屬的 attribute
TEST_F(ERModelTest, isAttribute)
{
	EXPECT_FALSE(_model.isAttribute(0, 1));
	loadConnection();
	EXPECT_TRUE(_model.isAttribute(0, 1));
}

// 測試是否有 entity
TEST_F(ERModelTest, hasEntity)
{
	EXPECT_TRUE(_model.hasEntity());
	_model.clearComponent();
	EXPECT_FALSE(_model.hasEntity());
}

// 測試是否有 attirbute
TEST_F(ERModelTest, hasAttribute)
{
	EXPECT_FALSE(_model.hasAttribute(0));
	loadConnection();
	EXPECT_TRUE(_model.hasAttribute(0));
}

// 測試設定 primary key
TEST_F(ERModelTest, setPrimaryKey)
{
	EXPECT_FALSE(((AttributeNode*)_model._components[1])->isPrimaryKey());
	setPrimaryKey(1);
	EXPECT_TRUE(((AttributeNode*)_model._components[1])->isPrimaryKey());
}

// 測試取得 primary key
TEST_F(ERModelTest, getPrimaryKey)
{
	vector<int> primaryKey = _model.getPrimaryKey(0);
	EXPECT_EQ(0, primaryKey.size());
	loadConnection();
	primaryKey.push_back(1);
	_model.setPrimaryKey(primaryKey);
	primaryKey = _model.getPrimaryKey(0);
	EXPECT_EQ(1, primaryKey.size());
	EXPECT_EQ(1, primaryKey[0]);
}

// 測試取得 primary key id
TEST_F(ERModelTest, getPrimaryKeyString)
{
	EXPECT_EQ("", _model.getPrimaryKeyString(0));
	loadConnection();
	setPrimaryKey(1);
	EXPECT_EQ("1", _model.getPrimaryKeyString(0));
}

// 測試取得 primary key text
TEST_F(ERModelTest, getPrimaryKeyText)
{
	EXPECT_EQ("", _model.getPrimaryKeyText(0));
	loadConnection();
	setPrimaryKey(1);
	EXPECT_EQ("Name", _model.getPrimaryKeyText(0));
}

// 測試取得資料庫欄位
TEST_F(ERModelTest, getTable)
{
	vector<pair<int, int>> oneToOne;
	EXPECT_EQ("         PC |  PK()\n", _model.getTable());
	loadConnection();
	addOneToOne();
	oneToOne = _model.getOneToOne();
	EXPECT_EQ("         PC |  PK(Name)\n     Person |  PK(ID), FK(Name)\n", _model.getTable());
}

// 測試取得一對一配對
TEST_F(ERModelTest, getOneToOne)
{
	vector<pair<int, int>> oneToOne = _model.getOneToOne();
	EXPECT_EQ(0, _model.getOneToOne().size());
	loadConnection();
	EXPECT_EQ(0, _model.getOneToOne().size());
	addOneToOne();
	EXPECT_EQ(1, _model.getOneToOne().size());
	EXPECT_EQ(0, _model.getOneToOne()[0].first);
	EXPECT_EQ(5, _model.getOneToOne()[0].second);
}

// 測試檢查一對一
TEST_F(ERModelTest, checkOneToOne)
{
	pair<int, int> relationPairFirst = make_pair(0, 2);
	pair<int, int> relationPairSecond = make_pair(2, 5);
	loadConnection();
	EXPECT_TRUE(_model.checkOneToOne(relationPairFirst));
	EXPECT_FALSE(_model.checkOneToOne(relationPairSecond));
	addOneToOne();
	EXPECT_TRUE(_model.checkOneToOne(relationPairFirst));
	EXPECT_TRUE(_model.checkOneToOne(relationPairSecond));
}

// 測試讀取元件
TEST_F(ERModelTest, loadComponent)
{
	_model.clearComponent();

	vector<string> content;
	_model.loadComponent(content);
	EXPECT_EQ(0, _model.getComponentSize());

	content.push_back("E, Engineer");
	content.push_back("A, Emp_ID");
	content.push_back("R, Has");
	content.push_back("C");
	_model.loadComponent(content);
	EXPECT_EQ(4, _model.getComponentSize());

	for (unsigned i = 0; i < content.size(); i++)
	{
		EXPECT_EQ(i, _model._components[i]->getID());
		EXPECT_EQ(content[i][0], _model._components[i]->getType().second[0]);
	}
}

// 測試讀取連結
TEST_F(ERModelTest, loadConnection)
{
	vector<string> content;
	_model.loadConnection(content);
	for (unsigned i = 0; i < _model._components.size(); i++)
	{
		EXPECT_EQ(0, _model._components[i]->getConnection().size());
	}

	content.push_back("3 0,1");
	content.push_back("4 0,2");

	_model.loadConnection(content);

	EXPECT_EQ(2, _model._components[0]->getConnection().size());
	EXPECT_EQ(1, _model._components[1]->getConnection().size());
	EXPECT_EQ(1, _model._components[2]->getConnection().size());
	EXPECT_EQ(2, _model._components[3]->getConnection().size());
	EXPECT_EQ(2, _model._components[4]->getConnection().size());
}

// 測試讀取 primary key
TEST_F(ERModelTest, loadPrimaryKey)
{
	_model._components.push_back(new AttributeNode(5, "ID"));

	vector<string> content;
	_model.loadPrimaryKey(content);
	EXPECT_FALSE(((AttributeNode*)_model._components[1])->isPrimaryKey());
	EXPECT_FALSE(((AttributeNode*)_model._components[5])->isPrimaryKey());

	content.push_back("0 1,5");
	_model.loadPrimaryKey(content);
	EXPECT_TRUE(((AttributeNode*)_model._components[1])->isPrimaryKey());
	EXPECT_TRUE(((AttributeNode*)_model._components[5])->isPrimaryKey());
}

TEST_F(ERModelTest, loadPosition)
{
	vector<QPointF> positionList;
	positionList.push_back(QPointF(100, 200));
	positionList.push_back(QPointF(300, 400));
	positionList.push_back(QPointF(500, 600));
	_model.loadPosition(positionList);
	EXPECT_EQ(QPointF(100, 200), _model.getComponent(0)->getPosition());
	EXPECT_EQ(QPointF(300, 400), _model.getComponent(1)->getPosition());
	EXPECT_EQ(QPointF(500, 600), _model.getComponent(2)->getPosition());
}

TEST_F(ERModelTest, canSetPrimaryKey)
{
	EXPECT_FALSE(_model.canSetPrimaryKey(1));
	loadConnection();
	EXPECT_TRUE(_model.canSetPrimaryKey(1));
}

TEST_F(ERModelTest, setNodeSelected)
{
	EXPECT_FALSE(_model.getComponent(0)->isSelected());
	_model.setNodeSelected(0, true);
	EXPECT_TRUE(_model.getComponent(0)->isSelected());
	_model.setNodeSelected(0, false);
	EXPECT_FALSE(_model.getComponent(0)->isSelected());
}

TEST_F(ERModelTest, getSelectedID)
{
	EXPECT_EQ(0, _model.getSelectedID().size());
	_model.getComponent(0)->setSelected(true);
	EXPECT_EQ(1, _model.getSelectedID().size());
	EXPECT_EQ(0, _model.getSelectedID()[0]);
	_model.getComponent(1)->setSelected(true);
	EXPECT_EQ(2, _model.getSelectedID().size());
	EXPECT_EQ(1, _model.getSelectedID()[1]);
}

TEST_F(ERModelTest, isDeleteEnabled)
{
	EXPECT_FALSE(_model.isDeleteEnabled());
	_model.getComponent(0)->setSelected(true);
	EXPECT_TRUE(_model.isDeleteEnabled());
}

TEST_F(ERModelTest, deleteMultiple)
{
	loadConnection();
	vector<int> deleteList;
	deleteList.push_back(0);
	deleteList.push_back(4);
	EXPECT_EQ(5, _model.getComponentSize());
	_model.deleteMultiple(deleteList);
	EXPECT_EQ(2, _model.getComponentSize());
	EXPECT_FALSE(_model.isIDExsit(0));
	EXPECT_FALSE(_model.isIDExsit(3));
	EXPECT_FALSE(_model.isIDExsit(4));
}

TEST_F(ERModelTest, copy)
{
	_model.getComponent(0)->setSelected(true);
	_model.getComponent(3)->setSelected(true);
	_model.copy();
	EXPECT_EQ(2, _model._clipboard.size());
	EXPECT_EQ(0, _model._clipboard[0]->getID());
	EXPECT_EQ(3, _model._clipboard[1]->getID());
}

TEST_F(ERModelTest, getGUITable)
{
	EXPECT_EQ("", _model.getGUITable());
	loadConnection();
	addOneToOne();
}

TEST_F(ERModelTest, getGUIPrimaryKey)
{
	loadConnection();
	addOneToOne();
	EXPECT_EQ("<td><img src=\"Resources/primary_key.png\" width=\"20\" height=\"20\">Name</td>", _model.getGUIPrimaryKey(0));
}