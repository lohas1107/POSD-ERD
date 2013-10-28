#include "gtest/gtest.h"
#include "ConnectComponentCommand.h"

class ConnectComponentCommandTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		_model = new ERModel();
		_model->addComponent(make_pair(entity, ""), "PC");
		_model->addComponent(make_pair(attribute, ""), "ID");
		_model->addComponent(make_pair(relation, ""), "Has");

		_noCardinality = ConnectComponentCommand(_model, 0, 1, "");
		_hasCardinality = ConnectComponentCommand(_model, 0, 2, "1");
	}

	virtual void TearDown()
	{
		delete _model;
	}
	ERModel* _model;
	ConnectComponentCommand _noCardinality;
	ConnectComponentCommand _hasCardinality;
};

// 測試執行連結元件
TEST_F(ConnectComponentCommandTest, execute)
{	
	_noCardinality.execute();
	EXPECT_EQ(4, _model->getComponentSize());
	EXPECT_EQ(3, _model->getNodeID());
	EXPECT_EQ(connection, _model->getNodeType(3).first);
	EXPECT_EQ("", _model->getNodeText(3));
	
	_hasCardinality.execute();
	EXPECT_EQ(5, _model->getComponentSize());
	EXPECT_EQ(4, _model->getNodeID());
	EXPECT_EQ(connection, _model->getNodeType(4).first);
	EXPECT_EQ("1", _model->getNodeText(4));
}

// 測試刪除連結元件
TEST_F(ConnectComponentCommandTest, unexecute)
{
	_noCardinality.execute();
	_hasCardinality.execute();
	EXPECT_EQ(5, _model->getComponentSize());
	_hasCardinality.unexecute();
	EXPECT_EQ(4, _model->getComponentSize());
	_noCardinality.unexecute();
	EXPECT_EQ(3, _model->getComponentSize());
}