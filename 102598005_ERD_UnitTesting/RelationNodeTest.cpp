#include "gtest/gtest.h"
#include "AttributeNode.h"
#include "EntityNode.h"
#include "AttributeNode.h"
#include "RelationNode.h"
#include "Connector.h"
#include <vector>

using namespace std;

class RelationNodeTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		_relationNode.setID(0);
		_relationNode.setText("Has");

		_components.push_back(new EntityNode(1, "PC"));
		_components.push_back(new AttributeNode(2, "Name"));
		_components.push_back(new RelationNode(3, "Manage"));
		_components.push_back(new Connector(4, ""));
		_components.push_back(new EntityNode(5, "Person"));
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

	void canNotConnect()
	{
		EXPECT_FALSE(_relationNode.canConnectTo(_components[1]));
		EXPECT_FALSE(_relationNode.canConnectTo(_components[2]));
		EXPECT_FALSE(_relationNode.canConnectTo(_components[3]));
	}
	RelationNode _relationNode;
	vector<ERComponent*> _components;
};

// 測試是否為某 relation
TEST_F(RelationNodeTest, isType)
{
	EXPECT_FALSE(_relationNode.isType(none));
	EXPECT_FALSE(_relationNode.isType(entity));
	EXPECT_FALSE(_relationNode.isType(attribute));
	EXPECT_TRUE(_relationNode.isType(relation));
	EXPECT_FALSE(_relationNode.isType(connection));
	EXPECT_FALSE(_relationNode.isType(all));
}

// 測試取得relation資訊
TEST_F(RelationNodeTest, getData)
{
	EXPECT_EQ("", _relationNode.getData(none));
	EXPECT_EQ("", _relationNode.getData(entity));
	EXPECT_EQ("", _relationNode.getData(attribute));
	EXPECT_EQ("   R  |   0  |  Has\n", _relationNode.getData(relation));
	EXPECT_EQ("", _relationNode.getData(connection));
	EXPECT_EQ("   R  |   0  |  Has\n", _relationNode.getData(all));
}

// 測試是否可以連結
TEST_F(RelationNodeTest, canConnectTo)
{
	EXPECT_TRUE(_relationNode.canConnectTo(_components[0]));
	canNotConnect();
	
	_relationNode.connectTo(_components[0]);
	EXPECT_TRUE(_relationNode.canConnectTo(_components[0]));
	canNotConnect();
	
	_relationNode.connectTo(_components[3]);
	EXPECT_FALSE(_relationNode.canConnectTo(_components[0]));
	canNotConnect();
}

// 測試取得連結配對
TEST_F(RelationNodeTest, getRelationPair)
{
	EXPECT_EQ(0, _relationNode.getRelationPair().size());
	_relationNode.connectTo(_components[0]);
	EXPECT_EQ(0, _relationNode.getRelationPair().size());
	_relationNode.connectTo(_components[3]);
	EXPECT_EQ(2, _relationNode.getRelationPair().size());
	EXPECT_EQ(1, _relationNode.getRelationPair()[0].first);
	EXPECT_EQ(0, _relationNode.getRelationPair()[0].second);
	EXPECT_EQ(4, _relationNode.getRelationPair()[1].first);
	EXPECT_EQ(0, _relationNode.getRelationPair()[0].second);
}