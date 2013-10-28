#include "gtest/gtest.h"
#include "AttributeNode.h"
#include "EntityNode.h"
#include "AttributeNode.h"
#include "RelationNode.h"
#include "Connector.h"
#include <vector>

using namespace std;

class ConnectorTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		_connector.setID(0);

		_components.push_back(new EntityNode(1, "PC"));
		_components.push_back(new AttributeNode(2, "Name"));
		_components.push_back(new RelationNode(3, "Has"));
		_components.push_back(new Connector(4, ""));
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
	Connector _connector;
	vector<ERComponent*> _components;
};

// 測試是否為 connector
TEST_F(ConnectorTest, isType)
{
	EXPECT_FALSE(_connector.isType(none));
	EXPECT_FALSE(_connector.isType(entity));
	EXPECT_FALSE(_connector.isType(attribute));
	EXPECT_FALSE(_connector.isType(relation));
	EXPECT_TRUE(_connector.isType(connection));
	EXPECT_FALSE(_connector.isType(all));
}

// 測試取得資料
TEST_F(ConnectorTest, getData)
{
	EXPECT_EQ("", _connector.getData(none));
	EXPECT_EQ("", _connector.getData(entity));
	EXPECT_EQ("", _connector.getData(attribute));
	EXPECT_EQ("", _connector.getData(relation));
	EXPECT_EQ("   C  |   0  |  \n", _connector.getData(connection));
	EXPECT_EQ("   C  |   0  |  \n", _connector.getData(all));
}

// 測試是否可以連結
TEST_F(ConnectorTest, canConnectTo)
{
	for (unsigned i = 0; i < 2; i++)
	{
		EXPECT_TRUE(_connector.canConnectTo(_components[i]));
		_connector.connectTo(_components[i]);
	}

	for (unsigned i = 0; i < _components.size(); i++)
	{
		EXPECT_FALSE(_connector.canConnectTo(_components[i]));
	}
}

// 測試是否在連結中
TEST_F(ConnectorTest, isInConnetion)
{
	for (unsigned i = 0; i < _components.size(); i++)
	{
		EXPECT_FALSE(_connector.isInConnetion(i));
	}
	_connector.connectTo(_components[0]);
	for (unsigned i = 0; i < _components.size(); i++)
	{
		EXPECT_FALSE(_connector.isInConnetion(i));
	}
	_connector.connectTo(_components[1]);
	EXPECT_TRUE(_connector.isInConnetion(1));
	EXPECT_TRUE(_connector.isInConnetion(2));
	EXPECT_FALSE(_connector.isInConnetion(3));
	EXPECT_FALSE(_connector.isInConnetion(4));
}

// 測試取得連結資訊
TEST_F(ConnectorTest, getConnectionLine)
{
	EXPECT_EQ("", _connector.getConnectionLine());
	_connector.connectTo(_components[0]);
	EXPECT_EQ("", _connector.getConnectionLine());
	_connector.connectTo(_components[1]);
	EXPECT_EQ("        0  |   1  |   2  |\n", _connector.getConnectionLine());
}

// 測試取得連結
TEST_F(ConnectorTest, getConnection)
{
	EXPECT_EQ("", _connector.getConnection());
	_connector.connectTo(_components[0]);
	EXPECT_EQ("", _connector.getConnection());
	_connector.connectTo(_components[1]);
	EXPECT_EQ("1,2", _connector.getConnection());
}

// 測試取得連結配對
TEST_F(ConnectorTest, getConnectionPair)
{
	EXPECT_EQ(INT_MIN, _connector.getConnectionPair().first);
	EXPECT_EQ(INT_MIN, _connector.getConnectionPair().second);
	_connector.connectTo(_components[0]);
	EXPECT_EQ(INT_MIN, _connector.getConnectionPair().first);
	EXPECT_EQ(INT_MIN, _connector.getConnectionPair().second);
	_connector.connectTo(_components[1]);
	EXPECT_EQ(1, _connector.getConnectionPair().first);
	EXPECT_EQ(2, _connector.getConnectionPair().second);
}

// 測試檢查一對一
TEST_F(ConnectorTest, checkOneToOne)
{
	EXPECT_FALSE(_connector.checkOneToOne(make_pair(1, 2)));
	_connector.setText("1");
	_connector.connectTo(_components[0]);
	_connector.connectTo(_components[1]);
	EXPECT_TRUE(_connector.checkOneToOne(make_pair(1, 2)));
	EXPECT_TRUE(_connector.checkOneToOne(make_pair(2, 1)));
	EXPECT_FALSE(_connector.checkOneToOne(make_pair(3, 4)));
	_connector.setText("N");
	EXPECT_FALSE(_connector.checkOneToOne(make_pair(1, 2)));
}

// 測試製作副本
TEST_F(ConnectorTest, clone)
{
	_connector.connectTo(_components[0]);
	_connector.connectTo(_components[1]);

	ERComponent* cloneConnector = _connector.clone();
	EXPECT_EQ(0, cloneConnector->getID());
	EXPECT_EQ(connection, cloneConnector->getType().first);
	EXPECT_EQ("", cloneConnector->getText());
	EXPECT_EQ(2, cloneConnector->getConnection().size());
	EXPECT_EQ(1, cloneConnector->getConnection()[0]->getID());
	EXPECT_EQ(2, cloneConnector->getConnection()[1]->getID());
	delete cloneConnector;
}