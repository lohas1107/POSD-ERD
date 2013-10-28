#include "gtest/gtest.h"
#include "AttributeNode.h"
#include "EntityNode.h"
#include "AttributeNode.h"
#include "RelationNode.h"
#include "Connector.h"
#include <vector>

using namespace std;

class AttributeNodeTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		_attributeNode.setID(0);
		_attributeNode.setText("ID");

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
	AttributeNode _attributeNode;
	vector<ERComponent*> _components;
};

// 測試是否為 attribute
TEST_F(AttributeNodeTest, isType)
{
	EXPECT_FALSE(_attributeNode.isType(none));
	EXPECT_FALSE(_attributeNode.isType(entity));
	EXPECT_TRUE(_attributeNode.isType(attribute));
	EXPECT_FALSE(_attributeNode.isType(relation));
	EXPECT_FALSE(_attributeNode.isType(connection));
	EXPECT_FALSE(_attributeNode.isType(all));
}

// 測試取得資料
TEST_F(AttributeNodeTest, getData)
{
	EXPECT_EQ("", _attributeNode.getData(none));
	EXPECT_EQ("", _attributeNode.getData(entity));
	EXPECT_EQ("   A  |   0  |  ID\n", _attributeNode.getData(attribute));
	EXPECT_EQ("", _attributeNode.getData(relation));
	EXPECT_EQ("", _attributeNode.getData(connection));
	EXPECT_EQ("   A  |   0  |  ID\n", _attributeNode.getData(all));
}

// 測試是否可以連接
TEST_F(AttributeNodeTest, canConnectTo)
{
	EXPECT_TRUE(_attributeNode.canConnectTo(_components[0]));
	EXPECT_FALSE(_attributeNode.canConnectTo(_components[1]));
	EXPECT_FALSE(_attributeNode.canConnectTo(_components[2]));
	EXPECT_FALSE(_attributeNode.canConnectTo(_components[3]));

	for (unsigned i = 0; i < _components.size(); i++)
	{
		_attributeNode.connectTo(_components[i]);
		EXPECT_FALSE(_attributeNode.canConnectTo(_components[i]));
	}
}

// 測試製作副本
TEST_F(AttributeNodeTest, clone)
{
	ERComponent* cloneAttribute = _attributeNode.clone();
	EXPECT_EQ(0, cloneAttribute->getID());
	EXPECT_EQ(attribute, cloneAttribute->getType().first);
	EXPECT_EQ("ID", cloneAttribute->getText());
	EXPECT_FALSE(((AttributeNode*)cloneAttribute)->isPrimaryKey());	
	
	_attributeNode.setPrimaryKey(true);
	cloneAttribute = _attributeNode.clone();
	EXPECT_EQ(0, cloneAttribute->getID());
	EXPECT_EQ(attribute, cloneAttribute->getType().first);
	EXPECT_EQ("ID", cloneAttribute->getText());
	EXPECT_TRUE(((AttributeNode*)cloneAttribute)->isPrimaryKey());
	delete cloneAttribute;
}