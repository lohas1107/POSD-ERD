#include "gtest/gtest.h"
#include "ERComponent.h"
#include "Node.h"
#include "EntityNode.h"
#include "AttributeNode.h"
#include "RelationNode.h"
#include "Connector.h"
#include <vector>

using namespace std;

class EntityNodeTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		_components.push_back(new EntityNode(0, "Engineer"));
		_components.push_back(new EntityNode(1, "PC"));
		_components.push_back(new AttributeNode(2, "ID"));
		_components.push_back(new RelationNode(3, "Has"));
		_components.push_back(new Connector(4, ""));
		_components.push_back(new AttributeNode(5, "Name"));
	}

	virtual void TearDown()
	{
		while (!_components.empty())
		{
			ERComponent* component = _components.back();
			_components.pop_back();
			delete component;
		}
	}

	void setConnection()
	{
		for (unsigned i = 1; i < _components.size(); i++)
		{
			_components[0]->connectTo(_components[i]);
		}

		_entityNode.setConnection(_components[0]->getConnection());
	}

	void setPrimaryAttribute(string &primaryKey, string &attributeString)
	{
		primaryKey = "";
		attributeString = "";
		_entityNode.setAttributeString(primaryKey, attributeString);
	}
	vector<ERComponent*> _components;
	EntityNode _entityNode;
};

// 測試是否為 entity
TEST_F(EntityNodeTest, isType)
{
	EXPECT_FALSE(_components[0]->isType(none));
	EXPECT_TRUE(_components[0]->isType(entity));
	EXPECT_FALSE(_components[0]->isType(attribute));
	EXPECT_FALSE(_components[0]->isType(relation));
	EXPECT_FALSE(_components[0]->isType(connection));
	EXPECT_FALSE(_components[0]->isType(all));
}

// 測試連結其他元件
TEST_F(EntityNodeTest, connectTo)
{
	EXPECT_EQ(0, _components[0]->getConnection().size());

	for (unsigned i = 1; i < _components.size(); i++)
	{
		_components[0]->connectTo(_components[i]);
		EXPECT_EQ(i, _components[0]->getConnection().size());
		EXPECT_EQ(_components[i]->getID(), _components[0]->getConnection().back()->getID());
		EXPECT_EQ(_components[i]->getType().first, _components[0]->getConnection().back()->getType().first);
		EXPECT_EQ(_components[i]->getText(), _components[0]->getConnection().back()->getText());
	}
}

// 測試取消聯結元件
TEST_F(EntityNodeTest, disconnectTo)
{
	_components[0]->connectTo(_components[1]);
	_components[0]->connectTo(_components[2]);
	EXPECT_EQ(2, _components[0]->getConnection().size());
	_components[0]->disconnectTo(3);
	EXPECT_EQ(2, _components[0]->getConnection().size());
	_components[0]->disconnectTo(2);
	EXPECT_EQ(1, _components[0]->getConnection().size());
	EXPECT_EQ(1, _components[0]->getConnection().back()->getID());
	EXPECT_EQ(entity, _components[0]->getConnection().back()->getType().first);
	EXPECT_EQ("PC", _components[0]->getConnection().back()->getText());
	_components[0]->disconnectTo(1);
	EXPECT_EQ(0, _components[0]->getConnection().size());
}

// 測試取得資料
TEST_F(EntityNodeTest, getData)
{
	EXPECT_EQ("", _components[0]->getData(none));
	EXPECT_EQ("   E  |   0  |  Engineer\n", _components[0]->getData(entity));
	EXPECT_EQ("", _components[0]->getData(attribute));
	EXPECT_EQ("", _components[0]->getData(relation));
	EXPECT_EQ("", _components[0]->getData(connection));
	EXPECT_EQ("   E  |   0  |  Engineer\n", _components[0]->getData(all));
}

// 測試製作副本
TEST_F(EntityNodeTest, clone)
{
	ERComponent* cloneEntity = _components[0]->clone();
	EXPECT_EQ(0, cloneEntity->getID());
	EXPECT_EQ(entity, cloneEntity->getType().first);
	EXPECT_EQ("Engineer", cloneEntity->getText());
	delete cloneEntity;
}

// 測試是否有此連結
TEST_F(EntityNodeTest, hasConnection)
{
	EXPECT_FALSE(((Node*)_components[0])->hasConnection(0));
	EXPECT_FALSE(((Node*)_components[0])->hasConnection(1));
	EXPECT_FALSE(((Node*)_components[0])->hasConnection(2));
	_components[0]->connectTo(_components[1]);
	_components[0]->connectTo(_components[2]);
	EXPECT_FALSE(((Node*)_components[0])->hasConnection(0));
	EXPECT_TRUE(((Node*)_components[0])->hasConnection(1));
	EXPECT_TRUE(((Node*)_components[0])->hasConnection(2));
	_components[0]->disconnectTo(1);
	EXPECT_FALSE(((Node*)_components[0])->hasConnection(1));
	_components[0]->disconnectTo(2);
	EXPECT_FALSE(((Node*)_components[0])->hasConnection(2));
}

// 測試是否可以連結
TEST_F(EntityNodeTest, canConnectTo)
{
	EXPECT_FALSE(_entityNode.canConnectTo(_components[1]));
	EXPECT_TRUE(_entityNode.canConnectTo(_components[2]));
	EXPECT_TRUE(_entityNode.canConnectTo(_components[3]));
	EXPECT_FALSE(_entityNode.canConnectTo(_components[4]));
}

// 測試取得 attribute
TEST_F(EntityNodeTest, getAttributes)
{
	EXPECT_EQ(0, _entityNode.getAttributes().size());

	setConnection();
	EXPECT_EQ(2, _entityNode.getAttributes().size());
	EXPECT_EQ(2, _entityNode.getAttributes()[0]->getID());
	EXPECT_EQ(attribute, _entityNode.getAttributes()[0]->getType().first);
	EXPECT_EQ("ID", _entityNode.getAttributes()[0]->getText());
	EXPECT_EQ(5, _entityNode.getAttributes()[1]->getID());
	EXPECT_EQ(attribute, _entityNode.getAttributes()[1]->getType().first);
	EXPECT_EQ("Name", _entityNode.getAttributes()[1]->getText());
}

// 測試取得 attribute 資料
TEST_F(EntityNodeTest, getAttributeLine)
{
	EXPECT_EQ("", _entityNode.getAttributeLine());
	setConnection();
	EXPECT_EQ("   A  |   2  |  ID\n   A  |   5  |  Name\n", _entityNode.getAttributeLine());
}

// 測試是否為所屬的 attribute
TEST_F(EntityNodeTest, isAttribute)
{
	for (unsigned i = 0; i < _components.size(); i++)
	{
		EXPECT_FALSE(_entityNode.isAttribute(i));
	}

	setConnection();
	EXPECT_FALSE(_entityNode.isAttribute(0));
	EXPECT_FALSE(_entityNode.isAttribute(1));
	EXPECT_TRUE(_entityNode.isAttribute(2));
	EXPECT_FALSE(_entityNode.isAttribute(3));
	EXPECT_FALSE(_entityNode.isAttribute(4));
	EXPECT_TRUE(_entityNode.isAttribute(5));
}

// 測試是否有 attribute
TEST_F(EntityNodeTest, hasAttribute)
{
	EXPECT_FALSE(_entityNode.hasAttribute());
	setConnection();
	EXPECT_TRUE(_entityNode.hasAttribute());
}

// 測試取得 primary key
TEST_F(EntityNodeTest, getPrimaryKey)
{
	EXPECT_EQ(0, _entityNode.getPrimaryKey().size());
	setConnection();
	((AttributeNode*)_components[2])->setPrimaryKey(true);
	EXPECT_EQ(1, _entityNode.getPrimaryKey().size());
	EXPECT_EQ(2, _entityNode.getPrimaryKey()[0]);
	((AttributeNode*)_components[5])->setPrimaryKey(true);
	EXPECT_EQ(2, _entityNode.getPrimaryKey().size());
	EXPECT_EQ(2, _entityNode.getPrimaryKey()[0]);
	EXPECT_EQ(5, _entityNode.getPrimaryKey()[1]);
}

// 測試設定 attribute
TEST_F(EntityNodeTest, setAttributeString)
{
	string primaryKey;
	string attributeString;
	setPrimaryAttribute(primaryKey, attributeString);
	EXPECT_EQ("", primaryKey);
	EXPECT_EQ("", attributeString);

	setConnection();
	setPrimaryAttribute(primaryKey, attributeString);
	EXPECT_EQ("", primaryKey);
	EXPECT_EQ(", ID, Name", attributeString);
	((AttributeNode*)_components[2])->setPrimaryKey(true);
	setPrimaryAttribute(primaryKey, attributeString);
	EXPECT_EQ(", ID", primaryKey);
	EXPECT_EQ(", Name", attributeString);
	((AttributeNode*)_components[5])->setPrimaryKey(true);
	setPrimaryAttribute(primaryKey, attributeString);
	EXPECT_EQ(", ID, Name", primaryKey);
	EXPECT_EQ("", attributeString);
}

// 測試取得資料庫欄位
TEST_F(EntityNodeTest, getTable)
{
	_entityNode.setText("Entity");
	EXPECT_EQ("     Entity |  PK()\n", _entityNode.getTable());
	setConnection();
	EXPECT_EQ("     Entity |  PK(), ID, Name\n", _entityNode.getTable());
	((AttributeNode*)_components[2])->setPrimaryKey(true);
	EXPECT_EQ("     Entity |  PK(ID), Name\n", _entityNode.getTable());
	_entityNode.setForeignKey("PC_ID");
	EXPECT_EQ("     Entity |  PK(ID), Name, FK(PC_ID)\n", _entityNode.getTable());
	((AttributeNode*)_components[5])->setPrimaryKey(true);
	_entityNode.setForeignKey("PC_ID, date");
	EXPECT_EQ("     Entity |  PK(ID, Name), FK(PC_ID, date)\n", _entityNode.getTable());
}